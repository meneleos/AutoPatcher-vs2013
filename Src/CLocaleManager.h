#pragma once

#include <unordered_map>
#include <Earth/EA_Singleton.h>

class CLocaleManager
{
	public:		
		bool			Load(MA_LPCTSTR tszFileName, CStatus* pcStatus);

		MA_LPCWSTR		Get(MA_LPCWSTR wszKey);
		MA_LPCWSTR		Get(MA_LPCASTR aszKey);
		bool			Add(MA_LPCWSTR wszKey, MA_LPCWSTR wszValue);
		bool			Add(MA_LPCASTR wszKey, MA_LPCWSTR wszValue);

	private:
		typedef std::unordered_map<EL_UINT32, std::wstring> LocaleMap;

		LocaleMap		m_localeMap;

		EA_DECLARE_SINGLETON(CLocaleManager)
};

#define EL_LTEXT(x) CLocaleManager::sGetActive()->Get(L##x)
