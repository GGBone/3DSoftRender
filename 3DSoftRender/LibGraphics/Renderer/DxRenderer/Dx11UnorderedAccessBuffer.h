#include "Graphics\Dx11RenderLIB.h"
#include "Graphics\UnorderedAccessBuffer.h"
#include "Graphics\CPUAccess.h"
namespace Hikari
{
	class UnorderedAccessBufferDX11 : public UnorderedAccessBuffer, public enable_shared_from_this<UnorderedAccessBufferDX11>
	{
	public:
		typedef UnorderedAccessBuffer base;

		UnorderedAccessBufferDX11(ID3D11Device* pDevice, uint8_t bindFlags, const void* data, uint32_t count, uint16_t stride,  bool AppendFlag = false);
		virtual ~UnorderedAccessBufferDX11();

		// Bind the buffer for rendering.
		virtual bool Bind(unsigned int id, Shader::ShaderType shaderType, ShaderParameter::Type parameterType, ...) override;
		// Unbind the buffer for rendering.
		virtual void UnBind(unsigned int id, Shader::ShaderType shaderType, ShaderParameter::Type parameterType) override;


		// How many elements does this buffer contain?
		virtual unsigned int GetElementCount() const;

		virtual void Copy(std::shared_ptr<UnorderedAccessBufferDX11> other);

		// Clear the contents of the buffer.
		virtual void Clear();

		virtual UINT GetStride() const;
		// Used by the RenderTargetDX11 only.
		ID3D11UnorderedAccessView* GetUnorderedAccessView() const;

		ID3D11ShaderResourceView* GetShaderResourceView() const;
	protected:
		virtual void Copy(std::shared_ptr<Buffer> other);
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
		typedef std::vector<uint8_t> BufferContainer;
		BufferContainer m_Data;

		// The stride of the vertex buffer in bytes.
		uint16_t m_uiStride;

		// How this buffer should be bound.
		uint8_t m_BindFlags;

		// The number of elements in this buffer.
		uint32_t m_uiCount;

		// The last slot the UAV was bound to.
		uint8_t m_uiSlot;

		// Marked dirty if the contents of the buffer differ
		// from what is stored on the GPU.
		bool m_bIsDirty;
	};
}
