#include "loaderPCH.h"
#include "LoaderLib.h"

using namespace ReadDirectoryChangesPrivate;

CReadDirectoryChanges::CReadDirectoryChanges(int nMaxChanges)
:m_Notifications(nMaxChanges)
{
	m_hThread = NULL;
	m_dwThreadId = 0;
	m_pServer = new CReadChangesServer(this);
}

CReadDirectoryChanges::~CReadDirectoryChanges()
{
	Terminate();
	delete m_pServer;
}

void CReadDirectoryChanges::Init()
{
	m_hThread = (HANDLE)_beginthreadex(NULL, 0, CReadChangesServer::ThreadStartProc,
		m_pServer, 0, &m_dwThreadId);
}

void CReadDirectoryChanges::Terminate()
{
	if (m_hThread)
	{
		::QueueUserAPC(CReadChangesServer::TerminateProc, m_hThread, (ULONG_PTR)m_pServer);
		::WaitForSingleObjectEx(m_hThread, 10000, true);
		::CloseHandle(m_hThread);
		m_hThread = NULL;

		m_dwThreadId = 0;
	}
}

void CReadDirectoryChanges::AddDictory(const std::wstring & szDictory, bool bWatchSubtree, DWORD dwNotifyFilter, DWORD dwBufferSize)
{
	if (!m_hThread)
		Init();
	CReadChangesRequest* pRequest = new CReadChangesRequest(m_pServer,szDictory,bWatchSubtree,dwNotifyFilter,dwBufferSize );
	::QueueUserAPC(CReadChangesServer::AddDirectoryProc, m_hThread, (ULONG_PTR)pRequest);


}

bool CReadDirectoryChanges::Pop(DWORD & dwAction, std::wstring & wstrFilename)
{
	TDirectoryChangeNotification pair;
	if(!m_Notifications.pop(pair))
		return false;
	dwAction = pair.first;
	wstrFilename = pair.second;
	return true;
}

void CReadDirectoryChanges::Push(DWORD & dwAction, const std::wstring & wstrFilename)
{
	m_Notifications.push(TDirectoryChangeNotification(dwAction, wstrFilename));

}

bool CReadDirectoryChanges::CheckOverflow()
{
	bool b = m_Notifications.overflow();
	if (b)
		m_Notifications.clear();
	return b;
}
