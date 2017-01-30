#include "GraphicsPCH.h"
#include "Dx11PixelShader.h"
#include "Renderer.h"
#include "Dx11RenderData.h"
Hikari::PdrPixelShader::PdrPixelShader(Renderer * renderer, const PixelShader * pshader)
{
	ID3DBlob* errorBlob = 0;
	ID3D11Device* d3dDevice = renderer->mData->mDevice;

	ID3D11DeviceContext* d3dContext = renderer->mData->mImmediateContext;
	UINT flags = D3DCOMPILE_DEBUG;
	std::string name = pshader->GetProgramName();

	size_t size = name.length();
	wchar_t* buffer = new wchar_t[size + 1];
	MultiByteToWideChar(CP_ACP, 0, name.c_str(), size, buffer, size * sizeof(wchar_t));
	buffer[size] = 0;

	HRESULT hr;
	hr = D3DCompileFromFile(buffer, nullptr, D3D_COMPILE_STANDARD_FILE_INCLUDE, "PS", "ps_4_0", flags, 0, &psBuffer, &errorBlob);

	
	hr = d3dDevice->CreatePixelShader(psBuffer->GetBufferPointer(), psBuffer->GetBufferSize(), 0, &mPShader);
	psBuffer->Release();
	delete buffer;
	buffer = 0;
	d3dContext->PSSetShader(mPShader, 0, 0);
}
