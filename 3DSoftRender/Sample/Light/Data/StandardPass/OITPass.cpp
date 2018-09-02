#include "GraphicsPCH.h"
#include "OITPass.h"
#include "Renderer/Renderer.h"

Hikari::OITPass::OITPass(std::shared_ptr<Renderer> render, vector<shared_ptr<Scene>> scene,
                         std::shared_ptr<PipelineState> pipeline)
	: BasePass(render, scene[0], pipeline)
{
	auto renderTarget = pipeline->GetRenderTarget();
	auto colorTexture = renderTarget->GetTexture(RenderTarget::AttachmentPoint::Color0);
	auto startCount = colorTexture->GetWidth() * colorTexture->GetHeight();

	const ShaderParameter::ShaderInputParameter start_offset =
	{
		ShaderParameter::ShaderInputType::Buffer,
		ShaderParameter::AppendFlag::RAW,
		ShaderParameter::Format::UNKNOWN,
		CPUAccess::None
	};
	mStartOffset = render->CreateBuffer(nullptr, startCount, sizeof(uint32_t), start_offset);

	auto pixCount = startCount * 2;
	const ShaderParameter::ShaderInputParameter pixel_list =
	{
		ShaderParameter::ShaderInputType::StructuredBuffer,
		ShaderParameter::AppendFlag::RAW,
		ShaderParameter::Format::UNKNOWN,
	};
	mPixelList = render->CreateStructuredBuffer(nullptr, pixCount, sizeof(FragmentAndLinkBuffer_STRUCT), pixel_list);
}

Hikari::OITPass::~OITPass()
= default;

void Hikari::OITPass::Visit(Mesh& mesh)
{
}
