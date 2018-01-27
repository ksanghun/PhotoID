
// MainFrm.h : interface of the CMainFrame class
//

#pragma once
//#include "FileView.h"
//#include "ClassView.h"
//#include "PropertiesWnd.h"
#include "DockFormView.h"
#include "DockFormViewFile.h"

class CMainFrame : public CFrameWndEx
{
	
protected: // create from serialization only
	CMainFrame();
	DECLARE_DYNCREATE(CMainFrame)

// Attributes
public:

// Operations
public:

// Overrides
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual BOOL LoadFrame(UINT nIDResource, DWORD dwDefaultStyle = WS_OVERLAPPEDWINDOW | FWS_ADDTOTITLE, CWnd* pParentWnd = NULL, CCreateContext* pContext = NULL);

	void UpdateImgListCtrl(CString strPath);

	void SetImageRotateValue(float _fAngle);
	void SetSliderStatus(bool IsCrop);
	void SetUndoButtonState(bool bIsEnable, unsigned short _type);
	void DisplayPreview(void* pImg);
	void ReSetSlideValues();
// Implementation
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // control bar embedded members
//	CMFCMenuBar       m_wndMenuBar;
	//CMFCToolBar       m_wndToolBar;
	//CMFCStatusBar     m_wndStatusBar;
	//CMFCToolBarImages m_UserImages;
	//CFileView         m_wndFileView;
	//CClassView        m_wndClassView;
//	CPropertiesWnd    m_wndProperties;

	CDockFormView	 m_wndFormView;
	CDockFormViewFile m_wndFormViewFile;

// Generated message map functions
protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnViewCustomize();
	afx_msg LRESULT OnToolbarCreateNew(WPARAM wp, LPARAM lp);
	afx_msg void OnApplicationLook(UINT id);
	afx_msg void OnUpdateApplicationLook(CCmdUI* pCmdUI);
	DECLARE_MESSAGE_MAP()

	BOOL CreateDockingWindows();
	void SetDockingWindowIcons(BOOL bHiColorIcons);
public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
};


