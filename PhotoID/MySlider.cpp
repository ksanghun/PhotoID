// MySlider.cpp : implementation file
//

#include "stdafx.h"
#include "PhotoID.h"
#include "MySlider.h"
#include "PhotoIDView.h"


// CMySlider

IMPLEMENT_DYNAMIC(CMySlider, CSliderCtrl)

CMySlider::CMySlider()
{
	m_prePos = 0.0f;
}

CMySlider::~CMySlider()
{
}


BEGIN_MESSAGE_MAP(CMySlider, CSliderCtrl)
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONUP()
END_MESSAGE_MAP()



// CMySlider message handlers




void CMySlider::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	SetCapture();

	CSliderCtrl::OnLButtonDown(nFlags, point);
}

void CMySlider::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default

	if (GetCapture()){
		UpdateData(TRUE);
		float fRotate = GetPos();
		//	m_strRotValue.Format(L"%3.1f", fRotate*0.1f);

		float dangle = fRotate - m_prePos;
		pView->RotateImage(dangle*0.1f, false);

		m_prePos = fRotate;
		UpdateData(FALSE);
	}

	CSliderCtrl::OnMouseMove(nFlags, point);
}


void CMySlider::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	UpdateData(TRUE);
	float fRotate = GetPos();
	float dangle = fRotate - m_prePos;
	pView->RotateImage(dangle*0.1f);
	m_prePos = fRotate;
	UpdateData(FALSE);


	ReleaseCapture();

	CSliderCtrl::OnLButtonUp(nFlags, point);
}
