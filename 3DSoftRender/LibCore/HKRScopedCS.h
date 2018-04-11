#pragma once
#include "Core\CoreLib.h"
#include "Core\HKRMutex.h"

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