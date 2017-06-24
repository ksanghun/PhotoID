#pragma once

#include "resource.h"

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
	
	afx_msg int OnMouseActivate(CWnd* pDesktopWnd, UINT nHitTest, UINT message);
};


