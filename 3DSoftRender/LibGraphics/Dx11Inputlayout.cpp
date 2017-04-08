#include "Dx11InputLayout.h"
using namespace Hikari;

const D3D11_INPUT_ELEMENT_DESC InputLayoutDesc::Pos[1] =
{
	{ "POSITION",0,DXGI_FORMAT_R32G32B32_FLOAT,0,0,D3D11_INPUT_PER_VERTEX_DATA,0 }
};

const D3D11_INPUT_ELEMENT_DESC InputLayoutDesc::BasicFormat[3] =
{
	{ "POSITION",0,DXGI_FORMAT_R32G32B32_FLOAT,0,0,D3D11_INPUT_PER_VERTEX_DATA,0 },
	{ "NORMAL",0,DXGI_FORMAT_R32G32B32_FLOAT,0,12,D3D11_INPUT_PER_VERTEX_DATA,0 },
	{ "TEXCOORD",0,DXGI_FORMAT_R32G32_FLOAT,0,24,D3D11_INPUT_PER_VERTEX_DATA,0 }

};

const D3D11_INPUT_ELEMENT_DESC InputLayoutDesc::TestFormat[3] =
{
	{ "POSITION",0,DXGI_FORMAT_R32G32B32_FLOAT,0,0,D3D11_INPUT_PER_VERTEX_DATA,0 },
	{ "NORMAL",0,DXGI_FORMAT_R32G32B32_FLOAT,0,12,D3D11_INPUT_PER_VERTEX_DATA,0 },
	{ "COLOR",0,DXGI_FORMAT_R32G32B32A32_FLOAT,0,24,D3D11_INPUT_PER_VERTEX_DATA,0 }

};
Hikari::InputLayout::InputLayout(DirectRenderer* renderer,const PdrVertexShader * vShader,const PdrVertexFormat * vFormat)
	:mInputLayout(0)
{
	DirectRenderData* mData = renderer->mData;
	ID3DBlob* vBuffer = vShader->vsBuffer;
	int numElement = ARRAYSIZE(InputLayoutDesc::TestFormat);
	HRESULT hr = mData->mDevice->CreateInputLayout(InputLayoutDesc::TestFormat, numElement,
		vBuffer->GetBufferPointer(), vBuffer->GetBufferSize(),
		&mInputLayout);
	if (FAILED(hr))
	{
		mInputLayout = 0;
	}
}

Hikari::InputLayout::~InputLayout()
{
}