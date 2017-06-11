// ImgList.cpp : implementation file
//

#include "stdafx.h"
#include "PhotoID.h"
#include "ImgList.h"


// CImgList

IMPLEMENT_DYNAMIC(CImgList, CListCtrl)

CImgList::CImgList()
{

}

CImgList::~CImgList()
{
}


BEGIN_MESSAGE_MAP(CImgList, CListCtrl)
END_MESSAGE_MAP()



// CImgList message handlers

void CImgList::UpdateImgListCtrl(CString strPath)
{
	DeleteAllItems();

	CFileFind finder;
	BOOL bWorking = finder.FindFile(strPath);
	while (bWorking){
		bWorking = finder.FindNextFile();
		if (finder.IsDots()) continue;

		InsertItem(1, finder.GetFileName());
	}

}


