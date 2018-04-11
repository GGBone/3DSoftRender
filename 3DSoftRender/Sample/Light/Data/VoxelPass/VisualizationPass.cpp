#include "VisualizationPass.h"
#include "Graphics\PipelineState.h"
#include "Graphics\Renderer.h"
#include "Graphics\Dx11ShaderParameter.h"
using namespace Hikari;

void Hikari::Visualization::SetRenderEventArgs(RenderEventArgs & e)
{
}

RenderEventArgs & Hikari::Visualization::GetRenderEventArgs() const
{
	// TODO: 在此处插入 return 语句
	return *m_pRenderEventArgs;
}

std::shared_ptr<Renderer> Hikari::Visualization::GetRenderDevice() const
{
	return m_RenderDevice;
}

void Hikari::Visualization::SetPerObjectConstantBufferData(PerObject & perObjectData)
{
}

void Hikari::Visualization::BindPerObjectConstantBuffer(std::shared_ptr<Shader> shader)
{
}

Hikari::Visualization::Visualization(std::shared_ptr<Renderer> render)
{
}

Hikari::Visualization::Visualization(std::shared_ptr<Renderer> render, std::shared_ptr<Scene> scene, std::shared_ptr<PipelineState> pipeline)
{
}

Hikari::Visualization::~Visualization()
{
}

void Hikari::Visualization::PreRender(RenderEventArgs & e)
{
	ShaderParameter* shaderParams = &e.PipelineState->GetShader(Shader::ShaderType::ComputeShader)->GetShaderParameterByName("nodesPool");
	
}

void Hikari::Visualization::Render(RenderEventArgs & e)
{
}

void Hikari::Visualization::PostRender(RenderEventArgs & e)
{
}

void Hikari::Visualization::Visit(Scene & scene)
{
}

void Hikari::Visualization::Visit(Node & node)
{
}

void Hikari::Visualization::Visit(Mesh & mesh)
{
}
