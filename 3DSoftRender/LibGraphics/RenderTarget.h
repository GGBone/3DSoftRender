#pragma once

#include "Object.h"
namespace Hikari
{
	class Texture;
	class StructuredBuffer;

	class RenderTarget : public Object
	{
	public:
		enum class AttachmentPoint : uint8_t
		{
			Color0,         // Must be a uncompressed color format.
			Color1,         // Must be a uncompressed color format.
			Color2,         // Must be a uncompressed color format.
			Color3,         // Must be a uncompressed color format.
			Color4,         // Must be a uncompressed color format.
			Color5,         // Must be a uncompressed color format.
			Color6,         // Must be a uncompressed color format.
			Color7,         // Must be a uncompressed color format.
			Depth,          // Must be a texture with a depth format.
			DepthStencil,   // Must be a texture with a depth/stencil format.
			NumAttachmentPoints
		};

		virtual void AttachTexture(AttachmentPoint attachment, Texture* texture) = 0;
		virtual Texture* GetTexture(AttachmentPoint attachment) = 0;

	
		virtual void Clear(AttachmentPoint attachemnt, ClearFlags clearFlags = ClearFlags::All, const Float4& color = Float4(0,0,0,0), float depth = 1.0f, uint8_t stencil = 0) = 0;

	
		virtual void Clear(ClearFlags clearFlags = ClearFlags::All, const Float4& color = Float4(0, 0, 0, 0), float depth = 1.0f, uint8_t stencil = 0) = 0;

		
		virtual void GenerateMipMaps() = 0;

	
		virtual void AttachStructuredBuffer(uint8_t slot, StructuredBuffer* rwBuffer) = 0;
		virtual StructuredBuffer* GetStructuredBuffer(uint8_t slot) = 0;

		virtual void AttachRWBuffer(uint8_t slot, RWBuffer* rwBuffer) = 0;
		virtual RWBuffer* GetRWBuffer(uint8_t slot) = 0;
		virtual void Resize(uint16_t width, uint16_t height) = 0;

		
		virtual void Bind() = 0;
	
		virtual void UnBind() = 0;

	
		virtual bool IsValid() const = 0;
	};
}
