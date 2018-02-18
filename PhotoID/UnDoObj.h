#pragma once

#include "opencv/cv.h"
#include "opencv2\core\core.hpp"

#define _NUM_OF_UNDO 100

class CUnDoObj
{
public:
	CUnDoObj();
	~CUnDoObj();

	void PushUndo(IplImage* pImg);
	void PopUndo();
	IplImage* GetUndoImg();

	void InitUnDoImg();
	int GetCurId(){ return m_curId; }

private:
	IplImage* m_ImgUndo[_NUM_OF_UNDO];
	int m_curId;
};

