#pragma once
#include "Core\CoreLib.h"
namespace Hikari
{
	

	class Timer
	{
	public:
		Timer(float maxTimeStep = 0.03333f);
		float GetElapsedTime() const;
		int64_t GetTimeInMicroseconds() const;
		double GetTimeInSeconds() const;
	private:
		
		float m_fMaxTimeStep;
		mutable float m_fPrevious;
	};
}