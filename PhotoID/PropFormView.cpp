// PropFormView.cpp : implementation file
//

#include "stdafx.h"
#include "PhotoID.h"
#include "PropFormView.h"


// CPropFormView

IMPLEMENT_DYNCREATE(CPropFormView, CFormView)

CPropFormView::CPropFormView()
	: CFormView(CPropFormView::IDD)
{

}

CPropFormView::~CPropFormView()
{
}

void CPropFormView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CPropFormView, CFormView)
	ON_WM_MOUSEACTIVATE()
END_MESSAGE_MAP()


// CPropFormView diagnostics

#ifdef _DEBUG
void CPropFormView::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CPropFormView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CPropFormView message handlers


void CPropFormView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	// TODO: Add your specialized code here and/or call the base class
}


CPropFormView *CPropFormView::CreateOne(CWnd *pParent)
{
	CPropFormView *pFormView = new CPropFormView;
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

int CPropFormView::OnMouseActivate(CWnd* pDesktopWnd, UINT nHitTest, UINT message)
{
	// TODO: Add your message handler code here and/or call default

//	return CFormView::OnMouseActivate(pDesktopWnd, nHitTest, message);

	int nResult = 0;

	CFrameWnd* pParentFrame = GetParentFrame();

	if (pParentFrame == pDesktopWnd)
	{
		// When this is docked
		nResult = CFormView::OnMouseActivate(pDesktopWnd, nHitTest, message);
	}
	else
	{
		// When this is not docked

		BOOL isMiniFrameWnd = pDesktopWnd->IsKindOf(RUNTIME_CLASS(CMiniFrameWnd));
		BOOL isPaneFrameWnd = pDesktopWnd->IsKindOf(RUNTIME_CLASS(CPaneFrameWnd));
		BOOL isMultiPaneFrameWnd = pDesktopWnd->IsKindOf(RUNTIME_CLASS(CMultiPaneFrameWnd));

		// pDesktopWnd is the frame window for CDockablePane

		nResult = CWnd::OnMouseActivate(pDesktopWnd, nHitTest, message);

		//nResult = CWnd::OnMouseActivate( pDesktopWnd, nHitTest, message );
		//if( nResult == MA_NOACTIVATE || nResult == MA_NOACTIVATEANDEAT )
		//  return nResult;

		//if (pDesktopWnd != NULL)
		//{
		//  // either re-activate the current view, or set this view to be active
		//  //CView* pView = pDesktopWnd->GetActiveView();
		//  //HWND hWndFocus = ::GetFocus();
		//  //if (pView == this &&
		//  //  m_hWnd != hWndFocus && !::IsChild(m_hWnd, hWndFocus))
		//  //{
		//  //  // re-activate this view
		//  //  OnActivateView(TRUE, this, this);
		//  //}
		//  //else
		//  //{
		//  //  // activate this view
		//  //  pDesktopWnd->SetActiveView(this);
		//  //}
		//}
	}

	return nResult;
}
