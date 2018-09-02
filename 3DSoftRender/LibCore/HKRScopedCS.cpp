#include "CorePCH.h"
#include "HKRScopedCS.h"

Hikari::ScopedCS::ScopedCS(Mutex* mutex)
	: mMutex(mutex)
{
	mMutex->Enter();
}

Hikari::ScopedCS::~ScopedCS()
{
	mMutex->Leave();
}
