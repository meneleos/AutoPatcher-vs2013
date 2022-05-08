// stdafx.h : ���� ��������� ���� ��������� �ʴ�
// ǥ�� �ý��� ���� ���� �� ������Ʈ ���� ���� ������
// ��� �ִ� ���� �����Դϴ�.
//

#ifndef TORRENTPATCH_METIN2TORRENTCONSOLE_H_
#define TORRENTPATCH_METIN2TORRENTCONSOLE_H_
//
//
//#define stdin  (__acrt_iob_func(0))
//#define stdout (__acrt_iob_func(1))
//#define stderr (__acrt_iob_func(2))

#define BOOST_FILESYSTEM_NARROW_ONLY
//#define BOOST_NO_STD_WSTRING

//#ifndef _WIN32_WINNT		// Windows XP �̻󿡼��� ����� ����� �� �ֽ��ϴ�.                   
//#define _WIN32_WINNT 0x0501	// �ٸ� ������ Windows�� �µ��� ������ ������ ������ �ֽʽÿ�.

// WIN98 ����
#define WINVER         0x0501
#define _WIN32_WINNT   0x0501 // Windows 2000
#define _WIN32_WINDOWS 0x0501 // WIN98
#define _WIN32_IE      0x0501 // ���ͳ� �ͽ��÷η� 4.1
//#endif						

// Windows ��� ����:
#include <winsock2.h>
#include <windows.h>
//#include <WinNT.h>

#include <wx-2.8.10/wxprec.h>
#ifndef WX_PRECOMP
   #include <wx-2.8.10/wx.h>
#endif

#include <stdio.h>
#include <stdlib.h>
#include <tchar.h>

//#include <YmirBase/YmirBase.h>
//#include <YmirBase/Log.h>
#include "Primitives.h"
#include "Macro.h"
#include "Status.h"

#include <Earth/Earth.h>
//#include <Earth/EA_CStatus.h>
#include <Mantle/MA_String.h>
//#include <Mantle/MA_StringCharSet.h>
#include <Mantle/MA_StringNumeric.h>
#include <Mantle/MA_STLString.h>

#include <TinyXML-2.6.1/TinyXML.h>

//#include <boost/filesystem/path.hpp>
#include <boost/foreach.hpp>
#include <boost/bind.hpp>

//#ifdef _DEBUG
//#define TORRENT_DEBUG
//#endif
//#define ENABLE_GUARD_CHECKER

#define _SFX_ENABLE

#define APP_VERSION_NAME			_T("v1.8.2")
#define APP_NAME					"Metin2-Patcher"
#define TAPP_NAME					_T("Metin2-Patcher")
#define TAPP_FULLNAME				_T("Metin2-Patcher") //## APP_VERSION_NAME
#define DIR_LOG						_T("temp")

#define FILENAME_PATCH_VER			_T("patch.ver")
#define FILENAME_PATCH_URL_XML		_T("TorrentPatch.url.xml")
#define FILENAME_APP_ICON			_T("TorrentPatch.ico")

//#ifndef _DEBUG
#define UPDATE_PATCHER_SELF
#define USE_FAST_SELFUPDATE
//#endif

#include "CLocaleManager.h"

#include "PatchInfo.h"
#include "PatchConfig.h"
#include "PatchStatus.h"
#include "StringMa.h"


#endif  // TORRENTPATCH_METIN2TORRENTCONSOLE_H_
