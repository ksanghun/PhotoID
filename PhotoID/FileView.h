
#pragma once

#include "ImgList.h"





class CFileViewToolBar : public CMFCToolBar
{
	virtual void OnUpdateCmdUI(CFrameWnd* /*pTarget*/, BOOL bDisableIfNoHndler)
	{
		CMFCToolBar::OnUpdateCmdUI((CFrameWnd*) GetOwner(), bDisableIfNoHndler);
	}

	virtual BOOL AllowShowOnList() const { return FALSE; }
};

class CFileView : public CDockablePane
{
// Construction
public:
	CFileView();

	void AdjustLayout();
	void OnChangeVisualStyle();

	void UpdateImgListCtrl(CString strPath);
	CListCtrl& GetListCtrl() { return m_wndListCtrl; }

	BOOL  GetImageFileNames(CString strFolder);
	void  DrawThumbnails(CString strFolder);

// Attributes
protected:

//	CViewTree m_wndFileView;
	CImgList m_wndListCtrl;
	CImageList m_FileViewImages;
	CFileViewToolBar m_wndToolBar;

	ULONG_PTR	m_gdiplusToken;

	std::vector<CString>	m_VectorImageNames;

protected:
	void FillFileView();

// Implementation
public:
	virtual ~CFileView();

protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	afx_msg void OnProperties();
	afx_msg void OnFileOpen();
	afx_msg void OnFileOpenWith();
	afx_msg void OnDummyCompile();
	afx_msg void OnEditCut();
	afx_msg void OnEditCopy();
	afx_msg void OnEditClear();
	afx_msg void OnPaint();
	afx_msg void OnSetFocus(CWnd* pOldWnd);

	DECLARE_MESSAGE_MAP()
};

