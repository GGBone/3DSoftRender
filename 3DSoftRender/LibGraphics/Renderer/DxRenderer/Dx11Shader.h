#pragma once

#include "Dx11RenderLIB.h"
#include <mutex>
#include <Shader/Shader.h>

namespace Hikari
{
	class ShaderParameterDx11;
	class DirectRenderer;

	class ShaderDx : public Shader
	{
	public:
		//Need hide only can be created by Renderer
		explicit ShaderDx(const std::shared_ptr<DirectRenderer>& renderer);

		ShaderType GetType() const override;

		void LoadShaderFromString(ShaderType type, const std::string& source, const std::string& sourceFileName,
		                          const ShaderMacros& shaderMacros, const std::string& entryPoint,
		                          const std::string& profile) override;

		bool LoadShaderFromFile(ShaderType type, const std::string& fileName, const ShaderMacros& shaderMacros,
		                        const std::string& entryPoint, const std::string& profile) override;

		ShaderParameter& GetShaderParameterByName(const std::string& name) const override;

		std::string GetLatestProfile(ShaderType type) override;

		bool HasSemantic(const BufferBinding& binding) const;

		UINT GetSlotIDBySemantic(const BufferBinding& binding);

		void Bind() override;
		void UnBind() override;

		void Dispatch(const Vector3UI& numGroup) override;

	protected:
		virtual void Destroy();

	private:
		ID3D11Device2* mDevice = nullptr;
		ID3D11DeviceContext2* mContext = nullptr;
		ID3D11VertexShader* vShader = nullptr;
		ID3D11HullShader* hShader = nullptr;
		ID3D11DomainShader* dShader = nullptr;
		ID3D11GeometryShader* gShader = nullptr;
		ID3D11PixelShader* pShader = nullptr;
		ID3D11ComputeShader* cShader = nullptr;

		ID3DBlob* mShaderBlob = nullptr;
		ID3D11InputLayout* mInputlayout = nullptr;
		typedef std::map<std::string, std::shared_ptr<ShaderParameterDx11>> ParameterMap;
		ParameterMap mShaderParameters{};

		typedef std::map<BufferBinding, UINT> SemanticMap;
		SemanticMap mInputSemantics{};

		ShaderMacros mShaderMacros;
		std::string mEntryPoint;
		std::string mProfile;
		std::string mShaderFile;

		Event::ScopedConnections m_Connections{};
		std::atomic<bool> m_bFileChanged = false;
		typedef unique_lock<std::recursive_mutex> MutexLock;
		std::recursive_mutex m_Mutex;
	};
}
