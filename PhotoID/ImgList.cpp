// ImgList.cpp : implementation file
//

#include "stdafx.h"
#include "PhotoID.h"
#include "ImgList.h"
#include "PhotoIDView.h"

// CImgList

IMPLEMENT_DYNAMIC(CImgList, CListCtrl)

CImgList::CImgList()
{
	m_pDragImage = NULL;
}

CImgList::~CImgList()
{
	//if (m_pDragImage){
	//	delete m_pDragImage;
	//}
}


BEGIN_MESSAGE_MAP(CImgList, CListCtrl)
	ON_NOTIFY_REFLECT(LVN_BEGINDRAG, &CImgList::OnLvnBegindrag)
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONUP()
END_MESSAGE_MAP()



// CImgList message handlers

//void CImgList::UpdateImgListCtrl(CString strPath)
//{
//	DeleteAllItems();
//
//	CFileFind finder;
//	BOOL bWorking = finder.FindFile(strPath);
//	while (bWorking){
//		bWorking = finder.FindNextFile();
//		if (finder.IsDots()) continue;
//
//		InsertItem(1, finder.GetFileName());
//	}
//
//}




void CImgList::OnLvnBegindrag(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: Add your control notification handler code here
	m_nDragIndex = pNMLV->iItem;

	POINT pt;
	int nOffset = 50; //offset in pixels for drag image
	pt.x = nOffset;
	pt.y = nOffset;

	m_pDragImage = CreateDragImage(m_nDragIndex, &pt);
	ASSERT(m_pDragImage); //make sure it was created

	//CBitmap bitmap;
	//bitmap.LoadBitmap(IDB_FILE_VIEW);
	//m_pDragImage->Replace(0, &bitmap, &bitmap);


	m_pDragImage->BeginDrag(0, CPoint(nOffset, nOffset));
	m_pDragImage->DragEnter(GetDesktopWindow(), pNMLV->ptAction);

	//// Set dragging flag and others
	m_bDragging = TRUE;	//we are in a drag and drop operation
	m_nDropIndex = -1;	//we don't have a drop index yet
//	m_pDragList = &m_listR; //make note of which list we are dragging from
//	m_pDropWnd = pView;	//at present the drag list is the drop list

	//// Capture all mouse messages
	SetCapture();

	*pResult = 0;
}


void CImgList::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default

	if (m_bDragging)
	{
		//// Move the drag image
		CPoint pt(point);	//get our current mouse coordinates
		ClientToScreen(&pt); //convert to screen coordinates
		m_pDragImage->DragMove(pt); //move the drag image to those coordinates
		// Unlock window updates (this allows the dragging image to be shown smoothly)
		m_pDragImage->DragShowNolock(false);

		//// Get the CWnd pointer of the window that is under the mouse cursor
		//CWnd* pDropWnd = WindowFromPoint(pt);
		//ASSERT(pDropWnd); //make sure we have a window


		// Save current window pointer as the CListCtrl we are dropping onto
	//	m_pDropWnd = pDropWnd;

		// Convert from screen coordinates to drop target client coordinates
		//pDropWnd->ScreenToClient(&pt);

		m_pDragImage->DragShowNolock(true);
	}

	CListCtrl::OnMouseMove(nFlags, point);
}


void CImgList::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	if (m_bDragging)
	{
		// Release mouse capture, so that other controls can get control/messages
		ReleaseCapture();

		// Note that we are NOT in a drag operation
		m_bDragging = FALSE;

		// End dragging image
		m_pDragImage->DragLeave(GetDesktopWindow());
		m_pDragImage->EndDrag();
		delete m_pDragImage; //must delete it because it was created at the beginning of the drag

		CPoint pt(point); //Get current mouse coordinates
		ClientToScreen(&pt); //Convert to screen coordinates
		// Get the CWnd pointer of the window that is under the mouse cursor
		CWnd* pDropWnd = WindowFromPoint(pt);
		ASSERT(pDropWnd); //make sure we have a window pointer
		// If window is CListCtrl, we perform the drop
		if (pDropWnd->IsKindOf(RUNTIME_CLASS(CWnd)))
		{
			// do something //
			CString filename = GetItemText(m_nDragIndex,0);
			CString filePath = m_strCurrFoler + filename;

			pView->SetPhotoIDimg(filePath);
		}
	}

	CListCtrl::OnLButtonUp(nFlags, point);
}
