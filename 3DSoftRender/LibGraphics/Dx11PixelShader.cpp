#include "GraphicsPCH.h"
#include "Dx11PixelShader.h"
#include "Renderer.h"
#include "Dx11RenderData.h"
Hikari::PdrPixelShader::PdrPixelShader(DirectRenderer * renderer, const PixelShader * pshader)
	:mConstantBuffer(0)
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

	int numInputs = pshader->GetNumInputs();
	HRESULT hr;
	hr = D3DCompileFromFile(buffer, nullptr, D3D_COMPILE_STANDARD_FILE_INCLUDE, pshader->GetInputName(numInputs - 1).c_str(), "ps_4_0", flags, 0, &psBuffer, &errorBlob);
	DWORD error = GetLastError();

	hr = d3dDevice->CreatePixelShader(psBuffer->GetBufferPointer(), psBuffer->GetBufferSize(), 0, &mPShader);
	delete[] buffer;
	buffer = 0;
	d3dContext->PSSetShader(mPShader, 0, 0);
}

void Hikari::PdrPixelShader::Enable(DirectRenderer * renderer, const PixelShader * pShader, const ShaderParameters* param)
{
	ID3D11Device* device = renderer->mData->mDevice;
	ID3D11DeviceContext* context = renderer->mData->mImmediateContext;
	const int numOfConstant = pShader->GetNumConstants();
	if (numOfConstant != 0)
	{
		if (mConstantBuffer == nullptr)
		{
			mConstantBuffer = new ID3D11Buffer*[numOfConstant];

			//Reflect to Get the ConstantBuffer size
			ID3D11ShaderReflection* pReflection = NULL;
			D3DReflect(psBuffer->GetBufferPointer(), psBuffer->GetBufferSize(), IID_ID3D11ShaderReflection,
				(void**)&pReflection);
			D3D11_SHADER_DESC shaderDesc;
			pReflection->GetDesc(&shaderDesc);
			const UINT numOfConstantBufferInShader = shaderDesc.ConstantBuffers;
			if (numOfConstantBufferInShader != numOfConstant) //Error
				return;

			ID3D11ShaderReflectionConstantBuffer* constantBuffer;
			D3D11_SHADER_BUFFER_DESC shaderBufferDesc;
			//Init Constant Buffer
			for (int i = 0; i < numOfConstant; ++i)
			{
				constantBuffer = pReflection->GetConstantBufferByIndex(i);
				constantBuffer->GetDesc(&shaderBufferDesc);

				D3D11_BUFFER_DESC bd;
				ZeroMemory(&bd, sizeof(bd));
				bd.Usage = D3D11_USAGE_DEFAULT;
				bd.ByteWidth = shaderBufferDesc.Size;
				bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
				bd.CPUAccessFlags = 0;
				device->CreateBuffer(&bd, NULL, mConstantBuffer + i);
			}
		}
		//Update Data
		for (int i = 0; i < numOfConstant; ++i)
		{
			context->UpdateSubresource(*(mConstantBuffer + i), 0, NULL, param->GetConstant(i)->GetData(), 0, 0);
		}

		//VSSetConstant
		context->PSSetConstantBuffers(0, numOfConstant, mConstantBuffer);
	}
	//context->PSSetShader(mPShader, 0, 0);
}
