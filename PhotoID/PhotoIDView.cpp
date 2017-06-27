
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
}

BOOL CPhotoIDView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CPhotoIDView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CPhotoIDView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

void CPhotoIDView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CPhotoIDView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
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
		for (int i = 0; i < 5; i++){
			float deskew = 0.0f;
			if (i == 2){
				deskew = m_pImageView->RotateImage(0.1f, true);
			}
			else{
				deskew = m_pImageView->RotateImage(0, true);
			}

			if ((deskew < 0.1) && (deskew > -0.1f)){
				break;
			}
		}
	}
}

void CPhotoIDView::ChangeBrightness(float _value)
{
	if (m_pImageView){
		m_pImageView->ChangeBrightness(_value);
		
	}

}
void CPhotoIDView::ChangeContrast(float _value)
{
	if (m_pImageView){
		m_pImageView->ChangeContrast(_value);
		
	}
}