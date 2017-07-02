#pragma once

#include "math_tool.h"

enum LINETYPES { _FACEBOTTOM, _FACECENTER, _FACETOP, _VERTICENTER};

class CGuideLine
{
public:
	CGuideLine();
	~CGuideLine();

	void SetStartPnt(float _x, float _y, float _z) { m_sPnt.x = _x, m_sPnt.y = _y; }
	void SetEndPnt(float _x, float _y, float _z) { m_ePnt.x = _x, m_ePnt.y = _y; }
	POINT2D GetStartPnt() { return m_sPnt; }
	POINT2D GetEndPnt() { return m_ePnt; }


	void SetDrawStartPnt(float _x, float _y) { m_sDPnt.x = _x, m_sDPnt.y = _y; }
	void SetDrawEndPnt(float _x, float _y) { m_eDPnt.x = _x, m_eDPnt.y = _y; }

	void DrawLine();
	void DrawButtions();
	void Init(float _r, float _g, float _b, int _size, int _type);

private:
	POINT2D m_sPnt, m_ePnt;
	POINT2D m_sDPnt, m_eDPnt;
	POINT2D m_increment;

	POINT3D m_color;
	POINT2D m_vecButton[4];

};

