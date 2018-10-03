#pragma once
#include "Dx11RenderLIB.h"
#include "Resource/Buffer.h"
#include "Dx11ShaderParameter.h"
#include <memory>
namespace Hikari
{
	class DirectRenderer;
	class BufferDX11 : public Buffer,public enable_shared_from_this<BufferDX11>
	{
	public:
		typedef Buffer base;
		BufferDX11(const BufferDX11& rhs);
		// Bind the buffer for rendering.
		bool bind(unsigned int id, Shader::ShaderType shaderType) override;
		// Unbind the buffer for rendering.
		void unbind(unsigned int id, Shader::ShaderType shaderType) override;

		// How many elements does this buffer contain?
		unsigned int get_element_count() const override;

		void copy(std::shared_ptr<BufferBase> other) override;
		void copy_buffer_data() override;
		void clear() override;
		// Used by the RenderTargetDX11 only.
		ID3D11UnorderedAccessView* GetUnorderedAccessView() const;
		void* get_data() const override;
		virtual ~BufferDX11();
		friend class std::_Ref_count_obj<BufferDX11>;

	protected:

		void set_data(const void* data, size_t elementSize, size_t offset, size_t numElements) override;
		// Commit the data from system memory to device memory.
		void commit();
	private:
		BufferDX11(const shared_ptr<DirectRenderer>& pDevice, const void* data, UINT count, UINT stride,
			ShaderParameter::ShaderInputParameter shader_input_param);

		ID3D11Device* m_pDevice;
		ID3D11DeviceContext* m_pDeviceContext{};
		ID3D11Buffer* m_pBuffer{};

		//Copy from a buffer<GPU write> to another buffer<CPU read> 
		ID3D11Buffer* m_pStage{};
		ID3D11ShaderResourceView* m_pSRV{};
		ID3D11UnorderedAccessView* m_pUAV{};


		ShaderParameter::ShaderInputParameter m_shader_input_parameter_;
		typedef std::vector<UINT> BufferContainer;
		BufferContainer m_Data{};

		UINT m_uiStride{};
		UINT m_BindFlags{};
		UINT m_uiCount{};
		UINT m_uiSlot{};
		bool m_bIsDirty = false;
		bool m_bUAV{};
	};
}
