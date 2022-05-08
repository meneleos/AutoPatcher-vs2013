#ifndef	_EA_ICHECKSUM_H_
#define	_EA_ICHECKSUM_H_

_EA_NAMESPACE_BEGIN

/**
 * @brief	CRC32�� Adler32�� Interface class
 */
class EA_IChecksum
{
public:
	/**
	 * @brief	Checksum�۾��� �����ϱ� ���� �ʱ�ȭ�ϴ� �Լ�.
	 */
	virtual	void	InitChecksum()					= 0;

	/**
	 * @brief	���� ���Ե� pvData�� �̿��Ͽ� u32DataLen��ŭ Checksum�� ���� �۾��� �����Ѵ�.
	 * @param[in]	pvData		Checksum�� �� ������
	 * @param[in]	DataLen		�������� ����
	 */
	virtual	void	UpdateChecksum( LPVOID pvData, MA_SIZE DataLen )	= 0;

	/**
	 * @brief	Checksum class�� ���ʱ�ȭ ��Ű�� �Լ�
	 */
	virtual	void	ResetChecksum()					= 0;

	/**
	 * @brief	Checksum�� ȹ���Ѵ�.
	 * @return	�� Checksum.
	 */
	virtual	DWORD	GetChecksum()					= 0;
};

_EA_NAMESPACE_END

#endif /* !_EA_ICHECKSUM_H_ */
