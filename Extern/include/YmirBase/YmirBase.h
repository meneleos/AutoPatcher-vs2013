// stdafx.h : ���� ��������� ���� ��������� �ʴ�
// ǥ�� �ý��� ���� ���� �� ������Ʈ ���� ���� ������
// ��� �ִ� ���� �����Դϴ�.
//

#pragma once

#if defined( EL_BASE_EXPORTS )
	#define EL_BASE_API __declspec(dllexport)
#elif defined( EL_BASE_IMPORTS )
	#define EL_BASE_API __declspec(dllimport)
#else
	#define EL_BASE_API
#endif

#include <Mantle/Mantle.h>
#include <Mantle/MA_String.h>
#include <tchar.h>

#include "STLString.h"
#include "STLVector.h"
#include "STLDeque.h"
#include "STLList.h"
#include "STLMap.h"
#include "STLHashMap.h"

#include "Macro.h"
#include "Primitives.h"
