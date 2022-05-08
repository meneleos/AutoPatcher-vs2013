/**
 * @file	EA_CDynamicModule.h
 * @brief	Earth Dynamic Module class header
 * @author	Standil (cpascal@cpascal.net)
 *
 * @version	2009/11/16 cpascal - First release
 */

#ifndef _EA_CDYNAMICMODULE_H_
#define _EA_CDYNAMICMODULE_H_

_EA_NAMESPACE_BEGIN

class EA_CDynamicModule
{
public:
	// EA_CDynamicModule ������
	EA_CDynamicModule( void ) : m_hDM( EA_NULL )		{}

	// EA_CDynamicModule �ı���
	virtual ~EA_CDynamicModule( void )			{ Destroy(); }

	void	Destroy( void )						{ EA_SAFE_FREELIBRARY( m_hDM ); }


	/**
	 * @brief	���̺귯���� �ε�Ǿ� �ִ��� Ȯ���Ѵ�.
	 * @returns	���� ���⿡ �����ϸ� EA_TRUE��, �׷��� ������ EA_FALSE�� ����
	 */
	EA_BOOL	IsLoaded( void ) const
	{
		return (m_hDM != EA_NULL)? EA_TRUE: EA_FALSE;
	}

	/**
	 * @brief	���̺귯���� �ε��Ѵ�.
	 * @param[in]	tszDll - DLL ���ϸ�
	 * @returns	�ʱ�ȭ�� �����ϸ� EA_TRUE��, �׷��� ������ EA_FALSE�� ����
	 */
	virtual EA_BOOL	vInit( MA_PCTSTR IN /*tszDll*/ )		{ return EA_FALSE; }

protected:
	EA_HMODULE	m_hDM;
};


// Macros: DECLARE_DM_FUNCTION
// �Լ��� �����Ѵ�.
#define EA_DECLARE_DM_FUNCTION( ret, cc, func, params )						\
		ret ( cc *func )params;

// Macros: BEGIN_DM_VINIT
// vInit() �������̵� �Լ� ����, ���̺귯���� �ε��Ѵ�.
#define EA_BEGIN_DM_VINIT()													\
	EA_BOOL	vInit( MA_PCTSTR IN tszDll )									\
	{																		\
		EA_SAFE_FREELIBRARY( m_hDM );										\
		m_hDM = ::LoadLibrary( tszDll );									\
		EA_BOOL	bOk = EA_FALSE;

// Macros: VINIT_DM_TWIN_FUNCTION
// ����� �Լ��� �����͸� �����´�. �Լ��� ���� ����.
#define EA_VINIT_DM_TWIN_FUNCTION_NULLABLE( ret, cc, func, params, origin )	\
		if( m_hDM )															\
			func = ( ret ( cc * )params )GetProcAddress( m_hDM, origin );	\
		else																\
			func = Earth::EA_NULL;											\

// Macros: VINIT_DM_TWIN_FUNCTION
// ����� �Լ��� �����͸� �����´�. �Լ��� ���� ����.
#define EA_VINIT_DM_TWIN_FUNCTION( ret, cc, func, params, origin )			\
		EA_VINIT_DM_TWIN_FUNCTION_NULLABLE( ret, cc, func, params, origin )	\
		if( func )															\
			bOk = EA_TRUE;

// Macros: VINIT_DM_FUNCTION
// ����� �Լ��� �����͸� �����´�. �Լ��� ���� �Ұ�.
#define EA_VINIT_DM_FUNCTION_NULLABLE( ret, cc, func, params )				\
		if( m_hDM )															\
			func = ( ret ( cc * )params )GetProcAddress( m_hDM, #func );	\
		else																\
			func = EA_NULL;													\

// Macros: VINIT_DM_FUNCTION
// ����� �Լ��� �����͸� �����´�. �Լ��� ���� �Ұ�.
#define EA_VINIT_DM_FUNCTION( ret, cc, func, params )						\
		EA_VINIT_DM_FUNCTION_NULLABLE( ret, cc, func, params )				\
		if( func )															\
			bOk = EA_TRUE;

// Macros: END_DM_VINIT
// vInit() �������̵� �Լ� ��
#define EA_END_DM_VINIT()								\
		return bOk;										\
	}

_EA_NAMESPACE_END

#endif /* !_EA_CDYNAMICMODULE_H_ */
