/**
 * @file	EA_CURLEncode.h
 * @brief	URL encoding/decoding class
 * @author	Standil (cpascal@cpascal.net)
 *
 * @version	2006/03/24 cpascal - First release
 */

#ifndef	_EA_CURLENCODE_H_
#define	_EA_CURLENCODE_H_

_EA_NAMESPACE_BEGIN

/**
 * @brief	TCHAR�� ���ڿ��� 3���ھ� �߶� 4�� ũ��� ������Ű�� Ŭ����
 * @remark	������ �����ϰ� �ϱ� ���Ͽ� ����Լ� ������ ANSI�� �������� �����ϰ���.
 */
class EA_CURLEncode
{
protected:
	enum	{
		ENCODE_LEN	= 3,
		DECODE_LEN	= 4
	};

public:
	/**
	 * @brief	������
	 */
	EA_CURLEncode();
	/**
	 * @brief	�Ҹ���
	 */
	~EA_CURLEncode();

	/**
	 * @brief	pbySource�� 3����Ʈ�� �߶� 4����Ʈ�� Encoding �ϴ� �Լ�
	 * @param[out]	tszTarget	Encoding�� ���� ����� ������ ������
	 * @param[in]	sizeTarget	tszTarget�� ��ȿ����
	 * @param[in]	pbySource	Encoding�� ���ڿ�
	 * @param[in[	sizeSource	pbySource�� ��ȿ����
	 * @return	Encode�� ������
	 */
	size_t	Encode( LPTSTR OUT tszTarget, size_t IN sizeTarget, LPCTSTR IN tszSource, size_t IN sizeSource );

	/**
	 * @brief	tszSource�� 4����Ʈ�� �߶� 3����Ʈ�� Decoding�ϴ� �Լ�
	 * @param[out]	tszTarget	Decoding�� ���� ����� ������ ������
	 * @param[in]	sizeTarget	tszTarget�� ��ȿ����
	 * @param[in]	tszSource	Decoding�� ���ڿ�
	 * @param[in]	sizeSource	tszSource�� ��ȿ����
	 * @return	Decode�� ������
	 */
	size_t	Decode( LPTSTR OUT tszTarget, size_t IN sizeTarget, LPCTSTR IN tszSource, size_t IN sizeSource );

	/**
	 * @brief	Encoding�� �ʿ��� ������ ���̸� �̸� ������ش�.
	 * @param[in]	sizeDecoded	Decode�Ǿ��ִ� ���ڿ��� ����
	 * @return	Encoding�� �ʿ��� ������ ���̸� ��ȯ
	 */
	size_t	CalculateEncodeLength( size_t IN sizeDecoded );

	/**
	 * @brief	Decoding�� �ʿ��� ������ ���̸� �̸� ������ش�.
	 * @param[in]	sizeEncoded	Encode�Ǿ��ִ� ���ڿ��� ����
	 * @return	Decoding�� �ʿ��� ������ ���̸� ��ȯ
	 */
	size_t	CalculateDecodeLength( size_t IN sizeEncoded );

#ifdef	_EA_UNITTEST
	BOOL	Test();
#endif
protected:
	static	BYTE	m_au8MapSafe[];
	static	TCHAR	m_tszHex[];
};

_EA_NAMESPACE_END

#endif /* !_EA_CURLENCODE_H_ */
