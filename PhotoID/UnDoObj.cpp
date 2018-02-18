#include "stdafx.h"
#include "UnDoObj.h"


CUnDoObj::CUnDoObj()
{
	m_curId = 0;
	for (auto i = 0; i < _NUM_OF_UNDO; i++){
		m_ImgUndo[i] = nullptr;
	}
}


CUnDoObj::~CUnDoObj()
{
}

void CUnDoObj::InitUnDoImg()
{
	for (auto i = 0; i < m_curId; i++){
		if (m_ImgUndo[i]){
			cvReleaseImage(&m_ImgUndo[i]);
			m_ImgUndo[i] = nullptr;
		}
	}

	m_curId = 0;
}

void CUnDoObj::PushUndo(IplImage* pImg)
{
	if (m_curId < _NUM_OF_UNDO){
		m_ImgUndo[m_curId] = cvCloneImage(pImg);
		m_curId++;
	}

}
void CUnDoObj::PopUndo()
{
	if (m_curId > 0){
		if (m_ImgUndo[m_curId - 1]){
			cvReleaseImage(&m_ImgUndo[m_curId - 1]);
			m_ImgUndo[m_curId - 1] = nullptr;
			m_curId--;
		}
	}
}
IplImage* CUnDoObj::GetUndoImg()
{
	if (m_curId > 0){
		return m_ImgUndo[m_curId-1];
	}
	return nullptr;
}