#pragma once
#include "afxcmn.h"
#include "ViewTree.h"
#include "ImgList.h"


// CFormViewFile form view

class CFormViewFile : public CFormView
{
	DECLARE_DYNCREATE(CFormViewFile)

protected:
	CFormViewFile();           // protected constructor used by dynamic creation
	virtual ~CFormViewFile();

public:
	enum { IDD = IDD_FORMVIEWFILE };
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif
	static CFormViewFile* CreateOne(CWnd *pParent);
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()

private:

	CImgList m_wndListCtrl;
	CImageList m_FileViewImages;

	CViewTree m_ctrlTreeView;
	CImageList m_ctrlTreeImages;
	std::vector<CString>	m_VectorImageNames;
	ULONG_PTR	m_gdiplusToken;
	
	BOOL  GetImageFileNames(CString strFolder);
	void  DrawThumbnails(CString strFolder);
	void FillClassView();
	void AdjustLayout();

public:
	CListCtrl& GetListCtrl() { return m_wndListCtrl; }
	virtual void OnInitialUpdate();
	void UpdateImgListCtrl(CString strPath);

	




	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
};


