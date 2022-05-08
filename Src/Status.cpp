#include "Metin2TorrentConsole.h"
#include "Status.h"

CStatus::CStatus()
{
	m_listStatus.clear();
	m_tszBuffer = MA_StringAlloc(2048);
}

CStatus::~CStatus()
{
	MA_StringFree(m_tszBuffer);
}

void CStatus::Clear(void)
{
//	ListStatusItr i;
//	for (i = m_listStatus.begin(); i != m_listStatus.end(); ++i)
//	{
//		SSTATUSENTRY& p = *i;
//		if (&p)
//			delete &i;
//	}
	m_listStatus.clear();
}

bool CStatus::IsEmpty(void)
{
	return m_listStatus.empty();
}

bool CStatus::AddNR(EA_STATUS_TYPE eSeverity, LPCTSTR tszMessage)
{
	SSTATUSENTRY neq;
	neq.eSeverity = eSeverity;
	wcscpy(neq.tszText, tszMessage);
	m_listStatus.push_back(neq);
	return true;

}

bool CStatus::AddNRf(EA_STATUS_TYPE eSeverity, LPCTSTR tszFormat, ...)
{
	//const size_t size = 1024;
	static wchar_t szBuf[MA_MAX_PATH];

	va_list args;
	va_start(args, tszFormat);
	_vsnwprintf(szBuf, sizeof(szBuf), tszFormat, args);
	va_end(args);

	//int len = WideCharToMultiByte(CP_ACP, 0, szBuf, wcslen(szBuf) + 1, 0, 0, 0, 0);
	//std::string r(len, '\0');
	//WideCharToMultiByte(CP_ACP, 0, szBuf, wcslen(szBuf) + 1, &r[0], len, 0, 0);

	SSTATUSENTRY neq;
	neq.eSeverity = eSeverity;
	neq.tszText = szBuf;
	//strcpy(neq.tszText, r.c_str());
	m_listStatus.push_back(neq);
	return true;
}

MA_LPTSTR CStatus::GetString(EA_STATUS_TYPE eMinSeverity)
{
	if (m_listStatus.empty())
		return L"Unknown Error!";

	for (const auto& p : m_listStatus)
	{
		if (p.eSeverity == eMinSeverity)
			return p.tszText;
	}
	return L"Unknown Error!";
}
