// PropFormView.cpp : implementation file
//

#include "stdafx.h"
#include "PhotoID.h"
#include "PropFormView.h"
#include "PhotoIDView.h"

// CPropFormView

IMPLEMENT_DYNCREATE(CPropFormView, CFormView)

CPropFormView::CPropFormView()
	: CFormView(CPropFormView::IDD)
	, m_sliderRotate(0)

	, m_strRotValue(_T("0"))
{
	m_preRotateSliderPos = 0;
}

CPropFormView::~CPropFormView()
{
}

void CPropFormView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Slider(pDX, IDC_SLIDER_ROTATE, m_sliderRotate);
	DDV_MinMaxInt(pDX, m_sliderRotate, -900, 900);
	DDX_Control(pDX, IDC_SLIDER_ROTATE, m_ctrlSliderRotate);
	//DDX_Text(pDX, IDC_EDIT_ROT_VALUE, m_editRotate);
	//DDV_MinMaxFloat(pDX, m_editRotate, -90.0, 90.0);
	DDX_Text(pDX, IDC_EDIT_ROT_VALUE, m_strRotValue);
	DDV_MaxChars(pDX, m_strRotValue, 5);
	DDX_Control(pDX, IDC_EDIT_ROT_VALUE, m_EditCtrlRotate);
}

BEGIN_MESSAGE_MAP(CPropFormView, CFormView)
	ON_WM_MOUSEACTIVATE()
	ON_EN_CHANGE(IDC_EDIT_ROT_VALUE, &CPropFormView::OnEnChangeEditRotValue)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER_ROTATE, &CPropFormView::OnNMCustomdrawSliderRotate)
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_SLIDER_ROTATE, &CPropFormView::OnNMReleasedcaptureSliderRotate)
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


	m_ctrlSliderRotate.SetRange(-900, 900, TRUE);
	m_ctrlSliderRotate.SetPos(0);
	
	m_ctrlSliderRotate.Invalidate(TRUE);

	UpdateData(TRUE);

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





void CPropFormView::OnEnChangeEditRotValue()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CFormView::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here

	//UpdateData(TRUE);
	//float fAngle = _wtof(m_strRotValue);
	//if ((!m_strRotValue.IsEmpty()) && (fAngle)){

	//	int sPos = fAngle * 10;
	//	m_ctrlSliderRotate.SetPos(sPos);
	//	pView->RotateImage(fAngle);
	//}
	//UpdateData(FALSE);
}




void CPropFormView::OnNMCustomdrawSliderRotate(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: Add your control notification handler code here

	UpdateData(TRUE);
	
	if (m_preRotateSliderPos != m_ctrlSliderRotate.GetPos()){

		float fRotate = m_ctrlSliderRotate.GetPos();
		m_strRotValue.Format(L"%3.1f", fRotate*0.1f);
		pView->RotateImage(fRotate*0.1f, false);
		UpdateData(FALSE);

		m_preRotateSliderPos = m_ctrlSliderRotate.GetPos();

	}

	


	*pResult = 0;
}


void CPropFormView::OnNMReleasedcaptureSliderRotate(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: Add your control notification handler code here

	UpdateData(TRUE);
	float fRotate = m_ctrlSliderRotate.GetPos();
	m_strRotValue.Format(L"%3.1f", fRotate*0.1f);
	pView->RotateImage(fRotate*0.1f);


	//UpdateData(FALSE);

	*pResult = 0;
}


void CPropFormView::SetImageRotateValue(float _fAngle)
{
	UpdateData(TRUE);
//	m_editRotate = _fAngle;
	m_strRotValue.Format(L"%3.1f", _fAngle);
	int sPos = _fAngle * 10;
	m_ctrlSliderRotate.SetPos(sPos);
	UpdateData(FALSE);
}

BOOL CPropFormView::PreTranslateMessage(MSG* pMsg)
{
	// TODO: Add your specialized code here and/or call the base class

	if ((pMsg->message == WM_KEYDOWN) && (pMsg->wParam == VK_RETURN)){

		UpdateData(TRUE);
		float fAngle = _wtof(m_strRotValue);
		if ((!m_strRotValue.IsEmpty()) && m_EditCtrlRotate.GetFocus()){

			int sPos = fAngle * 10;
			m_ctrlSliderRotate.SetPos(sPos);
			pView->RotateImage(fAngle);
		}
		UpdateData(FALSE);
	}


	return CFormView::PreTranslateMessage(pMsg);
}
