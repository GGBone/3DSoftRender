#pragma once

class CReadDirectoryChanges;

namespace ReadDirectoryChangesPrivate
{
	class CReadChangesServer;

	class CReadChangesRequest
	{
	public:
		CReadChangesRequest(CReadChangesServer* pServer, const std::wstring& sz, bool h, DWORD dw, DWORD size);
		~CReadChangesRequest();

		bool operator==(const CReadChangesRequest& other) const;

		bool OpenDirectory();
		void BeginRead();

		void BackupBuffer(DWORD dwSize)
		{
			memcpy(&m_BackupBuffer[0], &m_Buffer[0], dwSize);
		}

		void ProcessNotification();

		void RequestTermination()
		{
			CancelIo(m_hDirectory);
			CloseHandle(m_hDirectory);
			m_hDirectory = nullptr;
		}

		CReadChangesServer* m_pServer;
	protected:
		static VOID CALLBACK NotificationCompletion(
			DWORD dwErrorCode, //completion code
			DWORD dwNumberOfBytesTransfered, //num of bytes transferred
			LPOVERLAPPED lpoverLapped //I/O information buffer
		);
		DWORD m_dwFlags;
		BOOL m_bChildren;
		fs::path m_DirectoryPath;
		HANDLE m_hDirectory;
		OVERLAPPED m_Overlapped;
		std::vector<BYTE> m_Buffer;
		std::vector<BYTE> m_BackupBuffer;
	};

	class CReadChangesServer
	{
	public:
		CReadChangesServer(CReadDirectoryChanges* pParent)
		{
			m_bTerminate = false;
			m_nOutstandingRequests = 0;
			m_pBase = pParent;
		}

		static unsigned int WINAPI ThreadStartProc(LPVOID arg)
		{
			CReadChangesServer* pServer = (CReadChangesServer*)arg;
			pServer->Run();
			return 0;
		}

		static void CALLBACK TerminateProc(__in ULONG_PTR arg)
		{
			CReadChangesServer* pServer = (CReadChangesServer*)arg;
			pServer->RequestTermination();
		}

		static void CALLBACK AddDirectoryProc(__in ULONG_PTR arg)
		{
			CReadChangesRequest* pRequest = (CReadChangesRequest*)arg;
			pRequest->m_pServer->AddDirectory(pRequest);
		}

		CReadDirectoryChanges* m_pBase;
		volatile DWORD m_nOutstandingRequests;

	protected:
		void Run()
		{
			while (m_nOutstandingRequests || !m_bTerminate)
				DWORD rc = SleepEx(INFINITE, true);
		}

		void AddDirectory(CReadChangesRequest* pBlock)
		{
			Blocks::iterator iter = std::find_if(m_pBlocks.begin(), m_pBlocks.end(),
			                                     [=](const CReadChangesRequest* pChanges)
			                                     {
				                                     return *pBlock == *pChanges;
			                                     }
			);
			if (iter == m_pBlocks.end() && pBlock->OpenDirectory())
			{
				::InterlockedIncrement(&pBlock->m_pServer->m_nOutstandingRequests);
				m_pBlocks.push_back(pBlock);
				pBlock->BeginRead();
			}
			else
				delete pBlock;
		}

		void RequestTermination()
		{
			m_bTerminate = true;
			for (DWORD i = 0; i < m_pBlocks.size(); ++i)
			{
				m_pBlocks[i]->RequestTermination();
			}
			m_pBlocks.clear();
		}

		typedef std::vector<CReadChangesRequest*> Blocks;
		Blocks m_pBlocks{};
		bool m_bTerminate;
	};
}
