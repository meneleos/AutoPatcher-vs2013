#ifndef _EL_POLYGON2D_H_
#define _EL_POLYGON2D_H_

#include "TPos.h"

class EL_CPolygon2D
{
public:
	EL_CPolygon2D();
	~EL_CPolygon2D();

	EL_BOOL		Attach( LPVOID pvBuffer );
	LPVOID		Detatch( void );
	void		Free( void );
	EL_BOOL		Set( LPVOID pvBuffer );

	EL_BOOL		CheckPointInPolygon( EL_FPOS2& cPosition );

protected:
	DWORD		m_dwVerticles;			//< Vertex ����
	EL_FPOS2*	m_apcVertex;			//< Vertex ���� ������
	LPVOID		m_pvBuffer;				//< �Ҵ�� �޸� ������
	DWORD		m_dwReserved;			//< �Ҵ�� Vertex ����
	EL_BOOL		m_bBufferOwned;			//< �޸� ���� ����
};

#endif /* !_EL_POLYGON2D_H_ */
