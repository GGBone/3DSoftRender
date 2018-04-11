#include "Core\CorePCH.h"
#include "Core\HKRThread.h"
#include "Core\HKRAssert.h"
#include <windows.h>
Hikari::Thread::Thread(void * function, void * userData, unsigned int processorNumber, unsigned int stackSize)
	:mFunction(function),
	mUserData(userData),
	mProcessorNumber(mProcessorNumber),
	mStackSize(stackSize)
{
	mThread = CreateThread(NULL, (SIZE_T)stackSize,
		(LPTHREAD_START_ROUTINE)function, (LPVOID)userData,
		CREATE_SUSPENDED, (LPDWORD)&mThreadID);

}

Hikari::Thread::~Thread()
{
	//To-Do
	assertion(mThread == nullptr, "Destructored Thread\n");

}

void Hikari::Thread::Resume()
{
	DWORD result = ResumeThread((HANDLE)mThread);
	assertion(result != (DWORD)-1, "Failed to resume the Thread \n");
	UNUSED(result);
}

void Hikari::Thread::Suspend()
{
	DWORD result = SuspendThread((HANDLE)mThread);
	assertion(result != (DWORD)-1, "Failed to suspend thread\n");
	UNUSED(result);
}
