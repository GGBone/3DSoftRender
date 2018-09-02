#pragma once
namespace Hikari
{
	class Timer
	{
	public:
		Timer(float maxTimeStep = 0.03333f);
		float GetElapsedTime() const;
		static int64_t GetTimeInMicroseconds();
		double GetTimeInSeconds() const;
	private:

		float m_fMaxTimeStep;
		mutable float m_fPrevious;
	};
}
