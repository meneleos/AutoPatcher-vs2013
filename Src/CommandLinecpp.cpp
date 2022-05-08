#include "Metin2TorrentConsole.h"
#include "CommandLine.h"

MA_CCommandLine::MA_CCommandLine()
{
	memset(m_szCommandLine, 0, sizeof(m_szCommandLine));

}

MA_CCommandLine::MA_CCommandLine(MA_PCWSTR szCommandLine, MA_BOOL bHasProgramName)
{
	memset(m_szCommandLine, 0, sizeof(m_szCommandLine));

	m_szCommandLine[0] = _T('\0');

	if (wcslen(szCommandLine) > sizeof(m_szCommandLine) - 1)
	{
		return;
	}

	wcsncpy(m_szCommandLine, szCommandLine, wcslen(szCommandLine));
}

MA_CCommandLine::MA_CCommandLine(MA_INT IN nArgumentCount, MA_PWSTR IN aszArguments[], MA_BOOL bHasProgramName)
{

}

MA_CCommandLine::~MA_CCommandLine()
{

}
