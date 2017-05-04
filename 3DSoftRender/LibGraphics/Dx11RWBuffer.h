#pragma once
#include "Dx11RenderLIB.h"
#include "RWBuffer.h"
#include "CPUAccess.h"
namespace Hikari
{
	class RWBufferDX11 : public RWBuffer
	{
	public:
		typedef RWBuffer base;

		RWBufferDX11(ID3D11Device* pDevice, UINT bindFlags, const void* data, size_t count, UINT stride);
		virtual ~RWBufferDX11();

		// Bind the buffer for rendering.
		virtual bool Bind(unsigned int id, Shader::ShaderType shaderType, ShaderParameter::Type parameterType) override;
		// Unbind the buffer for rendering.
		virtual void UnBind(unsigned int id, Shader::ShaderType shaderType, ShaderParameter::Type parameterType) override;

		// How many elements does this buffer contain?
		virtual unsigned int GetElementCount() const;

		virtual void Copy(RWBuffer* other) override;

		// Used by the RenderTargetDX11 only.
		ID3D11UnorderedAccessView* GetUnorderedAccessView() const;
		virtual void* GetData() const override;
	protected:
		virtual void Copy(Buffer* other);
		virtual void SetData(void* data, size_t elementSize, size_t offset, size_t numElements);
		// Commit the data from system memory to device memory.
		void Commit();

	private:
		ID3D11Device* m_pDevice;
		ID3D11DeviceContext* m_pDeviceContext;
		ID3D11Buffer* m_pBuffer;
		ID3D11Buffer* m_pStage;
		ID3D11ShaderResourceView* m_pSRV;
		ID3D11UnorderedAccessView* m_pUAV;
		
		typedef std::vector<uint8_t> BufferType;
		BufferType m_Data;

		UINT m_uiStride;

		UINT m_BindFlags;

		UINT m_uiCount;

		UINT m_uiSlot;

		bool m_bIsDirty;

		bool m_bUAV;

	};

}