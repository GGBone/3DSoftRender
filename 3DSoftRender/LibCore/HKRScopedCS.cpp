#include "Core\CorePCH.h"
#include "Core\HKRScopedCS.h"

Hikari::ScopedCS::ScopedCS(Mutex * mutex)
	:mMutex(mutex)
{
	mMutex->Enter();
}

Hikari::ScopedCS::~ScopedCS()
{
	mMutex->Leave();
}
