#include "stdafx.h"
#include "GLHScrollBar.h"

#define _SCALE_WIDTH 30

CGLHScrollBar::CGLHScrollBar()
{
//	m_BASE_RANGE = 180;
}


CGLHScrollBar::~CGLHScrollBar()
{
}

void CGLHScrollBar::SetSize(int x1, int y1, int x2, int y2)
{
	mtSetPoint3D(&m_vRect[0], x1, y1, 0.0f);
	mtSetPoint3D(&m_vRect[1], x2, y1, 0.0f);
	mtSetPoint3D(&m_vRect[2], x2, y2, 0.0f);
	mtSetPoint3D(&m_vRect[3], x1, y2, 0.0f);

	if ((y2 - y1) != 0){
		m_fScale = static_cast<float>(y2 - y1) / (m_fMaxRange - m_fMinRange);
	}	

	m_vPosZero.x = x1;
	m_vPosZero.y = (y2 + y1)*0.5f;
	m_vPosZero.z = 0;

}

POINT3D CGLHScrollBar::convertPosByValue(float _value)
{
	POINT3D pos;
	float rValue = _value - m_fMinRange;

	pos.x = 0;
	pos.y = rValue*m_fScale;
	pos.z = 0;

	return pos;
}

void CGLHScrollBar::SetRange(float _fmin, float _fmax, float _fstep)
{
	m_fMaxRange = _fmax;
	m_fMinRange = _fmin;
	m_fStep = _fstep;

	if (m_fStep > 0){
		m_numStep = (m_fMaxRange - m_fMinRange) / m_fStep;
	}

	
}

void CGLHScrollBar::SetValue(float _value)
{
	m_fValue = _value;
}

void CGLHScrollBar::DrawBg()
{
	glColor4f(1.0f, 1.0f, 1.0f, 0.4f);
	glBegin(GL_QUADS);
	glVertex3f(m_vRect[0].x, m_vRect[0].y, m_vRect[0].z);
	glVertex3f(m_vRect[1].x, m_vRect[1].y, m_vRect[0].z);
	glVertex3f(m_vRect[2].x, m_vRect[2].y, m_vRect[0].z);
	glVertex3f(m_vRect[3].x, m_vRect[3].y, m_vRect[0].z);
	glEnd();

	glColor4f(0.0f, 0.0f, 0.0f, 0.3f);
	glBegin(GL_LINE_STRIP);
	glVertex3f(m_vRect[0].x, m_vRect[0].y, m_vRect[0].z);
	glVertex3f(m_vRect[1].x, m_vRect[1].y, m_vRect[0].z);
	glVertex3f(m_vRect[2].x, m_vRect[2].y, m_vRect[0].z);
	glVertex3f(m_vRect[3].x, m_vRect[3].y, m_vRect[0].z);
	glVertex3f(m_vRect[0].x, m_vRect[0].y, m_vRect[0].z);
	glEnd();


	// Draw grid //


	POINT3D p1, p2;
	p1 = m_vRect[0];
	p2 = m_vRect[1];	p2.x -= 20;

	p1.y += m_fStep*m_fScale;
	p2.y += m_fStep*m_fScale;

	glColor4f(0.0f, 0.0f, 0.0f, 0.9f);
	glBegin(GL_LINES);
	for (int i = 1; i < m_numStep; i++){
		glVertex3f(p1.x, p1.y, p1.z);
		glVertex3f(p2.x, p2.y, p2.z);

		p1.y += m_fStep*m_fScale;
		p2.y += m_fStep*m_fScale;
	}

	glColor4f(1.0f, 0.0f, 0.0f, 0.9f);
	glVertex3f(m_vPosZero.x, m_vPosZero.y, m_vPosZero.z);
	glVertex3f(m_vPosZero.x + _SCALE_WIDTH, m_vPosZero.y, m_vPosZero.z);

	glEnd();



}

void CGLHScrollBar::Draw()
{
	DrawBg();
}