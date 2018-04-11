#pragma once
#include "Core\CoreLib.h"
#include "Core\HKRMutexType.h"

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