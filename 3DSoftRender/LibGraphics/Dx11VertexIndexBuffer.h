#pragma once
#include "Graphics\GraphicsLib.h"
#include "Graphics\BufferBase.h"
namespace Hikari
{
	class Shader;
	class DirectRenderer;
	class VertexIndexBufferDx11 : public BufferBase
	{
	public:

		VertexIndexBufferDx11(std::shared_ptr<DirectRenderer>& render, UINT bindFlags, const void* data, size_t count, UINT stride);
		~VertexIndexBufferDx11();
		
		virtual void Copy(std::shared_ptr<BufferBase> other) override;
		virtual BufferBase::BufferType GetType() const override;

		virtual unsigned int GetElementCount()const override;

		// Bind the buffer to a particular attribute ID or slot
		virtual bool Bind(unsigned int id, Shader::ShaderType shaderType, ShaderParameter::Type parameterType,...) override;
		virtual void UnBind(unsigned int id, Shader::ShaderType shaderType, ShaderParameter::Type parameterType) override;

	private:
		ID3D11Device2* m_pDevice;
		ID3D11DeviceContext2* m_pDeviceContext;
		ID3D11Buffer* m_pBuffer;

		UINT m_uiStride;
		UINT m_BindFlags;
		UINT m_uiCount;
		bool m_bIsBound;
	};
}