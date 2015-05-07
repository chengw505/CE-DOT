#pragma once


// CFtpSetting dialog

class CFtpSetting : public CDialogEx
{
	DECLARE_DYNAMIC(CFtpSetting)

public:
	CFtpSetting(CWnd* pParent = NULL);   // standard constructor
	virtual ~CFtpSetting();

// Dialog Data
	enum { IDD = IDD_DLG_FTP_LOGON };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
    afx_msg void OnClickedCkAnonymous();
    afx_msg void OnBnClickedOk();
    virtual BOOL OnInitDialog();
    BOOL m_bAnonymous;
    CString m_hostName;
    int m_portNumber;
    CString m_userName;
    CString m_passwd;
};
