#pragma once

//#include <YmirBase/YmirBaseLink.h>
//#include <YmirLocale/YmirLocaleLink.h>
//#include <Earth/EA_LibLink.h>

#include <TinyXML-2.6.1/TinyXMLLibLink.h>
#include <zlib-1.2.3/zlibLibLink.h>

#pragma comment(lib, "comctl32.lib")
#pragma comment(lib, "rpcrt4.lib")

#pragma comment(lib, "Iphlpapi.lib")

#ifndef NO_LIBTORRENT
#ifdef _DEBUG
	#pragma comment(lib, "libtorrent-1.1.12WMTd.lib")
#else
	#pragma comment(lib, "libtorrent-1.1.12WMT.lib")
#endif
#endif
