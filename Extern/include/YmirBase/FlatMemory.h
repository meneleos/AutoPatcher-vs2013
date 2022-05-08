#pragma once

class EL_CFlatMemory
{
public:
	//-----------------------------------------------------------
	//	Constructor / Destructor
	//-----------------------------------------------------------

	/// Constructor
	EL_CFlatMemory( void );
	EL_CFlatMemory( const EL_CFlatMemory& );

	/// Destructor
	virtual ~EL_CFlatMemory();


	/**
	* @brief	������ ��� �����.
	*/
	void Clear( void );

	/**
	* @brief	������ ��� �����.
	*/
	void Close( void ) { Clear(); }

	/**
	* @brief	�� row�� �� ���� �� column�� cell ���� return �Ѵ�.
	* @return	���� �� column�� cell ��
	*/
	EL_SIZE GetMaxColumns( void ) const { return m_sizeMaxColumns; }

	/**
	* @brief	Row�� ���� return �Ѵ�.
	* @return	Row�� ��
	*/
	EL_SIZE GetRows( void ) const;

	/**
	* @brief	�� row�� column�� ���� return �Ѵ�.
	* @param[in]	iRow	Columns�� ���� return 
	* @return	������ column�� zero-based index + 1
	*/
	EL_SIZE GetColumns( int iRow ) const;

	/**
	* @brief	Header�� ������ �ִ��� return �Ѵ�.
	* @return	Header�� ������ ������ TRUE, �׷��� ������ FALSE�� return �Ѵ�.
	*/
	BOOL HasHeader( void ) const { return 0 < m_mapHeaders.size(); }

	/**
	* @brief			�־��� ����̸��� ���� column�� index�� return�Ѵ�.
	* @param[in]		tszHeader	Header�� �̸�
	* @return			�ش� ����� column ��ȣ�� ��ȯ�Ѵ�. �ش� ����� ã������ ��� -1�� ��ȯ�Ѵ�.
	*/
	int FindHeader( LPCTSTR tszColumnName ) const;

	/**
	* @brief	�־��� column�� header�� return �Ѵ�.
	* @param[in]		iCol		Zero-based index
	* @param[out]		tszHeader	Header�� ������ buffer
	* @param[in,out]	psizeHeader	[in] tszHeader�� ������ �� �ִ� ũ��
	[out] tszHeader�� ������ ũ��
	TCHAR ����
	* @return	�־��� column�� index�� header�� ���� �Ǿ������� TRUE, �׷��� ������ FALSE�� return �Ѵ�.
	*/
	BOOL GetHeader( int iCol, LPTSTR tszHeader, EL_SIZE *psizeHeader ) const;

	/**
	* @brief	�־��� column�� header�� return �Ѵ�.
	* @param[in]	iCol		Zero-based index
	* @param[out]	tszHeader	Header�� ������ buffer
	* @param[in]	sizeHeader	tszHeader�� ������ �� �ִ� ũ��. TCHAR ����
	* @return	�־��� column�� index�� header�� ���� �Ǿ������� TRUE, �׷��� ������ FALSE�� return �Ѵ�.
	*/
	BOOL GetHeader( int iCol, LPTSTR tszHeader, EL_SIZE sizeHeader ) const;

	/**
	* @brief	�־��� column�� header�� return �Ѵ�.
	* @param[in]	iCol		Zero-based index
	* @param[out]	rstrHeader	Header�� ������ buffer
	* @return	�־��� column�� index�� header�� ���� �Ǿ������� TRUE, �׷��� ������ FALSE�� return �Ѵ�.
	*/
	BOOL GetHeader( int iCol, EL_STLString &rstrHeader ) const;

	/**
	* @brief	�־��� column�� header�� return �Ѵ�.
	* @param[in]	iCol		Zero-based index
	* @return	�־��� column�� index�� header�� ���� �Ǿ������� string�� pointer��, �׷��� ������ NULL�� return �Ѵ�.
	*/
	LPCTSTR GetHeader( int iCol ) const;

	/**
	* @brief	Cell�� data ���� return �Ѵ�.
	* @param[in]		iRow		Row�� zero-based index
	* @param[in]		iCol		Column�� zero-based index
	* @param[out]		tszData		Data�� ������ buffer. NULL�� �� �ִ�.
	* @param[in,out]	psizeData	[in] tszData�� ������ �� �ִ� ũ��
	[out] tszData�� ������ ũ��
	TCHAR ����. tszData�� NULL�� ��쿡�� data�� ���̸� return �Ѵ�.
	NULL �� �� �ִ�. tszValue�� NULL�� �ƴϸ� �� ���� NULL�� �ƴϾ�� �Ѵ�.
	* @return	Cell�� data�� ������ TRUE, �׷��� ������ FALSE�� return �Ѵ�.
	*
	* tszValue�� psizeValue �Ѵ� NULL�� ����ϸ� cell�� ���� �ִ����� �� �� �ִ�
	*/
	BOOL Get( int iRow, int iCol, LPTSTR tszData, EL_SIZE IN*psizeData ) const;

	/**
	* @brief	Cell�� data ���� return �Ѵ�.
	* @param[in]	iRow		Row�� zero-based index
	* @param[in]	iCol		Column�� zero-based index
	* @param[out]	tszData		Data�� ������ buffer
	* @param[in]	sizeData	tszData�� ������ �� �ִ� ũ��. TCHAR ����
	* @return	Cell�� data�� ������ TRUE, �׷��� ������ FALSE�� return �Ѵ�.
	*/
	BOOL Get( int iRow, int iCol, LPTSTR tszData, EL_SIZE sizeData ) const;

	/**
	* @brief	Cell�� data ���� return �Ѵ�.
	* @param[in]	iRow		Row�� zero-based index
	* @param[in]	iCol		Column�� zero-based index
	* @param[out]	rstrData	Data�� ������ buffer
	* @return	Cell�� data�� ������ TRUE, �׷��� ������ FALSE�� return �Ѵ�.
	*/
	BOOL Get( int iRow, int iCol, EL_STLString &rstrData ) const;

	/**
	* @brief	Cell�� data ���� return �Ѵ�.
	* @param[in]	iRow		Row�� zero-based index
	* @param[in]	iCol		Column�� zero-based index
	* @return	Cell�� data�� ������ string�� pointer��, �׷��� ������ NULL�� return �Ѵ�.
	*/
	LPCTSTR Get( int iRow, int iCol ) const;

	/**
	* @brief	Cell�� data ���� return �Ѵ�.
	* @param[in]	iRow		Row�� zero-based index
	* @param[in]	iCol		Column�� zero-based index
	* @param[out]	rnData		Data�� ������ buffer
	* @return	Cell�� data�� �ְ� integer�� ��ȯ�� �� ������ TRUE, �׷��� ������ FALSE�� return �Ѵ�.
	*/
	BOOL Get( int iRow, int iCol, int &rnData ) const;

	/**
	* @brief	Cell�� data ���� return �Ѵ�.
	* @param[in]	iRow		Row�� zero-based index
	* @param[in]	iCol		Column�� zero-based index
	* @param[out]	rnData		Data�� ������ buffer
	* @return	Cell�� data�� �ְ� integer�� ��ȯ�� �� ������ TRUE, �׷��� ������ FALSE�� return �Ѵ�.
	*/
	template<typename IntType>
	BOOL Get( int iRow, int iCol, IntType &rnData ) const
	{
		int nData;
		if( !Get( iRow, iCol, nData ) )
			return FALSE;
		rnData = static_cast<IntType>( nData );

		return TRUE;
	}

	/**
	* @brief	Cell�� data ���� return �Ѵ�.
	* @param[in]	iRow		Row�� zero-based index
	* @param[in]	iCol		Column�� zero-based index
	* @param[out]	rfData		Data�� ������ buffer
	* @return	Cell�� data�� �ְ� integer�� ��ȯ�� �� ������ TRUE, �׷��� ������ FALSE�� return �Ѵ�.
	*/
	BOOL Get( int iRow, int iCol, float &rfData ) const;

	/**
	* @brief	Cell�� data ���� return �Ѵ�.
	* @param[in]	iRow		Row�� zero-based index
	* @param[in]	iCol		Column�� zero-based index
	* @param[out]	rdData		Data�� ������ buffer
	* @return	Cell�� data�� �ְ� integer�� ��ȯ�� �� ������ TRUE, �׷��� ������ FALSE�� return �Ѵ�.
	*/
	BOOL Get( int iRow, int iCol, double &rdData ) const
	{
		float fData;
		if( !Get( iRow, iCol, fData ) )
			return FALSE;
		rdData = static_cast<double>( fData );

		return TRUE;
	}

	/**
	* @brief	Header�� setting �Ѵ�.
	* @param[in]	iCol		Column�� zero-based index
	* @param[in]	tszHeader	Setting �� header
	*/
	void SetHeader( int iCol, LPCTSTR tszHeader );

	/**
	* @brief	Cell�� ���� setting �Ѵ�.
	* @param[in]	iRow	Row�� zero-based index
	* @param[in]	iCol	Column�� zero-based index
	* @param[in]	tszData	Cell�� setting �� ��
	*/
	void Set( int iRow, int iCol, LPCTSTR tszData );

	/**
	* @brief	Cell�� ���� setting �Ѵ�.
	* @param[in]	iRow	Row�� zero-based index
	* @param[in]	iCol	Column�� zero-based index
	* @param[in]	tszData	Cell�� setting �� ��
	*/
	void Set( int iRow, int iCol, LPTSTR tszData )
	{
		Set( iRow, iCol, reinterpret_cast<LPCTSTR>( tszData ) );
	}

	/**
	* @brief	Cell�� ���� setting �Ѵ�.
	* @param[in]	iRow	Row�� zero-based index
	* @param[in]	iCol	Column�� zero-based index
	* @param[in]	nData	Cell�� setting �� ��
	*/
	void Set( int iRow, int iCol, int nData );

	/**
	* @brief	Cell�� ���� setting �Ѵ�.
	* @param[in]	iRow	Row�� zero-based index
	* @param[in]	iCol	Column�� zero-based index
	* @param[in]	uData	Cell�� setting �� ��
	*/
	template<typename IntType>
	void Set( int iRow, int iCol, IntType nData )
	{
		Set( iRow, iCol, static_cast<int>( nData ) );
	}

	/**
	* @brief	Cell�� ���� setting �Ѵ�.
	* @param[in]	iRow	Row�� zero-based index
	* @param[in]	iCol	Column�� zero-based index
	* @param[in]	fData	Cell�� setting �� ��
	*/
	void Set( int iRow, int iCol, float fData );

	/**
	* @brief	Cell�� ���� setting �Ѵ�.
	* @param[in]	iRow	Row�� zero-based index
	* @param[in]	iCol	Column�� zero-based index
	* @param[in]	dData	Cell�� setting �� ��
	*/
	void Set( int iRow, int iCol, double dData );

protected:
	//-----------------------------------------------------------
	//	Private Types
	//-----------------------------------------------------------

	EL_DEFINE_STL_MAP( Values, int, EL_STLString );

	EL_DEFINE_STL_MAP( Rows, int, MapValues );

	/**
	* @brief	�־��� map���� ���� ã�� return �Ѵ�.
	* @param[in]		pmapValues	���� ã�� map
	* @parma[in]		iCol		Column�� zero-based index
	* @param[out]		tszValue	���� ������ buffer. NULL �� �� �ִ�.
	* @param[in,out]	psizeValue	[in] tszValues�� ������ �� �ִ� ũ��
	[out] tszValues�� ������ ũ��
	TCHAR ����. tszValue�� NULL�̸� ���� ũ�⸸ return �Ѵ�.
	NULL �� �� �ִ�. tszValue�� NULL�� �ƴϸ� �� ���� NULL�� �ƴϾ�� �Ѵ�.
	* @return	Cell�� ���� ������ TRUE, �׷��� ������ FALSE�� return �Ѵ�.
	*
	* tszValue�� psizeValue �Ѵ� NULL�� ����ϸ� cell�� ���� �ִ����� �� �� �ִ�
	*/
	static BOOL FindValue( const MapValues *pmapValues, int iCol, LPTSTR tszValue, EL_SIZE IN*psizeValue );

	/**
	* @brief	�־��� map���� ���� ã�� return �Ѵ�.
	* @param[in]	pmapValues	���� ã�� map
	* @parma[in]	iCol		Column�� zero-based index
	* @return	Cell�� ���� ������ EL_STLString*, �׷��� ������ NULL�� return �Ѵ�.
	*/
	static const EL_STLString* FindValue( const MapValues *pmapValues, int iCol );

	/**
	* @brief	�־��� row�� column�� index�� ���� ã�� return �Ѵ�.
	* @param[in]	iRow	���� ã�� map
	* @parma[in]	iCol		Column�� zero-based index
	* @return	Cell�� ���� ������ EL_STLString*, �׷��� ������ NULL�� return �Ѵ�.
	*/
	const EL_STLString* FindValue( int iRow, int iCol ) const;

	/**
	* @brief	�־��� row�� index�� row�� ã�´�.
	* @param[in]	iRow	Row�� zero-based index
	* @return	ã�� row�� pointer�� return �Ѵ�.
	*/
	const MapValues* FindRow( int iRow ) const;

	/**
	* @brief	Column�� index�� max columns�� update �Ѵ�.
	* @param[in]	iCol	Update�� column�� index
	*/
	void UpdateMaxColumns( unsigned int iCol );

protected:
	/// Parsing result
	typedef enum
	{ 
		PARSE_ERROR,
		PARSE_NEXT_RIGHT,
		PARSE_NEXT_BELOW,
		PARSE_END,
	} EParseCell;

	MapValues	m_mapHeaders;				///< Header�� ����
	MapRows		m_mapRows;					///< �� row�� ����
	EL_SIZE		m_sizeMaxColumns;			///< �ִ� column
};
