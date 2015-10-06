
#pragma once

#include "ViewTree.h"

class CFileViewToolBar : public CMFCToolBar
{
	virtual void OnUpdateCmdUI(CFrameWnd* /*pTarget*/, BOOL bDisableIfNoHndler)
	{
		CMFCToolBar::OnUpdateCmdUI((CFrameWnd*) GetOwner(), bDisableIfNoHndler);
	}

	virtual BOOL AllowShowOnList() const { return FALSE; }
};

class CFileView : public CDockablePane
{
// Construction
public:
	CFileView();

	void AdjustLayout();
	void OnChangeVisualStyle();

// Attributes
protected:
	CViewTree m_wndFileView;
	CImageList m_FileViewImages;
	CFileViewToolBar m_wndToolBar;

public:
    struct SRootInfo
    {
        SRootInfo() : m_htiRoot(NULL) {};
        CString                       m_cszRoot;
        CString                       m_cszDisplayName;
        HTREEITEM                     m_htiRoot;
    } m_RootInfo;

// Implementation
public:
	virtual ~CFileView();
    void ResetFileList();
    CString GetFullPath(HTREEITEM hItem) const;
    HTREEITEM GetSelectedItem();
    CString GetFileName(HTREEITEM hSelected);

protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	afx_msg void OnProperties();
	afx_msg void OnFileOpen();
	afx_msg void OnFileOpenWith();
	afx_msg void OnDummyCompile();
	afx_msg void OnPaint();
	afx_msg void OnSetFocus(CWnd* pOldWnd);
    afx_msg LRESULT OnFtpFileDoubleClick(WPARAM w, LPARAM l);

	DECLARE_MESSAGE_MAP()
};

