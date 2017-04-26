#pragma once
#include "Dx11RenderLIB.h"

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

		BasePass(Renderer* render);
		BasePass(Renderer* render,Scene* scene, PipelineState* pipeline);
		virtual ~BasePass();

		inline void SetDevice(Renderer* render)
		{
			m_RenderDevice = render;
		}
		// Render the pass. This should only be called by the RenderTechnique.
		virtual void PreRender(RenderEventArgs& e) override;
		virtual void Render(RenderEventArgs& e) override;
		virtual void PostRender(RenderEventArgs& e) override;

		// Inherited from Visitor
		virtual void Visit(Scene& scene) override;
		virtual void Visit(Node& node) override;
		virtual void Visit(Mesh& mesh) override;

	protected:
		// PerObject constant buffer data.
		__declspec(align(16)) struct PerObject
		{
			XMMATRIX ModelViewProjection;
			XMMATRIX ModelView;
		};

		void SetRenderEventArgs(RenderEventArgs& e);
		RenderEventArgs& GetRenderEventArgs() const;

		Renderer* GetRenderDevice() const;

		// Set and bind the constant buffer data.
		void SetPerObjectConstantBufferData(PerObject& perObjectData);
		// Bind the constant to the shader.
		void BindPerObjectConstantBuffer(Shader* shader);

	protected:

		PerObject* m_PerObjectData;
		ConstantBuffer* m_PerObjectConstantBuffer;

		RenderEventArgs* m_pRenderEventArgs;

		// The pipeline state that should be used to render this pass.
		PipelineState* m_Pipeline;

		// The scene to render.
		Scene* m_Scene;

		Renderer* m_RenderDevice;
	};
}