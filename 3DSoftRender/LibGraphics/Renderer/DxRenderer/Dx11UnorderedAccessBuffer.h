#include "Dx11RenderLIB.h"
#include "Resource/UnorderedAccessBuffer.h"

namespace Hikari
{
	class UnorderedAccessBufferDX11 : public UnorderedAccessBuffer,
	                                  public enable_shared_from_this<UnorderedAccessBufferDX11>
	{
	public:
		typedef UnorderedAccessBuffer base;

		UnorderedAccessBufferDX11(ID3D11Device* pDevice, const void* data, uint32_t count, uint16_t stride,
		                          ShaderParameter::ShaderInputParameter shader_param);
		virtual ~UnorderedAccessBufferDX11();

		// Bind the buffer for rendering.
		bool bind(unsigned int id, Shader::ShaderType shaderType) override;
		// Unbind the buffer for rendering.
		void unbind(unsigned int id, Shader::ShaderType shaderType) override;


		// How many elements does this buffer contain?
		unsigned int get_element_count() const override;


		// Clear the contents of the buffer.
		virtual void Clear();

		virtual UINT GetStride() const;
		// Used by the RenderTargetDX11 only.
		ID3D11UnorderedAccessView* GetUnorderedAccessView() const;

		ID3D11ShaderResourceView* GetShaderResourceView() const;
	protected:
		void copy(std::shared_ptr<BufferBase> other) override;
		void set_data(void* data, size_t elementSize, size_t offset, size_t numElements) override;
		// Commit the data from system memory to device memory.
		static void Commit();

	private:
		ID3D11Device* m_pDevice;
		ID3D11DeviceContext* m_pDeviceContext{};
		ID3D11Buffer* m_pBuffer{};
		ID3D11ShaderResourceView* m_pSRV{};
		ID3D11UnorderedAccessView* m_pUAV{};

		ShaderParameter::ShaderInputParameter m_shader_input_param_;
		// The system data buffer.
		typedef std::vector<uint8_t> BufferContainer;
		BufferContainer m_Data{};

		// The stride of the vertex buffer in bytes.
		uint16_t m_uiStride;

		// How this buffer should be bound.
		uint8_t m_BindFlags;

		// The number of elements in this buffer.
		uint32_t m_uiCount;

		// The last slot the UAV was bound to.
		uint8_t m_uiSlot{};

		// Marked dirty if the contents of the buffer differ
		// from what is stored on the GPU.
		bool m_bIsDirty;
	};
}
