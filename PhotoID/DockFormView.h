#pragma once
#include "PropFormView.h"

// CDockFormView

class CDockFormView : public CDockablePane
{
	DECLARE_DYNAMIC(CDockFormView)


	CPropFormView* m_pMyFormView;

public:
	CDockFormView();
	virtual ~CDockFormView();

	void SetImageRotateValue(float _fAngle);
	void SetSliderStatus(bool IsCropMode);
	void LoadCountryFormat();
	void SetUndoButton(bool IsEnable, unsigned short _type);
	void DisplayPreview(void* pImg);
	void ReSetSlideValues();

	virtual BOOL OnShowControlBarMenu(CPoint point);

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
};


