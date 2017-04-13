#include "Dx11RenderLIB.h"
#include "StructuredBuffer.h"
#include "CPUAccess.h"
namespace Hikari
{
	class StructuredBufferDX11 : public StructuredBuffer
	{
	public:
		typedef StructuredBuffer base;

		StructuredBufferDX11(ID3D11Device* pDevice, UINT bindFlags, const void* data, size_t count, UINT stride, CPUAccess cpuAccess = CPUAccess::None, bool bUAV = false);
		virtual ~StructuredBufferDX11();

		// Bind the buffer for rendering.
		virtual bool Bind(unsigned int id, Shader::ShaderType shaderType, ShaderParameter::Type parameterType) override;
		// Unbind the buffer for rendering.
		virtual void UnBind(unsigned int id, Shader::ShaderType shaderType, ShaderParameter::Type parameterType) override;

		// Is this an index buffer or an attribute/vertex buffer?
		virtual Buffer::BufferType GetType() const;

		// How many elements does this buffer contain?
		virtual unsigned int GetElementCount() const;

		virtual void Copy(StructuredBuffer* other);

		// Clear the contents of the buffer.
		virtual void Clear();

		// Used by the RenderTargetDX11 only.
		ID3D11UnorderedAccessView* GetUnorderedAccessView() const;

	protected:
		virtual void Copy(Buffer* other);
		virtual void SetData(void* data, size_t elementSize, size_t offset, size_t numElements);
		// Commit the data from system memory to device memory.
		void Commit();

	private:
		ID3D11Device* m_pDevice;
		ID3D11DeviceContext* m_pDeviceContext;
		ID3D11Buffer* m_pBuffer;
		ID3D11ShaderResourceView* m_pSRV;
		ID3D11UnorderedAccessView* m_pUAV;

		// The system data buffer.
		typedef std::vector<uint8_t> BufferType;
		BufferType m_Data;

		// The stride of the vertex buffer in bytes.
		UINT m_uiStride;

		// How this buffer should be bound.
		UINT m_BindFlags;

		// The number of elements in this buffer.
		UINT m_uiCount;

		// The last slot the UAV was bound to.
		UINT m_uiSlot;

		// Marked dirty if the contents of the buffer differ
		// from what is stored on the GPU.
		bool m_bIsDirty;
		// Does this buffer require GPU write access 
		// If so, it must be bound as a UAV instead of an SRV.
		bool m_bUAV;

		// Requires CPU read/write access.
		bool m_bDynamic;
		CPUAccess m_CPUAccess;
	};
}
