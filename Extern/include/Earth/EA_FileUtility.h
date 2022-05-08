/**
* @file		EA_FileUtility.h
* @brief	Galaxy file utility functions
* @author	Standil (cpascal@cpascal.net)
*
* @version	2008/04/24 cpascal - First release
**/

#ifndef _EA_FILEUTILITY_H_
#define _EA_FILEUTILITY_H_

_NTR_EXTERN_C_BEGIN

#if defined( _NTR_ASCII )
#define	EA_GetFileAttributes					EA_GetFileAttributesA
#define	EA_SetFileAttributes					EA_SetFileAttributesA
#define EA_AccessFile						EA_AccessFileA
#define	EA_MakeDirectory					EA_MakeDirectoryA
#define	EA_MakeDirectoryRecursive				EA_MakeDirectoryRecursiveA
#elif defined( _NTR_UNICODE )
#define	EA_GetFileAttributes					EA_GetFileAttributesW
#define	EA_SetFileAttributes					EA_SetFileAttributesW
#define EA_AccessFile						EA_AccessFileW
#define	EA_MakeDirectory					EA_MakeDirectoryW
#define	EA_MakeDirectoryRecursive				EA_MakeDirectoryRecursiveW
#else
#define	EA_GetFileAttributes					EA_GetFileAttributesE
#define	EA_SetFileAttributes					EA_SetFileAttributesE
#define EA_AccessFile						EA_AccessFileE
#define	EA_MakeDirectory					EA_MakeDirectoryE
#define	EA_MakeDirectoryRecursive				EA_MakeDirectoryRecursiveE
#endif

EA_BOOL	EA_GetFileVersion( VS_FIXEDFILEINFO* pstVersion, u64 OUT *pu64FileVersion, u64 OUT *pu64ProductVersion, u64 OUT *pu64VersionCreateTime );
EA_BOOL	EA_GetFileVersionByFile( MA_PCTSTR IN tszPath, u64 OUT *pu64Version, u64 OUT *pu64VersionCreateTime );

/*
 * Functions: GetFileAttributes
 * ������ Attributes�� ��´�.
 *
 * Parameters:
 *	tszFileName [in]	- Ȯ���� ������ �̸�
 *
 * Returns:
 *	������ Attributes�� ����.
 */
EA_DWORD	EA_GetFileAttributesA( MA_PCASTR szFileName );
EA_DWORD	EA_GetFileAttributesW( MA_PCWSTR szFileName );
EA_DWORD	EA_GetFileAttributesE( MA_PCESTR szFileName );

/*
 * Functions: SetFileAttributes
 * ������ Attributes�� �����Ѵ�.
 *
 * Parameters:
 *	tszFileName [in]	- ������ ������ �̸�
 *	dwAttributes [in]	- ������ Attributes
 *
 * Returns:
 *	������ Attributes�� �����ϴ� �� �����ߴٸ� EA_TRUE��, �׷��� ������ EA_FALSE�� ����.
 */
EA_BOOL		EA_SetFileAttributesA( MA_PCASTR tszFileName, DWORD IN dwAttributes );
EA_BOOL		EA_SetFileAttributesW( MA_PCWSTR tszFileName, DWORD IN dwAttributes );
EA_BOOL		EA_SetFileAttributesE( MA_PCESTR tszFileName, DWORD IN dwAttributes );

/*
 * Functions: AccessFile
 * ������ �����ϴ��� Ȯ��.
 *
 * Parameters:
 *	tszFileName [in]	- Ȯ���� ������ �̸�
 *
 * Returns:
 *	������ �����Ѵٸ� EA_TRUE��, �׷��� ������ EA_FALSE�� ����.
 */
EA_BOOL		EA_AccessFileA( MA_PCASTR IN szFileName );
EA_BOOL		EA_AccessFileW( MA_PCWSTR IN szFileName );
EA_BOOL		EA_AccessFileE( MA_PCESTR IN szFileName );

/*
 * Functions: EA_MakeDirectory
 * ���丮�� �����.
 *
 * Parameters:
 *	tszPathName [in]	- ���� ���丮 �̸�
 */
EA_BOOL		EA_MakeDirectoryA( MA_PCASTR IN tszPathName );
EA_BOOL		EA_MakeDirectoryW( MA_PCWSTR IN tszPathName );
EA_BOOL		EA_MakeDirectoryE( MA_PCESTR IN tszPathName );

/*
 * Functions: EA_MakeDirectoryRecursive
 * Recursive ��θ��� ���丮�� �����.
 *
 * Parameters:
 *	tszPathName [in]	- ���� ���丮 �̸�
 */
EA_BOOL		EA_MakeDirectoryRecursiveA( MA_PCASTR IN tszPathName );
EA_BOOL		EA_MakeDirectoryRecursiveW( MA_PCWSTR IN tszPathName );
EA_BOOL		EA_MakeDirectoryRecursiveE( MA_PCESTR IN tszPathName );


EA_BOOL		EA_IsValidDirectory( DWORD IN dwAttributes );

_NTR_EXTERN_C_END

#endif /* !_EA_FILEUTILITY_H_ */
