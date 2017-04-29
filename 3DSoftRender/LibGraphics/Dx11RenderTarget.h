#pragma once

#include <RenderTarget.h>

namespace Hikari
{

	class TextureDX11;
	class StructuredBufferDX11;
	class RWBufferDX11;
	class RenderTargetDX11 : public RenderTarget
	{
	public:
		RenderTargetDX11(ID3D11Device* pDevice);
		virtual ~RenderTargetDX11();

		virtual void AttachTexture(AttachmentPoint attachment,Texture* texture);
		virtual Texture* GetTexture(AttachmentPoint attachment);
		virtual void Clear(AttachmentPoint attachemnt, ClearFlags clearFlags = ClearFlags::All, const Float4& color = Float4(0, 0, 0, 0), float depth = 1.0f, uint8_t stencil = 0);
		virtual void Clear(ClearFlags clearFlags = ClearFlags::All, const Float4& color = Float4(0,0,0,0), float depth = 1.0f, uint8_t stencil = 0);
		virtual void GenerateMipMaps();
		virtual void AttachStructuredBuffer(uint8_t slot, StructuredBuffer* rwBuffer);
		virtual StructuredBuffer* GetStructuredBuffer(uint8_t slot);
		virtual void AttachRWBuffer(uint8_t slot, RWBuffer* rwBuffer) override;
		virtual RWBuffer* GetRWBuffer(uint8_t) override;
		virtual void Resize(uint16_t width, uint16_t height);
		virtual void Bind();
		virtual void UnBind();
		virtual bool IsValid() const;

	protected:


	private:
		ID3D11Device* m_pDevice;
		ID3D11DeviceContext* m_pDeviceContext;

		typedef std::vector< TextureDX11*> TextureList;
		TextureList m_Textures;

		typedef std::vector<StructuredBufferDX11*> StructuredBufferList;
		StructuredBufferList m_StructuredBuffers;

		typedef std::vector<RWBufferDX11*> RWBufferList;
		RWBufferList m_RWBuffers;
		// The width in pixels of textures associated to this render target.
		uint16_t m_Width;
		// The height in pixels of textures associated to this render target.
		uint16_t m_Height;

		// Check to see if the render target is valid.
		bool m_bCheckValidity;
	};
}