#pragma once
#include "BasePass.h"
#include <Graphics\Light.h>

namespace Hikari
{
	using namespace std;
	class Renderer;
	class Material;
	class StructuredBuffer;
	class OITPass : public BasePass
	{
	public:
		OITPass(std::shared_ptr<Renderer> render, shared_ptr<Scene> scene, std::shared_ptr<PipelineState> pipeline);

		virtual ~OITPass();

		virtual void Visit(Mesh& mesh) override;


		struct ScreenSize
		{
			float width;
			float height;
		};
		struct FragmentData_STRUCT
		{
			Float4 color;
			float depth;
		};

		struct FragmentAndLinkBuffer_STRUCT
		{
			FragmentData_STRUCT FragmentData;
			uint32_t nNext;
		};
	private:
		shared_ptr<StructuredBuffer> mPixelList;
		
	};
}