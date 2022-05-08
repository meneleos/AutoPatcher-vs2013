#ifndef	_EA_CHECKSUMUTILITY_H_
#define	_EA_CHECKSUMUTILITY_H_

_EA_NAMESPACE_BEGIN

#define	NUMBER_OF_CRC32_TABLE	4

typedef	union EA_tagUnionU32 {
	u32	u32Value;
	struct {
		u8 	u8B1;
		u8 	u8B2;
		u8 	u8B3;
		u8 	u8B4;
	} stu8s;
} UNION_U32;

extern	const	u32	g_u32MDInitializeTable[4];

extern	const	u8	g_u8MDPaddingTable[64];

/**
 * @brief	CRC�� ���� ����ϴ� 1KB�� ���̺�. �ӵ������ ���� 1K�� ����Ѵ�.
 * @author	bugmail (bugmail@buddygames.co.kr)
 */
extern	const u32	g_u32Crc32Table[ NUMBER_OF_CRC32_TABLE ][ 256 ];

_EA_NAMESPACE_END

#endif /* !_EA_CHECKSUMUTILITY_H_ */

