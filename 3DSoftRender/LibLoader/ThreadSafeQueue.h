#pragma once
#include <Windows.h>
#include <list>
#include <mutex>
template <typename C>
class CThreadSafeQueue : protected std::list<C>
{
public:
	CThreadSafeQueue(int nMaxCount)
	{
		m_bOverflow = false;
		m_hSemaphore = ::CreateSemaphore(
			NULL,	//no security attributes
			0,		//initial count
			nMaxCount,	//max Count
			NULL	//anonymous
		);
	}
	~CThreadSafeQueue()
	{
		::CloseHandle(m_hSemaphore);
		m_hSemaphore = NULL;
	}
	void push(C& c)
	{
		MutexLock lock(m_Crit);
		push_back(c);
		lock.unlock();

		if (!::ReleaseSemaphore(m_hSemaphore, 1, NULL))
		{
			// if the semaphore is full,than take back the entry
			pop_back();
			if (GetLastError() == ERROR_TOO_MANY_POSTS)
			{
				m_bOverflow = true;
			}
		}
	}

	bool pop(C& c)
	{
		MutexLock(m_Crit);

		//if the user calls pops() more than once after the semaphore is singaled,
		//than the semaphore count will get out of sync.We fix that when the queue empties.
		if (empty())
		{
			while (::WaitForSingleObject(m_hSemaphore, 0) != WAIT_TIMEOUT);
			return false;
		}

		c = front();
		pop_front();
		return true;
	}

	void clear()
	{
		MutexLock(m_Crit);
		for (DWORD i = 0; i < size(); ++i)
			WaitForSingleObject(m_hSemaphore, 0);
		__super::clear();
		m_bOverflow = false;
	}

	bool overflow()const { return m_bOverflow; }

	HANDLE GetWaitHandle()const { return m_hSemaphore; }
protected:
	HANDLE m_hSemaphore;
	typedef std::unique_lock<std::mutex> MutexLock;

	std::mutex m_Crit;
	bool m_bOverflow;
};