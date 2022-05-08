#pragma once
#include "Metin2TorrentConsole.h"

class WIN_CUAC
{
	public:
		WIN_CUAC();
		~WIN_CUAC();

		MA_BOOL		Init(void);

		MA_BOOL		RunElevated(MA_LPCTSTR tszFile, MA_LPCTSTR tszParameters, bool bGetCode = false);

		MA_BOOL		HasAdminRights(void) const;
		DWORD		GetElevationType(TOKEN_ELEVATION_TYPE* peTokenElevationType) const;
		MA_BOOL		IsUACSupported(void) const;
		//MA_BOOL		IsFileWritable(MA_LPCTSTR tszFile) const;

	protected:
		MA_BOOL		m_bInit;
};
