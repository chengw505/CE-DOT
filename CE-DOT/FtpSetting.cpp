// FtpSetting.cpp : implementation file
//

#include "stdafx.h"
#include "CE-DOT.h"
#include "FtpSetting.h"
#include "afxdialogex.h"


// CFtpSetting dialog

IMPLEMENT_DYNAMIC(CFtpSetting, CDialogEx)

CFtpSetting::CFtpSetting(CWnd* pParent /*=NULL*/)
	: CDialogEx(CFtpSetting::IDD, pParent)
    , m_bAnonymous(TRUE)
    , m_hostName(_T("localhost"))
    , m_portNumber(21)
    , m_userName(_T("anonymous"))
    , m_passwd(_T(""))
{

}

CFtpSetting::~CFtpSetting()
{
}

void CFtpSetting::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
    DDX_Check(pDX, IDC_CK_ANONYMOUS, m_bAnonymous);
    DDX_Text(pDX, IDC_HOST_NAME, m_hostName);
    DDX_Text(pDX, IDC_PORT_NUMBER, m_portNumber);
    DDX_Text(pDX, IDC_USER_NAME, m_userName);
    DDX_Text(pDX, IDC_USER_PASSWD, m_passwd);
}


BEGIN_MESSAGE_MAP(CFtpSetting, CDialogEx)
    ON_BN_CLICKED(IDC_CK_ANONYMOUS, &CFtpSetting::OnClickedCkAnonymous)
    ON_BN_CLICKED(IDOK, &CFtpSetting::OnBnClickedOk)
END_MESSAGE_MAP()


// CFtpSetting message handlers
void CFtpSetting::OnClickedCkAnonymous()
{
    UpdateData();

    CWnd* pWnd = DYNAMIC_DOWNCAST(CWnd, GetDlgItem(IDC_USER_NAME));
    if (pWnd) {
        pWnd->EnableWindow(!m_bAnonymous);
        static_cast<CEdit*>(pWnd)->SetWindowText(nsFTP::ANONYMOUS_USER);
    }
    pWnd = DYNAMIC_DOWNCAST(CWnd, GetDlgItem(IDC_USER_PASSWD));
    if (pWnd) {
        pWnd->EnableWindow(!m_bAnonymous);
    }
}


void CFtpSetting::OnBnClickedOk()
{
    CDialogEx::OnOK();
}


BOOL CFtpSetting::OnInitDialog()
{
    CDialogEx::OnInitDialog();

    OnClickedCkAnonymous();

    return TRUE;
}
