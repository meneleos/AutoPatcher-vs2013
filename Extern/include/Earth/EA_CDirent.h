/**
 * @file	EA_CDirent.h
 * @brief	Solar ���̺귯���� Directory Entry Ŭ���� ��� ����.
 * @author	cppis (cppeins@gmail.com)
 *
 * @version	2007/03/15 cppis - First release
 *
 * @see		EA_CDirentEx
 */

#ifndef _EA_CDIRENT_H_
#define _EA_CDIRENT_H_

_EA_NAMESPACE_BEGIN

/*
 * Class:	EA_CDirent
 * Directory Entry ó�� Ŭ����
 */
class EA_CDirent
{
public:
	/*
	 * Constructor:	EA_CDirent
	 * EA_CDirent�� �⺻ ������.
	 */
	EA_CDirent( void );

	/*
	 * Destructor:	~EA_CDirent
	 * EA_CDirent�� �Ҹ���.
	 */
	~EA_CDirent( void );

	/*
	 * Methods: Open
	 * ���� Open
	 *
	 * Parameters:
	 *	tszFileName [in] - Open�� ���ϸ�
	 *	enOpenFlags [in] - Open ���
	 *
	 * Returns:
	 *	���� ���⿡ �����ϸ� EA_TRUE, �׷��� ������ EA_FALSE�� ����
	 */
	EA_BOOL		Open( MA_PCTSTR IN tszFileName );

	/*
	 * Methods: FindFiles
	 * ���� Open
	 *
	 * Parameters:
	 *	tszFileName [in] - Open�� ���ϸ�
	 *	enOpenFlags [in] - Open ���
	 *
	 * Returns:
	 *	���� ���⿡ �����ϸ� EA_TRUE, �׷��� ������ EA_FALSE�� ����
	 */
	EA_BOOL		FindFiles( MA_PCTSTR IN tszFileName );

	/*
	 * Methods: Open
	 * ���� ����(Formatted FileName ����)
	 *
	 * Parameters:
	 *	tszFileName [in] - Open�� Formatted FileName
	 *
	 * Returns:
	 *	���� ���⿡ �����ϸ� EA_TRUE, �׷��� ������ EA_FALSE�� ����
	 */
	EA_BOOL		Openf( MA_PCTSTR IN tszFileName, ... );

	/*
	 * Methods: Read
	 * ù��° ��Ʈ��(���� �Ǵ� ���丮)�� �о�´�.
	 * EA_CDirent�� Directory DOT( _T("."), _T("..") )�� �����Ͽ� ó���Ѵ�.
	 *
	 * Parameters:
	 *	tszFileName [out]	- Read�� FileName
	 *	sizeFileName [in]	- Read�� FileName �ִ� ����
	 *	psizeFile [out]		- Read�� File ������
	 *	u32Attributes [out]	- Read�� File Attributes
	 *
	 * Returns:
	 *	���� ���⿡ �����ϸ� EA_TRUE, �׷��� ������ EA_FALSE�� ����
	 */
	EA_BOOL		Read( MA_PTSTR OUT tszFileName, EA_SIZE IN sizeFileName, EA_SIZE* OUT psizeFile, EA_DWORD* OUT pdwAttributes );


#if defined( _NTR_WINDOWS )
	EA_HANDLE	GetDirent( void )			{ return m_hDirent;		}
#else
	DIR*		GetDirent( void )			{ return m_pDirent;		}
#endif
	MA_PCTSTR	GetDirentName( void )		{ return m_tszDirentName;	}

	MA_PCTSTR	GetBaseDirectory( void )	{ return m_tszBaseDirectory;	}

	// ���� ���丮 ��Ʈ���� ��ġ�� ������.
	void	SetPosition( LONG IN lLocation );

	// ���� ���丮 ��Ʈ���� ��ġ�� ��ȯ��.
	LONG	GetPosition( void );

	// ���丮 ��Ʈ���� ���丮�� ���� ������ �ʱ�ȭ��.
	void	Rewind( void );

	// ���� �ݱ�
	void	Close( void );

protected:
	EA_DIRENT_HANDLE	m_hDirent;
	MA_TCHAR			m_tszDirentName[ MA_MAX_PATH ];
	MA_TCHAR			m_tszBaseDirectory[ MA_MAX_PATH ];
};

_EA_NAMESPACE_END

#endif /* !_EA_CDIRENT_H_ */
