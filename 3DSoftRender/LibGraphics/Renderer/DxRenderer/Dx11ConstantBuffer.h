#pragma once
#include "Dx11RenderLIB.h"
#include "Resource/ConstantBuffer.h"
#include "Shader/Shader.h"

namespace Hikari
{
	class Shader;

	class ConstantBufferDX11 : public ConstantBuffer, public enable_shared_from_this<ConstantBufferDX11>
	{
	public:
		ConstantBufferDX11(ID3D11Device* pDevice, size_t size);
		virtual ~ConstantBufferDX11();

		void bind(unsigned int id, Shader::ShaderType shaderType) override;
		void unbind(unsigned int id, Shader::ShaderType shaderType) override;

	protected:
		void copy(std::shared_ptr<BufferBase> other) override;
		void set(const void* data, size_t size) override;

	private:
		ID3D11Device* m_pDevice{};
		ID3D11DeviceContext* m_pDeviceContext{};
		ID3D11Buffer* m_pBuffer{};

		size_t m_BufferSize{};
	};
}
