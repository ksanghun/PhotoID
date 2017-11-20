#pragma once

#include "resource.h"
#include "afxcmn.h"
#include "afxwin.h"

#include "MySlider.h"
#include "HoverButton.h"

// CPropFormView form view

class CPropFormView : public CFormView
{
	DECLARE_DYNCREATE(CPropFormView)

protected:
	CPropFormView();           // protected constructor used by dynamic creation
	virtual ~CPropFormView();

	
public:
	enum { IDD = IDD_FORMVIEW };
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif


	static CPropFormView* CreateOne(CWnd *pParent);
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual void OnInitialUpdate();

	void SetImageRotateValue(float _fAngle);
	void SetSliderMode(bool IsCropMode);
	
	afx_msg int OnMouseActivate(CWnd* pDesktopWnd, UINT nHitTest, UINT message);
	int m_sliderRotate;


	CMySlider m_ctrlSliderRotate;
	int m_preRotateSliderPos;

//	afx_msg void OnEnChangeEditRotValue();
	afx_msg void OnNMCustomdrawSliderRotate(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMReleasedcaptureSliderRotate(NMHDR *pNMHDR, LRESULT *pResult);
	CString m_strRotValue;
	virtual BOOL PreTranslateMessage(MSG* pMsg);
//	CEdit m_EditCtrlRotate;
	afx_msg void OnBnClickedBnAutofit();
	afx_msg void OnNMReleasedcaptureSliderBringtness(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMReleasedcaptureSliderContrast(NMHDR *pNMHDR, LRESULT *pResult);
	int m_fBrightNess;
	int m_fContrast;
	CSliderCtrl m_SliderBrightness;
	CSliderCtrl m_SliderContrast;
	afx_msg void OnBnClickedBnPrint();
	CHoverButton m_pButtonAutoFit;
	CHoverButton m_pButtonCrop;
	CHoverButton m_pButtonStamp;
	CHoverButton m_pButtonBlur;
	CHoverButton m_pButtonPrint;

	bool m_IsBtnCreated;
	int m_fPreBrightness;
	int m_fPreContrast;

	afx_msg void OnBnClickedBnCropimg();
	//float m_fEditBrightness;
	//float m_fEditContrast;
	afx_msg void OnNMCustomdrawSliderBringtness(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMCustomdrawSliderContrast(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedBnBlur();
	afx_msg void OnBnClickedBnStemp();
};


