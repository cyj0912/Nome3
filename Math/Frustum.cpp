//
// Copyright (c) 2008-2018 the Urho3D project.
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.
//



#include "Frustum.h"



namespace tc
{

inline Vector3 ClipEdgeZ(const Vector3& v0, const Vector3& v1, float clipZ)
{
    return Vector3(
        v1.x + (v0.x - v1.x) * ((clipZ - v1.z) / (v0.z - v1.z)),
        v1.y + (v0.y - v1.y) * ((clipZ - v1.z) / (v0.z - v1.z)),
        clipZ
    );
}

void ProjectAndMergeEdge(Vector3 v0, Vector3 v1, Rect& rect, const Matrix4& projection)
{
    // Check if both vertices behind near plane
    if (v0.z < M_MIN_NEARCLIP && v1.z < M_MIN_NEARCLIP)
        return;

    // Check if need to clip one of the vertices
    if (v1.z < M_MIN_NEARCLIP)
        v1 = ClipEdgeZ(v1, v0, M_MIN_NEARCLIP);
    else if (v0.z < M_MIN_NEARCLIP)
        v0 = ClipEdgeZ(v0, v1, M_MIN_NEARCLIP);

    // Project, perspective divide and merge
    Vector3 tV0(projection * v0);
    Vector3 tV1(projection * v1);
    rect.Merge(Vector2(tV0.x, tV0.y));
    rect.Merge(Vector2(tV1.x, tV1.y));
}

Frustum::Frustum(const Frustum& frustum) noexcept
{
    *this = frustum;
}

Frustum& Frustum::operator =(const Frustum& rhs) noexcept
{
    for (unsigned i = 0; i < NUM_FRUSTUM_PLANES; ++i)
        planes_[i] = rhs.planes_[i];
    for (unsigned i = 0; i < NUM_FRUSTUM_VERTICES; ++i)
        vertices_[i] = rhs.vertices_[i];

    return *this;
}

void Frustum::Define(float fov, float aspectRatio, float zoom, float nearZ, float farZ, const Matrix3x4& transform)
{
    nearZ = Max(nearZ, 0.0f);
    farZ = Max(farZ, nearZ);
    float halfViewSize = tanf(fov * M_DEGTORAD_2) / zoom;
    Vector3 near, far;

    near.z = nearZ;
    near.y = near.z * halfViewSize;
    near.x = near.y * aspectRatio;
    far.z = farZ;
    far.y = far.z * halfViewSize;
    far.x = far.y * aspectRatio;

    Define(near, far, transform);
}

void Frustum::Define(const Vector3& near, const Vector3& far, const Matrix3x4& transform)
{
    vertices_[0] = transform * near;
    vertices_[1] = transform * Vector3(near.x, -near.y, near.z);
    vertices_[2] = transform * Vector3(-near.x, -near.y, near.z);
    vertices_[3] = transform * Vector3(-near.x, near.y, near.z);
    vertices_[4] = transform * far;
    vertices_[5] = transform * Vector3(far.x, -far.y, far.z);
    vertices_[6] = transform * Vector3(-far.x, -far.y, far.z);
    vertices_[7] = transform * Vector3(-far.x, far.y, far.z);

    UpdatePlanes();
}

void Frustum::Define(const BoundingBox& box, const Matrix3x4& transform)
{
    vertices_[0] = transform * Vector3(box.Max.x, box.Max.y, box.Min.z);
    vertices_[1] = transform * Vector3(box.Max.x, box.Min.y, box.Min.z);
    vertices_[2] = transform * Vector3(box.Min.x, box.Min.y, box.Min.z);
    vertices_[3] = transform * Vector3(box.Min.x, box.Max.y, box.Min.z);
    vertices_[4] = transform * Vector3(box.Max.x, box.Max.y, box.Max.z);
    vertices_[5] = transform * Vector3(box.Max.x, box.Min.y, box.Max.z);
    vertices_[6] = transform * Vector3(box.Min.x, box.Min.y, box.Max.z);
    vertices_[7] = transform * Vector3(box.Min.x, box.Max.y, box.Max.z);

    UpdatePlanes();
}

void Frustum::Define(const Matrix4& projection)
{
    Matrix4 projInverse = projection.Inverse();

    vertices_[0] = projInverse * Vector3(1.0f, 1.0f, 0.0f);
    vertices_[1] = projInverse * Vector3(1.0f, -1.0f, 0.0f);
    vertices_[2] = projInverse * Vector3(-1.0f, -1.0f, 0.0f);
    vertices_[3] = projInverse * Vector3(-1.0f, 1.0f, 0.0f);
    vertices_[4] = projInverse * Vector3(1.0f, 1.0f, 1.0f);
    vertices_[5] = projInverse * Vector3(1.0f, -1.0f, 1.0f);
    vertices_[6] = projInverse * Vector3(-1.0f, -1.0f, 1.0f);
    vertices_[7] = projInverse * Vector3(-1.0f, 1.0f, 1.0f);

    UpdatePlanes();
}

void Frustum::DefineOrtho(float orthoSize, float aspectRatio, float zoom, float nearZ, float farZ, const Matrix3x4& transform)
{
    nearZ = Max(nearZ, 0.0f);
    farZ = Max(farZ, nearZ);
    float halfViewSize = orthoSize * 0.5f / zoom;
    Vector3 near, far;

    near.z = nearZ;
    far.z = farZ;
    far.y = near.y = halfViewSize;
    far.x = near.x = near.y * aspectRatio;

    Define(near, far, transform);
}

void Frustum::DefineSplit(const Matrix4& projection, float near, float far)
{
    Matrix4 projInverse = projection.Inverse();

    // Figure out depth values for near & far
    Vector4 nearTemp = projection * Vector4(0.0f, 0.0f, near, 1.0f);
    Vector4 farTemp = projection * Vector4(0.0f, 0.0f, far, 1.0f);
    float nearZ = nearTemp.z / nearTemp.w;
    float farZ = farTemp.z / farTemp.w;

    vertices_[0] = projInverse * Vector3(1.0f, 1.0f, nearZ);
    vertices_[1] = projInverse * Vector3(1.0f, -1.0f, nearZ);
    vertices_[2] = projInverse * Vector3(-1.0f, -1.0f, nearZ);
    vertices_[3] = projInverse * Vector3(-1.0f, 1.0f, nearZ);
    vertices_[4] = projInverse * Vector3(1.0f, 1.0f, farZ);
    vertices_[5] = projInverse * Vector3(1.0f, -1.0f, farZ);
    vertices_[6] = projInverse * Vector3(-1.0f, -1.0f, farZ);
    vertices_[7] = projInverse * Vector3(-1.0f, 1.0f, farZ);

    UpdatePlanes();
}

void Frustum::Transform(const Matrix3& transform)
{
    for (auto& vertice : vertices_)
        vertice = transform * vertice;

    UpdatePlanes();
}

void Frustum::Transform(const Matrix3x4& transform)
{
    for (auto& vertice : vertices_)
        vertice = transform * vertice;

    UpdatePlanes();
}

Frustum Frustum::Transformed(const Matrix3& transform) const
{
    Frustum transformed;
    for (unsigned i = 0; i < NUM_FRUSTUM_VERTICES; ++i)
        transformed.vertices_[i] = transform * vertices_[i];

    transformed.UpdatePlanes();
    return transformed;
}

Frustum Frustum::Transformed(const Matrix3x4& transform) const
{
    Frustum transformed;
    for (unsigned i = 0; i < NUM_FRUSTUM_VERTICES; ++i)
        transformed.vertices_[i] = transform * vertices_[i];

    transformed.UpdatePlanes();
    return transformed;
}

Rect Frustum::Projected(const Matrix4& projection) const
{
    Rect rect;

    ProjectAndMergeEdge(vertices_[0], vertices_[4], rect, projection);
    ProjectAndMergeEdge(vertices_[1], vertices_[5], rect, projection);
    ProjectAndMergeEdge(vertices_[2], vertices_[6], rect, projection);
    ProjectAndMergeEdge(vertices_[3], vertices_[7], rect, projection);
    ProjectAndMergeEdge(vertices_[4], vertices_[5], rect, projection);
    ProjectAndMergeEdge(vertices_[5], vertices_[6], rect, projection);
    ProjectAndMergeEdge(vertices_[6], vertices_[7], rect, projection);
    ProjectAndMergeEdge(vertices_[7], vertices_[4], rect, projection);

    return rect;
}

void Frustum::UpdatePlanes()
{
    planes_[PLANE_NEAR].Define(vertices_[2], vertices_[1], vertices_[0]);
    planes_[PLANE_LEFT].Define(vertices_[3], vertices_[7], vertices_[6]);
    planes_[PLANE_RIGHT].Define(vertices_[1], vertices_[5], vertices_[4]);
    planes_[PLANE_UP].Define(vertices_[0], vertices_[4], vertices_[7]);
    planes_[PLANE_DOWN].Define(vertices_[6], vertices_[5], vertices_[1]);
    planes_[PLANE_FAR].Define(vertices_[5], vertices_[6], vertices_[7]);

    // Check if we ended up with inverted planes (reflected transform) and flip in that case
    if (planes_[PLANE_NEAR].Distance(vertices_[5]) < 0.0f)
    {
        for (auto& plane : planes_)
        {
            plane.normal_ = -plane.normal_;
            plane.d_ = -plane.d_;
        }
    }

}

}
