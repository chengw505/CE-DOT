// SqlSetting.cpp : implementation file
//

#include "stdafx.h"
#include "CE-DOT.h"
#include "SqlSetting.h"
#include "afxdialogex.h"


// CSqlSetting dialog

IMPLEMENT_DYNAMIC(CSqlSetting, CDialogEx)

CSqlSetting::CSqlSetting(CWnd* pParent /*=NULL*/)
	: CDialogEx(CSqlSetting::IDD, pParent)
    , m_strDbServerName(_T("LOCALHOST\\SQLEXPRESS"))
    , m_strDbUserName(_T(""))
    , m_strDbUserPasswd(_T(""))
    , m_iCurSel(0)
{

}

CSqlSetting::~CSqlSetting()
{
}

void CSqlSetting::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
    DDX_Text(pDX, IDC_DB_SERVER_NAME, m_strDbServerName);
    DDX_Control(pDX, IDC_DB_AUTH, m_cbAuthentication);
    DDX_Text(pDX, IDC_DB_USER_NAME, m_strDbUserName);
    DDV_MaxChars(pDX, m_strDbUserName, 128);
    DDX_Text(pDX, IDC_DB_USER_PASSWD, m_strDbUserPasswd);
    DDV_MaxChars(pDX, m_strDbUserPasswd, 128);
    DDX_CBIndex(pDX, IDC_DB_AUTH, m_iCurSel);
}


BEGIN_MESSAGE_MAP(CSqlSetting, CDialogEx)
    ON_CBN_SELCHANGE(IDC_DB_AUTH, &CSqlSetting::OnSelchangeDbAuth)
END_MESSAGE_MAP()


// CSqlSetting message handlers


BOOL CSqlSetting::OnInitDialog()
{
    CDialogEx::OnInitDialog();

    m_cbAuthentication.SetCurSel(0);
    GetDlgItem(IDC_DB_USER_NAME)->EnableWindow(FALSE);
    GetDlgItem(IDC_DB_USER_PASSWD)->EnableWindow(FALSE);

    return TRUE;  // return TRUE unless you set the focus to a control
    // EXCEPTION: OCX Property Pages should return FALSE
}


void CSqlSetting::OnSelchangeDbAuth()
{
    int iCurSel = m_cbAuthentication.GetCurSel();
    switch (iCurSel)
    {
    case 0:
        GetDlgItem(IDC_DB_USER_NAME)->EnableWindow(FALSE);
        GetDlgItem(IDC_DB_USER_PASSWD)->EnableWindow(FALSE);

        break;

    default:
        GetDlgItem(IDC_DB_USER_NAME)->EnableWindow(TRUE);
        GetDlgItem(IDC_DB_USER_PASSWD)->EnableWindow(TRUE);
        break;
    }
}
