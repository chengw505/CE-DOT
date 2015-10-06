
// CE-DOT.h : main header file for the CE-DOT application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols

#define LOCAL_BACKUP_DIR    _T("./data_backup/")
#define REMOTE_DATA_DIR     _T("../data_server")

// CCEDOTApp:
// See CE-DOT.cpp for the implementation of this class
//

class CCEDOTApp : public CWinAppEx
{
public:
	CCEDOTApp();

private:
    int InitAdoConnection();

// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Implementation
	BOOL  m_bHiColorIcons;

	virtual void PreLoadState();
	virtual void LoadCustomState();
	virtual void SaveCustomState();

	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CCEDOTApp theApp;
