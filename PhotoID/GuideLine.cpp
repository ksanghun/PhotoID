#include "stdafx.h"
#include "GuideLine.h"


CGuideLine::CGuideLine()
{
}


CGuideLine::~CGuideLine()
{
}

void CGuideLine::DrawLine()
{
	glVertex2f(m_sDPnt.x, m_sDPnt.y);
	glVertex2f(m_eDPnt.x, m_eDPnt.y);
}