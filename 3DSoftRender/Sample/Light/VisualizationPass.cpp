#include "VisualizationPass.h"
using namespace Hikari;

void Hikari::Visualization::SetRenderEventArgs(RenderEventArgs & e)
{
}

RenderEventArgs & Hikari::Visualization::GetRenderEventArgs() const
{
	// TODO: �ڴ˴����� return ���
	return *m_pRenderEventArgs;
}

Renderer * Hikari::Visualization::GetRenderDevice() const
{
	return nullptr;
}

void Hikari::Visualization::SetPerObjectConstantBufferData(PerObject & perObjectData)
{
}

void Hikari::Visualization::BindPerObjectConstantBuffer(Shader * shader)
{
}

Hikari::Visualization::Visualization(Renderer * render)
{
}

Hikari::Visualization::Visualization(Renderer * render, Scene * scene, PipelineState * pipeline)
{
}

Hikari::Visualization::~Visualization()
{
}

void Hikari::Visualization::PreRender(RenderEventArgs & e)
{
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
