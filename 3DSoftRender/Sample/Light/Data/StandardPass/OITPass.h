#pragma once
#include "BasePass.h"

namespace Hikari
{
	using namespace std;
	class Renderer;
	class Material;
	class StructuredBuffer;

	class OITPass : public BasePass
	{
	public:
		OITPass(std::shared_ptr<Renderer> render, vector<shared_ptr<Scene>> scene,
		        std::shared_ptr<PipelineState> pipeline);

		virtual ~OITPass();

		void Visit(Mesh& mesh) override;


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
		shared_ptr<StructuredBuffer> mPixelList{};
		shared_ptr<Buffer> mStartOffset{};
	};
}
