#pragma once
#include "Dx11RenderLIB.h"
#include "Resource/BufferBase.h"
#include "Dx11ShaderParameter.h"
#include "Resource/VertexIndexBuffer.h"

namespace Hikari
{
	class Shader;
	class DirectRenderer;

	class VertexIndexBufferDx11 : public VertexIndexBuffer
	{
	public:

		VertexIndexBufferDx11(std::shared_ptr<DirectRenderer>& render, UINT bindFlags, const void* data, size_t count,
			UINT stride);
		~VertexIndexBufferDx11();

		void copy(std::shared_ptr<BufferBase> other) override;
		BufferType get_type() const override;

		unsigned int get_element_count() const override;

		// Bind the buffer to a particular attribute ID or slot
		void bind(unsigned int id) override;
		void unbind(unsigned int id) override;

		void set(const void* data, size_t size) override;

		void set_instanced(bool value = false) override { m_bInstanced = value; }
		bool get_instanced()const override { return m_bInstanced; }
	private:
		ID3D11Device* m_pDevice{};
		ID3D11DeviceContext* m_pDeviceContext{};
		ID3D11Buffer* m_pBuffer{};

		UINT m_uiStride;
		UINT m_BindFlags;
		UINT m_uiCount;
		bool m_bIsBound;

		bool m_bInstanced;
	};
}
