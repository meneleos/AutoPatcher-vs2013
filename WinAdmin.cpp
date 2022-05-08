#include "Metin2TorrentConsole.h"

#include "WinAdmin.h"

#include <winnt.h>
#include <shellapi.h>


WIN_CUAC::WIN_CUAC()
{

}

WIN_CUAC::~WIN_CUAC()
{

}

MA_BOOL WIN_CUAC::Init(void)
{

	return true;
}

MA_BOOL WIN_CUAC::RunElevated(MA_LPCTSTR tszFile, MA_LPCTSTR tszParameters, bool bGetCode)
{
	// Launch itself as admin
	SHELLEXECUTEINFO sei = { sizeof(sei) };
	sei.fMask = SEE_MASK_NOCLOSEPROCESS;
	sei.lpVerb = L"runas";
	sei.lpFile = tszFile;
	sei.lpParameters = tszParameters;
	sei.hwnd = NULL;
	sei.nShow = SW_NORMAL;
	if (!ShellExecuteEx(&sei))
	{
		DWORD dwError = GetLastError();
		if (dwError == ERROR_CANCELLED)
			return -2; // The user refused to allow privileges elevation.
	}
	else
	{
		if (bGetCode)
		{
			WaitForSingleObject(sei.hProcess, 10000);
			DWORD ExitCode = -4;
			BOOL success = GetExitCodeProcess(sei.hProcess, &ExitCode);
			CloseHandle(sei.hProcess);
			return success ? ExitCode : -4;
		}
		return 0;
	}
	return -1;
}

MA_BOOL WIN_CUAC::IsUACSupported() const
{
	HKEY hkey;
	DWORD value = 1, size = sizeof(DWORD);

	OSVERSIONINFO osvi;

	ZeroMemory(&osvi, sizeof(OSVERSIONINFO));
	osvi.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);

	GetVersionEx(&osvi);

	if (osvi.dwMajorVersion < 6)
	{
		return FALSE;
	}

	if (RegOpenKeyEx(HKEY_LOCAL_MACHINE, _T("Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\System"), 0, KEY_READ, &hkey) == ERROR_SUCCESS)
	{
		if (RegQueryValueEx(hkey, _T("EnableLUA"), 0, 0, (LPBYTE)&value, &size) != ERROR_SUCCESS)
			value = 1;

		RegCloseKey(hkey);
	}

	return value != 0;
}


DWORD WIN_CUAC::GetElevationType(TOKEN_ELEVATION_TYPE* peTokenElevationType) const
{
	if (!peTokenElevationType)
		return E_POINTER;

	*peTokenElevationType = TokenElevationTypeDefault;

	HANDLE process_token;
	if (!OpenProcessToken(GetCurrentProcess(), TOKEN_QUERY, &process_token))
		return HRESULT_FROM_WIN32(GetLastError());

	DWORD size;
	TOKEN_ELEVATION_TYPE elevation_type;
	if (!GetTokenInformation(process_token, TokenElevationType, &elevation_type,
		sizeof(elevation_type), &size)) {
		return HRESULT_FROM_WIN32(GetLastError());
	}

	*peTokenElevationType = elevation_type;
	return S_OK;
}

MA_BOOL WIN_CUAC::HasAdminRights(void) const
{
	MA_BOOL fRet = MA_FALSE;
	HANDLE hToken = NULL;
	if (OpenProcessToken(GetCurrentProcess(), TOKEN_QUERY, &hToken)) {
		TOKEN_ELEVATION Elevation;
		DWORD cbSize = sizeof(TOKEN_ELEVATION);
		if (GetTokenInformation(hToken, TokenElevation, &Elevation, sizeof(Elevation), &cbSize)) {
			fRet = Elevation.TokenIsElevated;
		}
	}
	if (hToken) {
		CloseHandle(hToken);
	}
	return fRet;
}

//MA_BOOL WIN_CUAC::HasAdminRights(void) const
//{
//	static bool evaluated = false;
//	static bool has_rights = false;
//
	//if (!evaluated) {
	//	TOKEN_ELEVATION_TYPE elevation;
	//	if (SUCCEEDED(GetElevationType(&elevation))) {
	//		base::IntegrityLevel level = base::GetCurrentProcessIntegrityLevel();
	//			if (level != base::INTEGRITY_UNKNOWN) {
	//				has_rights = (elevation == TokenElevationTypeFull) ||
	//					(level == base::HIGH_INTEGRITY);
	//			}
	//		}
	//	}
	//}

	//evaluated = true;
	//if (!has_rights)
	//	ASSERT_STRING("ProcessInfo::HasAdminRights: Does not have admin rights.");

	//return has_rights;
//}


bool hasAdminRights()
{
	SID_IDENTIFIER_AUTHORITY authority = { SECURITY_NT_AUTHORITY };
	PSID adminGroup;
	// Initialize SID.
	if (!AllocateAndInitializeSid(&authority,
		2,
		SECURITY_BUILTIN_DOMAIN_RID,
		DOMAIN_ALIAS_RID_ADMINS,
		0, 0, 0, 0, 0, 0,
		&adminGroup))
		return false;

	BOOL isInAdminGroup = FALSE;
	if (!CheckTokenMembership(0, adminGroup, &isInAdminGroup))
		isInAdminGroup = FALSE;

	FreeSid(adminGroup);
	return (bool)isInAdminGroup;
}
