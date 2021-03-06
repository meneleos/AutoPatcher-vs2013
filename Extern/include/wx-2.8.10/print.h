/////////////////////////////////////////////////////////////////////////////
// Name:        wx/print.h
// Purpose:     Base header for printer classes
// Author:      Julian Smart
// Modified by:
// Created:
// RCS-ID:      $Id: print.h 41240 2006-09-15 16:45:48Z PC $
// Copyright:   (c) Julian Smart
// Licence:     wxWindows Licence
/////////////////////////////////////////////////////////////////////////////

#ifndef _WX_PRINT_H_BASE_
#define _WX_PRINT_H_BASE_

#include "wx-2.8.10/defs.h"

#if wxUSE_PRINTING_ARCHITECTURE

#if defined(__WXMSW__) && !defined(__WXUNIVERSAL__)

#include "wx-2.8.10/msw/printwin.h"

#elif defined(__WXMAC__)

#include "wx-2.8.10/mac/printmac.h"

#elif defined(__WXPM__)

#include "wx-2.8.10/os2/printos2.h"

#else

#include "wx-2.8.10/generic/printps.h"

#endif

#endif // wxUSE_PRINTING_ARCHITECTURE
#endif
    // _WX_PRINT_H_BASE_
