#pragma once
#include "Shader/ShaderParameter.h"
#include "Resource/StructBuffer.h"

namespace Hikari
{
	class ShaderParameterDx11 : public ShaderParameter
	{
	public:
		ShaderParameterDx11();
		ShaderParameterDx11(const std::string& name, UINT slotID, Shader::ShaderType shader_type,
		                    ShaderInputParameter shader_input_param);
		bool is_valid() const override;
		void bind() override;
		void unbind() override;
	};
}
