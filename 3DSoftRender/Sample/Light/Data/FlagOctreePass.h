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
	class Texture;
	class FlagOctreePass : public AbstractPass
	{
	public:
		typedef AbstractPass base;

		FlagOctreePass(Renderer* render, Scene* scene, PipelineState* pipeline);
		virtual ~FlagOctreePass();

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
		virtual void Visit(Hikari::Node& node) override;
		virtual void Visit(Mesh& mesh) override;

	public:
		struct  CBInfo
		{
			UINT curLevel;
			UINT totalLevel;
			UINT sumVoxels;
			UINT curNode;
		};
		
		struct Node
		{
			UINT brickPtr;
			UINT childPtr;
		};

		struct  CBGroupInfo
		{
			UINT groupInfo[3];
		};
		struct  CBBrickInfo
		{
			UINT extent[3];
		};
		struct NodesPool
		{
			NodesPool() { uav = nullptr; srv = nullptr; }
			~NodesPool() { uav->Release(); srv->Release(); }
			ID3D11UnorderedAccessView* uav;
			ID3D11ShaderResourceView* srv;
		};

		struct BricksPool
		{
			BricksPool() 
			{ 
				uav[0] = nullptr; uav[1] = nullptr; uav[2] = nullptr;
			}
			~BricksPool() 
			{
				uav[0]->Release(); uav[1]->Release(); uav[2]->Release();
			}
			ID3D11UnorderedAccessView* uav[3];
		};

		Renderer* GetRenderDevice() const;

		// Set and bind the constant buffer data.
		UINT m_TotalVoxel = 0;
		UINT m_TotalNode = 0;
		UINT m_TotalLevel = 0;
		UINT m_TotalBrick = 0;
	public:
		void SetConstantInfo(ConstantBuffer* buffer,const std::string& name);
		void SetConstantGroup(ConstantBuffer* buffer, const std::string& name);
		void SetConstantBrick(ConstantBuffer* buffer, const std::string& name);

		void SetNodeBuffer(StructuredBuffer* buffer, const std::string& name);
		void SetNumNode(RWBuffer* rwBuffer, const std::string& name);
		void SetNodeIndex(RWBuffer* rwBuffer, const std::string& name);
		void SetBrickIndex(RWBuffer* rwBuffer, const std::string& name);
		void SetTotalNode(UINT totalNode);
		void SetTotalLevel(UINT totalLevel);
		Buffer* GetStage() const;
		void SetComputeShaders(Shader*[]);
	private:
		ConstantBuffer* m_cbInfo;
		ConstantBuffer* m_groupInfo;
		ConstantBuffer* m_BrickInfo;
		Shader* m_shaders[4];
		static bool init;
		StructuredBuffer* m_NodePool;
		RWBuffer* m_NumNode;
		RWBuffer* m_BrickInedx;
		RWBuffer* m_NodeIndex;

		StructuredBuffer* m_fragmentList;

		Texture* m_BricksPool[3];
		Buffer* stage;
		std::vector<UINT>	   mNumNodePerLevel;
		RenderEventArgs* m_pRenderEventArgs;

		// The pipeline state that should be used to render this pass.
		PipelineState* m_Pipeline;

		// The scene to render.
		Scene* m_Scene;

		Renderer* m_RenderDevice;
	};
}