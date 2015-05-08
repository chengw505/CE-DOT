
#include "stdafx.h"
#include "mainfrm.h"
#include "FileView.h"
#include "Resource.h"
#include "CE-DOT.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

/////////////////////////////////////////////////////////////////////////////
// CFileView

CFileView::CFileView()
{
}

CFileView::~CFileView()
{
}

BEGIN_MESSAGE_MAP(CFileView, CDockablePane)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_CONTEXTMENU()
	ON_COMMAND(ID_PROPERTIES, OnProperties)
	ON_COMMAND(ID_OPEN, OnFileOpen)
	ON_COMMAND(ID_OPEN_WITH, OnFileOpenWith)
	ON_COMMAND(ID_DUMMY_COMPILE, OnDummyCompile)
	ON_COMMAND(ID_EDIT_CUT, OnEditCut)
	ON_COMMAND(ID_EDIT_COPY, OnEditCopy)
	ON_COMMAND(ID_EDIT_CLEAR, OnEditClear)
	ON_WM_PAINT()
	ON_WM_SETFOCUS()
    ON_MESSAGE(CUSTOM_WM_MESSAGE, OnFtpFileDoubleClick)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CWorkspaceBar message handlers

int CFileView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDockablePane::OnCreate(lpCreateStruct) == -1)
		return -1;

	CRect rectDummy;
	rectDummy.SetRectEmpty();

	// Create view:
	const DWORD dwViewStyle = WS_CHILD | WS_VISIBLE | TVS_HASLINES | TVS_LINESATROOT | TVS_HASBUTTONS;

	if (!m_wndFileView.Create(dwViewStyle, rectDummy, this, 4))
	{
		TRACE0("Failed to create file view\n");
		return -1;      // fail to create
	}

	// Load view images:
	m_FileViewImages.Create(IDB_FILE_VIEW, 16, 0, RGB(255, 0, 255));
	m_wndFileView.SetImageList(&m_FileViewImages, TVSIL_NORMAL);

	m_wndToolBar.Create(this, AFX_DEFAULT_TOOLBAR_STYLE, IDR_EXPLORER);
	m_wndToolBar.LoadToolBar(IDR_EXPLORER, 0, 0, TRUE /* Is locked */);

	OnChangeVisualStyle();

	m_wndToolBar.SetPaneStyle(m_wndToolBar.GetPaneStyle() | CBRS_TOOLTIPS | CBRS_FLYBY);

	m_wndToolBar.SetPaneStyle(m_wndToolBar.GetPaneStyle() & ~(CBRS_GRIPPER | CBRS_SIZE_DYNAMIC | CBRS_BORDER_TOP | CBRS_BORDER_BOTTOM | CBRS_BORDER_LEFT | CBRS_BORDER_RIGHT));

	m_wndToolBar.SetOwner(this);

	// All commands will be routed via this control , not via the parent frame:
	m_wndToolBar.SetRouteCommandsViaFrame(FALSE);

	AdjustLayout();

	return 0;
}

void CFileView::OnSize(UINT nType, int cx, int cy)
{
	CDockablePane::OnSize(nType, cx, cy);
	AdjustLayout();
}

void CFileView::OnContextMenu(CWnd* pWnd, CPoint point)
{
	CTreeCtrl* pWndTree = (CTreeCtrl*) &m_wndFileView;
	ASSERT_VALID(pWndTree);

	if (pWnd != pWndTree)
	{
		CDockablePane::OnContextMenu(pWnd, point);
		return;
	}

	if (point != CPoint(-1, -1))
	{
		// Select clicked item:
		CPoint ptTree = point;
		pWndTree->ScreenToClient(&ptTree);

		UINT flags = 0;
		HTREEITEM hTreeItem = pWndTree->HitTest(ptTree, &flags);
		if (hTreeItem != NULL)
		{
			pWndTree->SelectItem(hTreeItem);
		}
	}

	pWndTree->SetFocus();
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EXPLORER, point.x, point.y, this, TRUE);
}

void CFileView::AdjustLayout()
{
	if (GetSafeHwnd() == NULL)
	{
		return;
	}

	CRect rectClient;
	GetClientRect(rectClient);

	int cyTlb = m_wndToolBar.CalcFixedLayout(FALSE, TRUE).cy;

	m_wndToolBar.SetWindowPos(NULL, rectClient.left, rectClient.top, rectClient.Width(), cyTlb, SWP_NOACTIVATE | SWP_NOZORDER);
	m_wndFileView.SetWindowPos(NULL, rectClient.left + 1, rectClient.top + cyTlb + 1, rectClient.Width() - 2, rectClient.Height() - cyTlb - 2, SWP_NOACTIVATE | SWP_NOZORDER);
}

void CFileView::OnProperties()
{
	AfxMessageBox(_T("Properties...."));

}

void CFileView::OnFileOpen()
{
	// TODO: Add your command handler code here
}

void CFileView::OnFileOpenWith()
{
	// TODO: Add your command handler code here
}

void CFileView::OnDummyCompile()
{
	// TODO: Add your command handler code here
}

void CFileView::OnEditCut()
{
	// TODO: Add your command handler code here
}

void CFileView::OnEditCopy()
{
	// TODO: Add your command handler code here
}

void CFileView::OnEditClear()
{
	// TODO: Add your command handler code here
}

void CFileView::OnPaint()
{
	CPaintDC dc(this); // device context for painting

	CRect rectTree;
	m_wndFileView.GetWindowRect(rectTree);
	ScreenToClient(rectTree);

	rectTree.InflateRect(1, 1);
	dc.Draw3dRect(rectTree, ::GetSysColor(COLOR_3DSHADOW), ::GetSysColor(COLOR_3DSHADOW));
}

void CFileView::OnSetFocus(CWnd* pOldWnd)
{
	CDockablePane::OnSetFocus(pOldWnd);

	m_wndFileView.SetFocus();
}

void CFileView::OnChangeVisualStyle()
{
	m_wndToolBar.CleanUpLockedImages();
	m_wndToolBar.LoadBitmap(theApp.m_bHiColorIcons ? IDB_EXPLORER_24 : IDR_EXPLORER, 0, 0, TRUE /* Locked */);

	m_FileViewImages.DeleteImageList();

	UINT uiBmpId = theApp.m_bHiColorIcons ? IDB_FILE_VIEW_24 : IDB_FILE_VIEW;

	CBitmap bmp;
	if (!bmp.LoadBitmap(uiBmpId))
	{
		TRACE(_T("Can't load bitmap: %x\n"), uiBmpId);
		ASSERT(FALSE);
		return;
	}

	BITMAP bmpObj;
	bmp.GetBitmap(&bmpObj);

	UINT nFlags = ILC_MASK;

	nFlags |= (theApp.m_bHiColorIcons) ? ILC_COLOR24 : ILC_COLOR4;

	m_FileViewImages.Create(16, bmpObj.bmHeight, nFlags, 0, 0);
	m_FileViewImages.Add(&bmp, RGB(255, 0, 255));

	m_wndFileView.SetImageList(&m_FileViewImages, TVSIL_NORMAL);
}


void CFileView::ResetFileList(CFTPClient* ftpClient, CLogonInfo* ftpLogonInfo)
{
    ASSERT(ftpClient);
    ASSERT(ftpLogonInfo);

    if (ftpClient->Login(*ftpLogonInfo))
    {
        m_wndFileView.DeleteAllItems();

        HTREEITEM hRoot = m_wndFileView.InsertItem(_T("/"), 0, 0);
        m_RootInfo.m_cszDisplayName = ftpClient->LastLogonInfo().Hostname().c_str();
        m_RootInfo.m_cszRoot = _T("/");
        m_RootInfo.m_htiRoot = hRoot;

        TFTPFileStatusShPtrVec vFileList;
        GetDirectoryListing(ftpClient, hRoot, vFileList);
        std::sort(vFileList.begin(), vFileList.end(), CFTPFileStatusContainerSort(CFTPFileStatusContainerSort::CName(), true, true));

        for (TFTPFileStatusShPtrVec::iterator it = vFileList.begin(); it != vFileList.end(); it++)
        {
            TFTPFileStatusShPtr ftpFile = *it;
            if (ftpFile->IsDot())   continue;

            CString strFileName = ftpFile->Name().c_str();
            TRACE(_T("%s\t"), strFileName);

            CString strAttr = ftpFile->Attributes().c_str();
            BOOL isDir = strAttr[0] == 'd';
            int nImage = isDir ? 0 : 2;

            m_wndFileView.InsertItem(strFileName, nImage, nImage, hRoot);
        }
        m_wndFileView.Expand(hRoot, TVE_EXPAND);

        ftpClient->Logout();
    }
}

void CFileView::GetDirectoryListing(CFTPClient* ftpClient, HTREEITEM hItem, TFTPFileStatusShPtrVec& vFileList) const
{
    ASSERT(ftpClient);
    if (m_RootInfo.m_htiRoot == hItem) {
        ftpClient->List(static_cast<LPCTSTR>(m_RootInfo.m_cszRoot), vFileList);
        return;
    }

    ftpClient->List(static_cast<LPCTSTR>(GetFullPath(hItem)), vFileList);
}

CString CFileView::GetFullPath(HTREEITEM hItem) const
{
    CString cszFullPath;

    while (hItem)
    {
        if (hItem == m_RootInfo.m_htiRoot)
        {
            if (m_RootInfo.m_cszRoot.GetLength() > 0 && m_RootInfo.m_cszRoot.Right(1) == _T("/"))
                cszFullPath = m_RootInfo.m_cszRoot + cszFullPath;
            else
                cszFullPath = m_RootInfo.m_cszRoot + _T("/") + cszFullPath;
        }
        else
        {
            cszFullPath = m_wndFileView.GetItemText(hItem) + _T("/") + cszFullPath;
        }
        hItem = m_wndFileView.GetParentItem(hItem);
    }

    cszFullPath.TrimRight(_T("/"));

    return cszFullPath;
}


LRESULT CFileView::OnFtpFileDoubleClick(WPARAM /*w*/, LPARAM /*l*/)
{
    CString strFullPath = GetFullPath(m_wndFileView.GetSelectedItem());
    CString strFileName = m_wndFileView.GetItemText(m_wndFileView.GetSelectedItem());
    (((CMainFrame*)AfxGetMainWnd())->GetActiveView())->SendMessage(CUSTOM_WM_MESSAGE, (WPARAM)&strFullPath, (LPARAM)&strFileName);

    return (LRESULT)0;
}

HTREEITEM CFileView::GetSelectedItem()
{
    return m_wndFileView.GetSelectedItem();
}

CString CFileView::GetFileName(HTREEITEM hSelected)
{
    return m_wndFileView.GetItemText(m_wndFileView.GetSelectedItem());
}