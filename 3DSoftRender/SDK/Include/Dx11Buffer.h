#pragma once
#include "GraphicsLib.h"
#include "Buffer.h"
#include "Shader.h"
namespace Hikari
{
	class DirectRenderer;
	class BufferDx : public Buffer
	{
	public:

		BufferDx(DirectRenderer* render, UINT bindFlags, const void* data, size_t count, UINT stride);
		~BufferDx();
		
		virtual void Copy(Buffer* other) override;
		virtual BufferType GetType() const override;

		virtual unsigned int GetElementCount()const override;

		// Bind the buffer to a particular attribute ID or slot
		virtual bool Bind(unsigned int id, Shader::ShaderType shaderType, ShaderParameter::Type parameterType) override;
		virtual void UnBind(unsigned int id, Shader::ShaderType shaderType, ShaderParameter::Type parameterType) override;

	private:
		ID3D11Device* m_pDevice;
		ID3D11DeviceContext* m_pDeviceContext;
		ID3D11Buffer* m_pBuffer;

		UINT m_uiStride;
		UINT m_BindFlags;
		UINT m_uiCount;
		bool m_bIsBound;
	};
}