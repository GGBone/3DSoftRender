#pragma once
#include "HKRMutex.h"

namespace Hikari
{
	class ScopedCS
	{
	public:
		ScopedCS(Mutex* mutex);
		~ScopedCS();
	private:
		Mutex* mMutex;
	};
}
