#include "GraphicsPCH.h"
#include "Dx11ShaderParameter.h"
#include "Dx11ConstantBuffer.h"
#include "Dx11StructureBuffer.h"
#include "Dx11SamplerState.h"
#include "Resource/StructuredBuffer.h"
using namespace Hikari;

ShaderParameterDx11::ShaderParameterDx11()
	: ShaderParameter()
{
}

ShaderParameterDx11::ShaderParameterDx11(const std::string& name, UINT slotID, Shader::ShaderType shader_type,
                                         ShaderInputParameter shader_input_param)
	: ShaderParameter()
{
	m_sName = name;
	m_ui_slot_ = slotID;
	m_shader_type_ = shader_type;
	m_shader_input_parameter_ = shader_input_param;
}

bool ShaderParameterDx11::is_valid() const
{
	return m_shader_input_parameter_.m_parameterType != ShaderInputType::Invalid;
}


void ShaderParameterDx11::bind()
{
	if (m_constantBuffer)
		m_constantBuffer->bind(m_ui_slot_, m_shader_type_);
	if (m_texture)
		m_texture->bind(m_ui_slot_, m_shader_type_);
	if (m_samplerState)
		m_samplerState->bind(m_ui_slot_, m_shader_type_);
	if (m_structuredBuffer)
		m_structuredBuffer->bind(m_ui_slot_, m_shader_type_);
	if (m_buffer)
		m_buffer->bind(m_ui_slot_, m_shader_type_);
}

void ShaderParameterDx11::unbind()
{
	if (m_constantBuffer)
		m_constantBuffer->unbind(m_ui_slot_, m_shader_type_);
	if (m_texture)
		m_texture->unbind(m_ui_slot_, m_shader_type_);
	if (m_samplerState)
		m_samplerState->unbind(m_ui_slot_, m_shader_type_);
	if (m_structuredBuffer)
		m_structuredBuffer->unbind(m_ui_slot_, m_shader_type_);
	if (m_buffer)
		m_buffer->unbind(m_ui_slot_, m_shader_type_);
}
