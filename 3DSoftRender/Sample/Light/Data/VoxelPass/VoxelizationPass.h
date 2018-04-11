#pragma once
#include "Graphics\Dx11RenderLIB.h"

#include "AbstractPass.h"
#include "Math\Base\Float3.h"
#include "Math\Base\Float4.h"
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
	class StructuredBuffer;
	class SamplerState;
	class Buffer;
	class RWBuffer;
	class VoxelizationPass : public AbstractPass
	{
	public:
		typedef AbstractPass base;

		VoxelizationPass(std::shared_ptr<Renderer> render);
		VoxelizationPass(std::shared_ptr<Renderer> render, std::shared_ptr<Scene> scene, std::shared_ptr<PipelineState> pipeline);
		virtual ~VoxelizationPass();

		inline void SetDevice(std::shared_ptr<Renderer> render)
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



		std::shared_ptr<Renderer> GetRenderDevice() const;
	public:
		// PerObject constant buffer data.
		__declspec(align(16)) struct PerObject
		{
			XMMATRIX world;
		};

		__declspec(align(16)) struct PerGeometry
		{
			XMMATRIX zproj;
			XMMATRIX xproj;
			XMMATRIX yproj;

		};
		struct Attri
		{
			Float4 extent;
			Float4 origin;
		};

		struct Voxel
		{
			Float3 pos;
			UINT normal;
			UINT color;
		};
		static bool init;
		void SetRenderEventArgs(RenderEventArgs& e);

		void SetPerObjectConstantData(PerObject& perObjectData, const std::string& name);
		void SetPerGeometryConstantData(PerGeometry& perObjectData, const std::string& name);
		void SetAttriConstantData(Attri& perObjectData, const std::string& name);


		void SetSampler(std::shared_ptr<SamplerState>& samp, const std::string& name);

		UINT valueFragment;
	private:
		
		void BindSampler(const std::string& name);
		void BindAttriConstantBuffer(const std::string& name);
		void BindPerGeometryConstantBuffer(const std::string& name);
		void BindPerObjectConstantBuffer(const std::string& name);

		PerObject m_PerObjData;
		PerGeometry m_PerGeomData;
		Attri m_AttrData;

		std::shared_ptr<ConstantBuffer> m_PerObjectConstantBuffer;
		std::shared_ptr<ConstantBuffer> m_PerGeometryConstantBuffer;
		std::shared_ptr<ConstantBuffer> m_AttriConstantBuffer;
		std::shared_ptr<StructuredBuffer> m_VoxelBuffer;
		std::shared_ptr<RWBuffer> m_VoxelIndexBuffer;

		std::shared_ptr<Buffer> stage;
		std::shared_ptr<SamplerState> m_Sampler;
		std::shared_ptr<RenderEventArgs> m_pRenderEventArgs;

		// The pipeline state that should be used to render this pass.
		std::shared_ptr<PipelineState> m_Pipeline;

		// The scene to render.
		std::shared_ptr<Scene> m_Scene;

		std::shared_ptr<Renderer> m_RenderDevice;

		std::string m_sPerObjCBName = {};
		std::string m_sPerGeoCBName = {};
		std::string m_sAttCBName = {};

		std::string m_sSamplerName = {};


	};
}