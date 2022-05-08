#pragma once

/// \brief ����� ������ ��ȯ�Ѵ�.
LPCTSTR EL_GetUserInfo();

/// \brief �������� ������ ��ȯ�Ѵ�.
LPCTSTR EL_GetOSInfo();

/// \brief CPU ������ ��ȯ�Ѵ�.
LPCTSTR EL_GetCpuInfo();

/// \brief �޸� ������ ��ȯ�Ѵ�.
LPCTSTR EL_GetMemoryInfo();

/// \brief �������� ������ �˾Ƴ���.
bool EL_GetWinVersion( LPTSTR pszVersion, int *nVersion, LPTSTR pszMajorMinorBuild );

// \brief ������ ������ �˾Ƴ���
VS_FIXEDFILEINFO EL_GetFixedFileInfo( LPCTSTR tszFileName );
