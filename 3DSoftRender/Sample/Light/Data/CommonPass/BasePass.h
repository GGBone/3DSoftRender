#pragma once

#include "AbstractPass.h"


namespace Hikari
{
	// Base pass provides implementations for functions used by most passes.
	class Shader;
	class ConstantBuffer;
	class Camera;
	class Scene;
	class PipelineState;
	class Query;
	class Renderer;

	class BasePass : public AbstractPass
	{
	public:
		typedef AbstractPass base;

		BasePass(const std::shared_ptr<Renderer>& render);
		BasePass(const std::shared_ptr<Renderer>& render, const std::shared_ptr<Scene>& scene,
		         const std::shared_ptr<PipelineState>& pipeline);
		virtual ~BasePass();

		void SetDevice(const std::shared_ptr<Renderer>& render)
		{
			m_RenderDevice = render;
		}

		// Render the pass. This should only be called by the RenderTechnique.
		void PreRender(RenderEventArgs& e) override;
		void Render(RenderEventArgs& e) override;
		void PostRender(RenderEventArgs& e) override;

		// Inherited from Visitor
		void Visit(Scene& scene) override;
		void Visit(Node& node) override;
		void Visit(Mesh& mesh) override;

	protected:
		// PerObject constant buffer data.
		__declspec(align(16)) struct PerObject
		{
			XMMATRIX ModelViewProjection;
			XMMATRIX ModelView;
		};

		void SetRenderEventArgs(RenderEventArgs& e);
		RenderEventArgs& GetRenderEventArgs() const;

		std::shared_ptr<Renderer> GetRenderDevice() const;

		// set and bind the constant buffer data.
		void SetPerObjectConstantBufferData(PerObject& perObjectData);
		// Bind the constant to the shader.
		void BindPerObjectConstantBuffer(std::shared_ptr<Shader> shader);

	protected:

		std::shared_ptr<ConstantBuffer> m_PerObjectConstantBuffer{};

		std::shared_ptr<RenderEventArgs> m_pRenderEventArgs{};

		// The pipeline state that should be used to render this pass.
		std::shared_ptr<PipelineState> m_Pipeline{};

		// The scene to render.
		std::shared_ptr<Scene> m_Scene{};

		std::shared_ptr<Renderer> m_RenderDevice{};
	};
}
