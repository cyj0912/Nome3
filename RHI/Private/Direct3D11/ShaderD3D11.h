#pragma once
#include "ShaderModule.h"
#include "D3D11Platform.h"
#include <map>
#include <unordered_map>
#include <variant>

namespace RHI
{

//Mapping from user-facing parameters to pipeline slots for a single shader stage
class CVSRedir;
class CPSRedir;
class CPipelineParamMappingD3D11
{
public:
    //Id to slot
    std::map<uint32_t, uint32_t> Mappings;

    template <typename TRedir>
    void BindArguments(const CPipelineArguments& args, ID3D11DeviceContext* ctx) const;
};

class CShaderD3D11
{
public:
    CShaderD3D11(CShaderModule& fromSrc);

    const CVertexShaderInputSignature& GetVSInputSignature() const;
    const CPipelineParamMappingD3D11& GetParamMappings() const { return Mappings; }

    ComPtr<ID3DBlob> GetCodeBlob() const;

    ID3D11VertexShader* GetVS() const;
    ID3D11PixelShader* GetPS() const;

private:
    void GenMappings();

    //Code
    ComPtr<ID3DBlob> CodeBlob;

    //Reflection data
    CVertexShaderInputSignature InputSig;
    CPipelineParamMappingD3D11 Mappings;

    mutable ComPtr<ID3D11VertexShader> VS;
    mutable ComPtr<ID3D11PixelShader> PS;
};

class CShaderCacheD3D11
{
public:
    CShaderCacheD3D11() = default;
    CShaderCacheD3D11(const CShaderCacheD3D11&) = delete;
    CShaderCacheD3D11(CShaderCacheD3D11&&) = delete;
    CShaderCacheD3D11& operator=(const CShaderCacheD3D11&) = delete;
    CShaderCacheD3D11& operator=(CShaderCacheD3D11&&) = delete;

    ~CShaderCacheD3D11()
    {
        for (auto pair : ShaderCache)
            delete pair.second;
    }

    CShaderD3D11* GetShader(const std::string& key) const
    {
        auto iter = ShaderCache.find(key);
        if (iter == ShaderCache.end())
            return nullptr;
        return iter->second;
    }

    void PutShader(const std::string& key, CShaderD3D11* shader)
    {
        ShaderCache[key] = shader;
    }

    //CShaderD3D11* LoadFromDisk(const std::string& key);
    //void SaveAllToDisk();

private:
    //Owns all those shaders also
    std::unordered_map<std::string, CShaderD3D11*> ShaderCache;
};

} /* namespace RHI */