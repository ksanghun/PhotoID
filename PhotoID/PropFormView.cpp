// PropFormView.cpp : implementation file
//

#include "stdafx.h"
#include "PhotoID.h"
#include "PropFormView.h"
#include "PhotoIDView.h"

// CPropFormView
#include "DlgApply.h"

using namespace cv;

IMPLEMENT_DYNCREATE(CPropFormView, CFormView)

CPropFormView::CPropFormView()
	: CFormView(CPropFormView::IDD)
	, m_sliderRotate(0)

	, m_strRotValue(_T("0"))
	, m_fBrightNess(0)
	, m_fContrast(0)
	//, m_fEditBrightness(0)
	//, m_fEditContrast(0)
{
	m_preRotateSliderPos = 0;
	m_IsBtnCreated = false;

	m_fPreBrightness = 0;
	m_fPreContrast = 0;
}

CPropFormView::~CPropFormView()
{
}

void CPropFormView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Slider(pDX, IDC_SLIDER_ROTATE, m_sliderRotate);
	DDV_MinMaxInt(pDX, m_sliderRotate, -300, 300);
	DDX_Control(pDX, IDC_SLIDER_ROTATE, m_ctrlSliderRotate);
	//DDX_Text(pDX, IDC_EDIT_ROT_VALUE, m_editRotate);
	//DDV_MinMaxFloat(pDX, m_editRotate, -90.0, 90.0);
	//	DDX_Text(pDX, IDC_EDIT_ROT_VALUE, m_strRotValue);
	//	DDV_MaxChars(pDX, m_strRotValue, 5);
	//	DDX_Control(pDX, IDC_EDIT_ROT_VALUE, m_EditCtrlRotate);
	DDX_Slider(pDX, IDC_SLIDER_BRINGTNESS, m_fBrightNess);
	DDV_MinMaxInt(pDX, m_fBrightNess, -100, 100);
	DDX_Slider(pDX, IDC_SLIDER_CONTRAST, m_fContrast);
	DDV_MinMaxInt(pDX, m_fContrast, -100, 100);
	DDX_Control(pDX, IDC_SLIDER_BRINGTNESS, m_SliderBrightness);
	DDX_Control(pDX, IDC_SLIDER_CONTRAST, m_SliderContrast);
	DDX_Control(pDX, IDC_BN_AUTOFIT, m_pButtonAutoFit);
	DDX_Control(pDX, IDC_BN_CROPIMG, m_pButtonCrop);
	DDX_Control(pDX, IDC_BN_STEMP, m_pButtonStamp);
	DDX_Control(pDX, IDC_BN_STEMP2, m_pButtonBlur);
	DDX_Control(pDX, IDC_BN_PRINT, m_pButtonPrint);
	//	DDX_Text(pDX, IDC_EDIT_BRINGT_VALUE, m_fEditBrightness);
	//	DDX_Text(pDX, IDC_EDIT_CONT_VALUE, m_fEditContrast);
	DDX_Control(pDX, IDC_SLIDER_CURSOR_SIZE, m_sliderCurSize);
}

BEGIN_MESSAGE_MAP(CPropFormView, CFormView)
	ON_WM_MOUSEACTIVATE()
//	ON_EN_CHANGE(IDC_EDIT_ROT_VALUE, &CPropFormView::OnEnChangeEditRotValue)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER_ROTATE, &CPropFormView::OnNMCustomdrawSliderRotate)
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_SLIDER_ROTATE, &CPropFormView::OnNMReleasedcaptureSliderRotate)
	ON_BN_CLICKED(IDC_BN_AUTOFIT, &CPropFormView::OnBnClickedBnAutofit)
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_SLIDER_BRINGTNESS, &CPropFormView::OnNMReleasedcaptureSliderBringtness)
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_SLIDER_CONTRAST, &CPropFormView::OnNMReleasedcaptureSliderContrast)
	ON_BN_CLICKED(IDC_BN_PRINT, &CPropFormView::OnBnClickedBnPrint)
	ON_BN_CLICKED(IDC_BN_CROPIMG, &CPropFormView::OnBnClickedBnCropimg)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER_BRINGTNESS, &CPropFormView::OnNMCustomdrawSliderBringtness)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER_CONTRAST, &CPropFormView::OnNMCustomdrawSliderContrast)
	ON_BN_CLICKED(IDC_BN_STEMP2, &CPropFormView::OnBnClickedBnBlur)
	ON_BN_CLICKED(IDC_BN_STEMP, &CPropFormView::OnBnClickedBnStemp)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER_CURSOR_SIZE, &CPropFormView::OnNMCustomdrawSliderCursorSize)
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


	
	m_ctrlSliderRotate.SetRange(-300, 300, TRUE);
	m_ctrlSliderRotate.SetPos(0);
	m_ctrlSliderRotate.SetTicFreq(100);


	m_SliderBrightness.SetRange(-100, 100, TRUE);
	m_SliderBrightness.SetPos(0);
	m_SliderBrightness.SetTicFreq(10);

	m_SliderContrast.SetRange(-100, 100, TRUE);
	m_SliderContrast.SetPos(0);
	m_SliderContrast.SetTicFreq(10);
	
	m_ctrlSliderRotate.Invalidate(TRUE);



	m_sliderCurSize.SetRange(10, 100, TRUE);
	m_sliderCurSize.SetPos(50);
	m_sliderCurSize.SetTicFreq(1);

	pView->SetUserCursorSize(m_sliderCurSize.GetPos());

	SetSliderMode(false);


	// Set Button Icon //
	m_pButtonAutoFit.MoveWindow(5, 5, 64, 64);
	m_pButtonCrop.MoveWindow(70, 5, 64, 64);
	m_pButtonStamp.MoveWindow(135, 5, 64, 64);
	m_pButtonBlur.MoveWindow(200, 5, 64, 64);
	m_pButtonPrint.MoveWindow(265, 5, 64, 64);

	//m_pButtonAutoFit.SetBitmap((HBITMAP)LoadImage(AfxGetApp()->m_hInstance, MAKEINTRESOURCE(IDB_BITMAP_FITFACE), IMAGE_BITMAP, 64, 64, LR_COLOR));
	//m_pButtonCrop.SetBitmap((HBITMAP)LoadImage(AfxGetApp()->m_hInstance, MAKEINTRESOURCE(IDB_BITMAP_CROP), IMAGE_BITMAP, 64, 64, LR_COLOR));
	//m_pButtonStamp.SetBitmap((HBITMAP)LoadImage(AfxGetApp()->m_hInstance, MAKEINTRESOURCE(IDB_BITMAP_STAMP), IMAGE_BITMAP, 64, 64, LR_COLOR));
	//m_pButtonBlur.SetBitmap((HBITMAP)LoadImage(AfxGetApp()->m_hInstance, MAKEINTRESOURCE(IDB_BITMAP_BLUR), IMAGE_BITMAP, 64, 64, LR_COLOR));
	//m_pButtonPrint.SetBitmap((HBITMAP)LoadImage(AfxGetApp()->m_hInstance, MAKEINTRESOURCE(IDB_BITMAP_PRINT), IMAGE_BITMAP, 64, 64, LR_COLOR));
	//CRect rect;
	//m_pButtonAutoFit.GetWindowRect(&rect);

	if (m_IsBtnCreated == false){
		CString text = _T("Automatic Adjustment of Image Angle");
		m_pButtonAutoFit.LoadBitmap(IDB_BITMAP_FITFACE);
		m_pButtonAutoFit.SetToolTipText(&text);

		text = _T("Crop Image for Photo ID");
		m_pButtonCrop.LoadBitmap(IDB_BITMAP_CROP);
		m_pButtonCrop.SetToolTipText(&text);

		text = _T("Stamp Tool");
		m_pButtonStamp.LoadBitmap(IDB_BITMAP_STAMP);
		m_pButtonStamp.SetToolTipText(&text);

		text = _T("Blur Tool");
		m_pButtonBlur.LoadBitmap(IDB_BITMAP_BLUR);
		m_pButtonBlur.SetToolTipText(&text);

		text = _T("Print");
		m_pButtonPrint.LoadBitmap(IDB_BITMAP_PRINT);
		m_pButtonPrint.SetToolTipText(&text);

		m_IsBtnCreated = true;
	}


	UpdateData(TRUE);

}


void CPropFormView::SetSliderMode(bool IsCropMode)
{
	if (IsCropMode == false){
		m_ctrlSliderRotate.EnableWindow(TRUE);
		m_SliderBrightness.EnableWindow(FALSE);
		m_SliderContrast.EnableWindow(FALSE);
		m_sliderCurSize.EnableWindow(FALSE);
	}
	else{
		m_ctrlSliderRotate.EnableWindow(FALSE);
		m_SliderBrightness.EnableWindow(TRUE);
		m_sliderCurSize.EnableWindow(TRUE);
		m_SliderContrast.EnableWindow(TRUE);
	}
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





//void CPropFormView::OnEnChangeEditRotValue()
//{
//	// TODO:  If this is a RICHEDIT control, the control will not
//	// send this notification unless you override the CFormView::OnInitDialog()
//	// function and call CRichEditCtrl().SetEventMask()
//	// with the ENM_CHANGE flag ORed into the mask.
//
//	// TODO:  Add your control notification handler code here
//
//	//UpdateData(TRUE);
//	//float fAngle = _wtof(m_strRotValue);
//	//if ((!m_strRotValue.IsEmpty()) && (fAngle)){
//
//	//	int sPos = fAngle * 10;
//	//	m_ctrlSliderRotate.SetPos(sPos);
//	//	pView->RotateImage(fAngle);
//	//}
//	//UpdateData(FALSE);
//}




void CPropFormView::OnNMCustomdrawSliderRotate(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: Add your control notification handler code here

	UpdateData(TRUE);
	//


		if (m_preRotateSliderPos != m_ctrlSliderRotate.GetPos()){

			float fRotate = m_ctrlSliderRotate.GetPos();
			m_strRotValue.Format(L"%3.1f", fRotate*0.1f);
	//		pView->RotateImage(fRotate*0.1f, false);
			UpdateData(FALSE);

			m_preRotateSliderPos = m_ctrlSliderRotate.GetPos();

		}
	

	*pResult = 0;
}


void CPropFormView::OnNMReleasedcaptureSliderRotate(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: Add your control notification handler code here

	//UpdateData(TRUE);
	//float fRotate = m_ctrlSliderRotate.GetPos();
	//m_strRotValue.Format(L"%3.1f", fRotate*0.1f);
	//pView->RotateImage(fRotate*0.1f);
	////UpdateData(FALSE);

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
		//if ((!m_strRotValue.IsEmpty()) && m_EditCtrlRotate.GetFocus()){
		if ((!m_strRotValue.IsEmpty())){

			int sPos = fAngle * 10;
			m_ctrlSliderRotate.SetPos(sPos);
			pView->RotateImage(fAngle);
		}
		UpdateData(FALSE);
	}


	return CFormView::PreTranslateMessage(pMsg);
}


void CPropFormView::OnBnClickedBnAutofit()
{
	// TODO: Add your control notification handler code here
	pView->ProcAutoFitImage();
	SetSliderMode(false);
}




void CPropFormView::OnNMReleasedcaptureSliderBringtness(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: Add your control notification handler code here
	CDlgApply dlg;
	if (dlg.DoModal() == IDOK){
		UpdateData(TRUE);
		
		pView->ChangeBrightness(m_fBrightNess, true);		
		
		m_fPreBrightness = 0;
		m_SliderBrightness.SetPos(0);
		
	//	m_fEditBrightness = 0;
		UpdateData(FALSE);
	}
	else{
		UpdateData(TRUE);
		
		pView->ChangeBrightness(0, true);
				
		m_fPreBrightness = 0;
		m_SliderBrightness.SetPos(0);	
	//	m_fEditBrightness = 0;
		
		UpdateData(FALSE);
	}	

	*pResult = 0;
}


void CPropFormView::OnNMReleasedcaptureSliderContrast(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: Add your control notification handler code here
	CDlgApply dlg;
	if (dlg.DoModal() == IDOK){
		UpdateData(TRUE);
		float contrast = m_fContrast*0.01f + 1.0f;
		pView->ChangeContrast(contrast, true);

		m_fContrast = 0;
		m_fPreContrast = 0;		
		m_SliderContrast.SetPos(0);
	//	m_fEditContrast = 0;
		UpdateData(FALSE);
	}
	else{
		UpdateData(TRUE);

		pView->ChangeBrightness(1.0f, true);		
		
		m_fContrast = 0;
		m_fPreContrast = 0;
		m_SliderContrast.SetPos(0);
	//	m_fEditContrast = 0;
		
		UpdateData(FALSE);
	}




	*pResult = 0;
}


void CPropFormView::OnBnClickedBnPrint()
{
	// TODO: Add your control notification handler code here
	pView->PrintBitmap(L"PhtoID");
}



void CPropFormView::OnBnClickedBnCropimg()
{
	// TODO: Add your control notification handler code here
	pView->CropImage();
	SetSliderMode(true);
}


void CPropFormView::OnNMCustomdrawSliderBringtness(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	if (m_fPreBrightness != m_fBrightNess){

		pView->ChangeBrightness(m_fBrightNess, false);
	//	m_fEditBrightness = m_fBrightNess;
		m_fPreBrightness = m_fBrightNess;
		
	}
	UpdateData(FALSE);
	*pResult = 0;
}


void CPropFormView::OnNMCustomdrawSliderContrast(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	if (m_fPreContrast != m_fContrast){

		float contrast = m_fContrast*0.01f + 1.0f;
		pView->ChangeContrast(contrast, false);
	//	m_fEditContrast = m_fContrast;
		m_fPreContrast = m_fContrast;

	}
	UpdateData(FALSE);
	*pResult = 0;
}


void CPropFormView::OnBnClickedBnBlur()
{
	// TODO: Add your control notification handler code here


	pView->BlurImage(0);

	// TEST // iPlimge --> cv mat --> blur --> Iplimage
	//IplImage *pimg = cvLoadImage("D:/face.jpg");
	//cvShowImage("before", pimg);
	//
	//cv::Mat m = cv::cvarrToMat(pimg);
	//int orignaltype = m.type();

	//Mat mask = Mat::zeros(m.size(), m.type());
	//// mask is a disk
	//int radious = 100;
	//circle(mask, Point(200, 200), radious, Scalar(255, 255, 255), -1);
	//Mat md;
	//m.copyTo(md);

	//Size blurSize(7, 7);
	//blur(mask, mask, blurSize);
	//blur(md, md, blurSize);

	//mask.convertTo(mask, CV_32FC3, 1.0 / 255); // 
	//md.convertTo(md, CV_32FC3);
	//m.convertTo(m, CV_32FC3);

	//multiply(mask, md, md);
	//multiply(Scalar::all(1.0) - mask, m, m);

	//Mat ouImage = Mat::zeros(m.size(), m.type());
	//add(md, m, ouImage);

	//ouImage.convertTo(ouImage, orignaltype);

	//cvReleaseImage(&pimg);
	//pimg = new IplImage(ouImage);
	//cvShowImage("blur", pimg);





	
	// ** Direct Access Pixels //
	//void alphaBlend(Mat& foreground, Mat& background, Mat& alpha, Mat& outImage)
	//{
	//	// Find number of pixels. 
	//	int numberOfPixels = foreground.rows * foreground.cols * foreground.channels();

	//	// Get floating point pointers to the data matrices
	//	float* fptr = reinterpret_cast<float*>(foreground.data);
	//	float* bptr = reinterpret_cast<float*>(background.data);
	//	float* aptr = reinterpret_cast<float*>(alpha.data);
	//	float* outImagePtr = reinterpret_cast<float*>(outImage.data);

	//	// Loop over all pixesl ONCE
	//	for (
	//		int i = 0;
	//		i < numberOfPixels;
	//	i++, outImagePtr++, fptr++, aptr++, bptr++
	//		)
	//	{
	//		*outImagePtr = (*fptr)*(*aptr) + (*bptr)*(1 - *aptr);
	//	}
	//}
}


void CPropFormView::OnBnClickedBnStemp()
{
	// TODO: Add your control notification handler code here
	pView->StampImage();
}


void CPropFormView::OnNMCustomdrawSliderCursorSize(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: Add your control notification handler code here
	pView->SetUserCursorSize(m_sliderCurSize.GetPos());

	*pResult = 0;
}
