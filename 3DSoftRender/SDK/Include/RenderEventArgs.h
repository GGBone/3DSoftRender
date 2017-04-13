#pragma once
#include "GraphicsLib.h"
#include "Object.h"
namespace Hikari
{
	class Camera;
	class PipelineState;
	class EventArgs
	{
	public:
		EventArgs(const Object& caller)
			: Caller(caller)
		{}

		// The object that invoked the event
		const Object& Caller;
	};
	class RenderEventArgs : public EventArgs
	{
	public:
		typedef EventArgs base;
		RenderEventArgs(const Object& caller, float fDeltaTime, float fTotalTime, uint64_t frameCounter, Camera* camera = nullptr, PipelineState* pipelineState = nullptr)
			: base(caller)
			, ElapsedTime(fDeltaTime)
			, TotalTime(fTotalTime)
			, FrameCounter(frameCounter)
			, Camera(camera)
			, PipelineState(pipelineState)
		{}

		float ElapsedTime;
		float TotalTime;
		int64_t FrameCounter;
		Camera* Camera;
		PipelineState* PipelineState;
	};
}
