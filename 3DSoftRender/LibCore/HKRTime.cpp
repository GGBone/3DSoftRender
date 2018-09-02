#include "CorePCH.h"
#include "HKRTime.h"

namespace Hikari
{
#include <sys/timeb.h>
	static long gsInitialSec = 0;
	static long gsInitialUSec = 0;
	static bool gsInitializedTime = false;

	Timer::Timer(float maxTimeStep)
	{
		m_fMaxTimeStep = maxTimeStep;
		m_fPrevious = (std::clock() / (float)CLOCKS_PER_SEC);
	}

	float Timer::GetElapsedTime() const
	{
		float fCurrentTime = std::clock() / (float)CLOCKS_PER_SEC;
		float fDeltaTime = fCurrentTime - m_fPrevious;
		m_fPrevious = fCurrentTime;
		fDeltaTime = std::min<float>(fDeltaTime, m_fMaxTimeStep);
		return fDeltaTime;
	}
}

int64_t Hikari::Timer::GetTimeInMicroseconds()
{
	struct timeb currentTime{};

	if (!gsInitializedTime)
	{
		gsInitializedTime = true;
		ftime(&currentTime);
		gsInitialSec = (long)currentTime.time;
		gsInitialUSec = 1000 * currentTime.millitm;
	}

	ftime(&currentTime);
	long currentSec = (long)currentTime.time;
	long currentUSec = 1000 * currentTime.millitm;
	long deltaSec = currentSec - gsInitialSec;
	long deltaUSec = currentUSec - gsInitialUSec;
	if (deltaUSec < 0)
	{
		deltaUSec += 1000000;
		--deltaSec;
	}

	return 1000000 * deltaSec + deltaUSec;
}

double Hikari::Timer::GetTimeInSeconds() const
{
	int64_t microseconds = GetTimeInMicroseconds();
	return 1e-06 * microseconds;
}
