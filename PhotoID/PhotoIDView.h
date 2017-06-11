
// PhotoIDView.h : interface of the CPhotoIDView class
//

#pragma once
#include "ImageView.h"


class CPhotoIDView : public CView
{
protected: // create from serialization only
	CPhotoIDView();
	DECLARE_DYNCREATE(CPhotoIDView)

// Attributes
public:
//	CPhotoIDDoc* GetDocument() const;

private:

	CImageView* m_pImageView;

// Operations
public:

// Overrides
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// Implementation
public:
	virtual ~CPhotoIDView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext = NULL);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);

};

#ifndef _DEBUG  // debug version in PhotoIDView.cpp
//inline CPhotoIDDoc* CPhotoIDView::GetDocument() const
 //  { return reinterpret_cast<CPhotoIDDoc*>(m_pDocument); }
#endif

