#include "GraphicsPCH.h"
#include "ShadowPass.h"
#include "WindowApplicationEngine.h"
#include "SceneGraph/Camera.h"
#include "Renderer/DxRenderer/Dx11Renderer.h"
#include "resource/RasterizerState.h"


void Hikari::ShadowPass::PreRender(RenderEventArgs & e)
{
	if (e.PipelineState)
	{
		DebugBreak();
	}
	auto viewport = m_Pipeline->GetRasterizerState().GetViewports()[0];
	if (shadow_camera_vec_.size() != WindowApplicationEngine::g_Setting.Lights.size())
	{
		auto begin = WindowApplicationEngine::g_Setting.Lights.begin();
		auto end = WindowApplicationEngine::g_Setting.Lights.end();
		shadow_camera_vec_.clear();
		for (auto iter = begin; iter != end; ++iter)
		{
			auto shadow_camera = make_shared<Camera>();
			shadow_camera->LookAt({ iter->m_PositionWS[0],iter->m_PositionWS[1],iter->m_PositionWS[2] }, { 0.0,0.0,0.0 }, XMFLOAT3(0.0, 1.0, 0.0));
			shadow_camera->set_project_lh(90.0f, viewport.Width / (float)viewport.Height, 0.1f, 5000.0f);
			shadow_camera->UpdateViewMatrix();

			shadow_camera_vec_.push_back(shadow_camera);
			shadow_camera.reset();
		}
	}
	auto begin = shadow_camera_vec_.begin();
	auto end = shadow_camera_vec_.end();
	for (auto iter = begin; iter != end; ++iter)
	{
		RenderEventArgs render_args(*this, e.ElapsedTime, e.TotalTime, e.FrameCounter, iter->get(), m_Pipeline.get());
		BasePass::PreRender(render_args);
	}
}

void Hikari::ShadowPass::Render(RenderEventArgs & e)
{
	if (e.PipelineState)
	{
		DebugBreak();
	}
	auto begin = shadow_camera_vec_.begin();
	auto end = shadow_camera_vec_.end();
	for (auto iter = begin; iter != end; ++iter)
	{
		RenderEventArgs render_args(*this, e.ElapsedTime, e.TotalTime, e.FrameCounter, iter->get(), m_Pipeline.get());
		BasePass::Render(render_args);
	}
}

Hikari::ShadowPass::ShadowPass(std::shared_ptr<Renderer> render, shared_ptr<Scene> scene,
                               std::shared_ptr<PipelineState> pipeline)
	: BasePass(render, scene, pipeline)
{
	shadow_maps_ = render->CreateRenderTarget();
}


