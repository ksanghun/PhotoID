#pragma once
#include "opencv/cv.h"
#include "opencv2\core\core.hpp"
#include "opencv2\highgui\highgui.hpp"
#include "opencv2/objdetect/objdetect.hpp"
#include "opencv2/imgproc/imgproc.hpp"

#include "math_tool.h"

enum _FACEPOS { _EYE_CENTER, _LEFT_EYE, _RIGHT_EYE, _TOP_EYE, _BOTTOM_EYE, _LIP, _NOSE, _TOPHEAD, _CHIN };
#define _LNADMARK_POS_NUM 9
class CSNImage
{
public:
	CSNImage();
	~CSNImage();

	void SetName(CString _strpath, CString _strpname, CString _strname, unsigned long _pcode, unsigned long _nCode);
	void SetSize(unsigned short _w, unsigned short _h, float _size);
	void SetThTex(GLuint _thtex);
	void SetTexId(GLuint _texid);
	void SetTex(GLuint _tex);
	void SetPosition(POINT3D pos);
	void SetSelecttion(bool _isSel);
	void SetImgSize(unsigned short _w, unsigned long _h) { nImgWidth = _w; nImgHeight = _h; };
	void SetImgDrawAngle(float _angle) { m_fImgDrawAngle = _angle; }
//	void SetBgColor(float r, float g, float b);

	void DrawThumbNail(float fAlpha);
	void DrawForPicking();
	void DrawImage(float fAlpha);
	void DrawBMPText();

	bool AddMatchedPoint(_MATCHInfo info, int search_size);

	GLuint GetTexId() { return texId; };
	GLuint GetTxTex() { return thTexId; };
	CString GetPath() { return strPath; };
	unsigned short GetWidth() { return nWidth; };
	unsigned short GetHeight() { return nHeight; };
	POINT3D GetPos() { return m_pos; };
	unsigned short GetImgWidth() { return nImgWidth; };
	unsigned short GetImgHeight() { return nImgHeight; };

	unsigned long GetCode() { return nCode;  }

	bool IsDuplicate(POINT3D pos, int search_size);
	float GetAratio() { return fARatio; };

	float GetImgWScale() { return m_imgWScale; };
	float GetImgHScale() { return m_imgHScale; };
	POINT3D GetLeftTop() { return m_pntLT; };


	void ClearMatchResult();


	// Image processing //
	void SetSrcIplImage(IplImage* pimg);
	IplImage* GetSrcIplImage() { return m_pSrcImg; }
	IplImage* GetSrcCopyIplImage() { return m_pSrcImgCopy; }
//	IplImage* GetSrcSmallIplImage() { return m_pSrcImgSmall; }
	void SetGLTexture(IplImage* pimg);
	void RotateImage(float _fAngle, int nWidth, int nHeight, bool IsRot, IplImage* pImg);
	void SetImageCenter(POINT3D _cpos) { m_vSrcImgCenter = _cpos; }
	void SetRotateionAngle(float _fangle); 
	void SetDetectScale(float _scale) { m_fImgDetectScale = _scale; }
	float GetImgAngle() { return m_fImgAngle; }
	float GetImgBrightness() { return m_fSrcBrightness; }
	float GetImgContraast() { return m_fSrcContrast; }

//	std::vector<_MATCHInfo>* GetMatchResult() { return &m_matched_pos; };
//	int GetResultSize() { return m_matched_pos.size(); }

	void RestoreGuidePos();

	POINT2D convertImageToScreenSpace(POINT2D pnt, int nWidth, int nHeight, bool IsScaled);
	POINT2D convertScreenToImageSpace(POINT2D pnt, int nWidth, int nHeight);

	
	void ChangeBrightness(IplImage* pSrc, IplImage* pDst, float _value);
	void ChangeConstrast(IplImage* pSrc, IplImage* pDst, float _value);
	void ChangeRotation(IplImage* pSrc, IplImage* pDst);


	POINT2D m_guidePosOri[_LNADMARK_POS_NUM];
	POINT2D m_guidePos[_LNADMARK_POS_NUM];
	POINT2D m_guidePosDraw[_LNADMARK_POS_NUM];

	POINT2D m_tmpV[4];
	POINT2D m_tmpVDraw[4];

private:
	CString strPath;
	CString strPName;
	CString strName;

	unsigned long parentCode;
	unsigned long nCode;

	unsigned short nWidth;
	unsigned short nHeight;
	float fARatio;

	GLuint thTexId, texId;

	float	m_fRectWidth;
	POINT3D m_pos;
	POINT3D m_vertex[4];
	POINT3D m_vertexBg[4];
	POINT2D m_texcoord[4];

	POINT3D m_vBgColor;
	bool	m_bIsSelected;


	unsigned short nImgWidth;
	unsigned short nImgHeight;

	int m_imgRectSize;

//	std::vector<_MATCHInfo> m_matched_pos;

	float m_fXScale, m_fYScale;
	float m_imgWScale;
	float m_imgHScale;
	POINT3D m_pntLT;

	IplImage *m_pSrcImg;
	IplImage *m_pSrcImgCopy;
//	IplImage *m_pSrcImgSmall;


	float m_fImgDeskewAngle, m_fSrcBrightness, m_fSrcContrast, m_fImgAngle;
	float m_fImgDrawAngle;
	POINT3D m_vSrcImgCenter;
	float m_fImgDetectScale;

	float m_matRot[6];


};

