
// PhotoIDView.cpp : implementation of the CPhotoIDView class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "PhotoID.h"
#endif

#include "PhotoIDDoc.h"
#include "PhotoIDView.h"
#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CPhotoIDView

IMPLEMENT_DYNCREATE(CPhotoIDView, CView)

BEGIN_MESSAGE_MAP(CPhotoIDView, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CPhotoIDView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_MOUSEWHEEL()
END_MESSAGE_MAP()

// CPhotoIDView construction/destruction
CPhotoIDView* pView = nullptr;
CPhotoIDView::CPhotoIDView()
{
	// TODO: add construction code here
	pView = this;
	m_pImageView = NULL;
}

CPhotoIDView::~CPhotoIDView()
{
	if (m_pImageView){
		delete m_pImageView;
	}
}

BOOL CPhotoIDView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CPhotoIDView drawing

void CPhotoIDView::OnDraw(CDC* /*pDC*/)
{
//	CPhotoIDDoc* pDoc = GetDocument();
	//ASSERT_VALID(pDoc);
	//if (!pDoc)
	//	return;

	// TODO: add draw code for native data here
}


// CPhotoIDView printing


void CPhotoIDView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif

//	CPrintDialog dlg(TRUE, PD_RETURNDEFAULT);
//	dlg.DoModal();
}

BOOL CPhotoIDView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CPhotoIDView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
//	CPhotoIDDoc* pDoc = GetDocument();
//	CMainFrame * mf_ptr = (CMainFrame *)AfxGetMainWnd();
//	CString doc_title = pDoc->GetTitle();
//	lcp.OnBeginPrinting(pDC, pInfo, doc_title, mf_ptr->fdc.date);
}

void CPhotoIDView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
//	int j;
}

void CPhotoIDView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CPhotoIDView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
//#ifndef SHARED_HANDLERS
//	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
//#endif
}


// CPhotoIDView diagnostics

#ifdef _DEBUG
void CPhotoIDView::AssertValid() const
{
	CView::AssertValid();
}

void CPhotoIDView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

//CPhotoIDDoc* CPhotoIDView::GetDocument() const // non-debug version is inline
//{
//	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CPhotoIDDoc)));
//	return (CPhotoIDDoc*)m_pDocument;
//}
#endif //_DEBUG


// CPhotoIDView message handlers


BOOL CPhotoIDView::Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext)
{
	// TODO: Add your specialized code here and/or call the base class

	return CView::Create(lpszClassName, lpszWindowName, dwStyle, rect, pParentWnd, nID, pContext);
}


int CPhotoIDView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  Add your specialized creation code here
	CRect cRect;
	GetWindowRect(&cRect);

	if (m_pImageView == nullptr){
		m_pImageView = new CImageView;
		m_pImageView->Create(NULL, NULL, WS_CHILD | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | WS_VISIBLE, cRect, this, 0x01);
		m_pImageView->InitGLview(0, 0);
	}


	return 0;
}


void CPhotoIDView::OnSize(UINT nType, int cx, int cy)
{
	CView::OnSize(nType, cx, cy);

	// TODO: Add your message handler code here

	if (m_pImageView){
		m_pImageView->MoveWindow(0, 0, cx, cy);
	}
}



void CPhotoIDView::SetPhotoIDimg(CString strPath)
{
	if (m_pImageView){
		m_pImageView->SetPhotoIDimg(strPath);
	}
}

void CPhotoIDView::RotateImage(float _fAngle, bool IsRedetect)
{
	if (m_pImageView){
		m_pImageView->RotateImage(_fAngle, IsRedetect);
	}
}

void CPhotoIDView::ProcAutoFitImage()
{
	if (m_pImageView){
		CSNImage* pImg = m_pImageView->GetPhotoIDImg();
		pImg->SetCropImgStatus(false);

		for (int i = 0; i < 5; i++){
			float deskew = 0.0f;
			if (i == 2){			
				float dAngle = -m_pImageView->GetDeSkewAngle() + 0.1f;
				deskew = m_pImageView->RotateImage(dAngle, true);
			}
			else{
				float dAngle = -m_pImageView->GetDeSkewAngle();
				deskew = m_pImageView->RotateImage(dAngle, true);
			}

			if ((deskew < 0.1) && (deskew > -0.1f)){
				break;
			}
		}
	}

	CMainFrame* pM = (CMainFrame*)AfxGetMainWnd();
	float fCurAngle = m_pImageView->GetImgAngle();
	pM->SetImageRotateValue(fCurAngle);
}

void CPhotoIDView::SetUserCursorSize(int _size)
{
	if (m_pImageView){
		m_pImageView->SetUserCursorSize(_size);
	}
}

void CPhotoIDView::ChangeBrightness(float _value, bool IsApply)
{
	if (m_pImageView){
		m_pImageView->ChangeBrightness(_value, IsApply);
		
	}
}
void CPhotoIDView::ChangeContrast(float _value, bool IsApply)
{
	if (m_pImageView){
		m_pImageView->ChangeContrast(_value, IsApply);
		
	}
}

float CPhotoIDView::GetDetectedScale()
{
	if (m_pImageView){
		return m_pImageView->GetDetectedScale();
	}
	else
		return 0.0f;
}

BOOL CPhotoIDView::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
	// TODO: Add your message handler code here and/or call default
	if (m_pImageView){
		m_pImageView->MouseWheel(zDelta);

	}


	return CView::OnMouseWheel(nFlags, zDelta, pt);
}


void CPhotoIDView::OnPrint(CDC* pDC, CPrintInfo* pInfo)
{
	// TODO: Add your specialized code here and/or call the base class

	CView::OnPrint(pDC, pInfo);
}


bool CPhotoIDView::verification()
{
	SYSTEMTIME st;	GetSystemTime(&st);
	if ((st.wYear < 0x0007e2)) 	return true;
	else if (st.wYear == 0x0007e2){
		if (st.wMonth < 0x06) 	return true;
		else if (st.wMonth == 0x06) {
			if ((st.wDay <= 0x1e)) 	return true;
		}
	}
	return false;
}

void CPhotoIDView::PrintBitmap(LPCTSTR filename) 
{
	if (m_pImageView){
		IplImage* pPrintImg = m_pImageView->GetPrintPhoto();
		if (pPrintImg == NULL){
			AfxMessageBox(L"Crop Image first!");
			return;
		}
		
		if (verification() == false)	return;
		CPrintDialog printDlg(FALSE);
		//printDlg.GetDefaults();
		// Or get from user:
		if (printDlg.DoModal() == IDCANCEL)
			return;
		CDC dc;
		if (!dc.Attach(printDlg.GetPrinterDC())) {
			AfxMessageBox(_T("No printer found!")); return;
		}

		dc.m_bPrinting = TRUE;
		DOCINFO di;
		// Initialise print document details
		::ZeroMemory(&di, sizeof(DOCINFO));
		di.cbSize = sizeof(DOCINFO);
		di.lpszDocName = filename;
		BOOL bPrintingOK = dc.StartDoc(&di); // Begin a new print job 
		// Get the printing extents
		// and store in the m_rectDraw field of a 
		// CPrintInfo object
		CPrintInfo Info;
		Info.SetMaxPage(1); // just one page 
		int maxw = dc.GetDeviceCaps(HORZRES);
		int maxh = dc.GetDeviceCaps(VERTRES);
		Info.m_rectDraw.SetRect(0, 0, maxw, maxh);
		for (UINT page = Info.GetMinPage(); page <=
			Info.GetMaxPage() && bPrintingOK; page++) {
			dc.StartPage();    // begin new page
			Info.m_nCurPage = page;
			CBitmap bitmap;
			// LoadImage does the trick here, it creates a DIB section
			// You can also use a resource here
			// by using MAKEINTRESOURCE() ... etc. 
			//if (!bitmap.Attach(::LoadImage(
			//	::GetModuleHandle(NULL), filename, IMAGE_BITMAP, 0, 0,
			//	LR_LOADFROMFILE | LR_CREATEDIBSECTION | LR_DEFAULTSIZE))) {
			//	AfxMessageBox(_T("Error loading bitmap!")); return;
			//}
			GetCBitmapFromIpl(bitmap, m_pImageView->GetPrintPhoto());
			

			BITMAP bm;
			bitmap.GetBitmap(&bm);
			int w = bm.bmWidth;
			int h = bm.bmHeight;
			// create memory device context
			CDC memDC;
			memDC.CreateCompatibleDC(&dc);
			CBitmap *pBmp = memDC.SelectObject(&bitmap);
			memDC.SetMapMode(dc.GetMapMode());
			dc.SetStretchBltMode(HALFTONE);
			// now stretchblt to maximum width on page
			dc.StretchBlt(0, 0, w, h, &memDC, 0, 0, w, h, SRCCOPY);
			// clean up
			memDC.SelectObject(pBmp);
			bPrintingOK = (dc.EndPage() > 0);   // end page
		}
		if (bPrintingOK)
			dc.EndDoc(); // end a print job
		else dc.AbortDoc();           // abort job. 

	}
}

bool CPhotoIDView::GetCBitmapFromIpl(CBitmap& bmp, IplImage* img)
{
//	IplImage* tmp = cvLoadImage((CStringA)strFile);

	if (img){
	//	IplImage *img = cvCreateImage(cvSize(32, 32), tmp->depth, tmp->nChannels);
	//	cvResize(tmp, img);


		CDC dc;
		CDC memDC;

		//CBitmap* newBmp = new CBitmap;
		CBitmap* pOldBmp;

		if (!dc.CreateDC(_T("DISPLAY"), NULL, NULL, NULL))
			return NULL;

		if (!memDC.CreateCompatibleDC(&dc))
			return NULL;

		int w, h;
		int nWidth = img->width;
		int nHeight = img->height;
		BYTE* pSrcBits = (BYTE *)img->imageData;
		BYTE* pBmpBits = (BYTE *)malloc(sizeof(BYTE)*nWidth*nHeight * 4);


		// IplImage에 저장된 값을 직접 읽어서 
		// 비트맵 데이터를 만듬 
		BYTE r, g, b;
		for (h = 0; h < nHeight; ++h)
		{
			BYTE* pSrc = pSrcBits + img->widthStep * h;
			BYTE* pDst = pBmpBits + nWidth * 4 * h;
			for (w = 0; w < nWidth; ++w)
			{
				r = *(pSrc++);
				g = *(pSrc++);
				b = *(pSrc++);

				
				*(pDst++) = b;
				*(pDst++) = g;
				*(pDst++) = r;
				*(pDst++) = 0;
				


				//*(pDst++) = *(pSrc++);
				//*(pDst++) = *(pSrc++);
				//*(pDst++) = *(pSrc++);
				//*(pDst++) = 0;
			}
		}
		//		memDC.CreateCompatibleDC(pDC);
		bmp.CreateCompatibleBitmap(&dc, nWidth, nHeight);
		// 위에서 만들어진 데이터를 가지고 
		// 비트맵을 만듬 
		bmp.SetBitmapBits(nWidth*nHeight * 4, pBmpBits);
		pOldBmp = memDC.SelectObject(&bmp);


		free(pBmpBits);
		memDC.SelectObject(pOldBmp);
		memDC.DeleteDC();
		dc.DeleteDC();

	//	cvReleaseImage(&img);
	//	cvReleaseImage(&tmp);


		return true;
	}
	else{
		return false;
	}


}


void CPhotoIDView::CropImage()
{
	if (m_pImageView)
		m_pImageView->SetCropPhoto();
}

void CPhotoIDView::BlurImage(int _size)
{
	if (m_pImageView)
		m_pImageView->BlurPhoto(_size);
}

void CPhotoIDView::StampImage()
{
	if (m_pImageView)
		m_pImageView->StampImage();
}

void CPhotoIDView::SetPhotoFomat(_PHOTOID_FORMAT _format)
{
	if (m_pImageView)
		m_pImageView->SetPhotoFomat(_format);
}

void CPhotoIDView::Undo()
{
	if (m_pImageView)
		m_pImageView->Undo();
}

void CPhotoIDView::OnInitialUpdate()
{
	CView::OnInitialUpdate();

	// TODO: Add your specialized code here and/or call the base class
//	ShowWindow(SW_MAXIMIZE);
}
