// PJRegistry.cpp: implementation of the CPJRegistry class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "PJRegistry.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

// possible delimiters for compound items like CRect, CSize and CPoint
TCHAR	cSeps[]   = _T(" ,\t\n");

CPJRegistry::CPJRegistry(CWinApp*  pApp, BOOL	bIsGet)
{
	m_pApp = pApp;
	m_bGet = bIsGet;
	m_strSection = "";
	m_hRootKey    = HKEY_CURRENT_USER;
	m_hAppKey     = HKEY_CURRENT_USER;
	m_hSectionKey = NULL;
	m_bDirty = FALSE;

	m_strCompanyName = pApp->m_pszRegistryKey;
	m_strAppName     = pApp->m_pszProfileName;
	RootKey(HKEY_CURRENT_USER);
}

CPJRegistry::~CPJRegistry()
{
	if (m_bDirty)
		if (m_hAppKey)
			RegFlushKey(m_hAppKey);
	if (m_hSectionKey)
		::RegCloseKey(m_hSectionKey);
	if (m_hAppKey)
		::RegCloseKey(m_hAppKey);
}

HKEY CPJRegistry::GetAppRegistryKey()
{
	ASSERT(m_strCompanyName.GetLength() > 0);
	ASSERT(m_strAppName.GetLength() > 0);

	HKEY hAppKey = NULL;
	HKEY hSoftKey = NULL;
	HKEY hCompanyKey = NULL;
	if (RegOpenKeyEx(m_hRootKey, _T("software"), 0, KEY_WRITE|KEY_READ,
		&hSoftKey) == ERROR_SUCCESS)
	{
		DWORD dw;
		if (RegCreateKeyEx(hSoftKey, m_strCompanyName, 0, REG_NONE,
			REG_OPTION_NON_VOLATILE, KEY_WRITE|KEY_READ, NULL,
			&hCompanyKey, &dw) == ERROR_SUCCESS)
		{
			RegCreateKeyEx(hCompanyKey, m_strAppName, 0, REG_NONE,
				REG_OPTION_NON_VOLATILE, KEY_WRITE|KEY_READ, NULL,
				&hAppKey, &dw);
		}
	}
	if (hSoftKey != NULL)
		RegCloseKey(hSoftKey);
	if (hCompanyKey != NULL)
		RegCloseKey(hCompanyKey);

	return hAppKey;
}

void CPJRegistry::Section(CString strSection)
{
	DWORD	dw;
	long	lResult;

	if (m_hSectionKey != NULL)
		if (m_hSectionKey != m_hAppKey)
			::RegCloseKey(m_hSectionKey);
	m_hSectionKey = NULL;
	m_strSection = strSection;
	lResult = RegCreateKeyEx(m_hAppKey, strSection, 0, REG_NONE,
			REG_OPTION_NON_VOLATILE, KEY_WRITE|KEY_READ, NULL,
			&m_hSectionKey, &dw);
	if ((lResult != ERROR_SUCCESS) || (m_hSectionKey == NULL))
		m_hSectionKey = m_hAppKey;
}

BOOL CPJRegistry::RootKey(HKEY hRootKey)
{
	// not HKEY_USERS or HKEY_CLASSES_ROOT

	ASSERT((hRootKey == HKEY_CURRENT_USER) || (hRootKey == HKEY_LOCAL_MACHINE));

	if (m_bDirty)
		if (m_hAppKey)
			RegFlushKey(m_hAppKey);
	m_bDirty = FALSE;
	if (m_hSectionKey != NULL)
		if (m_hSectionKey != m_hAppKey)
			::RegCloseKey(m_hSectionKey);
	m_hSectionKey = NULL;
	if (m_hAppKey)
		::RegCloseKey(m_hAppKey);
	m_hRootKey = hRootKey;
	m_hAppKey  = GetAppRegistryKey();
	m_hSectionKey = NULL;
	m_strSection = "";

	return m_hAppKey != NULL;
}


long CPJRegistry::Profile(LPCTSTR lpszEntry, CString& strValue)
{
	DWORD	dwBytes  = 0;
	LPBYTE	lpData   = NULL;
	DWORD	dwType	 = REG_SZ;
	long	lResult  = ERROR_SUCCESS;

	ASSERT(m_hSectionKey != NULL);
	ASSERT(lpszEntry != NULL);
	ASSERT(m_strSection.GetLength() > 0);
	if (m_bGet)
	{
		// query for size
		lResult = ::RegQueryValueEx(m_hSectionKey, lpszEntry, NULL, &dwType, NULL, &dwBytes);
		if (lResult == ERROR_SUCCESS)
		{
			CString	strTemp;
			lpData = (LPBYTE) strTemp.GetBuffer(dwBytes+1);
			lResult = ::RegQueryValueEx(m_hSectionKey, lpszEntry, NULL, &dwType, lpData, &dwBytes);
			strTemp.ReleaseBuffer();
			if ((lResult == ERROR_SUCCESS) && (dwType == REG_SZ))
				strValue = strTemp;
		}
	}
	else
	{
		dwBytes = strValue.GetLength()+1;
		lpData = (LPBYTE) strValue.GetBuffer(dwBytes);
		lResult = ::RegSetValueEx(m_hSectionKey, lpszEntry, NULL, REG_SZ, lpData, dwBytes);			
		m_bDirty = TRUE;
	}
	return lResult;
}

long CPJRegistry::Profile(LPCTSTR lpszEntry, DWORD& dwValue)
{
	DWORD	dwBuffer = 0;
	DWORD	dwBytes  = sizeof(DWORD);
	DWORD	dwType	 = REG_DWORD;
	long	lResult  = ERROR_SUCCESS;

	ASSERT(m_hSectionKey != NULL);
	ASSERT(lpszEntry != NULL);
	ASSERT(m_strSection.GetLength() > 0);
	if (m_bGet)
	{
		lResult = ::RegQueryValueEx(m_hSectionKey, lpszEntry, NULL, &dwType, (LPBYTE)&dwBuffer, &dwBytes);
		if ((lResult == ERROR_SUCCESS) && (dwType == REG_DWORD))
			dwValue = dwBuffer;
	}
	else
	{
		lResult = ::RegSetValueEx(m_hSectionKey, lpszEntry, NULL, dwType, (LPBYTE)&dwValue, dwBytes);			
		m_bDirty = TRUE;
	}

	return lResult;
}

long CPJRegistry::Profile(LPCTSTR lpszEntry, LPBYTE pData, UINT& nBytes)
{
	UINT	nOrigSize = nBytes;
	DWORD	dwBytes   = 256;
	LPBYTE	lpData    = NULL;
	DWORD	dwType	  = REG_BINARY;
	long	lResult   = ERROR_SUCCESS;

	ASSERT(nBytes>0);
	ASSERT(pData != NULL);
	ASSERT(lpszEntry != NULL);
	ASSERT(m_hSectionKey != NULL);
	ASSERT(m_strSection.GetLength() > 0);
	if (m_bGet)
	{
		// query for length
		lResult = ::RegQueryValueEx(m_hSectionKey, lpszEntry, NULL, &dwType, NULL, &dwBytes);
		if (lResult == ERROR_SUCCESS)
		{
			lpData = new BYTE[dwBytes];
			lResult = ::RegQueryValueEx(m_hSectionKey, lpszEntry, NULL, &dwType, lpData, &dwBytes);
			if ((lResult == ERROR_SUCCESS) && (dwType == REG_BINARY))
				memcpy(pData, lpData, min(nBytes, nOrigSize));
			if (lpData)
				delete lpData;
		}
	}
	else
	{
		lResult = ::RegSetValueEx(m_hSectionKey, lpszEntry, NULL, REG_BINARY, pData, nBytes);			
		m_bDirty = TRUE;
	}
	return lResult;
}


long CPJRegistry::Profile(LPCTSTR lpszEntry, int& nValue)
{
	DWORD	dwValue = (DWORD) nValue;
	
	long lResult = Profile(lpszEntry, dwValue);
	nValue = (int) dwValue;
	return lResult;
}

long CPJRegistry::Profile(LPCTSTR lpszEntry, WORD& nValue)
{
	DWORD	dwValue = (DWORD) nValue;
	
	long lResult = Profile(lpszEntry, dwValue);
	nValue = (WORD) dwValue;
	return lResult;
}

long CPJRegistry::Profile(LPCTSTR lpszEntry, double& dValue)
{
	CString	strTemp;
	long	lResult;

	if (m_bGet)
	{
		lResult = Profile(lpszEntry, strTemp);
		if ((lResult == ERROR_SUCCESS) && !strTemp.IsEmpty())
			dValue = _wtof(strTemp.GetString());
	}
	else
	{
		strTemp.Format(_T("%.16g"),dValue);
		lResult = Profile(lpszEntry, strTemp);
	}
	return lResult;
}

long CPJRegistry::Profile(LPCTSTR lpszEntry, long& lValue)
{
	CString	strTemp;
	long	lResult;

	if (m_bGet)
	{
		lResult = Profile(lpszEntry, strTemp);
		if ((lResult == ERROR_SUCCESS) && !strTemp.IsEmpty())
			lValue = _wtol(strTemp.GetString());
	}
	else
	{
		strTemp.Format(_T("%ld"),lValue);
		lResult = Profile(lpszEntry, strTemp);
	}
	return lResult;
}

long CPJRegistry::Profile(LPCTSTR lpszEntry, COleDateTime& DateTime)
{
	CString strTemp;
	long	lResult;

	if (m_bGet)
	{
		lResult = Profile(lpszEntry, strTemp);
		if (lResult == ERROR_SUCCESS)
		{
			COleDateTime tempDateTime;
			tempDateTime.ParseDateTime(strTemp);
			if (tempDateTime.m_status == COleDateTime::valid)
				DateTime = tempDateTime;
		}
	}
	else
	{
		strTemp = DateTime.Format(_T("%I:%M:%S %p %b %d, %Y"));
		lResult = Profile(lpszEntry, strTemp);
	}
	return lResult;
}

long CPJRegistry::Profile(LPCTSTR lpszEntry, CPoint& PointValue)
{
	TCHAR*	lpszToken;
	CString strTemp;
	long	lResult;

	if (m_bGet)
	{
		TCHAR*	lpEnd;
		lResult = Profile(lpszEntry, strTemp);
		if ((lResult == ERROR_SUCCESS) && !strTemp.IsEmpty())
		{
            lpszToken = wcstok(strTemp.GetBuffer(strTemp.GetLength()), cSeps);
			if (lpszToken != NULL)
			{
				lpEnd = lpszToken + 100;
                PointValue.x = wcstol(lpszToken, &lpEnd, 10);
                lpszToken = wcstok(NULL, cSeps);
				if (lpszToken != NULL)
				{
					lpEnd = lpszToken + 100;
                    PointValue.y = wcstol(lpszToken, &lpEnd, 10);
				}
			}
		}
	}
	else
	{
		strTemp.Format(_T("%ld, %ld"), PointValue.x, PointValue.y);
		lResult = Profile(lpszEntry, strTemp);
	}
	return lResult;
}

long CPJRegistry::Profile(LPCTSTR lpszEntry, CSize& Size)
{
	TCHAR*	lpszToken;
	CString strTemp;
	long	lResult;

	if (m_bGet)
	{
        TCHAR*	lpEnd;
		lResult = Profile(lpszEntry, strTemp);
		if ((lResult == ERROR_SUCCESS) && !strTemp.IsEmpty())
		{
            lpszToken = wcstok(strTemp.GetBuffer(strTemp.GetLength()), cSeps);
			if (lpszToken != NULL)
			{
				lpEnd = lpszToken + 100;
                Size.cx = wcstol(lpszToken, &lpEnd, 10);
                lpszToken = wcstok(NULL, cSeps);
				if (lpszToken != NULL)
				{
					lpEnd = lpszToken + 100;
                    Size.cy = wcstol(lpszToken, &lpEnd, 10);
				}
			}
		}
	}
	else
	{
		strTemp.Format(_T("%ld, %ld"), Size.cx, Size.cy);
		lResult = Profile(lpszEntry, strTemp);
	}
	return lResult;
}

long CPJRegistry::Profile(LPCTSTR lpszEntry, CRect& rcValue)
{
	TCHAR*	lpszToken;
	CString strTemp;
	long	lResult;

	if (m_bGet)
	{
		TCHAR*	lpEnd;
		lResult = Profile(lpszEntry, strTemp);
		if ((lResult == ERROR_SUCCESS) && !strTemp.IsEmpty())
		{
            lpszToken = wcstok(strTemp.GetBuffer(strTemp.GetLength()), cSeps);
			for (int i=0; i<4 && (lpszToken != NULL); i++)
			{
				lpEnd = lpszToken + 100;
                long lTemp = wcstol(lpszToken, &lpEnd, 10);
				switch (i)
				{
					case 0: rcValue.left   = lTemp; break;
					case 1: rcValue.top    = lTemp; break;
					case 2: rcValue.right  = lTemp; break;
					case 3: rcValue.bottom = lTemp; break;
				}
                lpszToken = wcstok(NULL, cSeps);
			}
			strTemp.ReleaseBuffer();
		}
	}
	else
	{
		strTemp.Format(_T("%ld, %ld, %ld, %ld"), rcValue.left,rcValue.top,rcValue.right,rcValue.bottom);
		lResult = Profile(lpszEntry, strTemp);
	}
	return lResult;
}
