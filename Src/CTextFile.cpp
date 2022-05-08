// TextFile.cpp: implementation of the CTextFile class.
//
//////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <math.h>
#include <string.h>
#include <windows.h>

#include "CTextFile.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

#define MAX_BUF		255
#define ASCII_TAB	0x09

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CTextFile::CTextFile()
{
	m_pFP = NULL;
}

CTextFile::~CTextFile()
{
	if(m_pFP != NULL) Close();
}


//////////////////////////////////////////////////////////////////////
// Member Function

bool CTextFile::Open(const char *szFileName, int nMode)
{
	bool bRet = true;

	switch(nMode)
	{
		case TEXT_FILE_READ:
			fopen_s(&m_pFP, szFileName, "rt");
			break;
		case TEXT_FILE_WRITE:
			fopen_s(&m_pFP, szFileName, "r+t");
			break;
		case TEXT_FILE_CREATE:
			fopen_s(&m_pFP, szFileName, "w+t");
			break;
		case TEXT_FILE_APPEND:
			fopen_s(&m_pFP, szFileName, "a+t");
			break;
		default:
			bRet = false;
		break;
	}
	if(NULL == m_pFP)
	{
		bRet = false;
	}
	return bRet;
}

bool CTextFile::Open(const wchar_t * szFileName, int nMode)
{
	bool bRet = true;
	switch (nMode)
	{
		case TEXT_FILE_READ:
			_wfopen_s(&m_pFP, szFileName, L"rt");
			break;
		case TEXT_FILE_WRITE:
			_wfopen_s(&m_pFP, szFileName, L"r+t");
			break;
		case TEXT_FILE_CREATE:
			_wfopen_s(&m_pFP, szFileName, L"w+t");
			break;
		case TEXT_FILE_APPEND:
			_wfopen_s(&m_pFP, szFileName, L"a+t");
			break;
		default:
			bRet = false;
			break;
	}

	if (NULL == m_pFP)
	{
		bRet = false;
	}
	return bRet;
}

bool CTextFile::Close()
{
	if(m_pFP != NULL) { fclose(m_pFP); m_pFP = NULL; }
	return true;
}

bool CTextFile::FileExist(const char *szFileName)
{
	bool bRet = false;
	FILE *pFP;
	fopen_s(&pFP, szFileName, "r");
	if(pFP != NULL)
	{
		fclose(pFP);
		bRet = true;
	}
	return bRet;
}

#if !defined( _UNICODE )
bool CTextFile::DeleteFile(const char *szFileName)
{
	if(::DeleteFile(szFileName)) return true;
	return false;
}
#else
bool CTextFile::DeleteFile(const wchar_t *szFileName)
{
	if(::DeleteFile(szFileName)) return true;
	return false;
}
#endif

bool CTextFile::ReadWord(char *pBuf, char cToken)
{
	bool bRet = true;
	char szBuf[MAX_BUF] = "";
	*pBuf = NULL;

	do {
		if( feof(m_pFP) ) break;
		szBuf[0] = fgetc(m_pFP);
	} while(' ' == szBuf[0] || '\n' == szBuf[0]
						|| ASCII_TAB == szBuf[0] || szBuf[0] == cToken);
	int i = 0;
	do
	{
		if( feof(m_pFP) ) break;
		i++; szBuf[i] = fgetc(m_pFP);
	} while(szBuf[i] != ' ' && szBuf[i] != '\n'
						&& szBuf[i] != ASCII_TAB && szBuf[i] != cToken && i<MAX_BUF-1);
	szBuf[i] = NULL;
	strcpy(pBuf, szBuf);
	return bRet;
}

bool CTextFile::ReadWord(char cToken, char *pBuf, char cTok_B)
{
	bool bRet = false;
	if(Token(cToken) == true) bRet = ReadWord(pBuf, cTok_B);
	return bRet;
}

bool CTextFile::ReadLine(char *pBuf, char cToken)
{
	bool bRet = false;
	char szBuf[MAX_BUF] = "";
	*pBuf = NULL;

	if(true == GetLine(szBuf, sizeof(szBuf), cToken))
	{
		strcpy(pBuf, TrimLeft(szBuf));
		bRet = true;
	}
	return bRet;
}

bool CTextFile::ReadLine(char cToken, char *pBuf)
{
	bool bRet = false;
	if(Token(cToken) == true) bRet = ReadLine(pBuf);
	return bRet;
}

bool CTextFile::ReadInt(int *pValue, char cToken)
{
	bool bRet = false;
	char szBuf[MAX_BUF] = "";
	if(ReadWord(szBuf, cToken) == true)
	{
		*pValue = (int) atof(szBuf);
		bRet = true;
	}
	return bRet;
}

bool CTextFile::ReadInt(char cToken, int *pValue, char cTok_B)
{
	bool bRet = false;
	if(Token(cToken) == true) bRet = ReadInt(pValue, cTok_B);
	return bRet;
}

bool CTextFile::ReadFloat(float *pValue, char cToken)
{
	bool bRet = false;
	char szBuf[MAX_BUF] = "";
	if(ReadWord(szBuf, cToken) == true)
	{
		*pValue = (float) atof(szBuf);
		bRet = true;
	}
	return bRet;
}

bool CTextFile::ReadFloat(char cToken, float *pValue, char cTok_B)
{
	bool bRet = false;
	if(Token(cToken) == true) bRet = ReadFloat(pValue, cTok_B);
	return bRet;
}

bool CTextFile::ReadHexa(unsigned int *pValue, char cToken)
{
	bool bRet = false;
	char szBuf[MAX_BUF] = "";
	if(ReadWord(szBuf, cToken) == true)
	{
		*pValue = htoi(szBuf);
		bRet = true;
	}
	return bRet;
}

bool CTextFile::ReadHexa(char cToken, unsigned int *pValue, char cTok_B)
{
	bool bRet = false;
	if(Token(cToken) == true) bRet = ReadHexa(pValue, cTok_B);
	return bRet;
}

bool CTextFile::ReadDate(int *pYear, int *pMonth, int *pDay, char cToken)
{
	bool bRet = false;
	char szBuf[MAX_BUF] = "";
	do
	{
		if(ReadWord(szBuf, '.') == false) break;
		*pYear = (int) atof(szBuf);
		if(ReadWord(szBuf, '.') == false) break;
		*pMonth = (int) atof(szBuf);
		if(ReadWord(szBuf, cToken) == false) break;
		*pDay = (int) atof(szBuf);
		bRet = true;
	} while(0);
	return bRet;
}

bool CTextFile::ReadDate(char cToken, int *pYear, int *pMonth, int *pDay, char cTok_B)
{
	bool bRet = false;
	if(Token(cToken) == true) bRet = ReadDate(pYear, pMonth, pDay, cTok_B);
	return bRet;
}

bool CTextFile::ReadBool(bool *pValue, char cToken)
{
	bool bRet = false;
	char szBuf[MAX_BUF] = "";
	if(ReadWord(szBuf, cToken) == true)
	{
		bRet = true;
		if('Y' == szBuf[0] || 'y' == szBuf[0] || 'T' == szBuf[0] || 't' == szBuf[0])
			*pValue = true;
		else if('N' == szBuf[0] || 'n' == szBuf[0] || 'F' == szBuf[0] || 'f' == szBuf[0])
			*pValue = false;
		else bRet = false;
	}
	return bRet;
}

bool CTextFile::ReadBool(char cToken, bool *pValue, char cTok_B)
{
	bool bRet = false;
	if(Token(cToken) == true) bRet = ReadBool(pValue, cTok_B);
	return bRet;
}

bool CTextFile::WriteString(const char *pBuf)
{
	bool bRet = true;
	fputs(pBuf, m_pFP);
	return bRet;
}

#if defined( _UNICODE )
bool CTextFile::WriteLine(const wchar_t* pBuf)
{
	if (!m_pFP)
		return false;

	fputws(pBuf, m_pFP);
	fputc('\n', m_pFP);
	return true;
}
#else
bool CTextFile::WriteLine(const char *pBuf)
{
	bool bRet = false;
	fputs(pBuf, (FILE *)m_pFP);
	fputc('\n', (FILE *)m_pFP);
	return bRet;
}
#endif

bool CTextFile::Token(char cToken)
{
	bool bRet = true;
	char szBuf[MAX_BUF] = "";
	GetLine(szBuf, sizeof(szBuf)-1, cToken);
	return bRet;
}

bool CTextFile::SkipLine()
{
	bool bRet = true;
	char szBuf[MAX_BUF] = "";
	if(fgets(szBuf, MAX_BUF-1, (FILE *)m_pFP) == NULL) bRet = false;
	return bRet;
}

bool CTextFile::IsEOF()
{
	if( feof(m_pFP) != 0 ) return true;
	return false;
}

bool CTextFile::GetLine(char* szBuf, int nMax)
{
	return GetLine(szBuf, nMax, '\n');
}

bool CTextFile::GetLine(char* szBuf, int nMax, char cToken)
{
	bool bRet = false;

	int nIdx = 0;
	int nData = EOF;
	while( ! IsEOF() && nIdx < nMax)
	{
		nData = fgetc(m_pFP);
		if(cToken == nData || EOF == nData || '\n' == nData) break;
		*(szBuf + nIdx) = nData;
		nIdx++;
	}
	*(szBuf + nIdx) = NULL;
	if(nIdx > 0) bRet = true;

	return bRet;
}

char* CTextFile::TrimLeft(char *pBuf)
{
	char* pTrim = pBuf;
	while(' ' == *pTrim || ASCII_TAB == *pTrim) pTrim++;
	return pTrim;
}

unsigned int CTextFile::htoi(const char *hex_str)
{
	int i;
	int j=0;
	int esc = 0;
	char cha;
	unsigned int h = 0;

	while(esc == 0)
	{
		cha = hex_str[j];
		if( cha>='0' && cha<='9' ) i = cha - '0';
		else if( cha>='a' && cha<='f' ) i = 10+(cha -'a');
		else if( cha>='A' && cha<='F' ) i = 10+(cha -'A');
		else esc = 1;

		if(esc == 0) h = (h<<4) | i;
		j++;
	}
	return(h);
}

const char* CTextFile::YesNoStr(bool bTrueFalse)
{
	if(bTrueFalse) return "YES";
	else return "NO";
}

const char* CTextFile::YesNoStr(int nTrueFalse)
{
	if(nTrueFalse != 0) return "YES";
	else return "NO";
}

const char* CTextFile::TrueFalseStr(bool bTrueFalse)
{
	if(bTrueFalse) return "TRUE";
	else return "FALSE";
}

const char* CTextFile::TrueFalseStr(int nTrueFalse)
{
	if(nTrueFalse != 0) return "TRUE";
	else return "FALSE";
}
