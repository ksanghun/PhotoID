#pragma once

#include "resource.h"
#include "afxcmn.h"
#include "afxwin.h"

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
	
	afx_msg int OnMouseActivate(CWnd* pDesktopWnd, UINT nHitTest, UINT message);
	int m_sliderRotate;


	CSliderCtrl m_ctrlSliderRotate;
	int m_preRotateSliderPos;

	afx_msg void OnEnChangeEditRotValue();
	afx_msg void OnNMCustomdrawSliderRotate(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMReleasedcaptureSliderRotate(NMHDR *pNMHDR, LRESULT *pResult);
	CString m_strRotValue;
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	CEdit m_EditCtrlRotate;
};


