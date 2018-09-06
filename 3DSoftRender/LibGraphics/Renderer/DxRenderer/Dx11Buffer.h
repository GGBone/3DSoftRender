#pragma once
#include "Dx11RenderLIB.h"
#include "Resource/Buffer.h"
#include "Dx11ShaderParameter.h"

namespace Hikari
{
	class BufferDX11 : public Buffer
	{
	public:
		typedef Buffer base;

		BufferDX11(ID3D11Device* pDevice, const void* data, UINT count, UINT stride,
		           ShaderParameter::ShaderInputParameter shader_input_param);
		virtual ~BufferDX11();

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
	protected:

		void set_data(const void* data, size_t elementSize, size_t offset, size_t numElements) override;
		// Commit the data from system memory to device memory.
		void commit();
	private:
		ID3D11Device* m_pDevice;
		ID3D11DeviceContext* m_pDeviceContext{};
		ID3D11Buffer* m_pBuffer{};

		//Copy from a buffer<GPU write> to another buffer<CPU read> 
		ID3D11Buffer* m_pStage{};
		ID3D11ShaderResourceView* m_pSRV;
		ID3D11UnorderedAccessView* m_pUAV;


		ShaderParameter::ShaderInputParameter m_shader_input_parameter_;
		typedef std::vector<UINT> BufferContainer;
		BufferContainer m_Data{};

		UINT m_uiStride;

		UINT m_BindFlags{};

		UINT m_uiCount;

		UINT m_uiSlot{};

		bool m_bIsDirty = false;

		bool m_bUAV{};
	};
}
