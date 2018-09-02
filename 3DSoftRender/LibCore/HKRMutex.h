#pragma once
#include "HKRMutexType.h"

namespace Hikari
{
	class Mutex
	{
	public:
		Mutex();
		~Mutex();
		void Enter();
		void Leave();
	private:
		MutexType mMutex;
	};
}
