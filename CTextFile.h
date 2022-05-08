// TextFile.h : Interface for the CTextFile class.
// Create : 2002.7.12
// Last Update : 2006.07.24
// Programed by Chang-su, Kim
//
// This Class is to parse Text Configration File
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TEXTFILE_H__DE7D3573_9470_11D6_B64F_009027E90DD2__INCLUDED_)
#define AFX_TEXTFILE_H__DE7D3573_9470_11D6_B64F_009027E90DD2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

enum TextFileModeEnum
{
	TEXT_FILE_READ,
	TEXT_FILE_WRITE,
	TEXT_FILE_CREATE,
	TEXT_FILE_APPEND
};

class CTextFile
{
public:
	CTextFile();
	virtual ~CTextFile();

	bool Open(const wchar_t* szFileName, int nMode = TEXT_FILE_READ);
	bool Open(const char *szFileName, int nMode = TEXT_FILE_READ);
	bool Create(const char *szFileName)
	{
		return Open(szFileName, TEXT_FILE_CREATE);
	}
	bool Close();
	bool FileExist(const char *szFileName);
#if defined( _UNICODE )
	bool DeleteFile(const wchar_t *szFileName);
#else
	bool DeleteFile(const char* szFileName);
#endif

	bool ReadWord(char *pBuf, char cToken = NULL);
	bool ReadWord(char cToken, char *pBuf, char cTok_B = NULL);
	bool ReadLine(char *pBuf, char cToken = '\n');
	bool ReadLine(char cToken, char *pBuf);
	bool ReadInt(int *pValue, char cToken = NULL);
	bool ReadInt(char cToken, int *pValue, char cTok_B = NULL);
	bool ReadFloat(float *pValue, char cToken = NULL);
	bool ReadFloat(char cToken, float *pValue, char cTok_B = NULL);
	bool ReadHexa(unsigned int *pValue, char cToken = NULL);
	bool ReadHexa(char cToken, unsigned int *pValue, char cTok_B = NULL);
	bool ReadDate(int *pYear, int *pMonth, int *pDay, char cToken = NULL);
	bool ReadDate(char cToken, int *pYear, int *pMonth, int *pDay, char cTok_B = NULL);
	bool ReadBool(bool *pValue, char cToken = NULL);
	bool ReadBool(char cToken, bool *pValue, char cTok_B = NULL);

	bool Token(char cToken);
	bool SkipLine();
	bool IsEOF();
	bool WriteString(const char *pBuf);
#if defined( _UNICODE )
	bool WriteLine(const wchar_t*pBuf);
#else
	bool WriteLine(const char *pBuf);
#endif

	unsigned int htoi(const char *hex_str);
	const char* YesNoStr(bool bTrueFalse);
	const char* YesNoStr(int nTrueFalse);
	const char* TrueFalseStr(bool bTrueFalse);
	const char* TrueFalseStr(int nTrueFalse);

private:
	bool CTextFile::GetLine(char* szBuf, int nMax);
	bool CTextFile::GetLine(char* szBuf, int nMax, char cToken);

private:
	char* TrimLeft(char *pBuf);

// Member Variable
protected:
	FILE* m_pFP;
};

#endif // !defined(AFX_TEXTFILE_H__DE7D3573_9470_11D6_B64F_009027E90DD2__INCLUDED_)

//////////////////////////////////////////////////////////////////////
/* Update History
2002.07.12	Created, Text File Reading 및 Parsing class
2005.09.05	Update History 기록 시작
			일부 char type을 const char type으로 변경
2006.07.24	DeleteFile(...) Func 추가
--------------------------------------------------------------------*/