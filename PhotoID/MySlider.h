#pragma once


// CMySlider

class CMySlider : public CSliderCtrl
{
	DECLARE_DYNAMIC(CMySlider)

public:
	CMySlider();
	virtual ~CMySlider();

private:
	float m_prePos;

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
};


