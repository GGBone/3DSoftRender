#pragma once
#include "Object.h"
#include "Shader.h"

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
		typedef std::map<Shader::ShaderType, Shader* > ShaderMap;

		virtual void SetShader(Shader::ShaderType type, Shader* pShader) = 0;
		virtual Shader* GetShader(Shader::ShaderType type) const = 0;
		virtual const ShaderMap& GetShaders() const = 0;

		virtual void SetBlendState(const BlendState& blendState) = 0;
		virtual BlendState& GetBlendState() = 0;

		virtual void SetRasterizerState(const RasterizerState& rasterizerState) = 0;
		virtual RasterizerState& GetRasterizerState() = 0;

		virtual void SetDepthStencilState(const DepthStencilState& depthStencilState) = 0;
		virtual DepthStencilState& GetDepthStencilState() = 0;

		virtual void SetRenderTarget(RenderTarget* renderTarget) = 0;
		virtual RenderTarget* GetRenderTarget() const = 0;

		// Bind this pipeline state for rendering.
		virtual void Bind() = 0;
		// Unbind render target and shaders.
		virtual void UnBind() = 0;
	};
}