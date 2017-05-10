#pragma once
#include "Dx11RenderLIB.h"

#include "AbstractPass.h"
#include "Float3.h"
#include "Float4.h"
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

		VoxelizationPass(Renderer* render);
		VoxelizationPass(Renderer* render, Scene* scene, PipelineState* pipeline);
		virtual ~VoxelizationPass();

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



		Renderer* GetRenderDevice() const;
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
		struct cbAttri
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

		void SetPerObjectConstantBufferData(PerObject& perObjectData);

		void SetPerGeometryConstantBufferData(PerGeometry& perObjectData);


		void SetSampler(SamplerState* samp, const std::string& name);
		void SetCbAttriConstantBufferData(ConstantBuffer* perObjectData, const std::string& name);
		void SetGeometryConstantBuffer(ConstantBuffer* buffer, const std::string& name);
		void SetVoxelBuffer(StructuredBuffer* buffer, const std::string& name);
		void SetIndexBuffer(RWBuffer* buffer, const std::string& name);

		UINT valueFragment;
	private:
		
		void BindSampler(const std::string& name);
		void BindCbAttriConstantBuffer(const std::string& name);
		void BindPerGeometryConstantBuffer(const std::string& name);
		void BindPerObjectConstantBuffer(const std::string& name);

		PerObject* m_PerObjectData;

		ConstantBuffer* m_PerObjectConstantBuffer;
		ConstantBuffer* m_PerGeometryConstantBuffer;
		ConstantBuffer* m_AttriConstantBuffer;
		StructuredBuffer* m_VoxelBuffer;
		RWBuffer* m_VoxelIndexBuffer;

		Buffer* stage;
		SamplerState* m_Sampler;
		RenderEventArgs* m_pRenderEventArgs;

		// The pipeline state that should be used to render this pass.
		PipelineState* m_Pipeline;

		// The scene to render.
		Scene* m_Scene;

		Renderer* m_RenderDevice;
	};
}