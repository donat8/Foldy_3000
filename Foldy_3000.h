
// Foldy_3000.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CFoldy3000App:
// See Foldy_3000.cpp for the implementation of this class
//

class CFoldy3000App : public CWinApp
{
public:
	CFoldy3000App();

// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CFoldy3000App theApp;
