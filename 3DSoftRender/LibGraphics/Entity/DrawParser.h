#pragma once
#include "Graphics\GraphicsLib.h"
namespace Hikari
{
	typedef uint64_t entity_handle;
	class Entity
	{

	};
	class System
	{

	};
	class DrawEntitySelector
	{

	};
	struct SceneSelector
	{
		entity_handle sceneEntityHandle;
		DrawEntitySelector* drawEntitySelector;
		SceneSelector(entity_handle handle, DrawEntitySelector* selector)
			:sceneEntityHandle(handle),
			drawEntitySelector(selector)
		{}
	};
	class Device;
	class Context;
	typedef uint64_t DrawPlan;
	struct DrawPlanLex
	{
		DrawPlanLex(System& system, DrawPlanEntity& drawPlanEntity);

	};
	
	class DrawPlanEntity;
	struct DrawEntityItemBuffer
	{
	};
	struct SequenceThrowAwaryBuffer
	{
		void* current;
		void* m_buffer;
		size_t size;
		void Alloc(size_t size);
	};
	class DrawPlanParser
	{

	protected:
		typedef enum
		{
			PARSER_TYPE_DRAWPLANE,
			PARSER_TYPE_SURFACE,
			PARSER_TYPE_CAMERA,
			PARSE_TYPE_SURREY,
			PARSE_TYPE_SCENE,
			PARSE_TYPE_CREATERENDERTARGET
		}PARSER_TYPE;
	public:
		DrawPlanParser& m_parent;
		std::vector<DrawPlanParser*> m_child;
		DrawPlanLex drawPlanLex;
		SequenceThrowAwaryBuffer* buffer;
		entity_handle drawStageMask;
		entity_handle drawGroupMask;
		entity_handle viewport;
		entity_handle collectorFactoryHandle;
		entity_handle drawContextFactoryHandle;
		entity_handle swapTextureHandle;
		entity_handle m_RenderTargetSurfaceEntityArrayHandle [32];
		entity_handle m_DepthStencilSurfaceEntityHandle;
		entity_handle m_TargetCameraEntityHandle;
		entity_handle m_TargetSceneEntityHandle;


	protected:
		DrawPlanParser(System& system, Device& device, DrawPlanLex& drawPlanLex, SequenceThrowAwaryBuffer* buffer);

	public:
		DrawPlanParser(PARSER_TYPE type, DrawPlanParser& parent);
		void MakeTree();
		void MakeTree_BeginDrawPlan();
		void MakeTree_EndDrawPlan();
		void MakeTree_BeginTargetSurface();
		void MakeTree_EndTargetSurface();
		void MakeTree_BeginCamera();
		void MakeTree_EndCamera();

		void MakeTree_BeginConditionalRendering();
		void MakeTree_EndConditionalRender();

		void MakeTree_BeginScene();
		void MakeTree_EndScene();

		void MakeTree_Clear();

		void MakeTree_CreateRenderTarget();
		void MakeTree_PushMarker();


		void FixTree();
		void FixTree_AddTragetSurface();
		void FixTree_AddLight();
		void FixTree_AddDrawPlanContextFactory();
		void FixTree_AddCollectorFactory();
		void FixTree_AddDrawStageMask();
		void FixTree_AddDrawGroupMask();

		virtual void MakeSelector(std::vector<SceneSelector>& array, DrawEntityItemBuffer& buffer)
		{
			for each(DrawPlanParser* itor in m_child)
			{
				(*itor).MakeSelector(array, buffer);
			}
		}

		virtual void Draw(Context& drawContext);

		static Entity ParseDraw(System& system, Device& deivce, DrawPlanEntity& draPlanEntity, SequenceThrowAwaryBuffer* buffer)
		{
			DrawPlanLex(system, draPlanEntity);
			DrawPlanParser* rootParser = new DrawPlanParser(PARSER_TYPE_DRAWPLANE,);
			rootParser->MakeTree();
			rootParser->FixTree();

			DrawEntityItemBuffer Itembuffer(buffer->m_size);
			std::vector<SceneSelector&> sceneVector;
			rootParser->MakeSelector(sceneVector, Itembuffer);
			for each (SceneSelector var in sceneVector)
			{
				SceneEntity sceneEntity = var->GetSceneEntity();
				sceneEntity->CollectDrawEntity(var.selector);
			}

			drawContext = system->CreateDrawContext(drawContextFactory, true);
			drawContext->GetRender()->BeginScene();
			rootParser->Draw(drawContext);
			drawContext->EndScene();

			FreeSceneVector();

			return rootParser->swapTexture;
		}
	};

	class DrawPlanExecutant
	{
	public:
		DrawPlanEntity& drawPlanEntity;
		SequenceThrowAwaryBuffer& buffer;
		Entity swapEntityResult;
		DrawPlanExecutant(System& system, Device& device, entity_handle handle, SequenceThrowAwaryBuffer& buffer);
		void Execute()	//main
		{
			DrawPlanParser parseResult = DrawPlanParser::ParseDraw(system, device, handle, buffer);
		}
		Entity GetWwapEntityResult() {
			return swapEntityResult;
		}
	};
	class SceneEntity;
	class Region;
	class DrawEntityCollector
	{
	protected:
		SceneEntity* m_TailInsertSceneEntity[16];
		size_t m_TailInsertSceneEntityNum;
	public:
		DrawEntityCollector(DrawEntityItemBuffer& buffer, SceneEntity** list, size_t num) :
			m_TailInsertSceneEntity(list),
			m_TailInsertSceneEntityNum(num)
		{}
		virtual void SetCameraEntity(entity_handle cameraEntity);
		virtual void BeginRegion(Region& region);
		virtual void AddDrawEntity(DrawEntity entity, void* data);
		virtual void Draw(Context* context);
	};
	class DrawPlanParser_TargetScene: public DrawPlanParser
	{
	public:
		DrawPlanParser_TargetScene(PARSER_TYPE type, DrawPlanParser& parent)
		:
			DrawPlanParser(type, parent)
		{

		}
		virtual void MakeSelector(std::vector<SceneSelector>& array, DrawEntityItemBuffer& buffer)
		{
			DrawEntitySelector* drawEntitySelector = nullptr;
			DrawEntityCollector* drawEntityCollector = nullptr;
			for each (SceneSelector& var in array)
			{
				if (var.sceneEntityHandle == m_TargetSceneEntityHandle)
				{
					drawEntitySelector = var.drawEntitySelector;
					break;
				}
			}
			if (drawEntitySelector == nullptr)	//AddSelectorInVector
			{
				drawEntitySelector = new DrawEntitySelector;
				SceneSelector selector(m_TargetSceneEntityHandle, drawEntitySelector);
				array.push_back(selector);
			}

			if (drawEntityCollector == nullptr)//AddCollector
			{
				for (int i = 0; i < cullNum; ++i)
				{
					entity_handle cullCam = cullingCameraVec[i];
					frustumMask |= drawEntitySelector->AddFrustum(cullCam);
				}
			}
			drawEntityCollector = drawEntitySelector->AddCollector(collectorFactoryHandle, buffer,
				frustumMask, drawStageMask, drawGroupMask);
			drawEntityCollector->SetCameraEntity(m_TargetCameraEntityHandle);
			m_DrawEntityCollector = drawEntityCollector;

		}
		virtual void Draw(Context& drawContext)
		{

		}
	};
}