#pragma once

namespace Hikari
{
	class TextureDX11;
	class StructuredBufferDX11;
	class BufferDX11;

	class RenderTargetDX11 : public RenderTarget
	{
	public:
		RenderTargetDX11(ID3D11Device* pDevice);
		virtual ~RenderTargetDX11();

		void AttachTexture(AttachmentPoint attachment, std::shared_ptr<Texture> texture) override;
		std::shared_ptr<Texture> GetTexture(AttachmentPoint attachment) override;
		void Clear(const Float4& color, ClearFlags clearFlags = ClearFlags::All,
		           float depth = 1.0f, uint8_t stencil = 0) override;


		void Clear(AttachmentPoint attachment, const Float4& color, ClearFlags clearFlags = ClearFlags::All,
		           float depth = 1.0f, uint8_t stencil = 0) override;
		void GenerateMipMaps() override;
		void AttachStructuredBuffer(uint8_t slot, std::shared_ptr<StructuredBuffer> rwBuffer) override;
		std::shared_ptr<StructuredBuffer> GetStructuredBuffer(uint8_t slot) override;
		void AttachBuffer(uint8_t slot, std::shared_ptr<Buffer> rwBuffer) override;
		std::shared_ptr<Buffer> GetBuffer(uint8_t) override;
		void Resize(uint16_t width, uint16_t height) override;
		void Bind() override;
		void UnBind() override;
		bool IsValid() const override;

	protected:


	private:
		ID3D11Device* m_pDevice;
		ID3D11DeviceContext* m_pDeviceContext{};

		typedef std::vector<std::shared_ptr<TextureDX11>> TextureList;
		TextureList m_Textures{};

		typedef std::vector<std::shared_ptr<StructuredBufferDX11>> StructuredBufferList;
		StructuredBufferList m_StructuredBuffers{};

		typedef std::vector<std::shared_ptr<BufferDX11>> BufferList;
		BufferList m_Buffers{};
		// The width in pixels of textures associated to this render target.
		uint16_t m_Width;
		// The height in pixels of textures associated to this render target.
		uint16_t m_Height;

		// Check to see if the render target is valid.
		bool m_bCheckValidity;
	};
}
