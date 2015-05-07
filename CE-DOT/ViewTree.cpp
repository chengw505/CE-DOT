
#include "stdafx.h"
#include "MainFrm.h"
#include "ViewTree.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CViewTree

CViewTree::CViewTree()
{
}

CViewTree::~CViewTree()
{
}

BEGIN_MESSAGE_MAP(CViewTree, CTreeCtrl)
    ON_NOTIFY_REFLECT(NM_DBLCLK, &CViewTree::OnNMDblclk)
    ON_NOTIFY_REFLECT(TVN_ITEMEXPANDING, &CViewTree::OnTvnItemexpanding)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CViewTree message handlers

BOOL CViewTree::OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult)
{
	BOOL bRes = CTreeCtrl::OnNotify(wParam, lParam, pResult);

	NMHDR* pNMHDR = (NMHDR*)lParam;
	ASSERT(pNMHDR != NULL);

	if (pNMHDR && pNMHDR->code == TTN_SHOW && GetToolTips() != NULL)
	{
		GetToolTips()->SetWindowPos(&wndTop, -1, -1, -1, -1, SWP_NOMOVE | SWP_NOACTIVATE | SWP_NOSIZE);
	}

	return bRes;
}

void CViewTree::OnNMDblclk(NMHDR *pNMHDR, LRESULT *pResult)
{
    TRACE(_T("double click... %s\n"), GetItemText((GetSelectedItem())));
    (((CMainFrame*)AfxGetMainWnd())->GetFileView())->SendMessage(CUSTOM_WM_MESSAGE, 0, 0);

    *pResult = 0;
}

void CViewTree::OnTvnItemexpanding(NMHDR *pNMHDR, LRESULT *pResult)
{
    LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);

    TRACE(_T("expanding... %s\n"), GetItemText(pNMTreeView->itemNew.hItem));

    *pResult = 0;
}

