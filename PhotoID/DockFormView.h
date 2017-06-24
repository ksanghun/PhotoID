#pragma once


// CDockFormView
class CPropFormView;
class CDockFormView : public CDockablePane
{
	DECLARE_DYNAMIC(CDockFormView)


	CPropFormView* m_pMyFormView;

public:
	CDockFormView();
	virtual ~CDockFormView();

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
};


