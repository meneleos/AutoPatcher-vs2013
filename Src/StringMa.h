#pragma once
#include "Metin2TorrentConsole.h"
#include <ostream>
#include <iostream>
#include <algorithm>
#include <string>
#include <cassert>
#include <sstream>
#include <windows.h>
#include <iostream>
#include "Shlwapi.h"

#pragma comment(lib, "shlwapi.lib")

template <typename T>
static std::string NumberToString(T Number)
{
	std::ostringstream ss;
	ss << Number;
	return ss.str();
}

static int wreplace(std::wstring& str, const std::wstring& from, const std::wstring& to) {
	int delc = (from.length() > to.length()) ? from.length() - to.length() : 0;
	size_t start_pos = str.find(from, 7);
	if (start_pos == std::string::npos)
		return false;

	str.replace(start_pos, from.length(), to);

	return delc;
}

static void PathStandardizeWindows(MA_PWSTR IN szPath)
{
	//TCHAR temp[MA_MAX_PATH];
	//PathCanonicalize(temp, szPath);
	//szPath = temp;
	std::wstring in = szPath;

	int index = in.find('\\');
	while (index != -1) {
		in[index] = '/';
		index = in.find('\\');
	}

	//index = in.find('./');
	//while (index != -1) {
	//	in[index] = '/';
	//	index = in.find('./');
	//}

	int len = wreplace(in, L"./", L"/");
	wcsncpy(szPath, in.c_str(), in.length() + 1);
}

static void PathStandardizeURI(MA_PWSTR IN szPath)
{
	std::wstring in = szPath;
	int len = wreplace(in, L"/\\", L"/");
	wcsncpy(szPath, in.c_str(), in.length() + 1);
}

template <class _CharType>
inline BOOL _AllocConvMemory(_CharType** ppBuff, int nLength, _CharType* pszFixedBuffer, int nFixedBufferLength)
{
	//ATLENSURE_THROW(ppBuff != NULL, E_INVALIDARG);
	//ATLENSURE_THROW(nLength >= 0, E_INVALIDARG);
	//ATLENSURE_THROW(pszFixedBuffer != NULL, E_INVALIDARG);

	//if buffer malloced, try to realloc.
	if (*ppBuff != pszFixedBuffer) {
		if (nLength > nFixedBufferLength) {
#if defined( _NTR_WINDOWS )
			_CharType* ppReallocBuf = static_cast<_CharType*>(_recalloc(*ppBuff, nLength, sizeof(_CharType)));
#else
			_CharType* ppReallocBuf = static_cast<_CharType*>(recalloc(*ppBuff, nLength, sizeof(_CharType)));
#endif
			if (ppReallocBuf == NULL)
				return FALSE;
			*ppBuff = ppReallocBuf;
		}
		else {
			free(*ppBuff);
			*ppBuff = pszFixedBuffer;
		}
	}
	else { //Buffer is not currently malloced.
		if (nLength > nFixedBufferLength) {
			*ppBuff = static_cast<_CharType*>(calloc(nLength, sizeof(_CharType)));
		}
		else {
			*ppBuff = pszFixedBuffer;
		}
	}
	if (*ppBuff == NULL)
		return FALSE;
	return TRUE;
}

template <class _CharType>
inline void _FreeConvMemory(_CharType* pBuff, _CharType* pszFixedBuffer, int nFixedBufferLength)
{
	(nFixedBufferLength);
	if (pBuff != pszFixedBuffer) {
		free(pBuff);
	}
#ifdef _DEBUG
	else {
		memset(pszFixedBuffer, MA_SECURE_PATTERN, nFixedBufferLength * sizeof(_CharType));
	}
#endif
}

template< int t_nBufferLength = 128 >
class CW2EEX
{
public:
	CW2EEX(LPCWSTR psz) :
		m_psz(m_szBuffer)
	{
		Init(psz);
	}

	CW2EEX(MA_LPCWSTR psz, int nStringLength, MA_UINT nCodePage = CP_UTF8) : m_psz(m_szBuffer)
	{
		Init(psz, nStringLength);
		return;
		nCodePage;
	}

	~CW2EEX()
	{
		_FreeConvMemory(m_psz, m_szBuffer, t_nBufferLength);
	}

	operator MA_LPESTR() const
	{
		return(m_psz);
	}

private:
	void Init(MA_LPCWSTR psz)
	{
		if (psz == NULL) {
			m_psz = NULL;
			return;
		}
		int nLengthW = (int)MA_StringLengthW(psz);
		if (nLengthW == 0) {
			m_psz[0] = '\0';
			return;
		}
		int nLengthE = (int)WCtoEC(psz, nLengthW, NULL, 0);
		if (nLengthE == -1) {
			m_psz[0] = '\0';
			return;
		}

		_AllocConvMemory(&m_psz, nLengthE + 1, m_szBuffer, t_nBufferLength);
		WCtoEC(psz, nLengthW, m_psz, nLengthE + 1);
	}

	void Init(MA_LPCWSTR psz, int nStringLength)
	{
		if (psz == NULL) {
			m_psz = NULL;
			return;
		}

		if (nStringLength == 0) {
			m_psz[0] = '\0';
			return;
		}

		int nLengthW = nStringLength;
		int nLengthE = WCtoEC(psz, nLengthW, NULL, 0);
		if (nLengthE == -1) {
			m_psz[0] = '\0';
			return;
		}

		_AllocConvMemory(&m_psz, nLengthE + 1, m_szBuffer, t_nBufferLength);
		WCtoEC(psz, nLengthW, m_psz, nLengthE + 1);
	}

public:
	MA_LPESTR	m_psz;
	MA_ECHAR	m_szBuffer[t_nBufferLength];
//
//private:
//	CW2EEX(const MA_CW2EEX&);
//	CW2EEX& operator=(const CW2EEX&);
};
typedef CW2EEX<> CW2E;

#ifndef CP_ACP
#define CP_ACP		0
#endif

inline MA_UINT MA_GetConversionACP()
{
	return(CP_UTF8);
}

template< int t_nBufferLength = 128 >
class MA_CA2WEX
{
public:
	MA_CA2WEX(MA_LPCSTR psz) : m_psz(m_szBuffer)
	{
		Init(psz, MA_GetConversionACP());
	}

	MA_CA2WEX(MA_LPCSTR psz, int nStringLength, MA_UINT nCodePage = CP_UTF8) : m_psz(m_szBuffer)
	{
		Init(psz, nStringLength, nCodePage);
	}

	~MA_CA2WEX()
	{
		_FreeConvMemory(m_psz, m_szBuffer, t_nBufferLength);
	}

	operator MA_LPWSTR() const
	{
		return(m_psz);
	}

private:
	void Init(MA_LPCSTR psz, MA_UINT nCodePage)
	{
		if (psz == NULL) {
			m_psz = NULL;
			return;
		}
		int nLengthA = (int)MA_StringLengthA(psz);

		if (nLengthA == 0) {
			m_psz[0] = '\0';
			return;
		}
		int nLengthW = (int)MBtoWC(psz, nLengthA, NULL, 0);

		if (nLengthW == -1) {
			m_psz[0] = '\0';
			return;
		}

		_AllocConvMemory(&m_psz, nLengthW + 1, m_szBuffer, t_nBufferLength);
		MBtoWC(psz, nLengthA, m_psz, nLengthW + 1);
		return;
		(void)nCodePage;  // Code page doesn't matter
	}

	void Init(MA_LPCSTR psz, int nStringLength, MA_UINT nCodePage)
	{
		if (psz == NULL) {
			m_psz = NULL;
			return;
		}
		if (nStringLength == 0) {
			m_psz[0] = '\0';
			return;
		}

		int nLengthA = nStringLength;
		int nLengthW = MBtoWC(psz, nLengthA, NULL, 0);

		if (nLengthW == -1) {
			m_psz[0] = '\0';
			return;
		}

		_AllocConvMemory(&m_psz, nLengthW + 1, m_szBuffer, t_nBufferLength);
		MBtoWC(psz, nLengthA, m_psz, nLengthW + 1);
		return;
		(void)nCodePage;  // Code page doesn't matter
	}

public:
	MA_LPWSTR m_psz;
	wchar_t m_szBuffer[t_nBufferLength];

private:
	MA_CA2WEX(const MA_CA2WEX&);
	MA_CA2WEX& operator=(const MA_CA2WEX&);
};
typedef MA_CA2WEX<> MA_CA2W;

template< int t_nBufferLength = 128 >
class MA_CE2WEX
{
public:
	MA_CE2WEX(MA_LPCESTR psz) : m_psz(m_szBuffer)
	{
		Init(psz);
	}

	MA_CE2WEX(MA_LPCESTR psz, int nStringLength, MA_UINT nCodePage = CP_UTF8) : m_psz(m_szBuffer)
	{
		Init(psz, nStringLength);
		return;
		nCodePage;
	}

	~MA_CE2WEX()
	{
		_FreeConvMemory(m_psz, m_szBuffer, t_nBufferLength);
	}

	operator MA_LPWSTR() const
	{
		return(m_psz);
	}

private:
	void Init(MA_LPCESTR pesz)
	{
		if (pesz == NULL) {
			m_psz = NULL;
			return;
		}
		int nLengthE = (int)MA_StringLengthE(pesz);
		if (nLengthE == 0) {
			m_psz[0] = L'\0';
			return;
		}
		int nLengthW = (int)ECtoWC(pesz, nLengthE, NULL, 0);
		if (nLengthW == -1) {
			m_psz[0] = L'\0';
			return;
		}

		_AllocConvMemory(&m_psz, nLengthW + 1, m_szBuffer, t_nBufferLength);
		ECtoWC(pesz, nLengthE, m_psz, nLengthW + 1);
	}

	void Init(MA_LPCESTR pesz, int nStringLength)
	{
		if (pesz == NULL) {
			m_psz = NULL;
			return;
		}

		if (nStringLength == 0) {
			m_psz[0] = L'\0';
			return;
		}

		int nLengthE = nStringLength;
		int nLengthW = ECtoWC(pesz, nLengthE, NULL, 0);
		if (nLengthW == -1) {
			m_psz[0] = L'\0';
			return;
		}

		_AllocConvMemory(&m_psz, nLengthW + 1, m_szBuffer, t_nBufferLength);
		ECtoWC(pesz, nLengthE, m_psz, nLengthW + 1);
	}

public:
	MA_LPWSTR m_psz;
	wchar_t m_szBuffer[t_nBufferLength];

private:
	MA_CE2WEX(const MA_CE2WEX&);
	MA_CE2WEX& operator=(const MA_CE2WEX&);
};
typedef MA_CE2WEX<> MA_CE2W;

template< int t_nBufferLength = 128 >
class MA_CE2AEX
{
public:
	MA_CE2AEX(MA_LPCESTR pesz) :
		m_psz(m_szBuffer)
	{
		Init(pesz, MA_GetConversionACP());
	}

	MA_CE2AEX(MA_LPCESTR pesz, int nStringLength, MA_UINT nCodePage = CP_UTF8) : m_psz(m_szBuffer)
	{
		Init(pesz, nStringLength, nCodePage);
	}

	~MA_CE2AEX()
	{
		_FreeConvMemory(m_psz, m_szBuffer, t_nBufferLength);
	}

	operator MA_LPSTR() const
	{
		return(m_psz);
	}

private:
	void Init(MA_LPCESTR pesz, MA_UINT nCodePage)
	{
		if (pesz == NULL) {
			m_psz = NULL;
			return;
		}
		int nLengthE = (int)MA_StringLengthE(pesz);
		if (nLengthE == 0) {
			m_psz[0] = '\0';
			return;
		}
		int nLengthA = (int)ECtoMB(pesz, nLengthE, NULL, 0);
		if (nLengthA == -1) {
			m_psz[0] = '\0';
			return;
		}

		_AllocConvMemory(&m_psz, nLengthA + 1, m_szBuffer, t_nBufferLength);
		ECtoMB(pesz, nLengthE, m_psz, nLengthA + 1);
		return;
		(void)nCodePage;  // Code page doesn't matter
	}

	void Init(MA_LPCESTR pesz, int nStringLength, MA_UINT nCodePage)
	{
		if (pesz == NULL) {
			m_psz = NULL;
			return;
		}

		if (nStringLength == 0) {
			m_psz[0] = '\0';
			return;
		}

		int nLengthE = nStringLength;
		int nLengthA = ECtoMB(pesz, nLengthE, NULL, 0);
		if (nLengthA == -1) {
			m_psz[0] = '\0';
			return;
		}

		_AllocConvMemory(&m_psz, nLengthA + 1, m_szBuffer, t_nBufferLength);
		ECtoMB(pesz, nLengthE, m_psz, nLengthA + 1);
		return;
		(void)nCodePage;  // Code page doesn't matter
	}

public:
	MA_LPSTR	m_psz;
	char		m_szBuffer[t_nBufferLength];

private:
	MA_CE2AEX(const MA_CE2AEX&);
	MA_CE2AEX& operator=(const MA_CE2AEX&);
};
typedef MA_CE2AEX<> MA_CE2A;


template< int t_nBufferLength = 128 >
class MA_CW2AEX
{
public:
	MA_CW2AEX(MA_LPCWSTR psz) :
		m_psz(m_szBuffer)
	{
		Init(psz, MA_GetConversionACP());
	}

	MA_CW2AEX(MA_LPCWSTR psz, int nStringLength, MA_UINT nCodePage = CP_UTF8) : m_psz(m_szBuffer)
	{
		Init(psz, nStringLength, nCodePage);
	}

	~MA_CW2AEX()
	{
		_FreeConvMemory(m_psz, m_szBuffer, t_nBufferLength);
	}

	operator MA_LPSTR() const
	{
		return(m_psz);
	}

private:
	void Init(MA_LPCWSTR psz, MA_UINT nCodePage)
	{
		if (psz == NULL) {
			m_psz = NULL;
			return;
		}
		int nLengthW = (int)MA_StringLengthW(psz);
		if (nLengthW == 0) {
			m_psz[0] = '\0';
			return;
		}
		int nLengthA = (int)WCtoMB(psz, nLengthW, NULL, 0);
		if (nLengthA == -1) {
			m_psz[0] = '\0';
			return;
		}

		_AllocConvMemory(&m_psz, nLengthA + 1, m_szBuffer, t_nBufferLength);
		WCtoMB(psz, nLengthW, m_psz, nLengthA + 1);
		return;
		(void)nCodePage;  // Code page doesn't matter
	}

	void Init(MA_LPCWSTR psz, int nStringLength, MA_UINT nCodePage)
	{
		if (psz == NULL) {
			m_psz = NULL;
			return;
		}

		if (nStringLength == 0) {
			m_psz[0] = '\0';
			return;
		}

		int nLengthW = nStringLength;
		int nLengthA = WCtoMB(psz, nLengthW, NULL, 0);
		if (nLengthA == -1) {
			m_psz[0] = '\0';
			return;
		}

		_AllocConvMemory(&m_psz, nLengthA + 1, m_szBuffer, t_nBufferLength);
		WCtoMB(psz, nLengthW, m_psz, nLengthA + 1);
		return;
		(void)nCodePage;  // Code page doesn't matter
	}

public:
	MA_LPSTR m_psz;
	char m_szBuffer[t_nBufferLength];

private:
	MA_CW2AEX(const MA_CW2AEX&);
	MA_CW2AEX& operator=(const MA_CW2AEX&);
};
typedef MA_CW2AEX<> MA_CW2A;

static NTR_INLINE MA_SIZE WCtoWC(MA_LPCWSTR IN szFrom, MA_SIZE IN sizeFrom, MA_LPWSTR OUT szTo, MA_SIZE IN sizeTo)
{
	return MA_StringNCopyW(szTo, sizeTo, szFrom, sizeFrom);
}

#undef MA_WCtoEC
static MA_SIZE	WCtoEC(MA_LPCWSTR IN szFrom, MA_SIZE IN sizeFrom, MA_LPESTR OUT szTo, MA_SIZE IN sizeTo)
{
	int textLen = WideCharToMultiByte(1254, 0, szFrom, sizeFrom, 0, 0, NULL, NULL);
	if (szTo)
		szTo = (MA_LPESTR)textLen;

	return textLen;
}

static MA_SIZE MBtoEC(MA_LPCASTR IN szFrom, MA_SIZE IN sizeFrom, MA_LPESTR OUT szTo, MA_SIZE IN sizeTo)
{
	memcpy(szTo, szFrom, sizeTo);
}

namespace Mantle
{
	static MA_SIZE	MA_MBtoWC(MA_LPCASTR IN szFrom, MA_SIZE IN sizeFrom, MA_LPWSTR OUT szTo, MA_SIZE IN sizeTo)
	{
		if (szFrom == NULL) {
			return 0;
		}
		DWORD num = MultiByteToWideChar(CP_UTF8, 0, szFrom, -1, NULL, 0);
		MultiByteToWideChar(CP_UTF8, MB_PRECOMPOSED, szFrom, -1, szTo, sizeTo);
		return num;
	}
};

static MA_SIZE	MBtoWC(MA_LPCASTR IN szFrom, MA_SIZE IN sizeFrom, MA_LPWSTR OUT szTo, MA_SIZE IN sizeTo)
{
	if (szFrom == NULL) {
		return 0;
	}
	DWORD num = MultiByteToWideChar(CP_UTF8, 0, szFrom, -1, NULL, 0);
	MultiByteToWideChar(CP_UTF8, MB_PRECOMPOSED, szFrom, -1, szTo, sizeTo);
	return num;
}

static MA_SIZE	ECtoWC(MA_LPCESTR IN szFrom, MA_SIZE IN sizeFrom, MA_LPWSTR OUT szTo, MA_SIZE IN sizeTo)
{
	if (szFrom == NULL) {
		return 0;
	}
	DWORD num = MultiByteToWideChar(CP_UTF8, 0, (char*)szFrom, -1, NULL, 0);
	MultiByteToWideChar(CP_UTF8, MB_PRECOMPOSED, (char*)szFrom, -1, szTo, sizeTo);
	return num;
}

static MA_SIZE ECtoMB(MA_LPCESTR IN szFrom, MA_SIZE IN sizeFrom, MA_LPASTR OUT szTo, MA_SIZE IN sizeTo)
{
	if (szFrom == NULL) {
		return 0;
	}
	std::string s(reinterpret_cast<char const*>(szFrom));
	strcpy(szTo, s.c_str());
	return s.length();
}

static MA_SIZE WCtoMB(MA_LPCWSTR IN szFrom, MA_SIZE IN sizeFrom, MA_LPASTR OUT szTo, MA_SIZE IN sizeTo)
{
	wcstombs(szTo, szFrom, sizeTo);
	return strlen(szTo);
}

static std::string StringSearchCharacter(const char* sz, MA_ACHAR delim)
{
	std::string stSrc = sz;
	return stSrc.substr(stSrc.find(delim));
}

static const char* ws = " \t\n\r\f\v";
// trim from end of string (right)
inline std::string& rtrim(std::string& s, const char* t = ws)
{
	s.erase(s.find_last_not_of(t) + 1);
	return s;
}

// trim from beginning of string (left)
inline std::string& ltrim(std::string& s, const char* t = ws)
{
	s.erase(0, s.find_first_not_of(t));
	return s;
}

// trim from both ends of string (right then left)
inline std::string& trim(std::string& s, const char* t = ws)
{
	return ltrim(rtrim(s, t), t);
}

static MA_PASTR MA_StringTrimA(MA_PASTR OUT szDestination, MA_SIZE IN sizeDestination, MA_PCASTR IN szSource)
{
	std::string token = trim(std::string(szSource));
	strcpy(szDestination, token.c_str());

	return "";
}

#define LOWER(c)	(((c)>='A'  && (c) <= 'Z') ? ((c)+('a'-'A')) : (c))
#define UPPER(c)	(((c)>='a'  && (c) <= 'z') ? ((c)+('A'-'a')) : (c))

#ifdef __WIN32__
#define isdigit iswdigit
#define isspace iswspace
#endif

#define ishan(ch)       (((ch) & 0xE0) > 0x90)
#define ishanasc(ch)    (isascii(ch) || ishan(ch))
#define ishanalp(ch)    (isalpha(ch) || ishan(ch))
#define isnhdigit(ch)   (!ishan(ch) && isdigit(ch))
#define isnhspace(ch)   (!ishan(ch) && isspace(ch))
#define TOKEN(string) if (!str_cmp(token_string, string))

/* "Name : 비엽" 과 같이 "항목 : 값" 으로 이루어진 문자열에서
   항목을 token 으로, 값을 value 로 복사하여 리턴한다. */
static void parse_token(char* src, char* token, char* value)
{
	char* tmp;

	for (tmp = src; *tmp && *tmp != ':'; tmp++)
	{
		if (isnhspace(*tmp))
			continue;

		//*(token++) = LOWER(*tmp);
		*(token++) = (*tmp);
	}

	*token = '\0';

	for (tmp += 2; *tmp; tmp++)
	{
		if (*tmp == '\n' || *tmp == '\r')
			continue;

		*(value++) = *tmp;
	}

	*value = '\0';
}

static MA_XINT MA_StringToInt32W(MA_PCWSTR IN tszString, MA_SIZE IN sizeString)
{
	MA_XINT i = wcstol(tszString, NULL, 16);
	return i;
}

static EL_UINT StringToUInt(std::string data, MA_SIZE len)
{
	//unsigned int x;
	unsigned int x = (int)strtol(data.c_str(), NULL, 16);

	//std::stringstream ss;
	//ss << std::hex << data;
	//ss >> x;
	return x;
}

static float StringToFloatW(MA_PCWSTR IN tszString, MA_SIZE IN sizeString)
{
	float x = _wtof(tszString);
	return x;
}

#undef MA_StringToFloatW
static float MA_StringToFloatW(MA_PCWSTR IN tszString, MA_SIZE IN sizeString)
{
	float x = _wtof(tszString);
	return x;
}

#undef MA_StringNCopyA
#undef MA_StringNCopyW

static MA_SIZE NTR_FASTCALL MA_StringNCopyA(MA_PASTR OUT szDestination, MA_SIZE IN sizeDestination, MA_PCASTR IN szSource, MA_SIZE IN sizeSource)
{
	strncpy(szDestination, szSource, sizeSource);
	return strlen(szDestination);
}

static MA_SIZE NTR_FASTCALL MA_StringNCopyW(MA_PWSTR OUT szDestination, MA_SIZE IN sizeDestination, MA_PCWSTR IN szSource, MA_SIZE IN sizeSource)
{
	wcsncpy(szDestination, szSource, sizeSource);
	return wcslen(szDestination);
}

#undef MA_StringCopyA

static MA_SIZE NTR_FASTCALL MA_StringCopyA(MA_PASTR OUT szDestination, MA_SIZE IN sizeDestination, MA_PCASTR IN szSource)
{
	strncpy(szDestination, szSource, sizeDestination);
	return strlen(szDestination);
}

#undef MA_StringCopyW
static MA_SIZE NTR_FASTCALL MA_StringCopyW(MA_PWSTR OUT szDestination, MA_SIZE IN sizeDestination, MA_PCWSTR IN szSource)
{
	wcsncpy(szDestination, szSource, sizeDestination);
	return wcslen(szDestination);
}

#undef MA_StringNCompareA
#undef MA_StringNCompareW

static MA_XINT MA_StringNCompareA(MA_PCSTR OUT szDestination, MA_PCSTR IN szSource, MA_SIZE nCompareLength)
{
	return _strnicmp(szDestination, szSource, nCompareLength);
}

static MA_XINT MA_StringNCompareW(MA_PCWSTR OUT szDestination, MA_PCWSTR IN szSource, MA_SIZE nCompareLength)
{
	return _wcsnicmp(szDestination, szSource, nCompareLength);
}

#undef MA_StringLengthA
#undef MA_StringLengthW

static MA_SIZE MA_StringLengthA(MA_PCSTR IN szString)
{
	return strlen(szString);
}

static MA_SIZE MA_StringLengthW(MA_PCWSTR IN szString)
{
	return wcslen(szString);
}

static MA_SIZE	MA_StringLengthE(MA_PCESTR IN szString)
{
	int i = 0;
	while (*(szString++)) {
		i++;
		if (i == INT_MAX)
			return -1;
	}
	return i;
}

static MA_XINT StringToInt32W(MA_PCWSTR IN tszString, MA_SIZE IN sizeString)
{
	return (int)wcstol(tszString, NULL, 16);
}

#if defined( _NTR_UNICODE )

static void PathSplitFileName(MA_PCWSTR szSourceFileName, MA_PWSTR szFileName, MA_SIZE sizeFileName, MA_PWSTR szExtension, MA_SIZE sizeExtension)
{
	const std::wstring base_filename = std::wstring(szSourceFileName).substr(0, std::wstring(szSourceFileName).find_last_of(_T("\\")) + 1);
	_snwprintf(szFileName, base_filename.length(), L"%s", base_filename.c_str());
}

static void PathMerge(MA_PWSTR dst, MA_SIZE dstLen, MA_PCWSTR branch, MA_PCWSTR leaf)
{
	_snwprintf(dst, dstLen, L"%s\\%s", branch, leaf);
}

static void StringAppendf(MA_PWSTR dst, MA_SIZE dstLen, MA_PCWSTR branch, MA_PCWSTR leaf)
{
	wcscat(dst, branch);
	_snwprintf(dst, dstLen, L"%s%s", dst, leaf);
}

static void StringAppend(MA_PWSTR dst, MA_SIZE dstLen, MA_PCWSTR branch)
{
	wcscat(dst, branch);
	//_snwprintf(dst, dstLen, L"%s%s", dst, branch);
}

static MA_SIZE	StringFormat(MA_PWSTR szDestination, MA_SIZE sizeDestination, MA_PCWSTR szFormat, ...)
{
	//const int size = const_cast<size_t const&>(sizeDestination);
	const size_t size = 1024;
	static wchar_t szBuf[size];

	va_list args;
	va_start(args, szFormat);
	_vsnwprintf(szBuf, sizeof(szBuf), szFormat, args);
	va_end(args);

	wcscpy(szDestination, szBuf);
	return wcslen(szDestination);
}

static MA_SIZE StringFormat(MA_PSTR szDestination, MA_SIZE sizeDestination, MA_PCSTR szFormat, ...)
{
	int const size = const_cast<size_t const&>(sizeDestination);
	static char szBuf[256];

	va_list args;
	va_start(args, szFormat);
	_vsnprintf(szBuf, sizeof(szBuf), szFormat, args);
	va_end(args);

	strcat(szDestination, szBuf);
	return strlen(szDestination);
}

//static void StringFormat(MA_PWSTR dst, MA_SIZE dstLen, MA_PCWSTR branch)
//{
//	wcscat(dst, branch);
//	//_snwprintf(dst, dstLen, L"%s%s", dst, branch);
//}

static bool PathSplit(MA_PCWSTR src, MA_PWSTR branch, MA_SIZE branchLen, MA_PWSTR leaf, MA_SIZE leafLen)
{
	leafLen;
	branchLen;

	MA_PCWSTR p = src;
	MA_PCWSTR n = p;
	while (n = wcschr(p, '\\'))
		p = n + 1;

	//wxMessageBox(p, TAPP_NAME, wxOK | wxICON_INFORMATION);

	if (branch)
		wcsncpy(branch, src, p - src);

	//wxMessageBox(branch, TAPP_NAME, wxOK | wxICON_INFORMATION);
	if (leaf)
		wcscpy(leaf, p);

	//wxMessageBox(leaf, TAPP_NAME, wxOK | wxICON_INFORMATION);

	return true;
}

#else
void PathMerge(MA_PSTR dst, size_t dstLen, MA_PCSTR branch, MA_PCSTR leaf)
{
	_snwprintf(dst, dstLen, L"%s\\%s", branch, leaf);
}

void PathSplit(MA_LPCWSTR* src, MA_LPCWSTR* branch, size_t branchLen, MA_LPCWSTR* leaf, size_t leafLen)
{
	MA_LPCWSTR* p = src;
	MA_LPCWSTR* n = p;
	while (n = wcschr(p, '\\'))
		p = n + 1;

	if (branch)
		wcsncpy(branch, src, p - src);

	if (leaf)
		wcscpy(leaf, p);
}

MA_BOOL		MA_PathMergeA(MA_PSTR szDestination, MA_SIZE sizeDestination, MA_PCSTR szDirectory, MA_PCSTR szLeaf);
#endif
