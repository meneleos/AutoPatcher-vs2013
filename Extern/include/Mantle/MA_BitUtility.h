/**
 * @file	MA_BitUtiltiy.h
 * @brief	Bit utility functions header file
 * @author	Standil (cpascal@cpascal.net)
 *
 * @version	2008/04/24 cpascal - First release
 */

#ifndef _MA_BITUTILITY_H_
#define _MA_BITUTILITY_H_

_NTR_EXTERN_C_BEGIN

/*
 * Macro: BitFields
 * Bit field Macros
 *
 * (start code)
 * 
 * MA_BITFARRAY_DECLARE( bfFlags, 1000 );	// MA_BitField ���� (1000��)
 * 
 * MA_BITFARRAY_ZERO( bfFlags );		// MA_BitField �ʱ�ȭ
 * MA_BITFARRAY_CHECK( bfFlags, 103 );		// 103��° ��Ʈ Ȯ�� (TRUE/FALSE ��ȯ)
 * MA_BITFARRAY_REMOVE( bfFlags, 103 );		// 103��° ��Ʈ ����
 * MA_BITFARRAY_SET( bfFlags, 103 );		// 103��° ��Ʈ ����
 *
 * (end)
 */
#define MA_BIT_CHECK( LHSBit, RHSBit )			( (LHSBit) & (RHSBit) )		// ��Ʈ �˻�
#define MA_BIT_SET( LHSBit, RHSBit )			( (LHSBit) |= (RHSBit) )	// ��Ʈ ����
#define MA_BIT_REMOVE( LHSBit, RHSBit )			( (LHSBit) &= ~(RHSBit) )	// ��Ʈ ����
#define MA_BIT_ZERO( LHSBit )				( (LHSBit) = 0 )		// ��ü��Ʈ ����
#define	MA_BIT_MODIFY( Flags, Add, Remove )		{ MA_BIT_SET( Flags, Add ); MA_BIT_REMOVE( Flags, Remove );	}

// Bit fields
typedef MA_DWORD					MA_BitField;

// Number of Bits per BYtes
#define MA_BITF_FULL					0xFFFFFFFF
#define MA_NBBY						8				// �� ����Ʈ�� ��Ʈ��(Number of Bits per Byte - Glib �� ����)
#define MA_NFDBITS					( sizeof( MA_BitField ) * MA_NBBY )
// ���ϴ� bit field ���� �����ϴ� �ּ� ����Ʈ
#define MA_MINBYTES( MaxBits )				( ((MaxBits) + ((MA_NFDBITS)-1)) / ( MA_NFDBITS ) )

#define MA_BITF_SET( BitField, Position )		( BitField |=  (1 << ( Position ) ) )
#define MA_BITF_REMOVE( BitField, Position )		( BitField &= ~(1 << ( Position ) ) )
#define MA_BITF_CHECK( BitField, Position )		( BitField &   (1 << ( Position ) ) )
#define MA_BITF_ZERO( BitField )			memset( BitField, 0, sizeof( u32 ) );

#define MA_BITFARRAY_DECLARE( BitFieldArray, MaxBits )	MA_BitField	BitFieldArray[ MA_MINBYTES( MaxBits ) ]	= { 0, }
#define MA_BITFARRAY_SET( BitFieldArray, Position )	( (BitFieldArray)[ (Position)/MA_NFDBITS ] |=  (1 << ( (Position) & (MA_NFDBITS-1)) ) )
#define MA_BITFARRAY_REMOVE( BitFieldArray, Position )	( (BitFieldArray)[ (Position)/MA_NFDBITS ] &= ~(1 << ( (Position) & (MA_NFDBITS-1)) ) )
#define MA_BITFARRAY_CHECK( BitFieldArray, Position )	( (BitFieldArray)[ (Position)/MA_NFDBITS ] &   (1 << ( (Position) & (MA_NFDBITS-1)) ) )
#define MA_BITFARRAY_ZERO( BitFieldArray )		memset( BitFieldArray, 0, sizeof( *BitFieldArray ) );

extern MA_INT MA_FindHighestSetBitU32( MA_U32 dwValue );
extern MA_INT MA_FindHighestSetBitU64( MA_U64 qwValue );

_NTR_EXTERN_C_END

#endif // !_MA_BITUTILITY_H_
