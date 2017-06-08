#pragma once
#include "OGLWnd.h"

#include "opencv/cv.h"
#include "opencv2\core\core.hpp"
#include "opencv2\highgui\highgui.hpp"
#include "opencv2/objdetect/objdetect.hpp"
#include "opencv2/imgproc/imgproc.hpp"

#include <dlib/opencv.h>
#include <dlib/image_processing/frontal_face_detector.h>
#include <dlib/image_processing/render_face_detections.h>
#include <dlib/image_processing.h>
#include <dlib/gui_widgets.h>
#include <dlib/image_io.h>

#include "SNImage.h"


enum _RENDERMODE { _BYGROUP = 0, _BYORDER };
enum _PICKMODE { _PICK_SELECT=0 };
#define SEL_BUFF_SIZE 1024

class CViewTree;

typedef std::vector<CSNImage*> _vecSNImage;


class CImageView :
	public COGLWnd
{
public:
	CImageView();
	~CImageView();

	void Render();
	void Render2D();
	void InitGLview(int _nWidth, int _nHeight);
	void MouseWheel(short zDelta);

	bool LoadSNImage(CString strPath, CSNImage* pInfo);
	GLuint LoadSNImage(CString strPath);

	void ReleaseImageData();
	CBitmap* GetLogCBitmap(CString strFile);


private:

	int m_maxTextureSize;

	CPoint m_mousedown;
	CPoint m_preMmousedown;
	short m_mouseMode;

	POINT3D m_lookAt;
	LOGFONT		m_LogFont;
	BITMAPINFO* m_pBmpInfo;

	int			m_nWidth;
	int			m_nHeight;



	float m_left, m_right, m_bottom, m_top;

	// Image Data Set //
	CSNImage* m_pPhotoImg;

	float	m_iconSize;
	float	m_fScreenScale;
	void ReSizeIcon();

	int select_object_2d(int x, int y, int rect_width, int rect_height, _PICKMODE _mode);
	bool process_select(GLuint* index, int hit_num, int selmode);
	void ResetIconTextureId();
	void GenerateThumbnail();
	POINT3D convertScreenToImageSpace(POINT3D pnt);
	POINT3D convertImageToScreenSpace(POINT3D pnt);

	POINT3D GetColor(float fvalue);
	POINT3D m_result_color[10];

	bool FaceDetection(IplImage* pImg);
	void SetPhotoIDimg(CString strPath);

	dlib::shape_predictor m_sp;
	std::vector<POINT3D> m_faceLandmark;
	std::vector<POINT3D> m_faceLandmarkDraw;

	float m_fXScale, m_fYScale;
	CString m_strMousePos;

	POINT3D m_PosRightEye;
	POINT3D m_PosLeftEye;

	float m_yPosEye;
	float m_yPosLip;
	float m_yPosBottom;
	float m_yPosTop;
	float m_yPosNose;


public:
	DECLARE_MESSAGE_MAP()
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);

	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnDropFiles(HDROP hDropInfo);
};
