#include "GraphicsPCH.h"

#include "Dx11VertexShader.h"
#include "Renderer.h"
#include "Dx11RenderData.h"


Hikari::PdrVertexShader::PdrVertexShader(Renderer *renderer, const VertexShader *vshader)
{
	//Compiler Shader
	
	ID3DBlob* errorBlob = 0;
	ID3D11Device* d3dDevice = renderer->mData->mDevice;
	ID3D11DeviceContext* d3dContext = renderer->mData->mImmediateContext;
	UINT flags = D3DCOMPILE_DEBUG;
	std::string name = vshader->GetProgramName();
	//D3DReadFileToBlob(L"VertexShader.cso",&vsBuffer);
	size_t size = name.length();
	wchar_t* buffer = new wchar_t[size + 1];
	MultiByteToWideChar(CP_ACP, 0, name.c_str(), size, buffer, size * sizeof(wchar_t));
	buffer[size] = 0;

	HRESULT hr;
	hr = D3DCompileFromFile(buffer,nullptr,D3D_COMPILE_STANDARD_FILE_INCLUDE, "VS", "vs_4_0", flags,0, &vsBuffer, &errorBlob);

	
	hr = d3dDevice->CreateVertexShader(vsBuffer->GetBufferPointer(), vsBuffer->GetBufferSize(), 0, &mVShader);
	if (FAILED(hr))
	{
		if (vsBuffer)
			vsBuffer->Release();
	}

	d3dContext->VSSetShader(mVShader, 0, 0);
	delete buffer;
}