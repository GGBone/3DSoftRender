#include "loaderPCH.h"
#include "LoaderLib.h"

ReadDirectoryChangesPrivate::CReadChangesRequest::CReadChangesRequest(CReadChangesServer * pServer, const std::wstring & sz, bool b, DWORD dw, DWORD size)
{
	m_pServer = pServer;
	m_dwFlags = dw;
	m_bChildren = b;
	m_DirectoryPath = sz;
	m_hDirectory = 0;

	::ZeroMemory(&m_Overlapped, sizeof(OVERLAPPED));

	m_Overlapped.hEvent = this;
	m_Buffer.resize(size);
	m_BackupBuffer.resize(size);
}

ReadDirectoryChangesPrivate::CReadChangesRequest::~CReadChangesRequest()
{
	assert(m_hDirectory == NULL);
}

bool ReadDirectoryChangesPrivate::CReadChangesRequest::operator==(const CReadChangesRequest & other) const
{
	return (
		m_DirectoryPath == other.m_DirectoryPath &&
		m_bChildren == other.m_bChildren &&
		m_dwFlags == other.m_dwFlags
		);
}

bool ReadDirectoryChangesPrivate::CReadChangesRequest::OpenDirectory()
{
	if (m_hDirectory)
		return true;
	m_hDirectory = ::CreateFileW(
		m_DirectoryPath.c_str(),
		FILE_LIST_DIRECTORY,	//file name 
		FILE_SHARE_READ |		//access mode
		FILE_SHARE_WRITE |		//share mode
		FILE_SHARE_DELETE,
		NULL,
		OPEN_EXISTING,			//security descriptor
		FILE_FLAG_BACKUP_SEMANTICS |	//file attributes
		FILE_FLAG_OVERLAPPED,
		NULL					//file with attribute to copy
	);
	if (m_hDirectory == INVALID_HANDLE_VALUE)
		return false;
	return true;
}

void ReadDirectoryChangesPrivate::CReadChangesRequest::BeginRead()
{
	DWORD dwBytes = 0;
	BOOL sucess = ::ReadDirectoryChangesW(
		m_hDirectory,
		&m_Buffer[0],
		(DWORD)m_Buffer.size(),
		m_bChildren,
		FILE_NOTIFY_CHANGE_LAST_WRITE | FILE_NOTIFY_CHANGE_CREATION | FILE_NOTIFY_CHANGE_FILE_NAME,
		&dwBytes,
		&m_Overlapped,
		&NotificationCompletion
	);
}

void ReadDirectoryChangesPrivate::CReadChangesRequest::ProcessNotification()
{
	char* pBase = (char*)&m_BackupBuffer[0];
	for (;;)
	{
		FILE_NOTIFY_INFORMATION& fni = (FILE_NOTIFY_INFORMATION&)*pBase;
		std::wstring wstrFilename(fni.FileName, fni.FileNameLength / sizeof(wchar_t));
		fs::path filepath = m_DirectoryPath / wstrFilename;

		LPCWSTR wszFilename = PathFindFileNameW(filepath.c_str());
		int len = lstrlenW(wszFilename);

		if (len <= 12 && wcschr(wszFilename, L'~'))
		{
			wchar_t wbuf[MAX_PATH];
			if (::GetLongPathNameW(wstrFilename.c_str(), wbuf, _countof(wbuf)) > 0)
			{
				filepath = wbuf;
			}
			m_pServer->m_pBase->Push(fni.Action,filepath.c_str());
			
			if (!fni.NextEntryOffset)
				break;
			pBase += fni.NextEntryOffset;
		}
	}
}

VOID ReadDirectoryChangesPrivate::CReadChangesRequest::NotificationCompletion(DWORD dwErrorCode, DWORD dwNumberOfBytesTransfered, LPOVERLAPPED lpoverLapped)
{
	CReadChangesRequest* pBlock = (CReadChangesRequest*)lpoverLapped;
	if (dwErrorCode == ERROR_OPERATION_ABORTED)
	{
		::InterlockedDecrement(&pBlock->m_pServer->m_nOutstandingRequests);
		delete pBlock;
		return;
	}
	assert(dwNumberOfBytesTransfered >= offsetof(FILE_NOTIFY_INFORMATION, FileName) + sizeof(WCHAR));
	if (!dwNumberOfBytesTransfered)
		return;
	pBlock->BackupBuffer(dwNumberOfBytesTransfered);
	pBlock->BeginRead();
	pBlock->ProcessNotification();
}
