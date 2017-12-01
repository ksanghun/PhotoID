#pragma once
#include "FormViewFile.h"

// CDockFormViewFile

class CDockFormViewFile : public CDockablePane
{
	DECLARE_DYNAMIC(CDockFormViewFile)


	CFormViewFile* m_pMyFormView;
public:
	CDockFormViewFile();
	virtual ~CDockFormViewFile();

	void UpdateImgListCtrl(CString strPath);
	


protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
};


