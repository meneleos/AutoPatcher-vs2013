/**
 * @file	EA_IMDChecksum.h
 * @brief	Baekdu Checksum Library
 * @author	bugmail (bugmail@buddygames.co.kr)
 *
 * @version	2005/08/12 bugmail - first release
 */

#ifndef	_IMDCHECKSUM_H_
#define	_IMDCHECKSUM_H_

#include "EA_ChecksumUtility.h"

_EA_NAMESPACE_BEGIN

const	u32	SIZE_MD_RESULT	= 16;
/**
 * @brief	MD4�� MD5�� Interface�� �����͸� �����ϱ� ���� Interface Class
 * @author	bugmail (bugmail@buddygames.co.kr)
 * @remark	MD5�� MD4�� ���Ἲ�� ���� �� ���� �˰����̱⶧���� Interface�� �����͸� ���߱Ⱑ ����.
		��� ���ʿ��� �ߺ� �ڵ��� ���ֱ� ���� Class
 */
class	EA_IMDChecksum
{
public:
	/**
	 * @brief	MD�迭�� Checksum�� ����Ҷ� ���ο��� ����ϴ� ����ü.
	 * @author	bugmail (bugmail@buddygames.co.kr)
	 */
	typedef	struct	EA_tagMDContext
	{
		u32 		au32State[4];		// buf
		u32 		au32Count[2];		// number of bits
		BYTE		abyInput[64];
	} MDCONTEXT, *LPMDCONTEXT;

	/**
	 * @brief	�⺻������.
	 * @author	bugmail (bugmail@buddygames.co.kr)
	 */
	EA_IMDChecksum()					{}
	/**
	 * @brief	�Ҹ���.
	 * @author	bugmail (bugmail@buddygames.co.kr)
	 */
	virtual	~EA_IMDChecksum()				{}

	/**
	 * @brief	Checksum�۾��� �����ϱ� ���� �ʱ�ȭ�ϴ� �Լ�.
	 * @author	bugmail (bugmail@buddygames.co.kr)
	 */
	virtual	void	InitChecksum()					= 0;

	/**
	 * @brief	���� ���Ե� pvData�� �̿��Ͽ� u32DataLen��ŭ Checksum�� ���� �۾��� �����Ѵ�.
	 * @author	bugmail (bugmail@buddygames.co.kr)
	 * @param[in]	pvData		Checksum�� �� ������
	 * @param[in]	u32DataLen	�������� ����. ��Ȯ�� ���̸� �־�� ��Ȯ�� �����͸� �� �� �ִ�.
	 */
	virtual	void	UpdateChecksum( LPVOID pvData, u32 u32DataLen )	= 0;

	/**
	 * @brief	Checksum class�� ���ʱ�ȭ ��Ű�� �Լ�
	 * @author	bugmail (bugmail@buddygames.co.kr)
	 */
	virtual	void	ResetChecksum()					= 0;

	/**
	 * @brief	Checksum�� ȹ���Ѵ�.
	 * @author	bugmail (bugmail@buddygames.co.kr)
	 * @param[out]	pu8Checksum	16���� BYTE�� ������ ���´�.
	 */
	virtual	void	GetChecksum( u8 *pu8Checksum )			= 0;
};

_EA_NAMESPACE_END

#endif //_IMDCHECKSUM_H_