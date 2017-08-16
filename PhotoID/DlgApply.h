#pragma once


// CDlgApply dialog

class CDlgApply : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgApply)

public:
	CDlgApply(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDlgApply();

// Dialog Data
	enum { IDD = IDD_DIALOG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
};
