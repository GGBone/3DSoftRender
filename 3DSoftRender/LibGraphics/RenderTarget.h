#pragma once
#include "Texture2D.h"
#include "GraphicsLib.h"

namespace Hikari
{
	class RenderTarget : public Object
	{
		DECLARE_RTTI;
		DECLARE_NAMES;
	public:
		RenderTarget(int numTargets, Texture::Format format, int width, int height,
			bool hasMipmap, bool hasDepthStencil)
		:mHasMipmaps(hasMipmap)
		{
			mColorTextures = new Texture2DPtr[numTargets];
			for (int i = 0; i < numTargets; ++i)
			{
				*(mColorTextures + i) = new Texture2D(format, width, height, hasMipmap ? 0 : 1, Buffer::BU_RENDERTARGET);

			}
			if (hasDepthStencil)
				mDepthStencil = new Texture2D(Texture::Format::TF_D24S8, width, height, 1, Buffer::BU_DEPTHSTENCIL);
			
		}
		virtual ~RenderTarget()
		{
			for (size_t i = 0; i < mNumTargets; i++)
			{
				delete	mColorTextures[i];
			}
			delete mDepthStencil;
		}


		//Mem Access
		inline int GetNumTargets()const;
		inline Texture::Format GetFormat()const;
		inline int GetWidth() const;
		inline int GetHeight() const;
		inline Texture2D* GetColorTexture(int i)const;
		inline Texture2D* GetDepthStencilTexture()const;
		inline bool HasMipmaps() const;
		inline bool HasDepthStencil() const;
	protected:
		int mNumTargets;
		Texture2DPtr* mColorTextures;
		Texture2DPtr mDepthStencil;
		bool mHasMipmaps;
	};
	typedef RenderTarget* RenderTargetPtr;

	inline int Hikari::RenderTarget::GetNumTargets() const
	{
		return mNumTargets;
	}

	inline Texture::Format RenderTarget::GetFormat() const
	{
		if (*mColorTextures)
		{
			return (*mColorTextures)->GetFormat();
		}
		else return Texture::Format::TF_NONE;
	}

	inline int RenderTarget::GetWidth() const
	{
		if (*mColorTextures)
		{
			return (*mColorTextures)->GetWidth();
		}
		else return -1;
	}

	inline int RenderTarget::GetHeight() const
	{
		if (*mColorTextures)
		{
			return (*mColorTextures)->GetHeight();
		}
		else return -1;
	}

	inline Texture2D * RenderTarget::GetColorTexture(int i) const
	{
		assert(i >= 0);
		return *(mColorTextures+i);
	}

	inline Texture2D * RenderTarget::GetDepthStencilTexture() const
	{
		return mDepthStencil;
	}

	inline bool RenderTarget::HasMipmaps() const
	{
		return mHasMipmaps;
	}

	inline bool RenderTarget::HasDepthStencil() const
	{
		return mDepthStencil != nullptr;
	}

}