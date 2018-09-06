#pragma once
#include "Object.h"
#include "Shader/Shader.h"

namespace Hikari
{
	class BlendState;
	class DepthStencilState;
	class RenderTarget;
	class RasterizerState;
	class Shader;

	class PipelineState : Object
	{
	public:
		typedef std::map<Shader::ShaderType, std::shared_ptr<Shader>> ShaderMap;

		virtual void SetShader(Shader::ShaderType type, std::shared_ptr<Shader> pShader) = 0;
		virtual std::shared_ptr<Shader> GetShader(Shader::ShaderType type) const = 0;
		virtual const ShaderMap& GetShaders() const = 0;

		virtual void SetBlendState(const BlendState& blendState) = 0;
		virtual BlendState& GetBlendState() = 0;

		virtual void SetRasterizerState(const RasterizerState& rasterizerState) = 0;
		virtual RasterizerState& GetRasterizerState() = 0;

		virtual void SetDepthStencilState(const DepthStencilState& depthStencilState) = 0;
		virtual DepthStencilState& GetDepthStencilState() = 0;

		virtual void SetRenderTarget(std::shared_ptr<RenderTarget> renderTarget) = 0;
		virtual std::shared_ptr<RenderTarget> GetRenderTarget() const = 0;

		// Bind this pipeline state for rendering.
		virtual void bind() = 0;
		// Unbind render target and shaders.
		virtual void unbind() = 0;
	};
}
