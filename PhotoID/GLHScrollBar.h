#pragma once

#include "math_tool.h"

class CGLHScrollBar
{
public:
	CGLHScrollBar();
	~CGLHScrollBar();

	void SetSize(int x1, int y1, int x2, int y2);
	void SetRange(float _fmin, float _fmax, float _fStep);
	void SetValue(float _value);

	float GetValue() { return m_fValue; }
	void Draw();

private:

	void DrawBg();
	void DrawValue();
	POINT3D convertPosByValue(float _value);

	
	float m_fMinRange, m_fMaxRange;
	float m_fScale;
	float m_fValue;
	float m_fStep;
	int m_numStep;
	POINT3D m_vRect[4];

	POINT3D m_vPosValue, m_vPosZero;

};

