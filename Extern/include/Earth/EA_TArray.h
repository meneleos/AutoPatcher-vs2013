/**
 * @file	EA_TArray.h
 * @brief	Header file for Auto grow array template class in Solar System
 * @author	bravefirebat ( bravefirebat@gmail.com )
 *
 * @version	2008/04/28 bravefirebat - First release
 */

#ifndef	_EA_TARRAY_H_
#define	_EA_TARRAY_H_

#include "EA_Memory.h"

_EA_NAMESPACE_BEGIN

/**
 * @brief	Smart array.
 * @param[in]	fnMalloc - Function pointer for allocates memory blocks.
		fnFree - Function pointer for deallocates pr frees a memory blocks.
		fnRealloc - Function pointer for rellocate memory blocks.
 */
template<class T, EA_MALLOC fnMalloc = malloc, EA_FREE fnFree = free, EA_REALLOC fnRealloc = realloc>
class EA_TArray
{
public:
	typedef	typename EA_INT	(*ARRAY_COMPAREFUNC)( const T&, const T& );
	typedef	typename void	(*ARRAY_SWAPFUNC)( T&, T& );
public:
	/**
	 * @constructor	EA_TArray
	 * @brief	Basic constructor
	 */
	EA_TArray( void );

	/**
	 * @constructor	EA_TArray
	 * @brief	Constructor
	 * @param[in]	sizeChunk	- Size of memory chunk when array grow if necessary
	 */
	EA_TArray( EA_SIZE sizeChunk );

	/**
	 @destructor	~EA_TArray
	 @brief		Virtual destructor
	 */
	virtual	~EA_TArray( void );

	void		Exchange( EA_TArray* pcArray );

	T*		Attach( T* ptValue, EA_SIZE sizeCount );
	T*		Attach( T* ptValue, EA_SIZE sizeCount, EA_SIZE sizeAllocated );
	T*		Detach( void );
	void		Detach( T** pptValue, EA_SIZE* psizeCount, EA_SIZE* psizeAllocated );

	EA_SIZE	GetMemoryUsage( void ) const;
	EA_SIZE	GetMaxIndex( void ) const;
	EA_SIZE	GetAllocatedMemoryUsage( void ) const;

	/**
	 @brief		Get the number of elements in this array
	 */
	EA_SIZE	GetCount( void ) const;

	/**
	 * @brief	Set the number of elements to be contained in this array.
	 * @param[in]	sizeCount	- The new array size.
	 */
	virtual	void	SetCount( EA_SIZE sizeCount );

	/**
	 * @brief	Get the number of element slot to allocate.
	 */
	EA_SIZE	GetChunkSize( void ) const;

	/**
	 * @brief	Set the number of element slot to alloate.
	 * @param[in]	sizeChunk	- The number of elements slots to allocate if a size increase is necessary.
	 */
	void		SetChunkSize( EA_SIZE sizeChunk );

	/**
	 * @brief	Returns the number of elements that the this array could contain without allocating more storage.
	 */
	EA_SIZE	GetCapacitySize( void ) const;

	/**
	 * @brief	Returns the value at a given index.
	 * @returns	The pointer of array element currently at this index.
	 */
	T&		GetAt( EA_SIZE sizeIndex );

	/**
	 * @brief	Sets the value for a given index; array not allowed to grow.
	 * @param[in]	sizeIndex	- Index of array element.
	 *		pValue		- The new element.
	 */
	EA_BOOL		SetAt( EA_SIZE sizeIndex, T& rValue );

	/**
	 * @brief	Removes an element at a specific index.
	 * @param[in]	sizeIndex	- Index of array element.
	 */
	EA_BOOL		EraseAt( EA_SIZE sizeIndex );

	/**
	 * @brief	Find an element.
	 * @param[in]	pSource		- pointer an element that find.
	 *		pCompareFunc	- Pointer of find function.
	 * @returns	Index of found item. 0xFFFFFFFF if not found pSource in this class.
	 */
	EA_SIZE	Find( const T& rSource, ARRAY_COMPAREFUNC pCompareFunc = EA_NULL );

	/**
	 * @brief	Find an element in this class.
	 * @param[in]	pSource		- pointer an element that find.
	 *		pCompareFunc	- Pointer of find function.
	 * @returns	EA_TRUE if pValue is contained in this class. other wise EA_FALSE.
	 */
	EA_BOOL		IsContains( const T& rValue, ARRAY_COMPAREFUNC pCompareFunc = EA_NULL );

	/**
	 * @brief	Tests if the array is empty.
	 */
	EA_BOOL		IsEmpty( void );

	/**
	 * @brief	Get pointer of elements that allocated.
	 */
	const T*	GetRawBuffer( void ) const;

	T*		Get( void );
	const T*	Get( void ) const;
	void		Set( T* pSource, EA_SIZE sizeCount );

	/**
	 * @brief	Sort array elements in this class.
	 * @param[in]	pCompareFunc	- Pointer of compare function.
	 *		pSwapFunc	- Pointer of swap function.
	 */
	void		Sort( ARRAY_COMPAREFUNC pCompareFunc = EA_NULL, ARRAY_SWAPFUNC pSwapFunc = EA_NULL );

	/**
	 * @brief	Do a binary search, array must be sorted.
	 * @param[in]	pElement	- ã�� element
	 */
	EA_INDEX_T	BinarySearchIndex( const T& rElement ) const;

	/**
	 * @brief	sizeFromInde�� ��ġ���� sizeToIndex���� sizeCount��ŭ�� ������ �̵���Ų��.
	 * @param[in]	sizeFromIndex	- �̵� �� ���� index
	 *		sizeToIndex	- �̵� �� �������� index
	 *		sizeCount	- �̵��� element�� ����
	 * @returns	EA_TRUE		- �̵� ����
	 *		EA_FALSE	- �̵� ����. index + count�� ������ ��ü ����� �Ѿ�� ������ �� �ִ�.
	 */
	EA_BOOL		Move( EA_SIZE sizeFromIndex, EA_SIZE sizeToIndex, EA_SIZE sizeCount );

	/**
	 * @brief	pcSource�� ������ �����Ѵ�.
	 * @param[in]	pcSource	- ���� Ŭ����
	 */
	EA_SIZE	Copy( const EA_TArray& rcSource );

	/**
	 * @brief	���� Ŭ������ �ڿ� pcSourceŬ������ element�� �����Ѵ�.
	 * @param[in]	pcSource	- ���� Ŭ����
	 */
	EA_SIZE	Append( const EA_TArray& rcSource );

	/**
	 * @brief	���� Ŭ������ T�� sizeCount��ŭ �߰� �Ѵ�.
	 * @returns	�߰� �Ϸ�� ���� Ŭ������ �� count.
	 */
	EA_SIZE	Add( const T& rSource );
	EA_SIZE	Add( const T* pSource, EA_SIZE sizeCount );

	/**
	 * @brief	�̸� sizeReverse��ŭ�� element�� �����Ѵ�.(count�� �������� �ʴ´�)
	 */
	void		Reserve( EA_SIZE sizeReserve );

	/**
	 * @brief	sizeNew��ŭ array�� ���� ��Ų��. ���� sizeNew�� 2��� ��ü ũ�⸦ 2�� ����°� �ƴ϶�, 2��ŭ ���۸� �ø��� �ȴ�.
	 */
	void		Grow( EA_SIZE sizeNew );

	/**
	 * @brief	chunk������ �޸𸮸� �ø��� �ʰ� �Էµ� sizeNew��ŭ ��� ���۸� �ø���.
	 */
	void		GrowExact( EA_SIZE sizeNew );

	/**
	 * @brief	sizeCount��ŭ element�� �Ҵ��Ѵ�.
	 */
	void		Allocate( EA_SIZE sizeCount );

	/**
	 * @brief	sizeCount��ŭ element�� ���Ҵ��Ѵ�.
	 */
	void		Reallocate( EA_SIZE sizeNew );

	/**
	 * @brief	���������� �Ҵ�� �޸𸮸� �����Ѵ�.
	 */
	void		Free( void );

	/**
	 * @brief	Ŭ������ �ʱ�ȭ �Ѵ�.
	 */
	void		Clear( void );


	/**
	 * @brief	sizeIndex��ġ�� �ִ� element�� �����ڸ� ȣ���Ѵ�.
	 */
	void		Initialize( EA_SIZE sizeIndex );

	/**
	 * @brief	sizeIndex��ġ�� �ִ� element�� ��������ڸ� ȣ���Ѵ�.
	 */
	void		Initialize( EA_SIZE sizeIndex, const T& rValue );

	/**
	 * @brief	sizeIndex��ġ�� �ִ� element�� �Ҹ��ڸ� ȣ���Ѵ�.
	 */
	void		Destroy( EA_SIZE sizeIndex );

	/**
	 * @brief	GetAt�� �������. �ش���ġ�� �����͸� ���´�.
	 */
	T&		operator[]( EA_SIZE sizeIndex );

	/**
	 * @brief	GetAt�� �������. �ش���ġ�� �����͸� ���´�.
	 */
	const T&	operator[]( EA_SIZE sizeIndex ) const;
protected:
	void		QuickSort( EA_SIZE sizeFirstIndex, EA_SIZE sizeLastIndex, ARRAY_COMPAREFUNC pCompareFunc, ARRAY_SWAPFUNC pSwapFunc );
	//static	EA_INT	DefaultCompareFunc( T& pLHS, T& pRHS );
	//static	EA_INT	DefaultSwapFunc( T& pLHS, T& pRHS );

	EA_SIZE	m_sizeAllocatedCount;
	EA_SIZE	m_sizeCount;
	EA_SIZE	m_sizeChunk;
	T*		m_pData;
};

#include "EA_TArray.inl"

_EA_NAMESPACE_END

#endif /* !_EA_TARRAY_H_ */

