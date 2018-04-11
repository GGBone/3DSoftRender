#pragma once
#include "Core\HKRThreadType.h"

namespace Hikari
{
	class Thread
	{
	public:
		Thread(void* function, void* userData, unsigned int processorNumber = 0,
			unsigned int stackSize = 0);
		~Thread();

		void Resume();
		void Suspend();

	private:
		ThreadType mThread;
		unsigned int mThreadID;
		void* mFunction;
		void* mUserData;
		unsigned int mProcessorNumber;
		unsigned int mStackSize;
	};
}