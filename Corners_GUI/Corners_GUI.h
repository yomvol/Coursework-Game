
// Corners_GUI.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CCornersGUIApp:
// See Corners_GUI.cpp for the implementation of this class
//

class CCornersGUIApp : public CWinApp
{
public:
	CCornersGUIApp();

// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CCornersGUIApp theApp;
