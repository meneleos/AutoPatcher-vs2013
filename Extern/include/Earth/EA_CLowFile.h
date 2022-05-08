/**
 * @file	EA_CLowFile.h
 * @brief	Earth low-level file class
 * @author	Standil (cpascal@cpascal.net)
 *
 * @version	2005/07/19 cpascal - First release
 */

#ifndef _EA_CLOWFILE_H_
#define _EA_CLOWFILE_H_

#include "EA_IO.h"
//#include "EA_IFileSystem.h"
#include <time.h>

namespace Earth
{

class EA_CLowFile
{
public:
	/// LowFile ������
	EA_CLowFile();

	/// LowFile �ı���
	~EA_CLowFile();

	/// ���� ����
	/**
	 * @param[in] szFilename Open�� ���ϸ�
	 * @param[in] enOpenFlags Open ���
	 *
	 * @return ���� ���⿡ �����ϸ� TRUE
	 */
	BOOL Open( LPCTSTR szFilename, EA_EOpenFlags eOpenFlags = modeRead );

	/**
	 * @brief	Variable argument list�� �̿��ؼ� file�� open �Ѵ�.
	 * @param[in]	szFormat	Open�� filen name�� format
	 * @parma[in]	pArgs		va_list
	 * @param[in]	enOpenFlags	Open ���
	 *
	 * @return ���� ���⿡ �����ϸ� TRUE
	 */
	BOOL Openv( LPCTSTR IN tszFormat, va_list IN pArgs, EA_EOpenFlags IN eOpenFlags = modeRead );

	/// �б����� ���� ���� ����(Formatted Filename ����)
	/**
	 * @param[in] szFilename Open�� Formatted Filename
	 *
	 * @return ���� ���⿡ �����ϸ� TRUE
	 */
	BOOL OpenToReadf( LPCTSTR szFilename, ... );

	/// �������� ���� ���� ����(Formatted Filename ����)
	/**
	 * @param[in] szFilename Open�� Formatted Filename
	 *
	 * @return ���� ���⿡ �����ϸ� TRUE
	 */
	BOOL OpenToWritef( LPCTSTR szFilename, ... );

	/// ���� ���� ���� ����(Formatted Filename ����)
	/**
	 * @param[in] szFilename Open�� Formatted Filename
	 *
	 * @return ���� ���⿡ �����ϸ� TRUE
	 */
	BOOL OpenToCreatef( LPCTSTR szFilename, ... );

	/// ���� �ݱ�
	void Close( void );

	/// ������ �����ִ��� Ȯ��
	/**
	 * @return ���������� TRUE, �������� ������ FALSE
	 */
	BOOL IsOpened( void )			{ return (m_hFile != INVALID_HANDLE_VALUE) && (m_hFile != NULL); }

	/// ���� �����̸� ���
	LPCTSTR	GetFileName( void ) const	{ return m_szFilename; }

	/// ���� ���� ���
	/**
	 * @return ���� ���̸� ��ȯ�Ѵ�.
	 */
	MA_FSIZE Size( void ) const;

	/// ���� ��ġ ���
	/**
	 * @return ������ ���� ��ġ�� ��ȯ�Ѵ�.
	 */
	MA_FSIZE GetFilePointer( void ) const;

	/// ���� �б�
	size_t Read( LPVOID lpBuffer, size_t sizeToRead );

	/// ���� ����
	size_t Write( LPCVOID lpBuffer, size_t sizeToWrite );

	/// ��ġ �̵�
	MA_FSIZE Seek( MA_FSIZE sizeBytesToMove , EA_ESeekFlags eMoveMethod );

	/// Flush
	BOOL Flush( void );

	/// ������ �˻�
	BOOL IsEOF( void ) const;

	/// FileTime(Write) ���
	time_t GetTime( void );

	/// FileTime(Write) ����
	BOOL   SetTime( time_t timeSet );

	/// ���� �Ӽ� ������
	u32 GetAttribute();

	// NULLó���� �ϰ� HANDLE����
	HANDLE	GetSafeHandle() const;

	// HANDLE �ٷ� ����
	HANDLE	GetHandle() const;

	/// ���� ���翩�� �˻� (���ڷ� �����̸��� ����)
	static BOOL sAccess( LPCTSTR szFilename );

	/// ���� ���� ��� (���ڷ� �����̸��� ����)
	static MA_FSIZE sSize( LPCTSTR szFilename );

	/// ���� �б� (���ڷ� �����̸��� ����)
	static MA_SIZE sRead( LPCTSTR szFilename, LPVOID lpBuffer, size_t sizeBytesToRead );

	/// ���� ���� (���ڷ� �����̸��� ����)
	static MA_SIZE sWrite( LPCTSTR szFilename, LPVOID lpBuffer, size_t sizeBytesToRead );

	/// ���� �Ӽ� ������
	static u32 sGetAttribute( LPCTSTR tszFileName );

private:
	/// ���� ���� �ڵ�
	HANDLE		m_hFile;

	/// �����̸�
	MA_TCHAR	m_szFilename[MA_MAX_PATH];
};

typedef EA_CLowFile*	EA_PCLowFile;

};

#endif /* _EA_CLOWFILE_H_ */

