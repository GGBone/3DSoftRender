#pragma once
#include "Graphics\GraphicsLib.h"
#include "Graphics\Dx11Renderer.h"
#include "Graphics\ConstantBuffer.h"
#include "Graphics\Shader.h"

namespace Hikari
{
	class Shader;
	class ConstantBufferDX11 : public ConstantBuffer
	{
	public:
		ConstantBufferDX11(ID3D11Device* pDevice, size_t size);
		virtual ~ConstantBufferDX11();

		virtual bool Bind(unsigned int id, Shader::ShaderType shaderType, ShaderParameter::Type parameterType) override;
		virtual void UnBind(unsigned int id, Shader::ShaderType shaderType, ShaderParameter::Type parameterType) override;

		virtual void Copy(std::shared_ptr<ConstantBuffer> other) override;

	protected:
		virtual void Copy(std::shared_ptr<Buffer> other) override;
		void Set(const void* data, size_t size);

	private:
		ID3D11Device* m_pDevice;
		ID3D11DeviceContext* m_pDeviceContext;
		ID3D11Buffer* m_pBuffer;

		size_t  m_BufferSize;
	};
}
