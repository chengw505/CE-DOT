
// CMainFormView.cpp : implementation of the CMainFormView class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "CE-DOT.h"
#endif

#include "CE-DOTDoc.h"
#include "MainFrm.h"
#include "FtpSetting.h"
#include "SqlSetting.h"
#include "DataParser.h"
#include "CMainFormView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMainFormView

IMPLEMENT_DYNCREATE(CMainFormView, CFormView)

BEGIN_MESSAGE_MAP(CMainFormView, CFormView)
    ON_WM_CONTEXTMENU()
    ON_WM_RBUTTONUP()
    ON_BN_CLICKED(IDC_BTN_SETUP_FTP_ACCOUNT, &CMainFormView::OnBnClickedBtnSetupFtpAccount)
    ON_BN_CLICKED(IDC_BTN_SETUP_DB_ACCOUNT, &CMainFormView::OnBnClickedBtnSetupDbAccount)
    ON_MESSAGE(CUSTOM_WM_MESSAGE, OnFtpFileDoubleClick)
    ON_BN_CLICKED(IDC_BTN_DISPLAY_CONTENT, &CMainFormView::OnBnClickedBtnDisplayContent)
    ON_BN_CLICKED(IDC_BTN_CHECK_CONTENT, &CMainFormView::OnBnClickedBtnCheckContent)
END_MESSAGE_MAP()

// CMainFormView construction/destruction

CMainFormView::CMainFormView()
                : CFormView(CMainFormView::IDD)
                , m_ftpClient(nsSocket::CreateDefaultBlockingSocketInstance(), 30)
                , m_iPeriodNum(7)
                , m_strHintText(_T(""))
                , m_executeTime(0)
                , m_iManualMode(0)
{
    // TODO: add construction code here

}

CMainFormView::~CMainFormView()
{
    FinalizeAdoInstance();
    CloseDB();
}

void CMainFormView::DoDataExchange(CDataExchange* pDX)
{
    CFormView::DoDataExchange(pDX);
    DDX_Text(pDX, IDC_PERIOD_NUM, m_iPeriodNum);
    DDV_MinMaxUInt(pDX, m_iPeriodNum, 1, 366);
    DDX_Text(pDX, IDC_HINT_TEXT, m_strHintText);
    DDX_DateTimeCtrl(pDX, IDC_EXECUTE_TIME, m_executeTime);
    DDX_Control(pDX, IDC_BTN_CHECK_CONTENT, m_btnCheckContent);
    DDX_Control(pDX, IDC_BTN_DISPLAY_CONTENT, m_btnDispContent);
    DDX_Radio(pDX, IDC_AUTO_MODE, m_iManualMode);
    DDX_Control(pDX, IDC_AUTO_PERIOD, m_btnPeriod);
}

BOOL CMainFormView::PreCreateWindow(CREATESTRUCT& cs)
{
    // TODO: Modify the Window class or styles here by modifying
    //  the CREATESTRUCT cs

    return CFormView::PreCreateWindow(cs);
}

void CMainFormView::OnInitialUpdate()
{
    CFormView::OnInitialUpdate();
    GetParentFrame()->RecalcLayout();
    ResizeParentToFit();

    LoadFtpSettings();
    LoadSqlSettings();

    FillFtpFileView();

    InitialAdoInstance();
    ConnectDB();
}

void CMainFormView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
    ClientToScreen(&point);
    OnContextMenu(this, point);
}

void CMainFormView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
    theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CMainFormView diagnostics

#ifdef _DEBUG
void CMainFormView::AssertValid() const
{
    CFormView::AssertValid();
}

void CMainFormView::Dump(CDumpContext& dc) const
{
    CFormView::Dump(dc);
}

CCEDOTDoc* CMainFormView::GetDocument() const // non-debug version is inline
{
    ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CCEDOTDoc)));
    return (CCEDOTDoc*)m_pDocument;
}
#endif //_DEBUG


// CMainFormView message handlers


void CMainFormView::Initialize()
{
    if (m_iManualMode)
    {
        m_btnPeriod.EnableWindow(FALSE);
    }
    m_btnCheckContent.EnableWindow(FALSE);
    m_btnDispContent.EnableWindow(FALSE);
}


int CMainFormView::InitialAdoInstance()
{
    ::CoInitialize(NULL);

    m_pConnection = NULL;
    m_pRecordset = NULL;

    try {
        m_pConnection.CreateInstance("ADODB.Connection");

    }
    catch (_com_error e) {
        return -1;
    }

    return 0;
}

int CMainFormView::FinalizeAdoInstance()
{
    ::CoUninitialize();
    try
    {
        if (m_pRecordset) {
            m_pRecordset.Release();
        }

        if (m_pConnection) {
            m_pConnection->Close();
        }
    }
    catch (_com_error e)
    {
        return 1;
    }

    return 0;
}

int CMainFormView::ConnectDB()
{
    CString strConnect = _T("Provider=SQLOLEDB; \
                            Data Source=LOCALHOST\\SQLEXPRESS;\
                            Initial Catalog= DOT; \
                            integrated security=SSPI");
    try 
    {
        m_pConnection->Open((_bstr_t)strConnect, "", "", adModeUnknown);

    }
    catch (_com_error e) 
    {
        TRACE(_T("Fail to open database: %s\n"), e.ErrorMessage());
        return 1;
    }

    return 0;
}

int CMainFormView::ExecuteSQL(const CString& strSql)
{
    try {
        _variant_t recordsAffected;
        HRESULT hr = m_pConnection->Execute((_bstr_t)strSql, &recordsAffected, adCmdText);
        ASSERT(SUCCEEDED(hr));
    }
    catch (_com_error e) 
    {
        TRACE(_T("execute sql error: %s\n"), e.ErrorMessage());
        return 1;
    }

    return 0;
}

int CMainFormView::CloseDB()
{
    try
    {
        m_pConnection->Close();
    }
    catch (_com_error e) 
    {
        TRACE(_T("error: %s\n"), e.ErrorMessage());
        return 1;
    }

    return 0;
}

void CMainFormView::OnBnClickedBtnSetupFtpAccount()
{
    if (IDOK == m_ftpSettingDlg.DoModal()) 
    {
        m_ftpLogonInfo.SetHost(static_cast<LPCTSTR>(m_ftpSettingDlg.m_hostName), static_cast<USHORT>(m_ftpSettingDlg.m_portNumber), static_cast<LPCTSTR>(m_ftpSettingDlg.m_userName), static_cast<LPCTSTR>(m_ftpSettingDlg.m_passwd));
    }
}


void CMainFormView::OnBnClickedBtnSetupDbAccount()
{
    if (IDOK == m_sqlSettingDlg.DoModal())
    {
        m_ftpLogonInfo.SetHost(static_cast<LPCTSTR>(m_ftpSettingDlg.m_hostName), static_cast<USHORT>(m_ftpSettingDlg.m_portNumber), static_cast<LPCTSTR>(m_ftpSettingDlg.m_userName), static_cast<LPCTSTR>(m_ftpSettingDlg.m_passwd));
    }
}

void CMainFormView::LoadFtpSettings()
{
    // TODO load value from local storage and save into m_ftpSettingDlg

    m_ftpLogonInfo.SetHost(static_cast<LPCTSTR>(m_ftpSettingDlg.m_hostName), 
        static_cast<USHORT>(m_ftpSettingDlg.m_portNumber), 
        static_cast<LPCTSTR>(m_ftpSettingDlg.m_userName), 
        static_cast<LPCTSTR>(m_ftpSettingDlg.m_passwd));
}

void CMainFormView::LoadSqlSettings()
{
    // TODO throw std::logic_error("The method or operation is not implemented.");
}

void CMainFormView::FillFtpFileView()
{
    CMainFrame *pMainWnd = (CMainFrame *)AfxGetMainWnd();
    if (NULL != pMainWnd)
    {
        CFileView* fileView = (CFileView*)pMainWnd->GetFileView();
        if (NULL != fileView)
        {
            fileView->ResetFileList(&m_ftpClient, &m_ftpLogonInfo);
        }
    }
}

int CMainFormView::DownloadFile(CString& remoteFilename, CString& localFilename)
{
    int err = 1;

    TCHAR currentDir[MAX_PATH];
    GetCurrentDirectory(MAX_PATH, currentDir);
    CString strLocalFile = currentDir + CString(_T("\\Data\\"));
    if (!CreateDirectory(strLocalFile.GetString(), NULL))
    {
        if (GetLastError() != ERROR_ALREADY_EXISTS)
        {
            return err;
        }
    }
    strLocalFile += localFilename;

    if (m_ftpClient.Login(m_ftpLogonInfo))
    {
        if (m_ftpClient.DownloadFile(remoteFilename.GetString(), strLocalFile.GetString()))
        {
            localFilename = strLocalFile;
            err = 0;
        }
        m_ftpClient.Logout();
    }

    return err;
}

LRESULT CMainFormView::OnFtpFileDoubleClick(WPARAM w, LPARAM l)
{
    CString strLocalFilename = *(CString*)l;
    CString& strRemoteFilename = *(CString*)w;

    if (!DownloadFile(strRemoteFilename, strLocalFilename))
    {
        ShellExecute(0, NULL, strLocalFilename, NULL, NULL, SW_SHOWDEFAULT);
    }

    return (LRESULT)0;
}


void CMainFormView::OnBnClickedBtnDisplayContent()
{
    CMainFrame *pMainWnd = (CMainFrame *)AfxGetMainWnd();
    if (NULL != pMainWnd)
    {
        CFileView* fileView = (CFileView*)pMainWnd->GetFileView();
        fileView->SendMessage(CUSTOM_WM_MESSAGE, 0, 0);
    }
}


void CMainFormView::OnBnClickedBtnCheckContent()
{
    CMainFrame *pMainWnd = (CMainFrame *)AfxGetMainWnd();
    if (NULL != pMainWnd)
    {
        CFileView* fileView = (CFileView*)pMainWnd->GetFileView();
        HTREEITEM hSelected = fileView->GetSelectedItem();
        if (hSelected)
        {
            CString strLocalFileName = fileView->GetFileName(hSelected);
            CString strRemoteFullPath = fileView->GetFullPath(hSelected);

            if (!DownloadFile(strRemoteFullPath, strLocalFileName))
            {
                if (!m_dataParser.Parse(strLocalFileName))
                {
                    UINT urcNumber;
                    m_dataParser.GetUCRNumber(urcNumber);

                    CString strSql;
                    if (!m_dataParser.GetSQL_crash(strSql))
                    {
                        if (!ExecuteSQL(strSql))
                        {
                            strSql.Empty();
                            if (!m_dataParser.GetSQL_occupant(strSql))
                            {
                                if (!ExecuteSQL(strSql))
                                {
                                    strSql.Empty();
                                    if (!m_dataParser.GetSQL_vehicle(strSql))
                                    {
                                        if (!ExecuteSQL(strSql))
                                        {
                                            // success
                                        }
                                        else
                                        {
                                            // TODO rollback crash data, and occupant data
                                            Rollback(urcNumber);
                                        }
                                    }
                                    else
                                    {
                                        // TODO rollback crash data, and occupant data
                                        Rollback(urcNumber);
                                    }
                                }
                                else
                                {
                                    // TODO rollback crash data
                                    Rollback(urcNumber);
                                }
                            }
                            else
                            {
                                // TODO rollback crash data
                                Rollback(urcNumber);
                            }
                        }
                    }
                }
                else
                {
                    // TODO
                }
            }
        }
    }
}

int CMainFormView::Rollback(UINT urcNumber)
{
    CString strSql;

    strSql.Format(_T("DELETE FROM [dbo].[Acrash2012] WHERE ucrnumber = %d"), urcNumber);
    ExecuteSQL(strSql);

    strSql.Format(_T("DELETE FROM [dbo].[Aoccupant2012] WHERE ucrnumber = %d"), urcNumber);
    ExecuteSQL(strSql);

    strSql.Format(_T("DELETE FROM [dbo].[Avehicle2012] WHERE ucrnumber = %d"), urcNumber);
    ExecuteSQL(strSql);

    return 0;
}
