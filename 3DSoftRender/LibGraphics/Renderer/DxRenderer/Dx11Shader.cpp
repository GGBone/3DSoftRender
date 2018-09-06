#include <GraphicsPCH.h>

#include <Renderer/DxRenderer/Dx11Renderer.h>
#include "Renderer/DxRenderer/Dx11Shader.h"
#include <Renderer/DxRenderer/Dx11ShaderParameter.h>

using namespace Hikari;
/**
 * \brief global default param
 */
static ShaderParameterDx11 g_invalid_shader_parameter;


DXGI_FORMAT get_dxgi_format(const D3D11_SIGNATURE_PARAMETER_DESC& param_desc);

ShaderDx::ShaderDx(const std::shared_ptr<DirectRenderer>& renderer)
{
	mDevice = renderer->GetDevice();
	mDevice->GetImmediateContext2(&mContext);
}

Shader::ShaderType ShaderDx::GetType() const
{
	return mShaderType;
}

void ShaderDx::LoadShaderFromString(ShaderType type, const std::string& source, const std::string& sourceFileName,
                                    const ShaderMacros& shaderMacros, const std::string& entryPoint,
                                    const std::string& profile)
{
	HRESULT hr;

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

		macros.push_back({c_name, c_definition});
	}
	macros.push_back({nullptr, nullptr});

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


	auto& shader_param_ref = mShaderParameters;
	Destroy();
	mShaderType = type;
	switch (mShaderType)
	{
	case VertexShader:
		hr = mDevice->CreateVertexShader(mShaderBlob->GetBufferPointer(), mShaderBlob->GetBufferSize(), nullptr,
		                                 &vShader);
		break;
	case TessellationControlShader:
		hr = mDevice->CreateHullShader(mShaderBlob->GetBufferPointer(), mShaderBlob->GetBufferSize(), nullptr,
		                               &hShader);
		break;
	case TessellationEvaluationShader:
		hr = mDevice->CreateDomainShader(mShaderBlob->GetBufferPointer(), mShaderBlob->GetBufferSize(), nullptr,
		                                 &dShader);
		break;
	case GeometryShader:
		hr = mDevice->CreateGeometryShader(mShaderBlob->GetBufferPointer(), mShaderBlob->GetBufferSize(), nullptr,
		                                   &gShader);
		break;
	case PixelShader:
		hr = mDevice->CreatePixelShader(mShaderBlob->GetBufferPointer(), mShaderBlob->GetBufferSize(), nullptr,
		                                &pShader);
		break;
	case ComputeShader:
		hr = mDevice->CreateComputeShader(mShaderBlob->GetBufferPointer(), mShaderBlob->GetBufferSize(), nullptr,
		                                  &cShader);
		break;
	default:

		break;
	}

	ID3D11ShaderReflection* pReflector;
	hr = D3DReflect(mShaderBlob->GetBufferPointer(), mShaderBlob->GetBufferSize(), IID_ID3D11ShaderReflection,
	                reinterpret_cast<void**>(&pReflector));

	D3D11_SHADER_DESC shaderDescription;
	hr = pReflector->GetDesc(&shaderDescription);

	mInputSemantics.clear();
	const auto num_input_parameters = shaderDescription.InputParameters;
	std::vector<D3D11_INPUT_ELEMENT_DESC> inputElements{};

	for (UINT i = 0; i < num_input_parameters; ++i)
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
			inputElement.InputSlotClass = D3D11_INPUT_PER_INSTANCE_DATA; //WILL Modify
			inputElement.InstanceDataStepRate = 1;
		}
		else
		{
			inputElement.InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA; //WILL Modify

			inputElement.InstanceDataStepRate = 0;
		}
		inputElement.Format = get_dxgi_format(parameterSignature);
		inputElements.push_back(inputElement);
		mInputSemantics.insert(
			SemanticMap::value_type(BufferBinding(inputElement.SemanticName, inputElement.SemanticIndex), i));
	}
	if (inputElements.size() > 0)
	{
		hr = mDevice->CreateInputLayout(inputElements.data(), static_cast<UINT>(inputElements.size()),
		                                mShaderBlob->GetBufferPointer(), mShaderBlob->GetBufferSize(), &mInputlayout);
	}

	for (UINT i = 0; i < shaderDescription.BoundResources; i++)
	{
		D3D11_SHADER_INPUT_BIND_DESC bindDesc;
		pReflector->GetResourceBindingDesc(i, &bindDesc);

		std::string resourceName = bindDesc.Name;

		ShaderParameterDx11::ShaderInputParameter parameter_Input{};
		parameter_Input.m_cpuAccess = CPUAccess::None;
		parameter_Input.m_gpuAccess = GPUAccess::Read;

		switch (bindDesc.Type)
		{
		case D3D_SIT_CBUFFER:
			{
				parameter_Input.m_parameterType = ShaderParameterDx11::ShaderInputType::ConstantBuffer;
			}
			break;
		case D3D_SIT_TEXTURE:
			{
				parameter_Input.m_parameterType = ShaderParameterDx11::ShaderInputType::Texture;
			}
			break;
		case D3D_SIT_SAMPLER:
			{
				parameter_Input.m_parameterType = ShaderParameterDx11::ShaderInputType::Sampler;
			}
			break;
		case D3D_SIT_UAV_RWTYPED:
			{
				parameter_Input.m_gpuAccess = GPUAccess::ReadWrite;
				if (bindDesc.Dimension == D3D11_UAV_DIMENSION_BUFFER)
				{
					parameter_Input.m_parameterType = ShaderParameterDx11::ShaderInputType::Buffer;
					parameter_Input.m_dimension = ShaderParameterDx11::Dimension::Buffer;
				}
				else if (bindDesc.Dimension == D3D11_UAV_DIMENSION_TEXTURE2D)
				{
					parameter_Input.m_parameterType = ShaderParameterDx11::ShaderInputType::Texture;
					parameter_Input.m_dimension = ShaderParameterDx11::Dimension::TEXTURE2D;
				}
				else if (bindDesc.Dimension == D3D11_UAV_DIMENSION_TEXTURE3D)
				{
					parameter_Input.m_parameterType = ShaderParameterDx11::ShaderInputType::Texture;
					parameter_Input.m_dimension = ShaderParameterDx11::Dimension::TEXTURE3D;
				}
			}
			break;
		case D3D_SIT_STRUCTURED:
			{
				parameter_Input.m_parameterType = ShaderParameterDx11::ShaderInputType::StructuredBuffer;
			}
			break;
		case D3D_SIT_UAV_RWSTRUCTURED:
			{
				parameter_Input.m_parameterType = ShaderParameterDx11::ShaderInputType::StructuredBuffer;
				parameter_Input.m_gpuAccess = GPUAccess::ReadWrite;
			}
			break;
		case D3D_SIT_BYTEADDRESS:
			{
				parameter_Input.m_parameterType = ShaderParameterDx11::ShaderInputType::Buffer;
			}
			break;
		case D3D_SIT_UAV_RWBYTEADDRESS:
			{
				//RW
				parameter_Input.m_parameterType = ShaderParameterDx11::ShaderInputType::Buffer;
				parameter_Input.m_gpuAccess = GPUAccess::ReadWrite;
			}
			break;
		case D3D_SIT_UAV_APPEND_STRUCTURED:
			{
				parameter_Input.m_parameterType = ShaderParameterDx11::ShaderInputType::StructuredBuffer;
				parameter_Input.m_appendFlag = ShaderParameterDx11::AppendFlag::APPEND;
			}
			break;
		case D3D_SIT_UAV_CONSUME_STRUCTURED:
			{
				parameter_Input.m_parameterType = ShaderParameterDx11::ShaderInputType::StructuredBuffer;
			}
			break;
		case D3D_SIT_UAV_RWSTRUCTURED_WITH_COUNTER:
			{
				parameter_Input.m_parameterType = ShaderParameterDx11::ShaderInputType::StructuredBuffer;
				parameter_Input.m_appendFlag = ShaderParameterDx11::AppendFlag::COUNTER;
				parameter_Input.m_gpuAccess = GPUAccess::ReadWrite;
			}
			break;
		}
		std::shared_ptr<ShaderParameterDx11> shaderParameter = std::make_shared<ShaderParameterDx11>(
			resourceName, bindDesc.BindPoint, type, parameter_Input);
		mShaderParameters.insert(ParameterMap::value_type(resourceName, shaderParameter));
	}
	for (const auto shaderParameter : shader_param_ref)
	{
		ParameterMap::iterator iter = mShaderParameters.find(shaderParameter.first);
		if (iter != mShaderParameters.end())
		{
			iter->second = shaderParameter.second;
		}
	}
}

bool ShaderDx::LoadShaderFromFile(ShaderType shaderType, const std::string& fileName, const ShaderMacros& shaderMacros,
                                  const std::string& entryPoint, const std::string& profile)
{
	std::ifstream inputFile(fileName);
	std::string source((std::istreambuf_iterator<char>(inputFile)), std::istreambuf_iterator<char>());

	LoadShaderFromString(shaderType, source, fileName, shaderMacros, entryPoint, profile);
	return true;
}

ShaderParameter& ShaderDx::GetShaderParameterByName(const std::string& name) const
{
	ParameterMap::const_iterator iter = mShaderParameters.find(name);
	if (iter != mShaderParameters.end())
	{
		return *(iter->second);
	}

	return g_invalid_shader_parameter;
}

std::string ShaderDx::GetLatestProfile(ShaderType type)
{
	D3D_FEATURE_LEVEL featureLevel = mDevice->GetFeatureLevel();
	switch (type)
	{
	case UnKnownShaderType:
		break;
	case VertexShader:
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
	case TessellationControlShader:
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
	case TessellationEvaluationShader:
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
	case GeometryShader:
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
	case PixelShader:
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
	case ComputeShader:
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

bool ShaderDx::HasSemantic(const BufferBinding& binding) const
{
	SemanticMap::const_iterator iter = mInputSemantics.find(binding);
	return iter != mInputSemantics.end();
}

UINT ShaderDx::GetSlotIDBySemantic(const BufferBinding& binding)
{
	SemanticMap::const_iterator iter = mInputSemantics.find(binding);
	if (iter != mInputSemantics.end())
	{
		return iter->second;
	}

	// Some kind of error code or exception...
	return (UINT)-1;
}

void ShaderDx::Bind()
{
	for (auto value : mShaderParameters)
	{
		value.second->bind();
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

void ShaderDx::UnBind()
{
	for (ParameterMap::value_type value : mShaderParameters)
	{
		value.second->unbind();
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

void ShaderDx::Dispatch(const Vector3UI& numGroup)
{
	if (mContext && cShader)
	{
		mContext->Dispatch(numGroup.X(), numGroup.Y(), numGroup.Z());
	}
}

void ShaderDx::Destroy()
{
}

DXGI_FORMAT get_dxgi_format(const D3D11_SIGNATURE_PARAMETER_DESC& paramDesc)
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
