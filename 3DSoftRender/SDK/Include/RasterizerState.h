#pragma once
#include "Object.h"

namespace Hikari
{

	struct Viewport
	{
		explicit Viewport(float x = 0.0f, float y = 0.0f, float width = 0.0f, float height = 0.0f, float minDepth = 0.0f, float maxDepth = 1.0f)
			: X(x)
			, Y(y)
			, Width(width)
			, Height(height)
			, MinDepth(minDepth)
			, MaxDepth(maxDepth)
		{}

		float X;
		float Y;
		float Width;
		float Height;
		float MinDepth;
		float MaxDepth;
	};

	class Rect
	{
	public:
		Rect(float x = 0.0f, float y = 0.0f, float width = 0.0f, float height = 0.0f)
			: X(x)
			, Y(y)
			, Width(width)
			, Height(height)
		{}

		float X;
		float Y;
		float Width;
		float Height;
	};

	class RasterizerState :public Object
	{
	public:
		enum class FillMode
		{
			WireFrame,
			Solid
		};

		enum class CullMode
		{
			None,
			Front,
			Back,
			FrontAndBack
		};

		enum  class FrontFace
		{
			ClockWise,
			CounterClockwise
		};


		virtual void SetFillMode(FillMode frontFace = FillMode::Solid, FillMode backFace = FillMode::Solid) = 0;
		virtual void GetFillMode(FillMode& frontFace, FillMode& backFace) const = 0;

		virtual void SetCullMode(CullMode cullMode = CullMode::Back) = 0;
		virtual CullMode GetCullMode() const = 0;

		virtual void SetFrontFacing(FrontFace frontFace = FrontFace::CounterClockwise) = 0;
		virtual FrontFace GetFrontFacing() const = 0;

		virtual void SetDepthBias(float depthBias = 0.0f, float slopeBias = 0.0f, float biasClamp = 0.0f) = 0;
		virtual void GetDepthBias(float& depthBias, float& slopeBias, float& biasClamp) const = 0;

		virtual void SetDepthClipEnabled(bool depthClipEnabled = true) = 0;
		virtual bool GetDepthClipEnabled() const = 0;

		virtual void SetViewport(const Viewport& viewport) = 0;
		virtual void SetViewports(const std::vector<Viewport>& viewports) = 0;
		virtual const std::vector<Viewport>& GetViewports() = 0;

		virtual void SetScissorEnabled(bool scissorEnable = false) = 0;
		virtual bool GetScissorEnabled() const = 0;

		virtual void SetScissorRect(const Rect& rect) = 0;
		virtual void SetScissorRects(const std::vector<Rect>& rects) = 0;
		virtual const std::vector<Rect>& GetScissorRects() const = 0;

		virtual void SetMultisampleEnabled(bool multisampleEnabled = false) = 0;
		virtual bool GetMultisampleEnabled() const = 0;

		virtual void SetAntialiasedLineEnable(bool antialiasedLineEnable) = 0;
		virtual bool GetAntialiasedLineEnable() const = 0;

		virtual void SetForcedSampleCount(uint8_t forcedSampleCount = 0) = 0;
		virtual uint8_t GetForcedSampleCount() = 0;

		virtual void SetConservativeRasterizationEnabled(bool conservativeRasterizationEnabled = false) = 0;
		virtual bool GetConservativeRasterizationEnabled() const = 0;
	};
}