#pragma once
#include "GraphicsLib.h"
#include "Texture2D.h"
namespace Hikari
{
	class PdrTexture2D
	{
	public:
		PdrTexture2D(DirectRenderer* renderer, const Texture2D* texture);
		~PdrTexture2D();

		void Enable(DirectRenderer* renderer, int textureUnit);
		void Disable(DirectRenderer* renderer, int textureUnit);
		void* Lock(int level, Buffer::Locking mode);
		void Unlock(int level);

	private:
		friend class PdrRenderTarget;
		PdrTexture2D(DirectRenderer* renderer, bool isColorTexture, const Texture2D* texture,bool autoGeneralMipmap);

		ID3D11Texture2D* mTexture;
	};
}