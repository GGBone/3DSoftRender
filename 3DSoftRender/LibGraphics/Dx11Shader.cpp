#include "Graphics\GraphicsPCH.h"
#include "Graphics\Dx11Shader.h"
using namespace Hikari;
static ShaderParameterDx g_InvalidShaderParameter;


DXGI_FORMAT GetDXGIFormat(const D3D11_SIGNATURE_PARAMETER_DESC& paramDesc);
Hikari::ShaderDx::ShaderDx(std::shared_ptr<DirectRenderer>& renderer)
	:mShaderType(UnKnownShaderType),
	mDevice(nullptr),
	mContext(nullptr),
	vShader(nullptr),
	pShader(nullptr),
	hShader(nullptr),
	dShader(nullptr),
	gShader(nullptr),
	cShader(nullptr),
	mShaderBlob(nullptr),
	mInputlayout(nullptr),
	m_bFileChanged(false)
{
	mDevice = renderer->GetDevice();
	mDevice->GetImmediateContext2(&mContext);
	
}

Shader::ShaderType Hikari::ShaderDx::GetType() const
{
	return mShaderType;
}

void Hikari::ShaderDx::LoadShaderFromString(ShaderType type, const std::string & source, const std::string & sourceFileName, const ShaderMacros & shaderMacros, const std::string & entryPoint, const std::string & profile)
{
	HRESULT hr;
	{
		ID3DBlob* pShaderBlob;
		ID3DBlob* pErrorBlob;
		std::string _profile = profile;
		if (profile == "latest")
		{
			_profile = GetLatestProfile(type);
			if (_profile.empty())
				return;
		}

		std::vector<D3D_SHADER_MACRO> macros;
		for (auto macro : shaderMacros)
		{
			std::string name = macro.first;
			std::string definition = macro.second;

			char* c_name = new char[name.size() + 1];
			char* c_definition = new char[definition.size() + 1];

			strncpy_s(c_name, name.size() + 1, name.c_str(), name.size());
			strncpy_s(c_definition, definition.size() + 1, definition.c_str(), definition.size());

			macros.push_back({ c_name, c_definition });
		}
		macros.push_back({ 0,0 });

		UINT flags = D3DCOMPILE_ENABLE_STRICTNESS;
#if defined (_DEBUG)
		flags |= D3DCOMPILE_DEBUG;
#endif

		hr = D3DCompile((LPCVOID)source.c_str(), source.size(), sourceFileName.c_str(), macros.data(),
			D3D_COMPILE_STANDARD_FILE_INCLUDE, entryPoint.c_str(), _profile.c_str(),
			flags, 0, &pShaderBlob, &pErrorBlob);

		for (D3D_SHADER_MACRO macro : macros)
		{
			delete[] macro.Name;
			delete[] macro.Definition;
		}
		macros.clear();
		mShaderBlob = pShaderBlob;
	}

	ParameterMap ShaderParameter = mShaderParameters;
	Destroy();
	mShaderType = type;
	switch (mShaderType)
	{
	case VertexShader:
		hr = mDevice->CreateVertexShader(mShaderBlob->GetBufferPointer(), mShaderBlob->GetBufferSize(), nullptr, &vShader);
		break;
	case TessellationControlShader:
		hr = mDevice->CreateHullShader(mShaderBlob->GetBufferPointer(), mShaderBlob->GetBufferSize(), nullptr, &hShader);
		break;
	case TessellationEvaluationShader:
		hr = mDevice->CreateDomainShader(mShaderBlob->GetBufferPointer(), mShaderBlob->GetBufferSize(), nullptr, &dShader);
		break;
	case GeometryShader:
		hr = mDevice->CreateGeometryShader(mShaderBlob->GetBufferPointer(), mShaderBlob->GetBufferSize(), nullptr, &gShader);
		break;
	case PixelShader:
		hr = mDevice->CreatePixelShader(mShaderBlob->GetBufferPointer(), mShaderBlob->GetBufferSize(), nullptr, &pShader);
		break;
	case ComputeShader:
		hr = mDevice->CreateComputeShader(mShaderBlob->GetBufferPointer(), mShaderBlob->GetBufferSize(), nullptr, &cShader);
		break;
	default:
		
		break;
	}

	ID3D11ShaderReflection* pReflector;
	hr = D3DReflect(mShaderBlob->GetBufferPointer(), mShaderBlob->GetBufferSize(), IID_ID3D11ShaderReflection, (void**)&pReflector);
	
	D3D11_SHADER_DESC shaderDescription;
	hr = pReflector->GetDesc(&shaderDescription);

	mInputSemantics.clear();
	UINT numInputParameters = shaderDescription.InputParameters;
	std::vector<D3D11_INPUT_ELEMENT_DESC> inputElements;

	for (UINT i = 0; i < numInputParameters; ++i)
	{
		D3D11_INPUT_ELEMENT_DESC inputElement;
		D3D11_SIGNATURE_PARAMETER_DESC parameterSignature;

		pReflector->GetInputParameterDesc(i, &parameterSignature);
		inputElement.SemanticName = parameterSignature.SemanticName;
		inputElement.SemanticIndex = parameterSignature.SemanticIndex;
		inputElement.InputSlot = i;
		inputElement.AlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT;
		if (parameterSignature.Mask == 1)
		{
			inputElement.InputSlotClass = D3D11_INPUT_PER_INSTANCE_DATA;	//WILL Modify
			inputElement.InstanceDataStepRate = 1;

		}
		else
		{
			inputElement.InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;	//WILL Modify

			inputElement.InstanceDataStepRate = 0;

		}
		inputElement.Format = GetDXGIFormat(parameterSignature);
		inputElements.push_back(inputElement);
		mInputSemantics.insert(SemanticMap::value_type(BufferBinding(inputElement.SemanticName, inputElement.SemanticIndex), i));

	}
	if (inputElements.size() > 0)
	{
		hr = mDevice->CreateInputLayout(inputElements.data(), (UINT)inputElements.size(),
			mShaderBlob->GetBufferPointer(), mShaderBlob->GetBufferSize(), &mInputlayout);

	}

	for (UINT i = 0; i < shaderDescription.BoundResources; i++)
	{
		D3D11_SHADER_INPUT_BIND_DESC bindDesc;
		pReflector->GetResourceBindingDesc(i, &bindDesc);

		std::string resourceName = bindDesc.Name;

		ShaderParameter::Type parameterType = ShaderParameter::Type::Invalid;
		switch (bindDesc.Type)
		{
		case D3D_SIT_TEXTURE:
			parameterType = ShaderParameter::Type::Texture;
			break;
		case D3D_SIT_SAMPLER:
			parameterType = ShaderParameter::Type::Sampler;
			break;
		case D3D_SIT_CBUFFER:
		case D3D_SIT_STRUCTURED:
			parameterType = ShaderParameter::Type::Buffer;
			break;
		case D3D_SIT_UAV_RWSTRUCTURED:
		case D3D_SIT_UAV_APPEND_STRUCTURED:
			parameterType = ShaderParameter::Type::RWBuffer;
			break;
		case D3D_SIT_UAV_RWTYPED:
			parameterType = ShaderParameter::Type::RWTexture;
			break;
		}
		std::shared_ptr<ShaderParameterDx> shaderParameter = std::make_shared<ShaderParameterDx>(resourceName, bindDesc.BindPoint, type, parameterType);
		mShaderParameters.insert(ParameterMap::value_type(resourceName, shaderParameter));
	}
	for (auto shaderParameter : ShaderParameter)
	{
		ParameterMap::iterator iter = mShaderParameters.find(shaderParameter.first);
		if (iter != mShaderParameters.end())
		{
			iter->second = shaderParameter.second;
		}
	}
}

bool Hikari::ShaderDx::LoadShaderFromFile(ShaderType shaderType, const std::string & fileName, const ShaderMacros & shaderMacros, const std::string & entryPoint, const std::string & profile)
{
	std::ifstream inputFile(fileName);
	std::string source((std::istreambuf_iterator<char>(inputFile)), std::istreambuf_iterator<char>());

	LoadShaderFromString(shaderType, source, fileName, shaderMacros, entryPoint, profile);
	return true;
}

ShaderParameter& Hikari::ShaderDx::GetShaderParameterByName(const std::string & name) const
{

	ParameterMap::const_iterator iter = mShaderParameters.find(name);
	if (iter != mShaderParameters.end())
	{
		return *(iter->second);
	}

	return g_InvalidShaderParameter;
}

std::string Hikari::ShaderDx::GetLatestProfile(ShaderType type)
{
	D3D_FEATURE_LEVEL featureLevel = mDevice->GetFeatureLevel();
	switch (type)
	{
	case Hikari::Shader::UnKnownShaderType:
		break;
	case Hikari::Shader::VertexShader:
		switch (featureLevel)
		{
		case D3D_FEATURE_LEVEL_9_1:
		case D3D_FEATURE_LEVEL_9_2:
			return "vs_4_0_level_9_1";
			break;
		case D3D_FEATURE_LEVEL_9_3:
			return "vs_4_0_level_9_3";
			break;
		case D3D_FEATURE_LEVEL_10_0:
			return "vs_4_0";
			break;
		case D3D_FEATURE_LEVEL_10_1:
			return "vs_4_1";
			break;
		case D3D_FEATURE_LEVEL_11_0:
		case D3D_FEATURE_LEVEL_11_1:
			return "vs_5_0";
			break;
		default:
			break;
		}
		break;
	case Hikari::Shader::TessellationControlShader:
		switch (featureLevel)
		{
		case D3D_FEATURE_LEVEL_11_0:
		case D3D_FEATURE_LEVEL_11_1:
			return "ds_5_0";
			break;
		default:
			break;
		}
		break;
	case Hikari::Shader::TessellationEvaluationShader:
		switch (featureLevel)
		{
		case D3D_FEATURE_LEVEL_11_0:
		case D3D_FEATURE_LEVEL_11_1:
			return "hs_5_0";
			break;
		default:
			break;
		}
		break;
	case Hikari::Shader::GeometryShader:
		switch (featureLevel)
		{
		case D3D_FEATURE_LEVEL_11_1:
		case D3D_FEATURE_LEVEL_11_0:
			return "gs_5_0";
			break;
		case D3D_FEATURE_LEVEL_10_1:
			return "gs_4_1";
			break;
		case D3D_FEATURE_LEVEL_10_0:
			return "gs_4_0";
			break;
		}
		break;
	case Hikari::Shader::PixelShader:
		switch (featureLevel)
		{
		case D3D_FEATURE_LEVEL_11_1:
		case D3D_FEATURE_LEVEL_11_0:
			return "ps_5_0";
			break;
		case D3D_FEATURE_LEVEL_10_1:
			return "ps_4_1";
			break;
		case D3D_FEATURE_LEVEL_10_0:
			return "ps_4_0";
			break;
		case D3D_FEATURE_LEVEL_9_3:
			return "ps_4_0_level_9_3";
			break;
		case D3D_FEATURE_LEVEL_9_2:
		case D3D_FEATURE_LEVEL_9_1:
			return "ps_4_0_level_9_1";
			break;
		}
		break;
	case Hikari::Shader::ComputeShader:
		switch (featureLevel)
		{
		case D3D_FEATURE_LEVEL_11_1:
		case D3D_FEATURE_LEVEL_11_0:
			return "cs_5_0";
			break;
		case D3D_FEATURE_LEVEL_10_1:
			return "cs_4_1";
			break;
		case D3D_FEATURE_LEVEL_10_0:
			return "cs_4_0";
			break;
		}
		break;
	default:
		break;
	}
	return "";
}

bool Hikari::ShaderDx::HasSemantic(const BufferBinding & binding) const
{
	SemanticMap::const_iterator iter = mInputSemantics.find(binding);
	return iter != mInputSemantics.end();
}

UINT Hikari::ShaderDx::GeetSlotIDBySemantic(const BufferBinding & binding)
{
	SemanticMap::const_iterator iter = mInputSemantics.find(binding);
	if (iter != mInputSemantics.end())
	{
		return iter->second;
	}

	// Some kind of error code or exception...
	return (UINT)-1;
}

void Hikari::ShaderDx::Bind()
{

	for (ParameterMap::value_type value : mShaderParameters)
	{
		value.second->Bind();
	}

	if (vShader)
	{
		mContext->IASetInputLayout(mInputlayout);
		mContext->VSSetShader(vShader, nullptr, 0);
	}
	else if (hShader)
	{
		mContext->HSSetShader(hShader, nullptr, 0);
	}
	else if (dShader)
	{
		mContext->DSSetShader(dShader, nullptr, 0);
	}
	else if (gShader)
	{
		mContext->GSSetShader(gShader, nullptr, 0);
	}
	else if (pShader)
	{
		mContext->PSSetShader(pShader, nullptr, 0);
	}
	else if (cShader)
	{
		mContext->CSSetShader(cShader, nullptr, 0);
	}
}

void Hikari::ShaderDx::UnBind()
{
	for (ParameterMap::value_type value : mShaderParameters)
	{
		value.second->UnBind();
	}

	if (vShader)
	{
		mContext->IASetInputLayout(nullptr);
		mContext->VSSetShader(nullptr, nullptr, 0);
	}
	else if (hShader)
	{
		mContext->HSSetShader(nullptr, nullptr, 0);
	}
	else if (dShader)
	{
		mContext->DSSetShader(nullptr, nullptr, 0);
	}
	else if (gShader)
	{
		mContext->GSSetShader(nullptr, nullptr, 0);
	}
	else if (pShader)
	{
		mContext->PSSetShader(nullptr, nullptr, 0);
	}
	else if (cShader)
	{
		mContext->CSSetShader(nullptr, nullptr, 0);
	}
}

void Hikari::ShaderDx::Dispatch(const Vector3UI & numGroup)
{
	if (mContext && cShader)
	{
		mContext->Dispatch(numGroup.X(), numGroup.Y(), numGroup.Z());
	}
}

void Hikari::ShaderDx::Destroy()
{
}

DXGI_FORMAT GetDXGIFormat(const D3D11_SIGNATURE_PARAMETER_DESC& paramDesc)
{
	DXGI_FORMAT format = DXGI_FORMAT_UNKNOWN;
	if (paramDesc.Mask == 1) // 1 component
	{
		switch (paramDesc.ComponentType)
		{
		case D3D_REGISTER_COMPONENT_UINT32:
		{
			format = DXGI_FORMAT_R32_UINT;
		}
		break;
		case D3D_REGISTER_COMPONENT_SINT32:
		{
			format = DXGI_FORMAT_R32_SINT;
		}
		break;
		case D3D_REGISTER_COMPONENT_FLOAT32:
		{
			format = DXGI_FORMAT_R32_FLOAT;
		}
		break;
		}
	}
	else if (paramDesc.Mask <= 3) // 2 components
	{
		switch (paramDesc.ComponentType)
		{
		case D3D_REGISTER_COMPONENT_UINT32:
		{
			format = DXGI_FORMAT_R32G32_UINT;
		}
		break;
		case D3D_REGISTER_COMPONENT_SINT32:
		{
			format = DXGI_FORMAT_R32G32_SINT;
		}
		break;
		case D3D_REGISTER_COMPONENT_FLOAT32:
		{
			format = DXGI_FORMAT_R32G32_FLOAT;
		}
		break;
		}
	}
	else if (paramDesc.Mask <= 7) // 3 components
	{
		switch (paramDesc.ComponentType)
		{
		case D3D_REGISTER_COMPONENT_UINT32:
		{
			format = DXGI_FORMAT_R32G32B32_UINT;
		}
		break;
		case D3D_REGISTER_COMPONENT_SINT32:
		{
			format = DXGI_FORMAT_R32G32B32_SINT;
		}
		break;
		case D3D_REGISTER_COMPONENT_FLOAT32:
		{
			format = DXGI_FORMAT_R32G32B32_FLOAT;
		}
		break;
		}
	}
	else if (paramDesc.Mask <= 15) // 4 components
	{
		switch (paramDesc.ComponentType)
		{
		case D3D_REGISTER_COMPONENT_UINT32:
		{
			format = DXGI_FORMAT_R32G32B32A32_UINT;
		}
		break;
		case D3D_REGISTER_COMPONENT_SINT32:
		{
			format = DXGI_FORMAT_R32G32B32A32_SINT;
		}
		break;
		case D3D_REGISTER_COMPONENT_FLOAT32:
		{
			format = DXGI_FORMAT_R32G32B32A32_FLOAT;
		}
		break;
		}
	}

	return format;
}

