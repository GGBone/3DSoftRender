#include "GraphicsPCH.h"

#include "Dx11VertexShader.h"
#include "Renderer.h"
#include "Dx11RenderData.h"


Hikari::PdrVertexShader::PdrVertexShader(DirectRenderer *renderer, const VertexShader *vshader)
	:mConstantBuffer(0)
{
	//Compiler Shader

	ID3DBlob* errorBlob = 0;
	ID3D11Device* d3dDevice = renderer->mData->mDevice;
	ID3D11DeviceContext* d3dContext = renderer->mData->mImmediateContext;
	UINT flags = D3DCOMPILE_DEBUG;
	std::string name = vshader->GetFileName();
	//D3DReadFileToBlob(L"VertexShader.cso",&vsBuffer);
	size_t size = name.length();
	wchar_t* buffer = new wchar_t[size + 1];
	MultiByteToWideChar(CP_ACP, 0, name.c_str(), size, buffer, size * sizeof(wchar_t));
	buffer[size] = 0;

	int numInputs = vshader->GetNumInputs();
	HRESULT hr;
	hr = D3DCompileFromFile(buffer, nullptr, D3D_COMPILE_STANDARD_FILE_INCLUDE, vshader->GetInputName(numInputs - 1).c_str(), "vs_5_0", flags, 0, &vsBuffer, &errorBlob);
	DWORD error = GetLastError();

	hr = d3dDevice->CreateVertexShader(vsBuffer->GetBufferPointer(), vsBuffer->GetBufferSize(), 0, &mVShader);
	if (FAILED(hr))
	{
		if (vsBuffer)
			vsBuffer->Release();
	}
	d3dContext->VSSetShader(mVShader, 0, 0);
	delete buffer;
}

void Hikari::PdrVertexShader::Enable(DirectRenderer* renderer, const VertexShader* vshader, const ShaderParameters* param)
{
	ID3D11Device* device = renderer->mData->mDevice;
	ID3D11DeviceContext* context = renderer->mData->mImmediateContext;
	int numOfConstant = vshader->GetNumConstants();
	if (numOfConstant != 0)
	{
		if (mConstantBuffer == nullptr)
		{
			mConstantBuffer = new ID3D11Buffer*[numOfConstant];

			//Reflect to Get the ConstantBuffer size
			ID3D11ShaderReflection* pReflection = NULL;
			D3DReflect(vsBuffer->GetBufferPointer(), vsBuffer->GetBufferSize(), IID_ID3D11ShaderReflection,
				(void**)&pReflection);
			D3D11_SHADER_DESC shaderDesc;
			pReflection->GetDesc(&shaderDesc);
			const UINT numOfConstantBufferInShader = shaderDesc.ConstantBuffers;
			if (numOfConstantBufferInShader != numOfConstant) //Error
				return;

			ID3D11ShaderReflectionConstantBuffer* constantBuffer;
			D3D11_SHADER_BUFFER_DESC shaderBufferDesc;
			//Init Constant Buffer
			for (int i = 0; i < 4; ++i)
			{
				constantBuffer = pReflection->GetConstantBufferByIndex(i);
				constantBuffer->GetDesc(&shaderBufferDesc);

				D3D11_BUFFER_DESC bd;
				ZeroMemory(&bd, sizeof(bd));
				bd.Usage = D3D11_USAGE_DEFAULT;
				bd.ByteWidth = shaderBufferDesc.Size;
				bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
				bd.CPUAccessFlags = 0;
				HRESULT hr = device->CreateBuffer(&bd, NULL, mConstantBuffer + i);
			}
			//Update Data
			for (int i = 0; i < numOfConstant; ++i)
			{
				int p = sizeof(param->GetConstant(i)->GetData());
				if (mConstantBuffer != nullptr)
					context->UpdateSubresource(*(mConstantBuffer + i), 0, NULL, param->GetConstant(i)->GetData(), 0, 0);
			}
			//VSSetConstant
			context->VSSetConstantBuffers(0, numOfConstant, mConstantBuffer);
		}
		
	}
	
}