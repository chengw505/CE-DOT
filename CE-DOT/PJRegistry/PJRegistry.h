// PJRegistry.h: interface for the CPJRegistry class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PJREGISTRY_H__8031678F_65A4_4EDD_A914_5F31C8EDA68F__INCLUDED_)
#define AFX_PJREGISTRY_H__8031678F_65A4_4EDD_A914_5F31C8EDA68F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/*
Class:    CPJRegistry
Author:   Peter M. Jones
Email:    jonespm@home.com
Version:  2.0
Created:  May  7, 2001
Description:
	A class to simplify loading/saving data to the registry.
	Data is written to the registry in human readable form.
	A single call, eg: Reg.Profile("UserName", m_strUserName); 
	handles	both loading and saving of data to the registry.
	The class can use either HKEY_LOCAL_MACHINE or HKEY_CURRENT_USER
	as a base key.
	Binary data is supported with the final "Profile" (LPBYTE) call.
	"Profile" is overloaded to handle most data types including:
		bool, WORD, int, long, unsigned long, double,
		CSize, CPoint, CRect, COleDateTime, CString.
Modified: May 15, 2001
Changes: Re-written so class no longer uses CWinApp::WriteProfile...,
		 now calls RegSetValueEx, etc.  This allows the class to
		 select HKEY_LOCAL_MACHINE or HKEY_CURRENT_USER base keys
		 through the new call "RootKey".  Default is the same as
		 MFC, HKEY_CURRENT_USER.  ASSERTS are now used.

Example use:

// File MyApp.cpp

CMyApp::CMyApp()
{
	// initialize globals
	m_nUseCount    = 0;
	m_bMadeSummary = FALSE;
	m_strUserName  = "";
	m_StartDate    = GetCurrentTime();
	m_LastUsed     = GetCurrentTime();
	m_rcMainWindow = CRect(50, 50, 650, 450);
	...
}

#include "PJRegistry.h"

#define GET_REGISTRY TRUE
#define PUT_REGISTRY FALSE

// Get or put our global variables from the registry

int CMyApp::GetPutRegistryData(BOOL	bIsGet) 
{
	CPJRegistry	Reg((CWinApp*)this, bIsGet);

	Reg.RootKey(HKEY_LOCAL_MACHINE);
	Reg.Section("Settings");
	Reg.Profile("UseCount",    m_nUseCount);
	Reg.Profile("MadeSummary", m_bMadeSummary);

	Reg.RootKey(HKEY_CURRENT_USER);
	Reg.Section("Settings");
	Reg.Profile("UserName",    m_strUserName);
	Reg.Profile("StartDate",   m_StartDate);
	Reg.Profile("LastUsed",    m_LastUsed);

	Reg.Section("MainWindow");
	Reg.Profile("Position",	   m_rcMainWindow);

	if (bIsGet)
	{
		// Nothing is guaranteed, so correct illegal values
		// and check any relationships between variables, eg:
		if (m_LastUsed < m_StartDate)
			m_StartDate = m_LastUsed;	
	}
	return 0;
}

BOOL CMyApp::InitInstance()
{
	...
	LoadStdProfileSettings();  // Load standard INI file options (including MRU)

	// Load application registry settings
	GetPutRegistryData(GET_REGISTRY);
	...
}

int CMyApp::ExitInstance() 
{
	GetPutRegistryData(PUT_REGISTRY);
	return CWinApp::ExitInstance();
}
*/

class CPJRegistry  
{
public:
	CPJRegistry(CWinApp*  pApp, BOOL  bIsGet);
	virtual ~CPJRegistry();

	BOOL RootKey(HKEY hRootKey); // select HKEY_CURRENT_USER or HKEY_LOCAL_MACHINE
	void Section(CString strSection); // application section, eg: "Settings"

	// note: Visual C++ defines BOOL as an int, unsigned long as DWORD
	// The following reads/writes to registry according to bIsGet
	// Each call returns RegSetValueEx or RegQueryValueEx results.
	// ERROR_SUCCESS means everything worked.
	// ERROR_FILE_NOT_FOUND during a get means the key couldn't be found,
	// this is expected on the initial run of the program.
	long Profile(LPCTSTR lpszEntry, int& nValue);
	long Profile(LPCTSTR lpszEntry, WORD& nValue);
	long Profile(LPCTSTR lpszEntry, DWORD& dwValue);
	long Profile(LPCTSTR lpszEntry, long& lValue);
	long Profile(LPCTSTR lpszEntry, double& dValue);
	long Profile(LPCTSTR lpszEntry, CString& strValue);
	long Profile(LPCTSTR lpszEntry, CPoint& PointValue);
	long Profile(LPCTSTR lpszEntry, CSize& Size);
	long Profile(LPCTSTR lpszEntry, COleDateTime& DateTime);
	long Profile(LPCTSTR lpszEntry, CRect& rcValue);
	long Profile(LPCTSTR lpszEntry, LPBYTE pData, UINT& nBytes);
	
private:
	CWinApp*	m_pApp;				// to retrieve company and application name
	BOOL		m_bGet;				// get or put?
	CString		m_strSection;		// application section name, eg: "Settings"
	HKEY		m_hRootKey;			// HKEY_LOCAL_MACHINE or HKEY_CURRENT_USER
	HKEY		m_hAppKey;			// key for application under RootKey
	HKEY		m_hSectionKey;		// key for section key under application
	BOOL		m_bDirty;			// have changes requiring flush?
	CString		m_strCompanyName;	// company name from m_pApp
	CString		m_strAppName;		// application name from m_pApp

	HKEY GetAppRegistryKey();		// gets key to app based on company and app names
};

#endif // !defined(AFX_PJREGISTRY_H__8031678F_65A4_4EDD_A914_5F31C8EDA68F__INCLUDED_)
