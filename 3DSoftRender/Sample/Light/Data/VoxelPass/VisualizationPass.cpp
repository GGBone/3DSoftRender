#include "VisualizationPass.h"
#include "Shader/ShaderParameter.h"
#define ENABLE_BOOST
#include "Event.h"
#undef ENABLE_BOOST
#include "Resource/PipelineState.h"

using namespace Hikari;

void Visualization::SetRenderEventArgs(RenderEventArgs& e)
{
}

RenderEventArgs& Visualization::GetRenderEventArgs() const
{
	// TODO: 在此处插入 return 语句
	return *m_pRenderEventArgs;
}

std::shared_ptr<Renderer> Visualization::GetRenderDevice() const
{
	return m_RenderDevice;
}

void Visualization::SetPerObjectConstantBufferData(PerObject& perObjectData)
{
}

void Visualization::BindPerObjectConstantBuffer(std::shared_ptr<Shader> shader)
{
}

Visualization::Visualization(std::shared_ptr<Renderer> render)
{
}

Visualization::Visualization(std::shared_ptr<Renderer> render, std::shared_ptr<Scene> scene,
                             std::shared_ptr<PipelineState> pipeline)
{
}

Visualization::~Visualization()
{
}

void Visualization::PreRender(RenderEventArgs& e)
{
	ShaderParameter* shaderParams = &e.PipelineState->GetShader(Shader::ShaderType::ComputeShader)->
	                                   GetShaderParameterByName("nodesPool");
}

void Visualization::Render(RenderEventArgs& e)
{
}

void Visualization::PostRender(RenderEventArgs& e)
{
}

void Visualization::Visit(Scene& scene)
{
}

void Visualization::Visit(Node& node)
{
}

void Visualization::Visit(Mesh& mesh)
{
}
