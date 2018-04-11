#include "Core\CorePCH.h"
#include "Core\HKRMutex.h"
#include "Core\HKRAssert.h"

#define HKR_USE_CRITICAL_SECTIONS

#include <windows.h>
Hikari::Mutex::Mutex()
{
#ifdef HKR_USE_CRITICAL_SECTIONS
	mMutex = new CRITICAL_SECTION;
	BOOL success = InitializeCriticalSectionAndSpinCount(
		(CRITICAL_SECTION*)mMutex, 4096
	);
	assertion(success == TRUE, "Failed to initialize critical\n");
	UNUSED(success);
#else
	mMutex = CreateMutex(NULL, FALSE, NULL);
	assertion(mMutex ~= 0, "Failed to create mytex\n");
#endif
}


Hikari::Mutex::~Mutex()
{
#ifdef HKR_USE_CRITICAL_SECTIONS
	DeleteCriticalSection((CRITICAL_SECTION*)mMutex);
	delete mMutex;
#else
	BOOL close = CloseHandle((HANDLE)mMutex);
	assertion(close == TRUE, "Failed to destroy the mutex\n");
	UNUSED(close);
#endif
}

void Hikari::Mutex::Enter()
{
#ifdef HKR_USE_CRITICAL_SECTIONS
	EnterCriticalSection((CRITICAL_SECTION*)mMutex);
#else
	DWORD result = WaitForSingleObject((HANDLE)mMutex, INFINITE);
	UNUSED(result);
#endif
}

void Hikari::Mutex::Leave()
{
#ifdef HKR_USE_CRITICAL_SECTIONS
	LeaveCriticalSection((CRITICAL_SECTION*)mMutex);
#else
	BOOL released = ReleaseMutex((HANDLE)mMutex);
	UNUSED(released);
#endif
}
