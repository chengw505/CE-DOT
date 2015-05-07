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
{

}

CSqlSetting::~CSqlSetting()
{
}

void CSqlSetting::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CSqlSetting, CDialogEx)
END_MESSAGE_MAP()


// CSqlSetting message handlers
