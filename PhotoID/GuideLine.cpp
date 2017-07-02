#include "stdafx.h"
#include "GuideLine.h"

CGuideLine::CGuideLine()
{
	mtSetPoint2D(&m_increment, 0, 0);
	mtSetPoint2D(&m_sPnt, 0, 0);
	mtSetPoint2D(&m_ePnt, 0, 0);
	mtSetPoint2D(&m_sDPnt, 0, 0);
	mtSetPoint2D(&m_eDPnt, 0, 0);

}


CGuideLine::~CGuideLine()
{
}

void CGuideLine::Init(float _r, float _g, float _b, int _size, int _type)
{
	mtSetPoint3D(&m_color, _r, _g, _b);


	if (_type == 0){ // horizental bar
		mtSetPoint2D(&m_vecButton[0], -_size, _size*0.5f);
		mtSetPoint2D(&m_vecButton[1], -_size, -_size*0.5f);
		mtSetPoint2D(&m_vecButton[2], -0, 0);
	//	mtSetPoint2D(&m_vecButton[3], -0, _size*0.5f);
	}
	else{		// vertical bar
		mtSetPoint2D(&m_vecButton[0], _size*0.5f, _size);
		mtSetPoint2D(&m_vecButton[1], -_size*0.5f, _size);
		mtSetPoint2D(&m_vecButton[2], 0.0f, 0.0f);
	//	mtSetPoint2D(&m_vecButton[3], _size*0.5f, _size);

	}

	
}

void CGuideLine::DrawLine()
{
	glVertex2f(m_sDPnt.x+m_increment.x, m_sDPnt.y+m_increment.y);
	glVertex2f(m_eDPnt.x+m_increment.x, m_eDPnt.y+m_increment.y);
}

void CGuideLine::DrawButtions()
{
	glPushMatrix();
	glTranslatef(m_sDPnt.x + m_increment.x, m_sDPnt.y + m_increment.y, 0.0f);

	glColor3f(1, 1, 0);
	glBegin(GL_TRIANGLES);

	glVertex2f(m_vecButton[0].x, m_vecButton[0].y);
	glVertex2f(m_vecButton[1].x, m_vecButton[1].y);
	glVertex2f(m_vecButton[2].x, m_vecButton[2].y);
//	glVertex2f(m_vecButton[3].x, m_vecButton[3].y);

	glEnd();


	glColor3f(0, 0, 0);
	glBegin(GL_LINE_STRIP);
	glVertex2f(m_vecButton[0].x, m_vecButton[0].y);
	glVertex2f(m_vecButton[1].x, m_vecButton[1].y);
	glVertex2f(m_vecButton[2].x, m_vecButton[2].y);
	glVertex2f(m_vecButton[0].x, m_vecButton[0].y);
	glEnd();

	glPopMatrix();

}