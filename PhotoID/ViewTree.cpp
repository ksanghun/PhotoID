
#include "stdafx.h"
#include "ViewTree.h"
#include "MainFrm.h"

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
	ON_NOTIFY_REFLECT(TVN_SELCHANGED, &CViewTree::OnTvnSelchanged)
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


void CViewTree::OnTvnSelchanged(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);
	// TODO: Add your control notification handler code here

	HTREEITEM hSelected = pNMTreeView->itemNew.hItem;
	if (GetItemData(hSelected) == 0){
		CString pathSelected;
		CString pathFolder;

		HTREEITEM hParentsItem = hSelected;
		while (hParentsItem != NULL){
			pathSelected = L"\\" + pathSelected;
			pathSelected = GetItemText(hParentsItem) + pathSelected;
			hParentsItem = GetParentItem(hParentsItem);
		}
		pathFolder = pathSelected;
		pathSelected += L"*.*";

		CFileFind finder;
		BOOL bWorking = finder.FindFile(pathSelected);

		while (bWorking){
			bWorking = finder.FindNextFile();
			if (finder.IsDots()) continue;
			if (finder.IsDirectory()){
				InsertItem(finder.GetFileName(), hSelected);
			}
		}

		//SetItemData(hSelected, 1);
		EnsureVisible(hSelected);

	//	Expand(hSelected, TVE_EXPAND);

		CMainFrame* pM = (CMainFrame*)AfxGetMainWnd();
		pM->UpdateImgListCtrl(pathFolder);
	}


	


	// Update List Ctrl //
	


	//Invalidate(TRUE);

	*pResult = 0;
}
