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
	class Renderer;
	struct BufferBinding;
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

		struct cbAttri
		{
			Float4 extent;
			Float4 origin;
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
		void SetAttriConstant(ConstantBuffer* buffer, const std::string& name);

		void SetVisualPool(StructuredBuffer* buffer, const std::string& name);
		void SetVisualIndex(RWBuffer* buffer, const std::string& name);

		void SetNodeBuffer(StructuredBuffer* buffer, const std::string& name);
		void SetNumNode(RWBuffer* rwBuffer, const std::string& name);
		void SetNodeIndex(RWBuffer* rwBuffer, const std::string& name);
		void SetBrickIndex(RWBuffer* rwBuffer, const std::string& name);
		void SetTotalNode(UINT totalNode);
		void SetTotalLevel(UINT totalLevel);

		void SetComputeShaders(Shader*[]);
	private:
		ConstantBuffer* m_cbInfo;
		ConstantBuffer* m_groupInfo;
		ConstantBuffer* m_BrickInfo;

		ConstantBuffer* m_cbAttri;
		Shader* m_shaders[7];
		static bool init;
		RWBuffer* m_NumNode;
		RWBuffer* m_BrickInedx;
		RWBuffer* m_NodeIndex;
		RWBuffer* m_visualIndex;

		ConstantBuffer* cbTrans = nullptr;
		StructuredBuffer* m_NodePool;
		StructuredBuffer* m_fragmentList;
		StructuredBuffer* m_visualPool = nullptr;
		Buffer* m_InstanceBuffer = nullptr;
		BufferBinding* instantBind = nullptr;
		BufferBinding* positionBind;
		Texture* m_BricksPool[3] = { nullptr };
		ID3D11Buffer* mVisualInstanceBuf;
		ID3D11Buffer* mVisualVB;
		ID3D11Buffer* mVisualIB;
		std::vector<UINT>	   mNumNodePerLevel;
		RenderEventArgs* m_pRenderEventArgs;
		Buffer* vertexbuffer = nullptr;
		Buffer* indexbuffer = nullptr;
		Mesh* mCubeMesh = nullptr;
		// The pipeline state that should be used to render this pass.
		PipelineState* m_Pipeline;

		// The scene to render.
		Scene* m_Scene;
		Scene* m_SceneBox;
		Renderer* m_RenderDevice;
	};
}