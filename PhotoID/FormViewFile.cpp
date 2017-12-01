// FormViewFile.cpp : implementation file
//

#include "stdafx.h"
#include "PhotoID.h"
#include "FormViewFile.h"
#include <gdiplus.h>
using namespace Gdiplus;

// CFormViewFile
#define	THUMBNAIL_WIDTH		64
#define	THUMBNAIL_HEIGHT	64

IMPLEMENT_DYNCREATE(CFormViewFile, CFormView)

CFormViewFile::CFormViewFile()
	: CFormView(CFormViewFile::IDD)
{

}

CFormViewFile::~CFormViewFile()
{
}

void CFormViewFile::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CFormViewFile, CFormView)
	ON_WM_CREATE()
	ON_WM_SIZE()
END_MESSAGE_MAP()


// CFormViewFile diagnostics

#ifdef _DEBUG
void CFormViewFile::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CFormViewFile::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CFormViewFile message handlers


CFormViewFile *CFormViewFile::CreateOne(CWnd *pParent)
{
	CFormViewFile *pFormView = new CFormViewFile;
	//CMyFormView *pFormView = NULL;
	//CRuntimeClass *pRuntimeClass = RUNTIME_CLASS(CMyFormView);
	//pFormView = (CMyFormView *)pRuntimeClass->CreateObject();

	//CDockableFormViewAppDoc *pDoc = CDockableFormViewAppDoc::CreateOne();
	//pFormView->m_pDocument = pDoc;

	CCreateContext *pContext = NULL;

#if 0
	if (!pFormView->CreateEx(0, NULL, NULL, WS_CHILD | WS_VISIBLE, CRect(0, 0, 205, 157),
		pParent, -1, pContext))
#else
	if (!pFormView->Create(NULL, NULL, WS_CHILD | WS_VISIBLE, CRect(0, 0, 205, 157), pParent, 0, pContext))
#endif
		//if( !pFormView->CreateEx( 0, AfxRegisterWndClass(0, 0, 0, 0), NULL,
		//  WS_CHILD | WS_VISIBLE, CRect( 0, 0, 205, 157), pParent, -1, pContext) )
	{
		AfxMessageBox(_T("Failed in creating CMyFormView"));
	}

	pFormView->OnInitialUpdate();

	return pFormView;
}

void CFormViewFile::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	// TODO: Add your specialized code here and/or call the base class
	//FillClassView();
}



void CFormViewFile::FillClassView()
{
	HTREEITEM hRoot = m_ctrlTreeView.InsertItem(_T("C:"), 2, 2);
	m_ctrlTreeView.SetItemState(hRoot, TVIS_BOLD, TVIS_BOLD);

	CFileFind finder;
	BOOL bWorking = finder.FindFile(_T("C:\\*.*"));

	while (bWorking){
		bWorking = finder.FindNextFile();

		if (finder.IsDirectory()){
			CString strTemp = finder.GetFileName();
			m_ctrlTreeView.InsertItem(finder.GetFileName(), 2, 2, hRoot);
		}
	}

	//	m_wndClassView.EnsureVisible(hRoot);



	hRoot = m_ctrlTreeView.InsertItem(_T("D:"), 2, 2);
	m_ctrlTreeView.SetItemState(hRoot, TVIS_BOLD, TVIS_BOLD);

//	finder;
	bWorking = finder.FindFile(_T("D:\\*.*"));

	while (bWorking){
		bWorking = finder.FindNextFile();

		if (finder.IsDirectory()){
			CString strTemp = finder.GetFileName();
			m_ctrlTreeView.InsertItem(finder.GetFileName(), 2, 2, hRoot);
		}
	}

	m_ctrlTreeView.EnsureVisible(hRoot);

}

int CFormViewFile::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFormView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  Add your specialized creation code here
	GdiplusStartupInput gdiplusStartupInput;
	GdiplusStartup(&m_gdiplusToken, &gdiplusStartupInput, NULL);


	CRect rectDummy;
	rectDummy.SetRectEmpty();

	// Create views:
	const DWORD dwViewStyle = WS_CHILD | WS_VISIBLE | TVS_HASLINES | TVS_LINESATROOT | TVS_HASBUTTONS | WS_CLIPSIBLINGS | WS_CLIPCHILDREN;

	if (!m_ctrlTreeView.Create(dwViewStyle, rectDummy, this, 2))
	{
		TRACE0("Failed to create Class View\n");
		return -1;      // fail to create
	}

	m_ctrlTreeImages.DeleteImageList();
	UINT uiBmpId = theApp.m_bHiColorIcons ? IDB_CLASS_VIEW_24 : IDB_CLASS_VIEW;

	CBitmap bmp;
	if (!bmp.LoadBitmap(uiBmpId))
	{
		TRACE(_T("Can't load bitmap: %x\n"), uiBmpId);
		ASSERT(FALSE);
		return -1;
	}

	BITMAP bmpObj;
	bmp.GetBitmap(&bmpObj);

	UINT nFlags = ILC_MASK;

	nFlags |= (theApp.m_bHiColorIcons) ? ILC_COLOR24 : ILC_COLOR4;

	m_ctrlTreeImages.Create(16, bmpObj.bmHeight, nFlags, 0, 0);
	m_ctrlTreeImages.Add(&bmp, RGB(255, 0, 0));
	m_ctrlTreeView.SetImageList(&m_ctrlTreeImages, TVSIL_NORMAL);

	//==================================================================//

	m_wndListCtrl.Create(WS_CHILD | WS_VISIBLE | WS_BORDER | LVS_ICON | LVS_EDITLABELS, rectDummy, this, NULL);
	m_wndListCtrl.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);


	HIMAGELIST hImageList = ImageList_Create(100, 100, ILC_COLOR32, 0, 10);
	m_FileViewImages.Attach(hImageList);

	CBitmap dummy;
	dummy.LoadBitmap(ILC_COLOR32);
	m_FileViewImages.Add(&dummy, RGB(0, 0, 0));

	m_wndListCtrl.SetImageList(&m_FileViewImages, LVSIL_NORMAL);
	m_wndListCtrl.SetImageList(&m_FileViewImages, LVSIL_SMALL);

	//======================================================//


	FillClassView();
	return 0;
}


void CFormViewFile::OnSize(UINT nType, int cx, int cy)
{
	CFormView::OnSize(nType, cx, cy);

	// TODO: Add your message handler code here
	AdjustLayout();

	m_ctrlTreeView.MoveWindow(0, 0, cx, cy/2);
	m_wndListCtrl.MoveWindow(0, cy / 2 + 5, cx, cy / 2 - 5);
}


void CFormViewFile::UpdateImgListCtrl(CString strPath)
{
	//if (m_wndListCtrl){
	//	m_wndListCtrl.UpdateImgListCtrl(strPath);
	//}

	m_wndListCtrl.SetCurrFolderPath(strPath);
	GetImageFileNames(strPath);
	DrawThumbnails(strPath);
}


BOOL  CFormViewFile::GetImageFileNames(CString strFolder)
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

void  CFormViewFile::DrawThumbnails(CString strFolder)
{
	CBitmap*    pImage = NULL;
	HBITMAP		hBmp = NULL;
	POINT		pt;
	CString		strPath;
	int			i;

	// reset our image list
	for (i = 0; i<m_FileViewImages.GetImageCount(); i++)
		m_FileViewImages.Remove(i);

	// remove all items from list view
	if (m_wndListCtrl.GetItemCount() != 0)
		m_wndListCtrl.DeleteAllItems();

	// no images
	if (m_VectorImageNames.empty())
		return;

	// set the length of the space between thumbnails
	// you can also calculate and set it based on the length of your list control
	int nGap = 6;

	// hold the window update to avoid flicking
	m_wndListCtrl.SetRedraw(FALSE);



	// set the size of the image list
	m_FileViewImages.SetImageCount(m_VectorImageNames.size());
	i = 0;

	// draw the thumbnails
	std::vector<CString>::iterator	iter;
	for (iter = m_VectorImageNames.begin(); iter != m_VectorImageNames.end(); iter++)
	{
		// load the bitmap
		strPath.Format(TEXT("%s%s"), strFolder, *iter);

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

void CFormViewFile::AdjustLayout()
{
	if (GetSafeHwnd() == NULL)
	{
		return;
	}

	CRect rectClient;
	GetClientRect(rectClient);

	//	int cyTlb = m_wndToolBar.CalcFixedLayout(FALSE, TRUE).cy;
	int cyTlb = 0;

	//	m_wndToolBar.SetWindowPos(NULL, rectClient.left, rectClient.top, rectClient.Width(), cyTlb, SWP_NOACTIVATE | SWP_NOZORDER);
	m_wndListCtrl.SetWindowPos(NULL, rectClient.left + 1, rectClient.top + cyTlb + 1, rectClient.Width() - 2, rectClient.Height() - cyTlb - 2, SWP_NOACTIVATE | SWP_NOZORDER);
}