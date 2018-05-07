#pragma once
#include "Graphics\Dx11RenderLIB.h"

#include "AbstractPass.h"
#include "Math\Base\Float3.h"
#include "Math\Base\Float4.h"
#include "VoxelizationPass.h"
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
	class BufferBase;
	class Buffer;
	class Texture;
	class Renderer;
	struct BufferBinding;
	class FlagOctreePass : public AbstractPass
	{
	public:
		typedef AbstractPass base;

		FlagOctreePass(std::shared_ptr<Renderer> render, std::shared_ptr<Scene> scene, std::shared_ptr<PipelineState> pipeline);
		virtual ~FlagOctreePass();

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

	public:
		struct  CBInfo
		{
			UINT curLevel;
			UINT totalLevel;
			UINT sumVoxels;
			UINT curNode;
		};
		
		struct VisualPackage
		{
			XMFLOAT4X4 world;
			Float4  normal;
			Float4  color;
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

		std::shared_ptr<Renderer> GetRenderDevice() const;

		// Set and bind the constant buffer data.
		UINT m_TotalVoxel = 0;
		UINT m_TotalNode = 0;
		UINT m_TotalLevel = 0;
		UINT m_TotalBrick = 0;
	public:
		void SetConstantInfo(CBInfo& data,const std::string& name);
		void SetConstantGroup(CBGroupInfo& data, const std::string& name);
		void SetConstantBrick(CBBrickInfo& data, const std::string& name);
		void SetAttriConstant(VoxelizationPass::Attri& data, const std::string& name);

		void SetVisualPool(const std::vector<VisualPackage>& data, const std::string& name);
		void SetVisualIndex(const std::vector<UINT>&data, const std::string& name);

		//void SetNodeBuffer(std::shared_ptr<StructuredBuffer> buffer, const std::string& name);
		void SetNumOfNodes(std::vector<UINT>& numOfNodes, const std::string& name);
		void SetNodeIndex(std::vector<UINT>& nodeIndex, const std::string& name);

		
		void SetBrickIndex(std::vector<UINT>&  brickIndex, const std::string& name);
		void SetTotalNode(UINT totalNode);
		void SetTotalLevel(UINT totalLevel);

		void SetComputeShaders(std::shared_ptr<Shader>[], size_t size);
	private:
		void BindBrickIndex(const std::string& name);
		void BindNodeIndex(const std::string& name);
		void BindNumOfNodes(const std::string& name);
		void BindConstantInfo(const std::string& name);
		void BindConstantGroup(const std::string& name);
		void BindConstantBrick(const std::string& name);
		void BindAttriConstant(const std::string& name);
		void BindVisualIndex(const std::string& name);
		void BindVisualPool(const std::string& name);

	private:
		static bool init;

		std::shared_ptr<ConstantBuffer> m_cbInfo;
		std::shared_ptr<ConstantBuffer> m_groupInfo;
		std::shared_ptr<ConstantBuffer> m_BrickInfo;
		std::shared_ptr<ConstantBuffer> m_cbAttri;

		std::vector<std::shared_ptr<Shader>> m_shaders;
		
		std::shared_ptr<Buffer> m_NumNode;
		std::shared_ptr<Buffer> m_BrickInedx;
		std::shared_ptr<Buffer> m_NodeIndex;
		std::shared_ptr<Buffer> m_visualIndex;

		std::shared_ptr<ConstantBuffer> m_cbTrans = nullptr;
		std::shared_ptr<StructuredBuffer> m_NodePool = nullptr;;
		std::shared_ptr<StructuredBuffer> m_fragmentList = nullptr;
		std::shared_ptr<StructuredBuffer> m_visualPool = nullptr;

		std::shared_ptr<BufferBase> m_InstanceBuffer = nullptr;
		std::shared_ptr<BufferBinding> instantBind = nullptr;
		std::shared_ptr<BufferBinding> positionBind = nullptr;
		std::shared_ptr<Texture> m_BricksPool[3] = { nullptr };
		ID3D11Buffer* mVisualInstanceBuf = nullptr;
		ID3D11Buffer* mVisualVB = nullptr;
		ID3D11Buffer* mVisualIB = nullptr;
		std::vector<UINT>  mNumNodePerLevel;
		std::shared_ptr<RenderEventArgs> m_pRenderEventArgs = nullptr;
		std::shared_ptr<BufferBase> vertexbuffer = nullptr;
		std::shared_ptr<BufferBase> indexbuffer = nullptr;
		std::shared_ptr<Mesh> mCubeMesh = nullptr;
		// The pipeline state that should be used to render this pass.
		std::shared_ptr<PipelineState> m_Pipeline = nullptr;

		// The scene to render.
		std::shared_ptr<Scene> m_Scene = nullptr;
		std::shared_ptr<Scene> m_SceneBox = nullptr;
		std::shared_ptr<Renderer> m_RenderDevice = nullptr;
	};
}