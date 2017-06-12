#pragma once


// CImgList

class CImgList : public CListCtrl
{
	DECLARE_DYNAMIC(CImgList)

public:
	CImgList();
	virtual ~CImgList();

//	void UpdateImgListCtrl(CString strPath);
	void SetCurrFolderPath(CString strPath) { m_strCurrFoler = strPath; }

protected:

	CImageList* m_pDragImage;	//For creating and managing the drag-image
	BOOL		m_bDragging;	//T during a drag operation
	int			m_nDragIndex;	//Index of selected item in the List we are dragging FROM
	int			m_nDropIndex;	//Index at which to drop item in the List we are dropping ON
	CWnd*		m_pDropWnd;		//Pointer to window we are dropping on (will be cast to CListCtrl* type)

	CString m_strCurrFoler;

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLvnBegindrag(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
};


