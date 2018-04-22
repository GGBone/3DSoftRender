#pragma once
#include "Graphics\Shader.h"
#include "Graphics\Buffer.h"
#include "Graphics\Dx11ShaderParameter.h"
#include "Graphics\Dx11Renderer.h"
#include "Graphics\BufferBinding.h"
namespace Hikari
{
	class DirectRenderer;
	class ShaderDx : public Shader 
	{
	public:
		//Need hide only can be created by Renderer
		ShaderDx(std::shared_ptr<DirectRenderer>& renderer);
		virtual ShaderType GetType()const override;

		virtual void LoadShaderFromString(ShaderType type, const std::string& source, const std::string& sourceFileName,
			const ShaderMacros& shaderMacros, const std::string& entryPoint, const std::string& profile) override;

		virtual bool LoadShaderFromFile(ShaderType type, const std::string& fileName, const ShaderMacros& shaderMacros,
			const std::string& entryPoint, const std::string& profile)  override;

		virtual ShaderParameter& GetShaderParameterByName(const std::string& name)const override;

		virtual std::string GetLatestProfile(ShaderType type);

		bool HasSemantic(const BufferBinding& binding)const;

		UINT GeetSlotIDBySemantic(const BufferBinding& binding);
		
		virtual void Bind();
		virtual void UnBind();

		virtual void Dispatch(const Vector3UI& numGroup);

	protected:
		virtual void Destroy();
		
	private:
		ShaderType mShaderType;
		ID3D11Device2* mDevice;
		ID3D11DeviceContext2* mContext;
		ID3D11VertexShader* vShader;
		ID3D11HullShader* hShader;
		ID3D11DomainShader* dShader;
		ID3D11GeometryShader* gShader;
		ID3D11PixelShader* pShader;
		ID3D11ComputeShader* cShader;

		ID3DBlob* mShaderBlob;
		ID3D11InputLayout* mInputlayout;
		typedef std::map<std::string, std::shared_ptr<ShaderParameterDx>> ParameterMap;
		ParameterMap mShaderParameters;

		typedef std::map<BufferBinding, UINT> SemanticMap;
		SemanticMap mInputSemantics;

		ShaderMacros mShaderMacros;
		std::string mEntryPoint;
		std::string mProfile;
		std::string mShaderFile;
		
		Event::ScopedConnections m_Connections;
		std::atomic<bool> m_bFileChanged;
		typedef std::unique_lock<std::recursive_mutex> MutexLock;
		std::recursive_mutex m_Mutex;

	};
}
