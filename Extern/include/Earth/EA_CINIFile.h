#ifndef _EA_CINIFILE_H_
#define _EA_CINIFILE_H_

#include <Mantle/MA_STLVector.h>

#include "EA_CTextFile.h"

#define MAX_BUFFER_LEN		512
#define MAX_VALUE_LEN		MAX_BUFFER_LEN
#define MAX_KEY_LEN		256
#define MAX_SECTION_LEN		256

_EA_NAMESPACE_BEGIN

class EA_CINIFile
{
public:
	typedef struct tag_KeyType {
		TCHAR		szKey[MAX_KEY_LEN];
		TCHAR		szValue[MAX_VALUE_LEN];
	} KeyType;

	typedef std::vector<KeyType *> KeyArray;
	typedef KeyArray::iterator KeyItr;

	typedef struct tag_section {
		TCHAR		szName[MAX_KEY_LEN];
		KeyArray	Keys;
	} SectionType;

	typedef std::vector<SectionType *>	SectionArray;
	typedef SectionArray::iterator		SectionItr;

public:
	/// EA_CINIFile ������
	EA_CINIFile();
	/// EA_CINIFile ������
	EA_CINIFile( LPCTSTR szFileName, EA_EOpenFlags nOpenFlags = modeRead );
	/// EA_CINIFile �ı���
	~EA_CINIFile();

	/// INI ������ �����ϰ� ������ �޸𸮿� ���Խ�Ų��.
	/**
	 * @param[in] sFileName INI ���ϸ�
	 * @param[in] nOpenFlags INI ���� ���ٱ���( modeRead, modeWrite, modeCreate, modeAll )		
	 *							
	 * @return TRUE ����
	 * @return FALSE ����
	 */							
	BOOL Open( LPCTSTR szFileName, EA_EOpenFlags nOpenFlags = modeRead );
	/// �޸𸮿� �ִ� ������ ���Ϸ� �����Ѵ�.
	/**
	 * @param void		
	 *							
	 * @return TRUE ����
	 * @return FALSE ����
	 */
	BOOL Save( void );
	/// ����� ������ ������ �����ϰ�, ��� �޸𸮸� �����Ѵ�.
	/**
	 * @param void		
	 *							
	 * @return TRUE ����
	 * @return FALSE ����
	 */
	BOOL Close( void );

	/// ����ڰ� ���ϴ� Section ���� �̵�( m_CurrentSection )
	/**
	 * @param[in] szSection ���Ǹ�
	 *							
	 * @return TRUE ����
	 * @return FALSE ����
	 */
	EA_BOOL		OpenGroup( MA_LPCTSTR IN tszGroup = EA_NULL, EA_BOOL bCreateIfEmpty = EA_FALSE );

	/// Section �� �� ������ ��ȯ
	/**					
	 * @return Section �� ����
	 */
	int SectionCount( void );

	/// ���������� INI KeyName �� �о�´�. KeyName �� �� �� ����Ѵ�.
	/**
	 * @param szKeyName[out] Ű���� ��ȯ�Ѵ�.
	 * @param KeySize[in,out] szKeyName ���� ������( �Է¹��� �� �ִ� �ִ밪�� �����Ѵ�. )
	 * @param szSection[in] ���Ǹ�
	 *							
	 * @return TRUE ����
	 * @return FALSE ����
	 */
	BOOL EnumSection( LPTSTR OUT szSectionName, size_t IN OUT &SectionSize );

	/// Key �� �� ������ ��ȯ
	/**
	 * @param[in] szSection ���Ǹ�
	 *							
	 * @return Key �� ����
	 */
	int KeyCount( LPTSTR szSection = NULL );

	/// ���������� INI KeyName �� �о�´�. KeyName �� �� �� ����Ѵ�.
	/**
	 * @param szKeyName[out] Ű���� ��ȯ�Ѵ�.
	 * @param KeySize[in,out] szKeyName ���� ������( �Է¹��� �� �ִ� �ִ밪�� �����Ѵ�. )
	 * @param szSection[in] ���Ǹ�
	 *							
	 * @return TRUE ����
	 * @return FALSE ����
	 */
	BOOL EnumKey( LPTSTR OUT szKeyName, size_t IN OUT &KeySize, LPCTSTR IN szSection = NULL );

	/// INI ������ �о�´�. ( for s8 )
	/**
	 * @param szKey[in] Ű��
	 * @param s8Value[out] Ű�� ���� ��ȯ�Ѵ�.
	 * @param szSection[in] ���Ǹ�
	 *							
	 * @return TRUE ����
	 * @return FALSE ����
	 */
	BOOL GetValue( LPCTSTR szKey, s8 &s8Value, LPCTSTR szSection = NULL );
	/// INI ������ �о�´�. ( for u8 )
	/**
	 * @param szKey[in] Ű��
	 * @param u8Value[out] Ű�� ���� ��ȯ�Ѵ�.
	 * @param szSection[in] ���Ǹ�
	 *							
	 * @return TRUE ����
	 * @return FALSE ����
	 */
	BOOL GetValue( LPCTSTR szKey, u8 &u8Value, LPCTSTR szSection = NULL );
	/// INI ������ �о�´�. ( for s16 )
	/**
	 * @param szKey[in] Ű��
	 * @param s16Value[out] Ű�� ���� ��ȯ�Ѵ�.
	 * @param szSection[in] ���Ǹ�
	 *							
	 * @return TRUE ����
	 * @return FALSE ����
	 */
	BOOL GetValue( LPCTSTR szKey, s16 &s16Value, LPCTSTR szSection = NULL );
	/// INI ������ �о�´�. ( for u16 )
	/**
	 * @param szKey[in] Ű��
	 * @param u16Value[out] Ű�� ���� ��ȯ�Ѵ�.
	 * @param szSection[in] ���Ǹ�
	 *							
	 * @return TRUE ����
	 * @return FALSE ����
	 */
	BOOL GetValue( LPCTSTR szKey, u16 &u16Value, LPCTSTR szSection = NULL );
	/// INI ������ �о�´�. ( for s32 )
	/**
	 * @param szKey[in] Ű��
	 * @param s32Value[out] Ű�� ���� ��ȯ�Ѵ�.
	 * @param szSection[in] ���Ǹ�
	 *							
	 * @return TRUE ����
	 * @return FALSE ����
	 */
	BOOL GetValue( LPCTSTR szKey, s32 &s32Value, LPCTSTR szSection = NULL );
	/// INI ������ �о�´�. ( for u32 )
	/**
	 * @param szKey[in] Ű��
	 * @param u32Value[out] Ű�� ���� ��ȯ�Ѵ�.
	 * @param szSection[in] ���Ǹ�
	 *							
	 * @return TRUE ����
	 * @return FALSE ����
	 */
	BOOL GetValue( LPCTSTR szKey, u32 &u32Value, LPCTSTR szSection = NULL );
	/// INI ������ �о�´�. ( for s64 )
	/**
	 * @param szKey[in] Ű��
	 * @param s64Value[out] Ű�� ���� ��ȯ�Ѵ�.
	 * @param szSection[in] ���Ǹ�
	 *							
	 * @return TRUE ����
	 * @return FALSE ����
	 */
	BOOL GetValue( LPCTSTR szKey, s64 &s64Value, LPCTSTR szSection = NULL );
	/// INI ������ �о�´�. ( for u64 )
	/**
	 * @param szKey[in] Ű��
	 * @param u64Value[out] Ű�� ���� ��ȯ�Ѵ�.
	 * @param szSection[in] ���Ǹ�
	 *							
	 * @return TRUE ����
	 * @return FALSE ����
	 */
	BOOL GetValue( LPCTSTR szKey, u64 &u64Value, LPCTSTR szSection = NULL );
	/// INI ������ �о�´�. ( for float )
	/**
	 * @param szKey[in] Ű��
	 * @param fValue[out] Ű�� ���� ��ȯ�Ѵ�.
	 * @param szSection[in] ���Ǹ�
	 *							
	 * @return TRUE ����
	 * @return FALSE ����
	 */
	BOOL GetValue( LPCTSTR szKey, float &fValue, LPCTSTR szSection = NULL );

	BOOL GetValue( LPCTSTR szKey, bool &bValue, LPCTSTR szSection = NULL );

	/// GetValueAsString() : INI ������ �о�´�. ( for TCHAR )
	/**
	 * @param szKey[in] Ű��
	 * @param szValue[out] Ű�� ���� ��ȯ�Ѵ�.
	 * @param ValueSize[in] szValue �� ����� �����Ѵ�.
	 * @param szSection[in] ���Ǹ�
	 *							
	 * @return TRUE ����
	 * @return FALSE ����
	 */
	BOOL GetValueAsString( LPCTSTR szKey, LPTSTR szValue, size_t ValueSize, LPCTSTR szSection = NULL );

	/// SetValue() : INI ������ �Է��Ѵ�. ( for s8 )
	/**
	 * @param szKey[in] Ű��
	 * @param s8Value[in] Ű�� ���� ��ȯ�Ѵ�.
	 * @param szSection[in] ���Ǹ�
	 *							
	 * @return TRUE ����
	 * @return FALSE ����
	 */
	BOOL SetValue( LPCTSTR szKey, s8 s8Value, LPCTSTR szSection = NULL );
	/// SetValue() : INI ������ �Է��Ѵ�. ( for u8 )
	/**
	 * @param szKey[in] Ű��
	 * @param u8Value[in] Ű��
	 * @param szSection[in] ���Ǹ�
	 *							
	 * @return TRUE ����
	 * @return FALSE ����
	 */
	BOOL SetValue( LPCTSTR szKey, u8 u8Value, LPCTSTR szSection = NULL );
	/// SetValue() : INI ������ �Է��Ѵ�. ( for s16 )
	/**
	 * @param szKey[in] Ű��
	 * @param s16Value[in] Ű��
	 * @param szSection[in] ���Ǹ�
	 *							
	 * @return TRUE ����
	 * @return FALSE ����
	 */
	BOOL SetValue( LPCTSTR szKey, s16 s16Value, LPCTSTR szSection = NULL );
	/// SetValue() : INI ������ �Է��Ѵ�. ( for u16 )
	/**
	 * @param szKey[in] Ű��
	 * @param u16Value[in] Ű��
	 * @param szSection[in] ���Ǹ�
	 *							
	 * @return TRUE ����
	 * @return FALSE ����
	 */
	BOOL SetValue( LPCTSTR szKey, u16 u16Value, LPCTSTR szSection = NULL );
	/// SetValue() : INI ������ �Է��Ѵ�. ( for s32 )
	/**
	 * @param szKey[in] Ű��
	 * @param s32Value[in] Ű��
	 * @param szSection[in] ���Ǹ�
	 *							
	 * @return TRUE ����
	 * @return FALSE ����
	 */
	BOOL SetValue( LPCTSTR szKey, s32 s32Value, LPCTSTR szSection = NULL );
	/// SetValue() : INI ������ �Է��Ѵ�. ( for u32 )
	/**
	 * @param szKey[in] Ű��
	 * @param u32Value[in] Ű��
	 * @param szSection[in] ���Ǹ�
	 *							
	 * @return TRUE ����
	 * @return FALSE ����
	 */
	BOOL SetValue( LPCTSTR szKey, u32 u32Value, LPCTSTR szSection = NULL );
	/// SetValue() : INI ������ �Է��Ѵ�. ( for s64 )
	/**
	 * @param szKey[in] Ű��
	 * @param s64Value[in] Ű��
	 * @param szSection[in] ���Ǹ�
	 *							
	 * @return TRUE ����
	 * @return FALSE ����
	 */
	BOOL SetValue( LPCTSTR szKey, s64 s64Value, LPCTSTR szSection = NULL );
	/// SetValue() : INI ������ �Է��Ѵ�. ( for u64 )
	/**
	 * @param szKey[in] Ű��
	 * @param u64Value[in] Ű��
	 * @param szSection[in] ���Ǹ�
	 *							
	 * @return TRUE ����
	 * @return FALSE ����
	 */
	BOOL SetValue( LPCTSTR szKey, u64 u64Value, LPCTSTR szSection = NULL );
	/// SetValue() : INI ������ �Է��Ѵ�. ( for float )
	/**
	 * @param szKey[in] Ű��
	 * @param fValue[in] Ű��
	 * @param szSection[in] ���Ǹ�
	 *							
	 * @return TRUE ����
	 * @return FALSE ����
	 */
	BOOL SetValue( LPCTSTR szKey, float fValue, LPCTSTR szSection = NULL );

	BOOL SetValue( LPCTSTR szKey, bool bValue, LPCTSTR szSection = NULL );

	/// SetValueAsString() : INI ������ �Է��Ѵ�. ( for TCHAR )
	/**
	 * @param szKey[in] Ű��
	 * @param szValue[in] Ű��
	 * @param ValueSize[in] szValue �� ����� �����Ѵ�.
	 * @param szSection[in] ���Ǹ�
	 *							
	 * @return TRUE ����
	 * @return FALSE ����
	 */
	BOOL SetValueAsString( LPCTSTR szKey, 
		LPCTSTR szValue, 
		size_t ValueSize, 
		LPCTSTR szSection = NULL );

	/// Load() : �޸𸮿� �ִ� INI ���Ͽ��� ������ �о� Ŭ������ ���Խ�Ų��.
	BOOL Load( LPTSTR tszMemory );
	/// Load() : INI ���Ͽ��� ������ �о� Ŭ������ ���Խ�Ų��.
	BOOL Load( EA_CTextFile *plfFile );
	/// Save() : Ŭ������ �ִ� ������ ���Ϸ� �����Ѵ�.
	BOOL Save( EA_CTextFile*plfFile );

private:
	/// GetSection() : ����ڰ� ���ϴ� Section �� SectionType * �� ��ȯ
	SectionType *GetSection( LPCTSTR szSection );

	/// GetKey() : ����ڰ� ���ϴ� Key �� KeyType * �� ��ȯ
	KeyType *GetKey( LPCTSTR szKey );
	/// GetKey() : ����ڰ� ���ϴ� Key �� KeyType * �� ��ȯ
	KeyType	*GetKey( LPCTSTR szKey, LPCTSTR szSection );

	/// CheckWriteFlag() : ���Ͽ� �� �� �ִ��� ������ �� �Էµ� �÷��׸� �˻��Ѵ�.
	BOOL CheckWriteFlag( void );
	/// SetValue() : Key �� �����Ͽ� Section �� ���Խ�Ų��. �ش� Section �� ���ٸ� ���� �����Ѵ�.
	BOOL SetValue( LPCTSTR szKey, LPCTSTR szValue, LPCTSTR szSection );

	/// CreateSection() : Section �Ѱ��� ���� �����Ѵ�.
	BOOL CreateSection( LPCTSTR szSection );
	/// CreateSection() : Section �Ѱ��� ���� �����Ѵ�.
	BOOL CreateSection( LPCTSTR szSection, KeyArray Keys );

	/// WriteLn() : ���Ͽ� ���˿� ���缭 ������ �����Ѵ�.
	int WriteLn( EA_CTextFile *plfFile, LPCTSTR fmt, ... );

private:
	SectionArray	m_Sections;
	TCHAR		m_szFileName[MA_MAX_PATH];

	u32		m_u32CurrentSIndex;
	TCHAR		m_szCurrentSectionName[MA_MAX_PATH];
	BOOL		m_bDirty;
	u32		m_u32CurrentKeyIndex;
	EA_EOpenFlags	m_nFlag;
};

_EA_NAMESPACE_END

#endif /* _EA_CINIFILE_H_ */
