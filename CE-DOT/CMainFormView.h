
// CMainFormView.h : interface of the CMainFormView class
//

#pragma once

#include "resource.h"
#include "atltime.h"
#include "afxwin.h"

#define IDT_TIMER_MON   100
#define IDT_TIMER_TUE   101
#define IDT_TIMER_WED   102
#define IDT_TIMER_THU   103
#define IDT_TIMER_FRI   104
#define IDT_TIMER_SAT   105
#define IDT_TIMER_SUN   106

class CMainFormView : public CFormView
{
protected: // create from serialization only
	CMainFormView();
	DECLARE_DYNCREATE(CMainFormView)

public:
	enum{ IDD = IDD_CEDOT_FORM };

// Attributes
public:
	CCEDOTDoc* GetDocument() const;

// Operations
public:

// Overrides
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void OnInitialUpdate(); // called first time after construct

// Implementation
public:
	virtual ~CMainFormView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
    afx_msg void OnManualMode();
    afx_msg void OnBnClickedBtnSetupFtpAccount();
    afx_msg void OnBnClickedBtnSetupDbAccount();
    afx_msg LRESULT OnFtpFileDoubleClick(WPARAM w, LPARAM l);
    DECLARE_MESSAGE_MAP()

public:
    CString m_strHintText;
    CTime m_executeTime;
    CButton m_btnCheckContent;
    CButton m_btnDispContent;
    int m_iManualMode;
    CButton m_btnRepeat;

    CFtpSetting m_ftpSettingDlg;
    CSqlSetting m_sqlSettingDlg;
    CLogonInfo  m_ftpLogonInfo;
    CFTPClient  m_ftpClient;

    CDataParser m_dataParser;

    _ConnectionPtr  m_pConnection;
    _RecordsetPtr   m_pRecordset;
    CString         m_strOutputMessage;

    int InitialAdoInstance();
    int FinalizeAdoInstance();
    int ConnectDB();
    int ExecuteSQL(const CString& strSql);
    int CloseDB();

    void Initialize();
    void LoadFtpSettings();
    void LoadSqlSettings();
    void FillFtpFileView();

    int DownloadFile(CString& remoteFilename, CString& localFilename);
    int Rollback(UINT urcNumber);
    void UpdateModeUI();
    afx_msg void OnBnClickedBtnDisplayContent();
    afx_msg void OnBnClickedBtnCheckContent();
    afx_msg void OnBnClickedManualMode();
    afx_msg void OnBnClickedAutoMode();
    afx_msg void OnBnClickedAutoPeriod();
    afx_msg void OnBnClickedBtnConfirmSchedule();
    afx_msg void OnTimer(UINT_PTR nIDEvent);
    void SendOutputMessage(CString& strText);
    int StartSchedule();
    int StoptSchedule(UINT nIDEvent);
    int ScheduleProc();
};

#ifndef _DEBUG  // debug version in CMainFormView.cpp
inline CCEDOTDoc* CMainFormView::GetDocument() const
   { return reinterpret_cast<CCEDOTDoc*>(m_pDocument); }
#endif

