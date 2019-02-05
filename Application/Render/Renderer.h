#pragma once
#include <Matrix4.h>
#include <Color.h>
#include <utility>
#include <set>
#include <memory>

namespace Nome
{

class CGraphicsDevice;
class CGeometry;
class CMaterial;
class CRenderer;
extern CRenderer* GRenderer;

class CBasicShader;
class CWireShader;
class CPointShader;
class CViewport;

struct CRendererPrivData;

class CRenderer
{
public:
	CRenderer();
	~CRenderer();

	CGraphicsDevice* GetGD() const { return GD; }

	void BeginView(const tc::Matrix4& view, const tc::Matrix4& proj, CViewport* viewport, const tc::Color& clearColor,
        float lineWidth, float pointRadius);
	void EndView();

    void Draw(const tc::Matrix4& modelMat, CGeometry* geometry, CMaterial* material);

	void Render();

private:
	CGraphicsDevice* GD;

    struct CViewData
    {
        tc::Matrix4 ViewMat;
        tc::Matrix4 ProjMat;
		CViewport* Viewport;
		tc::Color ClearColor;
        float LineWidth, PointRadius;

        struct CObjectData
        {
            CGeometry* Geom;
            CMaterial* Material;
            tc::Matrix4 ModelMat;

            bool operator<(const CObjectData& rhs) const { return Geom < rhs.Geom; }
        };

        std::set<CObjectData> DrawListBasic;
    };

    std::vector<CViewData> Views;

    std::unique_ptr<CBasicShader> BasicShader;
	std::unique_ptr<CWireShader> WireShader;
    std::unique_ptr<CPointShader> PointShader;

    CRendererPrivData* Pd;
};

}