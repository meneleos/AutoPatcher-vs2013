//#ifndef _EA_CWORDSEARCHBITBINARY_H_
//#define _EA_CWORDSEARCHBITBINARY_H_
//
//#define CS_BIT_COUNT		3
//#define CS_RESTBIT_COUNT	(8 - CS_BIT_COUNT)
//#define CS_MASK				(((u8) ~0) >> CS_RESTBIT_COUNT)
//#define CS_NODE_COUNT		(CS_MASK + 1)
//
//class EA_CWordSearchBitBinary
//{
//
//};
//
//#endif /* !_EA_CWORDSEARCHBITBINARY_H_ */
//
//#include "STLMap.h"
//
//
///**
// * @class	WordSearchBitBinary
// * @brief	Tree�� �̿��� word �˻� class
// * @author	Standil (cpascal@cpascal.net)
// */
//class WordSearchBitBinary
//{
//public:
//	/// Tree�� node�� �ش��ϴ� data�� ������ map
//	DEFINE_STL_MAP( BitBinary, DWORD, LPVOID );
//
//
//	/**
//	* @class	WordNode
//	* @brief	WordSearchBitBinary tree�� node
//	* @author	Standil (cpascal@cpascal@e-zen.net)
//	*/
//	class WordNode
//	{
//		friend class WordSearchBitBinary;
//	public:
//		/// �ܾ��� ���� ǥ��
//		BOOL			bTermination;
//
//		/// Parent node
//		WordNode		* pParent;
//
//		/// Parent node������ index
//		int			m_iIndex;
//
//		/// Child node��
//		WordNode		* pNext[CS_NODE_COUNT];
//
//		/// Node�� ������ data
//		BitBinaryMap		IndexMap;
//
//
//	public:
//		/// Constructor
//		WordNode( WordNode IN * pParent, int IN iIndex )
//			: bTermination	( FALSE )
//			, pParent	( pParent )
//			, m_iIndex	( iIndex )
//		{
//			memset( pNext, 0, sizeof(pNext) );
//		}
//
//		// Destructor
//		~WordNode() {}
//
//
//		/// Parent node�� return �Ѵ�.
//		WordNode * GetParent() const	{ return pParent; }
//
//		/// ���� node�� parent���� ������ index�� return �Ѵ�.
//		int GetIndex() const		{ return m_iIndex; }
//	};
//
//	typedef WordNode *	PWordNode;
//
//
//	/**
//	* @class	Iterator
//	* @brief	WordSearchBitBinary�� tree�� traverse �ϱ� ���� itearator
//	* @autho	MadKnight (mknight@e-zen.net)
//	*/
//	class Iterator
//	{
//		friend class WordSearchBitBinary;
//	private:
//		/// WordSearchBitBinary�� instance pointer
//		WordSearchBitBinary	* m_pWSBB;
//
//		/// Node
//		PWordNode		m_pNode;
//
//		/// Node������ interator
//		BitBinaryMapItr		m_Itr;
//
//
//	public:
//		/// Constructor
//		Iterator( WordSearchBitBinary IN * pWSBB = NULL, PWordNode IN pNode = NULL )
//			: m_pWSBB	( pWSBB )
//			, m_pNode	( pNode )
//		{
//		}
//
//		/// Destructor
//		~Iterator() {}
//
//		/// Data�� return �Ѵ�.
//		LPVOID GetData()	{ return m_Itr->second; }
//
//		/// Overloadded prefix ++ operator
//		Iterator & operator++()
//		{
//			Iterator	Next( m_pWSBB );
//
//
//			++ m_Itr;
//			if( m_Itr == m_pNode->IndexMap.end() ) {
//				Next = m_pWSBB->GetNext( *this );
//				m_pNode = Next.m_pNode;
//				m_Itr	= Next.m_Itr;
//			}
//
//			return *this;
//		}
//
//		/// Overridded posfix ++ operator
//		Iterator operator++( int )
//		{
//			Iterator	Temp = *this;
//
//			++ *this;
//
//			return Temp;
//		}
//
//		/// Overloadded == operator
//		BOOL operator==( const Iterator & Right )
//		{
//			return (m_pWSBB == Right.m_pWSBB)
//				&& (m_pNode == Right.m_pNode)
//				&& (m_Itr == Right.m_Itr);
//		}
//
//		/// Overloadded == operator
//		BOOL operator!=( const Iterator & Right )
//		{
//			return !(*this == Right);
//		}
//	};
//
//	/// Constructor
//	WordSearchBitBinary( BOOL bCaseSensitive = TRUE );
//
//	/// Destructor
//	~WordSearchBitBinary( void );
//
//	/// �˻��� word�� �߰�
//	/**
//	 * @param[in]	szWord		�߰��� �˻���
//	 * @param[in]	lpData		�߰��� word�� ����� data
//	 */
//	BOOL		AddWord( LPCTSTR IN szWord, LPVOID IN lpData = NULL );
//
//	/// �־��� ���ڿ��� �˻��ؼ� ����� �ܾ '*'�� �ٲ۴�.
//	/**
//	 * @param[in]	szString	�˻��� ���ڿ�
//	 * @return	szString	�ܾ �ٲ� ���ڿ�
//	 */
//	TCHAR *		ReplaceString( LPTSTR INOUT szString );
//
//	/// �־��� ���ڿ��� �˻��ؼ� ����� �ܾ �ִ��� ã�´�.
//	/**
//	 * @param[in]	szString	�˻��� ���ڿ�
//	 * @return	����� �ܾ �����ϸ� TRUE, �׷��� ������ FALSE
//	 */
//	BOOL		SearchString( LPCTSTR IN szString );
//
//	/// ����� word�� �˻��Ѵ�.
//	/**
//	 * @param[in]	szString	�˻��� word
//	 * @param[out]	lpData		�˻��� word�� ����� data
//	 */
//	BOOL		SearchWord( LPCTSTR IN szString, LPVOID OUT * lpData = NULL ) const;
//
//	/// ����� word�� �˻��Ѵ�.
//	/**
//	 * @param[in]	szString	�˻��� word
//	 * @param[out]	lpData		�˻��� word�� ����� data
//	 */
//	size_t		MatchWord( LPCTSTR IN szString, BOOL bMustMatchTermination, LPVOID OUT * lpData = NULL ) const;
//	size_t		MatchWordCI( LPCTSTR IN szString, BOOL bMustMatchTermination, LPVOID OUT * lpData = NULL ) const;
//
//	/// �˻��� �ܾ���� ��� ����� instance�� �ʱ�ȭ ��Ų��.
//	void		Clear();
//
//	/// ����� word�� ���� return �Ѵ�.
//	size_t		GetCount() const	{ return m_sizeWords; }
//
//	/// Tree�� �� ���� �Ʒ� node�� return �Ѵ�.
//	Iterator	GetFirst();
//
//	/// Tree�� �� ������ �Ʒ� node�� return �Ѵ�.
//	Iterator	GetLast();
//
//	/// Tree�� traverse �Ѵ�. (depth-first, preorder)
//	Iterator	GetNext( const Iterator IN & Itr );
//
//
//private:
//	/// ����� word�� ��
//	size_t		m_sizeWords;
//
//	/// �˻� tree�� root node
//	PWordNode	m_pRoot;
//
//	/// �־��� node�� child node���� ��� ���� �Ѵ�.
//	void		ReleaseWordNode( PWordNode IN pWordNode );
//
//	BOOL		m_bCaseSensitive;
//};
//
//class WordSearchBitBinaryIterator : public WordSearchBitBinary::Iterator
//{
//};
//
//#endif
