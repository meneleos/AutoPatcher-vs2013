#include "Metin2TorrentConsole.h"

#include "ServerGuardChecker.h"

#ifdef ENABLE_GUARD_CHECKER

#include "../eterLib/NetAddress.h"

#pragma pack(push)
#pragma pack(1)

typedef unsigned char ServerStateChecker_Header;
typedef unsigned long ServerStateChecker_Key;
typedef unsigned long ServerStateChecker_Index;
typedef unsigned char ServerStateChecker_State;

enum {
	HEADER_CG_GUARD_CHECKER = 69,
	HEADER_GC_RESPOND_CHANNELSTATUS				= 100,
};
typedef struct SChannelStatus
{
	short nPort;
	BYTE bStatus;
} TChannelStatus;

#pragma pack(pop)

CServerGuardChecker::CServerGuardChecker()
{
	Initialize();
}

CServerGuardChecker::~CServerGuardChecker()
{
	Initialize();
}

void CServerGuardChecker::Create()
{
}

void CServerGuardChecker::AddChannel(UINT uServerIndex, const char* c_szAddr, UINT uPort)
{
	TGuardChannel c;
	c.uServerIndex = uServerIndex;
	c.c_szAddr = c_szAddr;
	c.uPort = uPort;

	m_lstChannel.push_back(c);
}

bool CServerGuardChecker::Request()
{
	if (m_lstChannel.empty()) {
		return false;
	}

	if (!m_kStream.Connect(m_lstChannel.begin()->c_szAddr, m_lstChannel.begin()->uPort))
	{
		for (std::list<TGuardChannel>::const_iterator it = m_lstChannel.begin(); it != m_lstChannel.end(); ++it) {
			//PyCallClassMemberFunc(m_poWnd, "NotifyChannelState", Py_BuildValue("(ii)", it->uServerIndex, 0));
		}
		return false;
	}
	m_kStream.ClearRecvBuffer();
	m_kStream.SetSendBufferSize(1024);
	m_kStream.SetRecvBufferSize(1024);

	BYTE bHeader = 76;
	if (!m_kStream.Send(sizeof(bHeader), &bHeader))
	{
		for (std::list<TGuardChannel>::const_iterator it = m_lstChannel.begin(); it != m_lstChannel.end(); ++it) {
			//PyCallClassMemberFunc(m_poWnd, "NotifyChannelState", Py_BuildValue("(ii)", it->uServerIndex, 0));
		}
		Initialize();
		return true;
	}
}

bool CServerGuardChecker::Update()
{
	m_kStream.Process();

	BYTE bHeader;
	if (!m_kStream.Recv(sizeof(bHeader), &bHeader)) {
		return false;
	}
	if (HEADER_GC_RESPOND_CHANNELSTATUS != bHeader) {
		return false;
	}
	int nSize;
	if (!m_kStream.Recv(sizeof(nSize), &nSize)) {
		return false;
	}
	for (int i = 0; i < nSize; i++) {
		TChannelStatus channelStatus;
		if (!m_kStream.Recv(sizeof(channelStatus), &channelStatus)) {
			return false;
		}
		EL_TCHAR buf[2048];
		MA_StringFormat(buf, MA_ARRAYCOUNT(buf), MA_T("port %d"), channelStatus.nPort);

		wxMessageBox(wxString(buf), EL_LTEXT("NOTICE"));
		for (std::list<TGuardChannel>::const_iterator it = m_lstChannel.begin(); it != m_lstChannel.end(); ++it) {
			if (channelStatus.nPort == it->uPort) {
				//PyCallClassMemberFunc(m_poWnd, "NotifyChannelState", Py_BuildValue("(ii)", it->uServerIndex, channelStatus.bStatus));
				break;
			}
		}
	}
	Initialize();
	return true;
}

void CServerGuardChecker::Initialize()
{
	m_lstChannel.clear();
	m_kStream.Disconnect();
}
#endif
