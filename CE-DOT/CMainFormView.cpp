
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
    ON_MESSAGE(WM_DOUBLE_CLICK_FTP_FILE, &CMainFormView::OnFtpFileDoubleClick)
    ON_BN_CLICKED(IDC_BTN_CONFIRM_SCHEDULE, &CMainFormView::OnBnClickedBtnConfirmSchedule)
    ON_WM_TIMER()
END_MESSAGE_MAP()

// CMainFormView construction/destruction

CMainFormView::CMainFormView()
                : CFormView(CMainFormView::IDD)
                , m_ftpClient(nsSocket::CreateDefaultBlockingSocketInstance(), 30)
                , m_strHintText(_T(""))
                , m_iManualMode(1)
                , m_bRepeat(TRUE)
                , m_bMonday(FALSE)
                , m_bTuesday(FALSE)
                , m_bWednesday(FALSE)
                , m_bThursday(FALSE)
                , m_bFriday(FALSE)
                , m_bSaturday(FALSE)
                , m_bSunday(FALSE)
{
    GetSetSettings();
}

CMainFormView::~CMainFormView()
{
    CloseDB();
    FinalizeAdoInstance();

    GetSetSettings(FALSE);
}

int CMainFormView::GetSetSettings(BOOL bLoad/* = TRUE*/)
{
    CPJRegistry reg((CWinApp*)AfxGetApp(), bLoad);
    reg.Section(REG_SECTION);

    reg.Profile(REG_MANUAL_MODE, m_iManualMode);
    reg.Profile(REG_AUTO_MON, m_bMonday);
    reg.Profile(REG_AUTO_TUE, m_bTuesday);
    reg.Profile(REG_AUTO_WED, m_bWednesday);
    reg.Profile(REG_AUTO_THU, m_bThursday);
    reg.Profile(REG_AUTO_FRI, m_bFriday);
    reg.Profile(REG_AUTO_SAT, m_bSaturday);
    reg.Profile(REG_AUTO_SUN, m_bSunday);
    reg.Profile(REG_AUTO_REPEAT, m_bRepeat);

    int hh = m_executeTime.GetHour();
    int mm = m_executeTime.GetMinute();
    int ss = m_executeTime.GetSecond();
    reg.Profile(REG_AUTO_TIME_HH, hh);
    reg.Profile(REG_AUTO_TIME_MM, mm);
    reg.Profile(REG_AUTO_TIME_SS, ss);

    CTime now = CTime::GetCurrentTime();
    m_executeTime = CTime(now.GetYear(), now.GetMonth(), now.GetDay(), hh, mm, ss);

    reg.Profile(REG_FTP_HOST, m_ftpSettingDlg.m_hostName);
    reg.Profile(REG_FTP_ANONY, m_ftpSettingDlg.m_bAnonymous);
    reg.Profile(REG_FTP_USER, m_ftpSettingDlg.m_userName);
    reg.Profile(REG_FTP_PASSWD, m_ftpSettingDlg.m_passwd);
    reg.Profile(REG_FTP_PORT, m_ftpSettingDlg.m_portNumber);

    // sql settings
    reg.Profile(REG_DB_HOST, m_sqlSettingDlg.m_strDbServerName);
    reg.Profile(REG_DB_USER, m_sqlSettingDlg.m_strDbUserName);
    reg.Profile(REG_DB_PASSWD, m_sqlSettingDlg.m_strDbUserPasswd);

    return 0;
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
    DDX_Check(pDX, IDC_MON, m_bMonday);
    DDX_Check(pDX, IDC_AUTO_PERIOD, m_bRepeat);
    DDX_Check(pDX, IDC_TUE, m_bTuesday);
    DDX_Check(pDX, IDC_WED, m_bWednesday);
    DDX_Check(pDX, IDC_THU, m_bThursday);
    DDX_Check(pDX, IDC_FRI, m_bFriday);
    DDX_Check(pDX, IDC_SAT, m_bSaturday);
    DDX_Check(pDX, IDC_SUN, m_bSunday);
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

    Initialize();
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
    LoadFtpSettings();

    InitialAdoInstance();
    LoadSqlSettings();

    if (!m_iManualMode)
    {
        StartSchedule();
    }

    FillFtpFileView();
    UpdateModeUI();
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

    try {
        m_pRecordset.CreateInstance(__uuidof(Recordset));
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
    CloseDB();

    CString strServerName;
    strServerName = m_sqlSettingDlg.m_strDbServerName;
    //strServerName.Replace(_T("\\"), _T("\\\\"));

    CString strConnect;
    strConnect .Format(_T("Provider=SQLOLEDB; \
                            Data Source=%s;\
                            Initial Catalog= DOT; \
                            integrated security=SSPI"), strServerName);
    try 
    {
        m_pConnection->Open((_bstr_t)strConnect, "", "", adModeUnknown);
    }
    catch (_com_error e) 
    {
        TRACE(_T("Fail to open database: %s\n"), CString((LPCTSTR)e.Description()));
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
        TRACE(_T("ExecuteSQL error: %s\n"), CString((LPCTSTR)e.Description()));
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
        TRACE(_T("error: %s\n"), CString((LPCTSTR)e.Description()));
        return 1;
    }

    return 0;
}

void CMainFormView::OnBnClickedBtnSetupFtpAccount()
{
    if (IDOK == m_ftpSettingDlg.DoModal()) 
    {
        if (!m_ftpClient.Login(m_ftpLogonInfo))
        {
            CString strText;
            strText.Format(_T("Fail to connect FTP server: %s"), m_ftpSettingDlg.m_hostName);
            MessageBox(strText, _T("Error"), MB_OK | MB_ICONINFORMATION);
            return;
        }

        m_ftpClient.Logout();
        m_ftpLogonInfo.SetHost(static_cast<LPCTSTR>(m_ftpSettingDlg.m_hostName),
            static_cast<USHORT>(m_ftpSettingDlg.m_portNumber), 
            static_cast<LPCTSTR>(m_ftpSettingDlg.m_userName), 
            static_cast<LPCTSTR>(m_ftpSettingDlg.m_passwd));

        FillFtpFileView();
    }
}

void CMainFormView::OnBnClickedBtnSetupDbAccount()
{
    if (IDOK == m_sqlSettingDlg.DoModal())
    {
        if (!ConnectDB())
        {
            GetSetSettings(FALSE);
            MessageBox(_T("Setting updated"), _T("Info"), MB_OK | MB_ICONINFORMATION);
        }
        else
        {
            MessageBox(_T("Setting update failed"), _T("Error"), MB_OK | MB_ICONWARNING);
        }
    }
}

void CMainFormView::LoadFtpSettings()
{
    m_ftpLogonInfo.SetHost(static_cast<LPCTSTR>(m_ftpSettingDlg.m_hostName), 
        static_cast<USHORT>(m_ftpSettingDlg.m_portNumber), 
        static_cast<LPCTSTR>(m_ftpSettingDlg.m_userName), 
        static_cast<LPCTSTR>(m_ftpSettingDlg.m_passwd));

    if (!m_ftpClient.Login(m_ftpLogonInfo))
    {
        CString strText;
        strText.Format(_T("Fail to connect FTP server: %s"), m_ftpSettingDlg.m_hostName);
        MessageBox(strText, _T("Error"), MB_OK | MB_ICONINFORMATION);
        return;
    }
    m_ftpClient.Logout();
}

void CMainFormView::LoadSqlSettings()
{
    ConnectDB();
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

int CMainFormView::CheckContent(CString& strRemoteFullPath, CString& strLocalFileName)
{
    int err = 1;

    if (DownloadFile(strRemoteFullPath, strLocalFileName))
    {
        // download file failed
        CString strText;
        strText.Format(_T("FAILURE: download file %s from FTP failed"), strRemoteFullPath);
        SendOutputMessage(strText);

        return err;
    }

    if (m_dataParser.Parse(strLocalFileName))
    {
        // parse file failed
        CString strText;
        strText.Format(_T("FAILURE: fail to parse file %s"), strLocalFileName);
        SendOutputMessage(strText);

        return err;
    }
     
    UINT urcNumber;
    m_dataParser.GetUCRNumber(urcNumber);
    if (RecordExisted(urcNumber))
    {
        // case already exists
        CString strText;
        strText.Format(_T("WARNING: case %d already exists"), urcNumber);
        SendOutputMessage(strText);
        err = 0;

        return err;
    }

    // get crash data and import into database
    CString strSql;
    if (m_dataParser.GetSQL_crash(strSql))
    {
        CString strText;
        strText.Format(_T("ERROR: fail to import data into database from file %s"), strLocalFileName);
        SendOutputMessage(strText);

        return err;
    }
     
    if (ExecuteSQL(strSql))
    {
        CString strText;
        strText.Format(_T("ERROR: fail to import data into database from file %s"), strLocalFileName);
        SendOutputMessage(strText);

        return err;
    }

    // get vehicle data and import into database
    strSql.Empty();
    if (m_dataParser.GetSQL_vehicle(strSql))
    {
        Rollback(urcNumber);

        CString strText;
        strText.Format(_T("ERROR: fail to import data into database from file %s"), strLocalFileName);
        SendOutputMessage(strText);

        return err;
    }
     
    if (ExecuteSQL(strSql))
    {
        Rollback(urcNumber);

        CString strText;
        strText.Format(_T("ERROR: fail to import data into database from file %s"), strLocalFileName);
        SendOutputMessage(strText);

        return err;
    }

    // get occupant data and import into database
    strSql.Empty();
    if (!m_dataParser.GetSQL_occupant(strSql))
    {
        ExecuteSQL(strSql);
    }
    else
    {
        // sometimes, we don't have occupant in vehicle
    }

    err = 0;

    // success
    CString strText;
    strText.Format(_T("SUCCESS: file %s imported"), strLocalFileName);
    SendOutputMessage(strText);

    return err;
}

int CMainFormView::RecordExisted(UINT urcNumber)
{
    int exist = 0;
    CString strSql;
    strSql.Format(_T("SELECT * FROM [DOT].[dbo].[Acrash2012] WHERE ucrnumber=%d"), urcNumber);

    try
    {
        m_pConnection->CursorLocation = adUseClient;
        m_pRecordset->Open(strSql.GetBuffer(0), m_pConnection.GetInterfacePtr(), adOpenDynamic, adLockOptimistic, adCmdText);
        if (m_pRecordset->GetRecordCount() > 0)
        {
            exist = 1;
        }
        m_pRecordset->Close();
    }
    catch (_com_error e)
    {
        TRACE(_T("%s\n"), CString((LPCTSTR)e.Description()));
    }

    return exist;
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

            CheckContent(strRemoteFullPath, strLocalFileName);
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

    CMainFrame *pMainWnd = (CMainFrame *)AfxGetMainWnd();
    if (NULL != pMainWnd)
    {
        CFileView* fileView = (CFileView*)pMainWnd->GetFileView();
        if (fileView->IsAutoHideMode())
        {
            fileView->ToggleAutoHide();
        }
    }

    m_strHintText = _T("Under Manual Mode");
    UpdateData(FALSE);
}


void CMainFormView::OnBnClickedAutoMode()
{
    UpdateModeUI();
    CMainFrame *pMainWnd = (CMainFrame *)AfxGetMainWnd();
    if (NULL != pMainWnd)
    {
        CFileView* fileView = (CFileView*)pMainWnd->GetFileView();
        if (!fileView->IsAutoHideMode())
        {
            fileView->ToggleAutoHide();
        }
    }

    m_strHintText = _T("Under Auto Mode");
    UpdateData(FALSE);
}

void CMainFormView::UpdateModeUI()
{
    UpdateData(TRUE);
    if (m_iManualMode)
    {
        m_strHintText = _T("Under Manual Mode");
        UpdateData(FALSE);

        m_btnDispContent.EnableWindow(TRUE);
        m_btnCheckContent.EnableWindow(TRUE);

        GetDlgItem(IDC_EXECUTE_TIME)->EnableWindow(FALSE);
        GetDlgItem(IDC_MON)->EnableWindow(FALSE);
        GetDlgItem(IDC_TUE)->EnableWindow(FALSE);
        GetDlgItem(IDC_WED)->EnableWindow(FALSE);
        GetDlgItem(IDC_THU)->EnableWindow(FALSE);
        GetDlgItem(IDC_FRI)->EnableWindow(FALSE);
        GetDlgItem(IDC_SAT)->EnableWindow(FALSE);
        GetDlgItem(IDC_SUN)->EnableWindow(FALSE);
        m_btnRepeat.EnableWindow(FALSE);
        GetDlgItem(IDC_BTN_CONFIRM_SCHEDULE)->EnableWindow(FALSE);
        GetDlgItem(IDC_BTN_CANCEL_SCHEDULE)->EnableWindow(FALSE);
    }
    else
    {
        m_strHintText = _T("Under Auto Mode");
        UpdateData(FALSE);

        m_btnDispContent.EnableWindow(FALSE);
        m_btnCheckContent.EnableWindow(FALSE);

        GetDlgItem(IDC_EXECUTE_TIME)->EnableWindow(TRUE);
        GetDlgItem(IDC_MON)->EnableWindow(TRUE);
        GetDlgItem(IDC_TUE)->EnableWindow(TRUE);
        GetDlgItem(IDC_WED)->EnableWindow(TRUE);
        GetDlgItem(IDC_THU)->EnableWindow(TRUE);
        GetDlgItem(IDC_FRI)->EnableWindow(TRUE);
        GetDlgItem(IDC_SAT)->EnableWindow(TRUE);
        GetDlgItem(IDC_SUN)->EnableWindow(TRUE);
        m_btnRepeat.EnableWindow(TRUE);
        GetDlgItem(IDC_BTN_CONFIRM_SCHEDULE)->EnableWindow(TRUE);
        GetDlgItem(IDC_BTN_CANCEL_SCHEDULE)->EnableWindow(TRUE);
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
    // stop all previous timer
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

        SetTimer(IDT_TIMER_MON, nElapse * 1000, NULL);
    }

    if (((CButton*)GetDlgItem(IDC_TUE))->GetCheck())
    {
        nSchedule += E_TUE * 24 * 3600;
        if (currentLocalTime.wDayOfWeek > E_TUE || nCurrent > nSchedule)
        {
            nSchedule += 7 * 24 * 3600;
        }

        nElapse = nSchedule - nCurrent;

        SetTimer(IDT_TIMER_TUE, nElapse * 1000, NULL);
    }

    if (((CButton*)GetDlgItem(IDC_WED))->GetCheck())
    {
        nSchedule += E_WED * 24 * 3600;
        if (currentLocalTime.wDayOfWeek > E_WED || nCurrent > nSchedule)
        {
            nSchedule += 7 * 24 * 3600;
        }

        nElapse = nSchedule - nCurrent;

        SetTimer(IDT_TIMER_WED, nElapse * 1000, NULL);
    }

    if (((CButton*)GetDlgItem(IDC_THU))->GetCheck())
    {
        nSchedule += E_THU * 24 * 3600;
        if (currentLocalTime.wDayOfWeek > E_THU || nCurrent > nSchedule)
        {
            nSchedule += 7 * 24 * 3600;
        }

        nElapse = nSchedule - nCurrent;

        SetTimer(IDT_TIMER_THU, nElapse * 1000, NULL);
    }

    if (((CButton*)GetDlgItem(IDC_FRI))->GetCheck())
    {
        nSchedule += E_FRI * 24 * 3600;
        if (currentLocalTime.wDayOfWeek > E_FRI || nCurrent > nSchedule)
        {
            nSchedule += 7 * 24 * 3600;
        }

        nElapse = nSchedule - nCurrent;

        SetTimer(IDT_TIMER_FRI, nElapse * 1000, NULL);
    }

    if (((CButton*)GetDlgItem(IDC_SAT))->GetCheck())
    {
        nSchedule += E_SAT * 24 * 3600;
        if (currentLocalTime.wDayOfWeek > E_SAT || nCurrent > nSchedule)
        {
            nSchedule += 7 * 24 * 3600;
        }

        nElapse = nSchedule - nCurrent;

        SetTimer(IDT_TIMER_SAT, nElapse * 1000, NULL);
    }

    if (((CButton*)GetDlgItem(IDC_SUN))->GetCheck())
    {
        nSchedule += E_SUN * 24 * 3600;
        if (currentLocalTime.wDayOfWeek > E_SUN || nCurrent > nSchedule)
        {
            nSchedule += 7 * 24 * 3600;
        }

        nElapse = nSchedule - nCurrent;

        SetTimer(IDT_TIMER_SUN, nElapse * 1000, NULL);
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

    CString strRoot = _T("/");
    CString strRemoteFullPath;

    if (!m_ftpClient.Login(m_ftpLogonInfo))
    {
        CString strText;
        strText.Format(_T("FAILURE: fail to login ftp %s:%d"), m_ftpLogonInfo.Hostname().c_str(), m_ftpLogonInfo.Hostport());
        SendOutputMessage(strText);
        return 1;
    }

    TFTPFileStatusShPtrVec vFileList;
    m_ftpClient.List(static_cast<LPCTSTR>(strRoot), vFileList);
    std::sort(vFileList.begin(), vFileList.end(), CFTPFileStatusContainerSort(CFTPFileStatusContainerSort::CName(), true, true));

    for (TFTPFileStatusShPtrVec::iterator it = vFileList.begin(); it != vFileList.end(); it++)
    {
        TFTPFileStatusShPtr ftpFile = *it;
        if (ftpFile->IsDot())   continue;

        CString strFileName = ftpFile->Name().c_str();
        TRACE(_T("%s\t"), strFileName);

        CString strAttr = ftpFile->Attributes().c_str();
        BOOL isDir = strAttr[0] == 'd';

        if (isDir)
        {
            // TODO fix me in the future!
            continue;
        }

        strRemoteFullPath = strRoot + strFileName;
        if (!CheckContent(strRemoteFullPath, strFileName))
        {
            // TODO delete file from FTP server
        }
    }

    return 0;
}


void CMainFormView::OnBnClickedBtnConfirmSchedule()
{
    UpdateData(TRUE);
    GetSetSettings(FALSE);

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
        StoptSchedule(nIDEvent);
        ScheduleProc();

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
