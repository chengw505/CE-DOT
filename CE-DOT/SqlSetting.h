#pragma once


// CSqlSetting dialog

class CSqlSetting : public CDialogEx
{
	DECLARE_DYNAMIC(CSqlSetting)

public:
	CSqlSetting(CWnd* pParent = NULL);   // standard constructor
	virtual ~CSqlSetting();

// Dialog Data
	enum { IDD = IDD_DLG_SQL_LOGON };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
    CString m_strDbServerName;
    CComboBox m_cbAuthentication;
    CString m_strDbUserName;
    CString m_strDbUserPasswd;
    virtual BOOL OnInitDialog();
    afx_msg void OnSelchangeDbAuth();
    int m_iCurSel;
};
