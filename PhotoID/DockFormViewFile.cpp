// DockFormViewFile.cpp : implementation file
//

#include "stdafx.h"
#include "PhotoID.h"
#include "DockFormViewFile.h"


// CDockFormViewFile

IMPLEMENT_DYNAMIC(CDockFormViewFile, CDockablePane)

CDockFormViewFile::CDockFormViewFile()
{

}

CDockFormViewFile::~CDockFormViewFile()
{
}


BEGIN_MESSAGE_MAP(CDockFormViewFile, CDockablePane)
	ON_WM_CREATE()
	ON_WM_SIZE()
END_MESSAGE_MAP()



// CDockFormViewFile message handlers




int CDockFormViewFile::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDockablePane::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  Add your specialized creation code here
	m_pMyFormView = CFormViewFile::CreateOne(this);

	return 0;
}


void CDockFormViewFile::OnSize(UINT nType, int cx, int cy)
{
	CDockablePane::OnSize(nType, cx, cy);

	// TODO: Add your message handler code here
	if (m_pMyFormView){
		m_pMyFormView->SetWindowPos(NULL, 0, 0, cx, cy, SWP_NOZORDER);
	}
}


void CDockFormViewFile::UpdateImgListCtrl(CString strPath)
{
	if (m_pMyFormView){
		m_pMyFormView->UpdateImgListCtrl(strPath);
	}
}