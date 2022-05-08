/**
 * @file	EA_CMD5Checksum.h
 * @brief	Baekdu Checksum Library
 * @author	bugmail (bugmail@buddygames.co.kr)
 *
 * @version	2005/08/12 bugmail - first release
 */
#ifndef	_MD5_CHECKSUM_H_
#define	_MD5_CHECKSUM_H_


#include "EA_IMDChecksum.h"

_EA_NAMESPACE_BEGIN

/**
 * @brief	MD5�� Checksum�� ��� �κ��� ĸ��ȭ�� Ŭ����
 * @author	bugmail (bugmail@buddygames.co.kr)
 * @remark	�ܺο��� ���η����� ���� ���� ���ϰ� �ܺο� ������ �κ��� UpdateChecksum�� �����Ϳ� �����ͻ����� �ۿ� ����.
		MD5�κ��� �ִ��� ĸ��ȭ�� Ŭ����

		\b Example
 * @code
BYTE		pbyResult[17]	= { 0, };
char	pMDTest[] = "FEATURE DevPartnerVB compuware 007.01 31-dec-2019 uncounted aF7253938817B VENDOR_STRING=11111;0;FIXED HOSTID=ANY aISSUER=ORiON ISSUED=17-MAY-2004 ck=165FEATURE BoundsChecker compuware 007.01 31-dec-2019 uncounted a64FA8156C55A VENDOR_STRING=11111;0;FIXED HOSTID=ANY aISSUER=ORiON ISSUED=17-MAY-2004 ck=110FEATURE DevPartnerVC compuware 007.01 31-dec-2019 uncounted a";

EA_CMD5Checksum	md5;
md5.InitChecksum();
md5.UpdateChecksum( pMDTest, sizeof( pMDTest ) - 1 );
md5.GetChecksum( pbyResult );
 * @endcode
 */
class	EA_CMD5Checksum : public EA_IMDChecksum
{
public:
	EA_CMD5Checksum()							{}
	virtual	~EA_CMD5Checksum()						{}

	void	InitChecksum();
	void	UpdateChecksum( LPVOID pvData, u32 u32DataLen);
	void	ResetChecksum()					{ InitChecksum();	}
	void	GetChecksum( u8 *pu8Checksum );
#ifdef	_EA_UNITTEST
	BOOL	Test();
#endif
protected:
	void	Transform( u32 *pu32Block );

	MDCONTEXT	m_stContext;
};

_EA_NAMESPACE_END

#endif	//_MD5_CHECKSUM_H_