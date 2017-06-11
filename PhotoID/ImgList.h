#pragma once


// CImgList

class CImgList : public CListCtrl
{
	DECLARE_DYNAMIC(CImgList)

public:
	CImgList();
	virtual ~CImgList();

	void UpdateImgListCtrl(CString strPath);

protected:
	DECLARE_MESSAGE_MAP()
};


