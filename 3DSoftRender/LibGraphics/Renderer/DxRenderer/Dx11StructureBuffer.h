#include "Dx11RenderLIB.h"
#include "Resource/StructuredBuffer.h"
#include "Dx11ShaderParameter.h"

namespace Hikari
{
	class StructuredBufferDX11 : public StructuredBuffer, public enable_shared_from_this<StructuredBufferDX11>
	{
	public:
		typedef StructuredBuffer base;

		StructuredBufferDX11(ID3D11Device* pDevice, const void* data, size_t count, UINT stride,
		                     ShaderParameter::ShaderInputParameter inputParameter);
		virtual ~StructuredBufferDX11();

		// Bind the buffer for rendering.
		void bind(unsigned int ID, Shader::ShaderType shaderType) override;
		// Unbind the buffer for rendering.
		void unbind(unsigned int id, Shader::ShaderType shaderType) override;


		// How many elements does this buffer contain?
		unsigned int get_element_count() const override;


		// Clear the contents of the buffer.
		void Clear() override;

		UINT GetStride() const override;
		// Used by the RenderTargetDX11 only.
		ID3D11UnorderedAccessView* GetUnorderedAccessView() const;


		void copy(std::shared_ptr<BufferBase> other) override;
	protected:

		void SetData(const void* data, size_t elementSize, size_t offset, size_t numElements) override;
		// Commit the data from system memory to device memory.
		void Commit();

	private:
		ID3D11Device* m_pDevice;
		ID3D11DeviceContext* m_pDeviceContext{};
		ID3D11Buffer* m_pBuffer{};
		ID3D11Buffer* m_pStage{};
		ID3D11ShaderResourceView* m_pSRV{};
		ID3D11UnorderedAccessView* m_pUAV{};

		// The system data buffer.
		typedef std::vector<uint8_t> BufferType;
		BufferType m_Data{};

		void*	m_data_;
		// The stride of the vertex buffer in bytes.
		UINT m_uiStride;

		// How this buffer should be bound.
		UINT m_BindFlags{};

		// The number of elements in this buffer.
		UINT m_uiCount;

		// The last slot the UAV was bound to.
		UINT m_uiSlot{};

		// Marked dirty if the contents of the buffer differ
		// from what is stored on the GPU.
		bool m_bIsDirty{};
		// Does this buffer require GPU write access 
		// If so, it must be bound as a UAV instead of an SRV.
		bool m_bUAV{};

		bool m_bSRV{};
		// Requires CPU read/write access.
		bool m_bDynamic{};
	};
}
