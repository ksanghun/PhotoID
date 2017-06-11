
#include "stdafx.h"
#include "mainfrm.h"
#include "FileView.h"
#include "Resource.h"
#include "PhotoID.h"

#include <gdiplus.h>
using namespace Gdiplus;

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

#define	THUMBNAIL_WIDTH		100
#define	THUMBNAIL_HEIGHT	100
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
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CWorkspaceBar message handlers

int CFileView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDockablePane::OnCreate(lpCreateStruct) == -1)
		return -1;

	// initialize GDI+
	GdiplusStartupInput gdiplusStartupInput;
	GdiplusStartup(&m_gdiplusToken, &gdiplusStartupInput, NULL);


	CRect rectDummy;
	rectDummy.SetRectEmpty();


	m_wndListCtrl.Create(WS_CHILD | WS_VISIBLE | WS_BORDER | LVS_ICON | LVS_EDITLABELS, rectDummy, this, NULL);
	m_wndListCtrl.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);


	HIMAGELIST hImageList = ImageList_Create(100, 100, ILC_COLOR32, 0, 10);
	m_FileViewImages.Attach(hImageList);

	CBitmap dummy;
	dummy.LoadBitmap(ILC_COLOR32);
	m_FileViewImages.Add(&dummy, RGB(0, 0, 0));

	m_wndListCtrl.SetImageList(&m_FileViewImages, LVSIL_NORMAL);
	m_wndListCtrl.SetImageList(&m_FileViewImages, LVSIL_SMALL);

	//// Create view:
	//const DWORD dwViewStyle = WS_CHILD | WS_VISIBLE | TVS_HASLINES | TVS_LINESATROOT | TVS_HASBUTTONS;

	//if (!m_wndListCtrl.Create(dwViewStyle, rectDummy, this, 4))
	//{
	//	TRACE0("Failed to create file view\n");
	//	return -1;      // fail to create
	//}

	// Load view images:
	//m_FileViewImages.Create(IDB_FILE_VIEW, 16, 0, RGB(255, 0, 255));
	//m_wndFileView.SetImageList(&m_FileViewImages, TVSIL_NORMAL);

	m_wndToolBar.Create(this, AFX_DEFAULT_TOOLBAR_STYLE, IDR_EXPLORER);
	m_wndToolBar.LoadToolBar(IDR_EXPLORER, 0, 0, TRUE /* Is locked */);

	OnChangeVisualStyle();

	m_wndToolBar.SetPaneStyle(m_wndToolBar.GetPaneStyle() | CBRS_TOOLTIPS | CBRS_FLYBY);

	m_wndToolBar.SetPaneStyle(m_wndToolBar.GetPaneStyle() & ~(CBRS_GRIPPER | CBRS_SIZE_DYNAMIC | CBRS_BORDER_TOP | CBRS_BORDER_BOTTOM | CBRS_BORDER_LEFT | CBRS_BORDER_RIGHT));

	m_wndToolBar.SetOwner(this);

	// All commands will be routed via this control , not via the parent frame:
	m_wndToolBar.SetRouteCommandsViaFrame(FALSE);

	// Fill in some static tree view data (dummy code, nothing magic here)
	FillFileView();
	AdjustLayout();

	return 0;
}

void CFileView::OnSize(UINT nType, int cx, int cy)
{
	CDockablePane::OnSize(nType, cx, cy);
	AdjustLayout();
}

void CFileView::FillFileView()
{
	return;

	//HTREEITEM hRoot = m_wndFileView.InsertItem(_T("FakeApp files"), 0, 0);
	//m_wndFileView.SetItemState(hRoot, TVIS_BOLD, TVIS_BOLD);

	//HTREEITEM hSrc = m_wndFileView.InsertItem(_T("FakeApp Source Files"), 0, 0, hRoot);

	//m_wndFileView.InsertItem(_T("FakeApp.cpp"), 1, 1, hSrc);
	//m_wndFileView.InsertItem(_T("FakeApp.rc"), 1, 1, hSrc);
	//m_wndFileView.InsertItem(_T("FakeAppDoc.cpp"), 1, 1, hSrc);
	//m_wndFileView.InsertItem(_T("FakeAppView.cpp"), 1, 1, hSrc);
	//m_wndFileView.InsertItem(_T("MainFrm.cpp"), 1, 1, hSrc);
	//m_wndFileView.InsertItem(_T("StdAfx.cpp"), 1, 1, hSrc);

	//HTREEITEM hInc = m_wndFileView.InsertItem(_T("FakeApp Header Files"), 0, 0, hRoot);

	//m_wndFileView.InsertItem(_T("FakeApp.h"), 2, 2, hInc);
	//m_wndFileView.InsertItem(_T("FakeAppDoc.h"), 2, 2, hInc);
	//m_wndFileView.InsertItem(_T("FakeAppView.h"), 2, 2, hInc);
	//m_wndFileView.InsertItem(_T("Resource.h"), 2, 2, hInc);
	//m_wndFileView.InsertItem(_T("MainFrm.h"), 2, 2, hInc);
	//m_wndFileView.InsertItem(_T("StdAfx.h"), 2, 2, hInc);

	//HTREEITEM hRes = m_wndFileView.InsertItem(_T("FakeApp Resource Files"), 0, 0, hRoot);

	//m_wndFileView.InsertItem(_T("FakeApp.ico"), 2, 2, hRes);
	//m_wndFileView.InsertItem(_T("FakeApp.rc2"), 2, 2, hRes);
	//m_wndFileView.InsertItem(_T("FakeAppDoc.ico"), 2, 2, hRes);
	//m_wndFileView.InsertItem(_T("FakeToolbar.bmp"), 2, 2, hRes);

	//m_wndFileView.Expand(hRoot, TVE_EXPAND);
	//m_wndFileView.Expand(hSrc, TVE_EXPAND);
	//m_wndFileView.Expand(hInc, TVE_EXPAND);
}

void CFileView::OnContextMenu(CWnd* pWnd, CPoint point)
{
	//CTreeCtrl* pWndTree = (CTreeCtrl*) &m_wndFileView;
	//ASSERT_VALID(pWndTree);

	//if (pWnd != pWndTree)
	//{
	//	CDockablePane::OnContextMenu(pWnd, point);
	//	return;
	//}

	//if (point != CPoint(-1, -1))
	//{
	//	// Select clicked item:
	//	CPoint ptTree = point;
	//	pWndTree->ScreenToClient(&ptTree);

	//	UINT flags = 0;
	//	HTREEITEM hTreeItem = pWndTree->HitTest(ptTree, &flags);
	//	if (hTreeItem != NULL)
	//	{
	//		pWndTree->SelectItem(hTreeItem);
	//	}
	//}

	//pWndTree->SetFocus();
	//theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EXPLORER, point.x, point.y, this, TRUE);
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
//	int cyTlb = 0;

	m_wndToolBar.SetWindowPos(NULL, rectClient.left, rectClient.top, rectClient.Width(), cyTlb, SWP_NOACTIVATE | SWP_NOZORDER);
	m_wndListCtrl.SetWindowPos(NULL, rectClient.left + 1, rectClient.top + cyTlb + 1, rectClient.Width() - 2, rectClient.Height() - cyTlb - 2, SWP_NOACTIVATE | SWP_NOZORDER);
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
	m_wndListCtrl.GetWindowRect(rectTree);
	ScreenToClient(rectTree);

	rectTree.InflateRect(1, 1);
	dc.Draw3dRect(rectTree, ::GetSysColor(COLOR_3DSHADOW), ::GetSysColor(COLOR_3DSHADOW));
}

void CFileView::OnSetFocus(CWnd* pOldWnd)
{
	CDockablePane::OnSetFocus(pOldWnd);

	//m_wndFileView.SetFocus();
}

void CFileView::OnChangeVisualStyle()
{
	m_wndToolBar.CleanUpLockedImages();
	m_wndToolBar.LoadBitmap(theApp.m_bHiColorIcons ? IDB_EXPLORER_24 : IDR_EXPLORER, 0, 0, TRUE /* Locked */);

	//m_FileViewImages.DeleteImageList();

	//UINT uiBmpId = theApp.m_bHiColorIcons ? IDB_FILE_VIEW_24 : IDB_FILE_VIEW;

	//CBitmap bmp;
	//if (!bmp.LoadBitmap(uiBmpId))
	//{
	//	TRACE(_T("Can't load bitmap: %x\n"), uiBmpId);
	//	ASSERT(FALSE);
	//	return;
	//}

	//BITMAP bmpObj;
	//bmp.GetBitmap(&bmpObj);

	//UINT nFlags = ILC_MASK;

	//nFlags |= (theApp.m_bHiColorIcons) ? ILC_COLOR24 : ILC_COLOR4;

	//m_FileViewImages.Create(16, bmpObj.bmHeight, nFlags, 0, 0);
	//m_FileViewImages.Add(&bmp, RGB(255, 0, 255));

	//m_wndFileView.SetImageList(&m_FileViewImages, TVSIL_NORMAL);
}


void CFileView::UpdateImgListCtrl(CString strPath)
{
	//if (m_wndListCtrl){
	//	m_wndListCtrl.UpdateImgListCtrl(strPath);
	//}

	GetImageFileNames(strPath);
	DrawThumbnails(strPath);
}


BOOL  CFileView::GetImageFileNames(CString strFolder)
{
	m_VectorImageNames.clear();

	CString	strExt;
	CString	strName;
	CString	strPattern;
	BOOL	bRC = TRUE;

	HANDLE					hFind = NULL;
	WIN32_FIND_DATA			FindFileData;
	std::vector<CString>	VectorImageNames;

	strPattern.Format(TEXT("%s\\*.*"), strFolder);

	hFind = ::FindFirstFile(strPattern, &FindFileData);	// strat search	
	if (hFind == INVALID_HANDLE_VALUE)
	{
		LPVOID  msg;
		::FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
			NULL,
			GetLastError(),
			MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
			(LPTSTR)&msg,
			0,
			NULL);
		//MessageBox((LPTSTR)msg, CString((LPCSTR)IDS_TITLE), MB_OK | MB_ICONSTOP);
		::LocalFree(msg);
		return FALSE;
	}

	// filter off the system files and directories
	if (!(FindFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) &&
		!(FindFileData.dwFileAttributes & FILE_ATTRIBUTE_SYSTEM) &&
		!(FindFileData.dwFileAttributes & FILE_ATTRIBUTE_HIDDEN) &&
		!(FindFileData.dwFileAttributes & FILE_ATTRIBUTE_TEMPORARY))
	{
		// test file extension
		strName = FindFileData.cFileName;
		strExt = strName.Right(3);

		if ((strExt.CompareNoCase(TEXT("bmp")) == 0) ||
			(strExt.CompareNoCase(TEXT("jpg")) == 0) ||
			(strExt.CompareNoCase(TEXT("gif")) == 0) ||
			(strExt.CompareNoCase(TEXT("tif")) == 0) ||
			(strExt.CompareNoCase(TEXT("png")) == 0))
		{
			// save the image file name
			VectorImageNames.push_back(strName);
		}
	}

	// loop through to add all of them to our vector	
	while (bRC)
	{
		bRC = ::FindNextFile(hFind, &FindFileData);
		if (bRC)
		{
			// filter off the system files and directories
			if (!(FindFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) &&
				!(FindFileData.dwFileAttributes & FILE_ATTRIBUTE_SYSTEM) &&
				!(FindFileData.dwFileAttributes & FILE_ATTRIBUTE_HIDDEN) &&
				!(FindFileData.dwFileAttributes & FILE_ATTRIBUTE_TEMPORARY))
			{
				// test file extension
				strName = FindFileData.cFileName;
				strExt = strName.Right(3);

				if ((strExt.CompareNoCase(TEXT("bmp")) == 0) ||
					(strExt.CompareNoCase(TEXT("jpg")) == 0) ||
					(strExt.CompareNoCase(TEXT("gif")) == 0) ||
					(strExt.CompareNoCase(TEXT("tif")) == 0) ||
					(strExt.CompareNoCase(TEXT("png")) == 0))
				{
					// save the image file name
					VectorImageNames.push_back(strName);
				}
			}
		}
		else
		{
			DWORD err = ::GetLastError();
			if (err != ERROR_NO_MORE_FILES)
			{
				LPVOID msg;
				::FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
					NULL, err,
					MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
					(LPTSTR)&msg, 0, NULL);
				//MessageBox((LPTSTR)msg, CString((LPCSTR)IDS_TITLE), MB_OK | MB_ICONSTOP);
				::LocalFree(msg);
				::FindClose(hFind);
				return FALSE;
			}
		}
	} // end of while loop

	// close the search handle
	::FindClose(hFind);

	// update the names, if any
	if (!VectorImageNames.empty())
	{
		// reset the image name vector		
		m_VectorImageNames = VectorImageNames;
		return TRUE;
	}

	return FALSE;
}

void  CFileView::DrawThumbnails(CString strFolder)
{
	CBitmap*    pImage = NULL;
	HBITMAP		hBmp = NULL;
	POINT		pt;
	CString		strPath;
	int			i;

	// no images
	if (m_VectorImageNames.empty())
		return;

	// set the length of the space between thumbnails
	// you can also calculate and set it based on the length of your list control
	int nGap = 6;

	// hold the window update to avoid flicking
	m_wndListCtrl.SetRedraw(FALSE);

	// reset our image list
	for (i = 0; i<m_FileViewImages.GetImageCount(); i++)
		m_FileViewImages.Remove(i);

	// remove all items from list view
	if (m_wndListCtrl.GetItemCount() != 0)
		m_wndListCtrl.DeleteAllItems();

	// set the size of the image list
	m_FileViewImages.SetImageCount(m_VectorImageNames.size());
	i = 0;

	// draw the thumbnails
	std::vector<CString>::iterator	iter;
	for (iter = m_VectorImageNames.begin(); iter != m_VectorImageNames.end(); iter++)
	{
		// load the bitmap
		strPath.Format(TEXT("%s\\%s"), strFolder, *iter);

		USES_CONVERSION;
		Bitmap img((strPath));
		Bitmap* pThumbnail = static_cast<Bitmap*>(img.GetThumbnailImage(THUMBNAIL_WIDTH, THUMBNAIL_HEIGHT, NULL, NULL));

		// attach the thumbnail bitmap handle to an CBitmap object
		pThumbnail->GetHBITMAP(NULL, &hBmp);
		pImage = new CBitmap();
		pImage->Attach(hBmp);

		// add bitmap to our image list
		m_FileViewImages.Replace(i, pImage, NULL);

		// put item to display
		// set the image file name as item text
		m_wndListCtrl.InsertItem(i, m_VectorImageNames[i], i);

		// get current item position	 
		m_wndListCtrl.GetItemPosition(i, &pt);

		// shift the thumbnail to desired position
		//pt.x = nGap + i*(THUMBNAIL_WIDTH + nGap);
		m_wndListCtrl.SetItemPosition(i, pt);
		i++;

		delete pImage;
		delete pThumbnail;
	}

	// let's show the new thumbnails
	m_wndListCtrl.SetRedraw();
}