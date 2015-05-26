
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
    ON_BN_CLICKED(IDC_BTN_DISPLAY_CONTENT, &CMainFormView::OnBnClickedBtnDisplayContent)
    ON_BN_CLICKED(IDC_BTN_CHECK_CONTENT, &CMainFormView::OnBnClickedBtnCheckContent)
    ON_BN_CLICKED(IDC_MANUAL_MODE, &CMainFormView::OnBnClickedManualMode)
    ON_BN_CLICKED(IDC_AUTO_MODE, &CMainFormView::OnBnClickedAutoMode)
    ON_BN_CLICKED(IDC_AUTO_PERIOD, &CMainFormView::OnBnClickedAutoPeriod)
    ON_MESSAGE(WM_DOUBLE_CLICK_FTP_FILE, &CMainFormView::OnFtpFileDoubleClick)
    ON_BN_CLICKED(IDC_BTN_CONFIRM_SCHEDULE, &CMainFormView::OnBnClickedBtnConfirmSchedule)
    ON_WM_TIMER()
END_MESSAGE_MAP()

// CMainFormView construction/destruction

CMainFormView::CMainFormView()
                : CFormView(CMainFormView::IDD)
                , m_ftpClient(nsSocket::CreateDefaultBlockingSocketInstance(), 30)
                , m_strHintText(_T(""))
                , m_executeTime(0)
                , m_iManualMode(0)
{
}

CMainFormView::~CMainFormView()
{
    FinalizeAdoInstance();
    CloseDB();
}

void CMainFormView::DoDataExchange(CDataExchange* pDX)
{
    CFormView::DoDataExchange(pDX);
    DDX_Text(pDX, IDC_HINT_TEXT, m_strHintText);
    DDX_DateTimeCtrl(pDX, IDC_EXECUTE_TIME, m_executeTime);
    DDX_Control(pDX, IDC_BTN_CHECK_CONTENT, m_btnCheckContent);
    DDX_Control(pDX, IDC_BTN_DISPLAY_CONTENT, m_btnDispContent);
    DDX_Radio(pDX, IDC_AUTO_MODE, m_iManualMode);
    DDX_Control(pDX, IDC_AUTO_PERIOD, m_btnRepeat);
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

    UpdateModeUI();

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
        m_btnRepeat.EnableWindow(FALSE);
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
        m_ftpLogonInfo.SetHost(static_cast<LPCTSTR>(m_ftpSettingDlg.m_hostName), 
            static_cast<USHORT>(m_ftpSettingDlg.m_portNumber), 
            static_cast<LPCTSTR>(m_ftpSettingDlg.m_userName), 
            static_cast<LPCTSTR>(m_ftpSettingDlg.m_passwd));
    }
}


void CMainFormView::OnBnClickedBtnSetupDbAccount()
{
    if (IDOK == m_sqlSettingDlg.DoModal())
    {
        m_ftpLogonInfo.SetHost(static_cast<LPCTSTR>(m_ftpSettingDlg.m_hostName), 
            static_cast<USHORT>(m_ftpSettingDlg.m_portNumber), 
            static_cast<LPCTSTR>(m_ftpSettingDlg.m_userName), 
            static_cast<LPCTSTR>(m_ftpSettingDlg.m_passwd));
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

    CString strText;
    strText.Format(_T("Downlaoding file %s ..."), remoteFilename);
    SendOutputMessage(strText);

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
        fileView->SendMessage(WM_DOUBLE_CLICK_FTP_FILE, 0, 0);
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
                            if (!m_dataParser.GetSQL_vehicle(strSql))
                            {
                                if (!ExecuteSQL(strSql))
                                {
                                    strSql.Empty();
                                    if (!m_dataParser.GetSQL_occupant(strSql))
                                    {
                                        ExecuteSQL(strSql);
                                    }
                                    else
                                    {
                                        // sometimes, we don't have occupant in vehicle
                                    }

                                    // success
                                    CString strText;
                                    strText.Format(_T("SUCCESS: file %s imported"), strLocalFileName);
                                    SendOutputMessage(strText);
                                }
                                else
                                {
                                    Rollback(urcNumber);
                                }
                            }
                            else
                            {
                                Rollback(urcNumber);
                            }
                        }
                        else
                        {
                            CString strText;
                            strText.Format(_T("ERROR: fail to import data into database from file %s"), strLocalFileName);
                            SendOutputMessage(strText);
                        }
                    }
                }
                else
                {
                    // TODO download file failed
                    CString strText;
                    strText.Format(_T("FAILURE: download file %s from FTP failed"), strRemoteFullPath);
                    SendOutputMessage(strText);
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


void CMainFormView::OnBnClickedManualMode()
{
    StoptSchedule(0);
    UpdateModeUI();

    m_strHintText = _T("Under Manual Mode");
    UpdateData(FALSE);
}


void CMainFormView::OnBnClickedAutoMode()
{
    UpdateModeUI();

    m_strHintText = _T("Under Auto Mode");
    UpdateData(FALSE);
}

void CMainFormView::UpdateModeUI()
{
    UpdateData(TRUE);
    if (m_iManualMode)
    {
        m_btnDispContent.EnableWindow(TRUE);
        m_btnCheckContent.EnableWindow(TRUE);

        GetDlgItem(IDC_EXECUTE_TIME)->EnableWindow(FALSE);
        m_btnRepeat.EnableWindow(FALSE);
    }
    else
    {
        m_btnDispContent.EnableWindow(FALSE);
        m_btnCheckContent.EnableWindow(FALSE);

        GetDlgItem(IDC_EXECUTE_TIME)->EnableWindow(TRUE);
        m_btnRepeat.EnableWindow(TRUE);
    }
}

void CMainFormView::OnBnClickedAutoPeriod()
{
    UpdateData(FALSE);
    if (m_btnRepeat.GetCheck())
    {
        GetDlgItem(IDC_PERIOD_NUM)->EnableWindow(TRUE);
    }
    else
    {
        GetDlgItem(IDC_PERIOD_NUM)->EnableWindow(FALSE);
    }
}

void CMainFormView::SendOutputMessage(CString& strText)
{
    m_strOutputMessage = strText;

    CMainFrame *pMainWnd = (CMainFrame *)AfxGetMainWnd();
    if (NULL != pMainWnd)
    {
        pMainWnd->SendMessage(WM_FILL_OUTPUT_WND, (WPARAM)&m_strOutputMessage);
    }

    // TODO store the result into log file
}


int CMainFormView::StartSchedule()
{
    StoptSchedule(0);
    
    SYSTEMTIME currentLocalTime;
    GetLocalTime(&currentLocalTime);

    UpdateData(TRUE);
    UINT nCurrent = currentLocalTime.wDayOfWeek * 24 * 3600 
        + currentLocalTime.wHour * 3600 
        + currentLocalTime.wMinute * 60 
        + currentLocalTime.wSecond;

    UINT nSchedule = m_executeTime.GetHour() * 3600 
        + m_executeTime.GetMinute() * 60 
        + m_executeTime.GetSecond();

    UINT nElapse;

    enum MyEnum
    {
        E_SUN = 0, 
        E_MON, 
        E_TUE, 
        E_WED, 
        E_THU, 
        E_FRI, 
        E_SAT
    };
    if (((CButton*)GetDlgItem(IDC_MON))->GetCheck())
    {
        nSchedule += E_MON * 24 * 3600;
        if (currentLocalTime.wDayOfWeek > E_MON || nCurrent > nSchedule)
        {
            nSchedule += 7 * 24 * 3600;
        }

        nElapse = nSchedule - nCurrent;

        SetTimer(IDT_TIMER_MON, nElapse, NULL);
    }

    if (((CButton*)GetDlgItem(IDC_TUE))->GetCheck())
    {
        nSchedule += E_TUE * 24 * 3600;
        if (currentLocalTime.wDayOfWeek > E_TUE || nCurrent > nSchedule)
        {
            nSchedule += 7 * 24 * 3600;
        }

        nElapse = nSchedule - nCurrent;

        SetTimer(IDT_TIMER_TUE, nElapse, NULL);
    }

    if (((CButton*)GetDlgItem(IDC_WED))->GetCheck())
    {
        nSchedule += E_WED * 24 * 3600;
        if (currentLocalTime.wDayOfWeek > E_WED || nCurrent > nSchedule)
        {
            nSchedule += 7 * 24 * 3600;
        }

        nElapse = nSchedule - nCurrent;

        SetTimer(IDT_TIMER_WED, nElapse, NULL);
    }

    if (((CButton*)GetDlgItem(IDC_THU))->GetCheck())
    {
        nSchedule += E_THU * 24 * 3600;
        if (currentLocalTime.wDayOfWeek > E_THU || nCurrent > nSchedule)
        {
            nSchedule += 7 * 24 * 3600;
        }

        nElapse = nSchedule - nCurrent;

        SetTimer(IDT_TIMER_THU, nElapse, NULL);
    }

    if (((CButton*)GetDlgItem(IDC_FRI))->GetCheck())
    {
        nSchedule += E_FRI * 24 * 3600;
        if (currentLocalTime.wDayOfWeek > E_FRI || nCurrent > nSchedule)
        {
            nSchedule += 7 * 24 * 3600;
        }

        nElapse = nSchedule - nCurrent;

        SetTimer(IDT_TIMER_FRI, nElapse, NULL);
    }

    if (((CButton*)GetDlgItem(IDC_SAT))->GetCheck())
    {
        nSchedule += E_SAT * 24 * 3600;
        if (currentLocalTime.wDayOfWeek > E_SAT || nCurrent > nSchedule)
        {
            nSchedule += 7 * 24 * 3600;
        }

        nElapse = nSchedule - nCurrent;

        SetTimer(IDT_TIMER_SAT, nElapse, NULL);
    }

    if (((CButton*)GetDlgItem(IDC_SUN))->GetCheck())
    {
        nSchedule += E_SUN * 24 * 3600;
        if (currentLocalTime.wDayOfWeek > E_SUN || nCurrent > nSchedule)
        {
            nSchedule += 7 * 24 * 3600;
        }

        nElapse = nSchedule - nCurrent;

        SetTimer(IDT_TIMER_SUN, nElapse, NULL);
    }

    return 0;
}


int CMainFormView::StoptSchedule(UINT nIDEvent)
{
    switch (nIDEvent)
    {
    case IDT_TIMER_MON:
        KillTimer(IDT_TIMER_MON);
        break;

    case IDT_TIMER_TUE:
        KillTimer(IDT_TIMER_TUE);
        break;

    case IDT_TIMER_WED:
        KillTimer(IDT_TIMER_WED);
        break;

    case IDT_TIMER_THU:
        KillTimer(IDT_TIMER_THU);
        break;

    case IDT_TIMER_FRI:
        KillTimer(IDT_TIMER_FRI);
        break;

    case IDT_TIMER_SAT:
        KillTimer(IDT_TIMER_SAT);
        break;

    case IDT_TIMER_SUN:
        KillTimer(IDT_TIMER_SUN);
        break;

    default:
        KillTimer(IDT_TIMER_MON);
        KillTimer(IDT_TIMER_TUE);
        KillTimer(IDT_TIMER_WED);
        KillTimer(IDT_TIMER_THU);
        KillTimer(IDT_TIMER_FRI);
        KillTimer(IDT_TIMER_SAT);
        KillTimer(IDT_TIMER_SUN);
        break;
    }

    return 0;
}


int CMainFormView::ScheduleProc()
{
    TRACE(_T("Schedule Proc Fired\n"));

    return 0;
}


void CMainFormView::OnBnClickedBtnConfirmSchedule()
{
    MessageBox(_T("Schedule Confirmed"), _T("Notice"), MB_OK | MB_ICONINFORMATION);
    StartSchedule();
}


void CMainFormView::OnTimer(UINT_PTR nIDEvent)
{
    switch (nIDEvent)
    {
    case IDT_TIMER_MON:
    case IDT_TIMER_TUE:
    case IDT_TIMER_WED:
    case IDT_TIMER_THU:
    case IDT_TIMER_FRI:
    case IDT_TIMER_SAT:
    case IDT_TIMER_SUN:
        ScheduleProc();

        StoptSchedule(nIDEvent);
        if (m_btnRepeat.GetCheck())
        {
            TRACE(_T("Re-Schedule Proc %d\n"), nIDEvent);
            SetTimer(nIDEvent, 7 * 24 * 3600, NULL);
        }
        break;

    default:
        break;
    }

    CFormView::OnTimer(nIDEvent);
}
