
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

#define REG_SECTION     _T("Settings")
#define REG_MANUAL_MODE _T("Manual Mode")
#define REG_AUTO_TIME_HH   _T("Auto Time HH")
#define REG_AUTO_TIME_MM   _T("Auto Time MM")
#define REG_AUTO_TIME_SS   _T("Auto Time SS")
#define REG_AUTO_MON    _T("Mon")
#define REG_AUTO_TUE    _T("Tue")
#define REG_AUTO_WED    _T("Wed")
#define REG_AUTO_THU    _T("Thu")
#define REG_AUTO_FRI    _T("Fri")
#define REG_AUTO_SAT    _T("Sat")
#define REG_AUTO_SUN    _T("Sun")
#define REG_AUTO_REPEAT _T("Repeat")
#define REG_FTP_HOST    _T("FTP Host")
#define REG_FTP_ANONY   _T("FTP Anonoymous")
#define REG_FTP_USER    _T("FTP User Name")
#define REG_FTP_PASSWD  _T("FTP Password")
#define REG_FTP_PORT    _T("FTP Port")
#define REG_DB_HOST     _T("DB Host")
#define REG_DB_USER     _T("DB User Name")
#define REG_DB_PASSWD   _T("DB Password")
#define REG_DB_WIN_AUTH _T("DB Windows Auth")

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
    enum {
        XMLDATA_OK = 0, 
        XMLDATA_DOWNLOAD_ERR, 
        XMLDATA_PARSE_ERR,
        XMLDATA_URC_DUPLICATE, 
        XMLDATA_PARSE_CRASH_DATA_ERR, 
        XMLDATA_IMPORT_CRASH_DATA_ERR, 
        XMLDATA_PARSE_VEH_DATA_ERR,
        XMLDATA_IMPORT_VEH_DATA_ERR
    };
    CString m_strHintText;
    CButton m_btnCheckContent;
    CButton m_btnDispContent;
    int m_iManualMode;
    CTime m_executeTime;
    BOOL m_bMonday;
    BOOL m_bTuesday;
    BOOL m_bWednesday;
    BOOL m_bThursday;
    BOOL m_bFriday;
    BOOL m_bSaturday;
    BOOL m_bSunday;
    BOOL m_bRepeat;
    CButton m_btnRepeat;

    BOOL m_bFtpReady;
    BOOL m_bDBReady;

    CSqlSetting m_sqlSettingDlg;
    CFtpSetting m_ftpSettingDlg;
    CLogonInfo  m_ftpLogonInfo;
    CFTPClient  m_ftpClient;

    

    _ConnectionPtr  m_pConnection;
    _RecordsetPtr   m_pRecordset;
    CString         m_strOutputMessage;

    int InitialAdoInstance();
    int FinalizeAdoInstance();
    int ConnectDB();
    int RecordExisted(UINT urcNumber);
    int ExecuteSQL(const CString& strSql);
    int CloseDB();

    void Initialize();
    int LoadFtpSettings();
    int LoadSqlSettings();
    void FillFtpFileView();

    void UpdateModeUI();
    afx_msg void OnBnClickedBtnDisplayContent();
    afx_msg void OnBnClickedBtnCheckContent();
    afx_msg void OnBnClickedManualMode();
    afx_msg void OnBnClickedAutoMode();
    afx_msg void OnBnClickedBtnConfirmSchedule();
    afx_msg void OnTimer(UINT_PTR nIDEvent);
    afx_msg void OnBnClickedBtnSetupDbAccount2();
    void SendOutputMessage(CString& strText);
    int StartSchedule();
    int StoptSchedule(UINT nIDEvent);
    int GetSetSettings(BOOL bLoad = TRUE);
    int DownloadFile(const CString& remoteFilename, CString& localFilename);
    int DeleteFileFromFtp(CString& strRemoteFileFullPath);
    int Rollback(UINT urcNumber);
    int CheckContent(CDataParser& dataParser, CString& strRemoteFullPath, CString& strLocalFileName);
    int ScheduleProc();
    int CurrentTime(char* buffer);
    CString CheckReportCriteria(CDataParser& parser);
    void UploadReports(CStringList& reportFileList);
};

#ifndef _DEBUG  // debug version in CMainFormView.cpp
inline CCEDOTDoc* CMainFormView::GetDocument() const
   { return reinterpret_cast<CCEDOTDoc*>(m_pDocument); }
#endif

