#pragma once

#include <Mantle\NTR_OSFamilyWindows.h>
#include <Mantle/MA_STLList.h>
#include <Mantle/MA_STLVector.h>
#include <Mantle/MA_Type.h>

class CStatus
{
	public:

		enum EA_STATUS_TYPE {
			EA_STATUS_INFO = 0,
			EA_STATUS_WARNING,
			EA_STATUS_ERROR,
			EA_STATUS_FATAL,
			EA_STATUS_QUANTITY
		};

		CStatus();
		~CStatus();

		void			Clear(void);
		bool			IsEmpty(void);

		//EA_BOOL			Add(EA_STATUS_TYPE eSeverity, LPCTSTR tszMessage);
		//EA_BOOL			Addf(EA_STATUS_TYPE eSeverity, LPCTSTR tszFormat, ...);
		bool			AddNR(EA_STATUS_TYPE eSeverity, LPCTSTR tszMessage);
		bool			AddNRf(EA_STATUS_TYPE eSeverity, LPCTSTR tszFormat, ...);
		//EA_BOOL			Prepend(EA_STATUS_TYPE eSeverity, LPCTSTR tszMessage);
		//EA_BOOL			Prependf(EA_STATUS_TYPE eSeverity, LPCTSTR tszFormat, ...);
		//EA_BOOL			PrependNR(EA_STATUS_TYPE eSeverity, LPCTSTR tszMessage);
		//EA_BOOL			PrependNRf(EA_STATUS_TYPE eSeverity, LPCTSTR tszFormat, ...);
		//EA_BOOL			GetString(MA_LPTSTR tszBuffer, EA_SIZE sizeBuffer, EA_STATUS_TYPE eMinSeverity = EA_STATUS_INFO);
		//EA_SIZE			GetStringLength(EA_STATUS_TYPE eMinSeverity = EA_STATUS_INFO);
		//MA_LPTSTR		GetStringAlloc(EA_STATUS_TYPE eMinSeverity = EA_STATUS_INFO);
		MA_LPTSTR		GetString(EA_STATUS_TYPE eMinSeverity = EA_STATUS_INFO);

		//EA_STATUS_TYPE	GetHighestSeverity();
		CStatus& operator=(const CStatus& cStatus);

	protected:
		struct SSTATUSENTRY {
			MA_LPTSTR			tszText;
			EA_STATUS_TYPE		eSeverity;
			//TSExplicitList<STATUSENTRY,8> statusList;
		};

		MA_DEFINE_STL_LIST(Status, struct SSTATUSENTRY);
		ListStatus			m_listStatus;
		MA_LPTSTR			m_tszBuffer;
};
