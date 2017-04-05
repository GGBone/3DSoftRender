#include "GraphicsPCH.h"
#include "Dx11Texture2D.h"
using namespace Hikari;
Hikari::PdrTexture2D::PdrTexture2D(DirectRenderer * renderer, const Texture2D * texture)
{
	ID3D11Device* device = renderer->mData->mDevice;
	ID3D11DeviceContext* contex = renderer->mData->mImmediateContext;

	int numLevels = texture->GetNumLevels();

	D3D11_TEXTURE2D_DESC desc;
	D3D11_SUBRESOURCE_DATA resData; 
	char* data;
	ZeroMemory(&desc, sizeof(desc));
	desc.Width = texture->GetWidth();
	desc.Height = texture->GetHeight();
	switch (texture->GetFormat())
	{
	case Texture::Format::TF_R8G8B8:
		desc.Format = DXGI_FORMAT_B8G8R8X8_TYPELESS;
		break;
	case Texture::Format::TF_R8G8B8A8:
		desc.Format = DXGI_FORMAT_R8G8B8A8_UINT;
		break;
	case Texture::Format::TF_D24S8:
		desc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
		break;
	default:
		desc.Format = DXGI_FORMAT_UNKNOWN;
		break;
	}

	switch (texture->GetUsage())
	{
		//shader source 
	case Buffer::BU_TEXTURE:
		desc.BindFlags = D3D11_BIND_SHADER_RESOURCE;

		desc.CPUAccessFlags = 0;
		desc.MipLevels = numLevels;
		desc.MiscFlags = 0;
		desc.SampleDesc.Count = 1;
		desc.SampleDesc.Quality = 0;
		desc.Usage = D3D11_USAGE_DEFAULT;
		device->CreateTexture2D(&desc, nullptr, &mTexture);
		break;
		//depth buffer
	case Buffer::BU_DEPTHSTENCIL:
		desc.BindFlags = D3D11_BIND_DEPTH_STENCIL;

		desc.CPUAccessFlags = 0;
		desc.MipLevels = numLevels;
		desc.MiscFlags = 0;
		desc.SampleDesc.Count = 1;
		desc.SampleDesc.Quality = 0;
		desc.Usage = D3D11_USAGE_DEFAULT;
		device->CreateTexture2D(&desc, nullptr, &mTexture);
		break;

		//rt
	case Buffer::BU_RENDERTARGET:
		desc.BindFlags = D3D11_BIND_RENDER_TARGET;
		desc.CPUAccessFlags = 0;
		desc.MipLevels = numLevels;
		desc.MiscFlags = 0;
		desc.SampleDesc.Count = 1;
		desc.SampleDesc.Quality = 0;
		desc.Usage = D3D11_USAGE_DEFAULT;
		device->CreateTexture2D(&desc, nullptr, &mTexture);

		break;
		//Initial with data firstly
	case Buffer::BU_STATIC:
		desc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
		desc.CPUAccessFlags = 1;
		desc.MipLevels = numLevels;
		desc.MiscFlags = 0;
		desc.SampleDesc.Count = 1;
		desc.SampleDesc.Quality = 0;
		desc.Usage = D3D11_USAGE_DEFAULT;
		data = new char[texture->GetNumTotalBytes()];
		for (int i = 0; i < numLevels; ++i)
		{
			memcpy(data, texture->GetData(i), texture->GetNumLevelBytes(i));
		}
		
		resData.pSysMem = data;
		resData.SysMemPitch = 0;
		resData.SysMemSlicePitch = 0;

		device->CreateTexture2D(&desc, &resData, &mTexture);
		break;

	case Buffer::BU_DYNAMIC:
		desc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
		desc.CPUAccessFlags = 1;
		desc.MipLevels = numLevels;
		desc.MiscFlags = 0;
		desc.SampleDesc.Count = 1;
		desc.SampleDesc.Quality = 0;
		desc.Usage = D3D11_USAGE_DYNAMIC;
		device->CreateTexture2D(&desc, nullptr, &mTexture);
		break;
	default:
		desc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
		desc.CPUAccessFlags = 1;
		desc.MipLevels = numLevels;
		desc.MiscFlags = 0;
		desc.SampleDesc.Count = 1;
		desc.SampleDesc.Quality = 0;
		desc.Usage = D3D11_USAGE_DEFAULT;
		data = new char[texture->GetNumTotalBytes()];
		for (int i = 0; i < numLevels; ++i)
		{
			memcpy(data, texture->GetData(i), texture->GetNumLevelBytes(i));
		}
		resData.pSysMem = data;
		resData.SysMemPitch = 0;
		resData.SysMemSlicePitch = 0;

		device->CreateTexture2D(&desc, &resData, &mTexture);
		break;
		break;
	}

}

void Hikari::PdrTexture2D::Enable(DirectRenderer * renderer, int textureUnit)
{
}
