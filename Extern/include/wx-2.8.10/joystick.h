/////////////////////////////////////////////////////////////////////////////
// Name:        joystick.h
// Purpose:     wxJoystick base header
// Author:      wxWidgets Team
// Modified by:
// Created:
// Copyright:   (c) wxWidgets Team
// RCS-ID:      $Id: joystick.h 32852 2005-03-16 16:18:31Z ABX $
// Licence:     wxWindows licence
/////////////////////////////////////////////////////////////////////////////

#ifndef _WX_JOYSTICK_H_BASE_
#define _WX_JOYSTICK_H_BASE_

#include "wx-2.8.10/defs.h"

#if wxUSE_JOYSTICK

#if defined(__WXMSW__)
#include "wx-2.8.10/msw/joystick.h"
#elif defined(__WXMOTIF__)
#include "wx-2.8.10/unix/joystick.h"
#elif defined(__WXGTK__)
#include "wx-2.8.10/unix/joystick.h"
#elif defined(__WXX11__)
#include "wx-2.8.10/unix/joystick.h"
#elif defined(__DARWIN__)
#include "wx-2.8.10/mac/corefoundation/joystick.h"
#elif defined(__WXMAC__)
#include "wx-2.8.10/mac/joystick.h"
#elif defined(__WXPM__)
#include "wx-2.8.10/os2/joystick.h"
#endif

#endif // wxUSE_JOYSTICK

#endif
    // _WX_JOYSTICK_H_BASE_
