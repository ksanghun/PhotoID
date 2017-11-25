// Sanghun Kim //

#include "stdafx.h"
#include "ImageView.h"
#include "resource.h"
#include "ViewTree.h"
#include "MainFrm.h"
#include "PhotoIDView.h"




enum TIMEREVNT { _RENDER=100, _ADDIMG , _SEARCHIMG, _UPDATE_IMAGE};
#define _MIN_ICON_SIZE 16
#define FACE_DETECT_SIZE 100
#define _PI 3.1414529

using namespace cv;


CImageView::CImageView()
{
	memset(&m_LogFont, 0, sizeof(m_LogFont));
//	strcpy((char*)m_LogFont.lfFaceName, ("Arial"));
	m_LogFont.lfCharSet = ANSI_CHARSET;
	m_LogFont.lfHeight = -14;
	m_LogFont.lfWidth = 0;
	//	m_LogFont.lfWeight = FW_BOLD;
	

	memset(&m_LogFontBig, 0, sizeof(m_LogFontBig));
	//	strcpy((char*)m_LogFont.lfFaceName, ("Arial"));
	m_LogFontBig.lfCharSet = ANSI_CHARSET;
	m_LogFontBig.lfHeight = -12;
	m_LogFontBig.lfWidth = 0;
	//m_LogFont.lfWeight = FW_BOLD;


	m_pBmpInfo = (BITMAPINFO *)malloc(sizeof(BITMAPINFOHEADER) + (sizeof(RGBQUAD) * 256));


	m_nWidth = 0;
	m_nHeight = 0;


//	m_dragOper.init();
	m_mouseMode = 0;

	m_iFrameCnt = 0;


//	m_bNeedPrepare = false;

	m_left = m_right = m_bottom = m_top =0.0f;


	m_iconSize = 100.0f;
//	m_fScreenScale = 2.5f;
	m_fScreenScale = 1.0f;

//	m_fMoveSpeed = 0.0f;
//	m_bIconMode = false;

//	m_renderMode = _BYGROUP;
//	m_pCurrSelImg = NULL;


	mtSetPoint3D(&m_result_color[9], 1.0f, 0.0f, 0.0f);
	mtSetPoint3D(&m_result_color[8], 1.0f, 0.2f, 0.0f);
	mtSetPoint3D(&m_result_color[7], 1.0f, 0.4f, 0.0f);
	mtSetPoint3D(&m_result_color[6], 1.0f, 0.6f, 0.0f);
	mtSetPoint3D(&m_result_color[5], 1.0f, 0.8f, 0.0f);
	mtSetPoint3D(&m_result_color[4], 1.0f, 1.0f, 0.0f);
	mtSetPoint3D(&m_result_color[3], 0.8f, 1.0f, 0.0f);
	mtSetPoint3D(&m_result_color[2], 0.6f, 1.0f, 0.0f);
	mtSetPoint3D(&m_result_color[1], 0.4f, 1.0f, 0.0f);
	mtSetPoint3D(&m_result_color[0], 0.2f, 1.0f, 0.0f);


	m_pPhotoImg = NULL;
	m_bIsThreadEnd = false;
	m_fImgDetectScale = 1.0f;

	m_fDeSkewAngle = 0.0f;

//	m_faceLandmarkDraw = NULL;

	
	m_selButtonId = -1;

	
	// Init Mouse Circle Cursor //
	float rad = 1.0f;
	float angleStep = 2.0f*3.141529f/36.0f;
	for (int i = 0; i < 36; i++){
		m_vecCircle[i].x = rad*cos(angleStep*i);
		m_vecCircle[i].y = rad*sin(angleStep*i);
		m_vecCircle[i].z = 0;
	}


	m_bBlurMode = false;
	m_bStampMode = false;
	m_cursorSize = 0;

}


CImageView::~CImageView()
{
//	wglMakeCurrent(m_CDCPtr->GetSafeHdc(), m_hRC);


	//std::map<unsigned long, CSNImage*>::iterator iter = m_mapImageData.begin();
	//for (; iter != m_mapImageData.end(); iter++){

	//	GLuint tex = iter->second->GetTxTex();
	//	glDeleteTextures(1, &tex);
	//	delete iter->second;
	//}

	m_faceLandmark.clear();
//	m_faceLandmarkDraw.clear();

	//if (m_faceLandmarkDraw != NULL){
	//	delete[] m_faceLandmarkDraw;
	//	m_faceLandmarkDraw = NULL;
	//}


	delete m_pBmpInfo;
	ReleaseImageData();

}

BEGIN_MESSAGE_MAP(CImageView, COGLWnd)
	ON_WM_SIZE()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_ERASEBKGND()
	ON_WM_TIMER()
	ON_WM_LBUTTONDOWN()
	ON_WM_KEYDOWN()
	ON_WM_LBUTTONDBLCLK()
	ON_WM_DROPFILES()
	ON_WM_NCDESTROY()
	ON_WM_RBUTTONDOWN()
END_MESSAGE_MAP()



void CImageView::ReleaseImageData()
{
	//std::map<unsigned long, CSNImage*> m_mapImageData;
	//std::map<unsigned long, _vecSNImage> m_mapGrupImg;
	//_vecSNImage m_vecImageData;

	if (m_pPhotoImg){
	//	GLuint texid = m_pPhotoImg->GetTexId();
	//	if (texid != 0)	glDeleteTextures(1, &texid);
		delete m_pPhotoImg;
		m_pPhotoImg = NULL;
	}

	//for (int i = 0; i < m_vecImageData.size(); i++){
	//	GLuint texid = m_vecImageData[i]->GetTexId();
	//	if (texid != 0)	glDeleteTextures(1, &texid);
	//	GLuint thtex = m_vecImageData[i]->GetTxTex();
	//	if (thtex != 0) glDeleteTextures(1, &thtex);

	//	delete m_vecImageData[i];
	//	m_vecImageData[i] = NULL;
	//}
	//
	//std::map<unsigned long, _vecSNImage>::iterator iter_gr = m_mapGrupImg.begin();
	//for (; iter_gr != m_mapGrupImg.end(); iter_gr++){
	//	iter_gr->second.clear();
	//}

	//m_vecImageData.clear();
	//m_mapImageData.clear();
	//m_mapGrupImg.clear();
	//m_addCnt = 0;

	//CMainFrame* pM = (CMainFrame*)AfxGetMainWnd();
	//pM->AddOutputString(_T("Clear All Images.."));

//	m_centerx = m_nWidth*0.5f;
//	m_centery = m_nHeight*0.5f;
	
}


void CImageView::ResetIconTextureId()
{
}

void CImageView::DrawCircle(POINT2D pos, float fScale)
{
	glPushMatrix();
//	
	glTranslatef(pos.x, m_nHeight-pos.y, 0.0f);
	glScalef(fScale, fScale, fScale);	

	glBegin(GL_LINE_STRIP);
	for (int i = 0; i < 36; i++){
		glVertex3f(m_vecCircle[i].x, m_vecCircle[i].y, 0.0f);
	}
	glVertex3f(m_vecCircle[0].x, m_vecCircle[0].y, 0.0f);
	glEnd();

	glPopMatrix();
}

void CImageView::Render()
{
	wglMakeCurrent(m_CDCPtr->GetSafeHdc(), m_hRC);

	glClearColor(0.7f, 0.7f, 0.7f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	gl_PushOrtho(m_left, m_right, m_bottom, m_top);
	Render2D();

//	RenderMenu();
	gl_PopOrtho();

	SwapBuffers(m_CDCPtr->GetSafeHdc());
}

void CImageView::RenderMenu()
{
	glDisable(GL_DEPTH_TEST);

	m_glHScrollBar.Draw();

	//float fMargin = 32.0f;
	//glColor4f(1.0f, 1.0f, 1.0f, 0.4f);
	//glBegin(GL_QUADS);
	//glVertex3f(m_right - fMargin, m_top - fMargin, 0.0f);
	//glVertex3f(m_right - fMargin, m_bottom + fMargin, 0.0f);
	//glVertex3f(m_right- 10.0f, m_bottom + fMargin, 0.0f);
	//glVertex3f(m_right- 10.0f, m_top - fMargin, 0.0f);
	//glEnd();

	//glColor4f(0.0f, 0.0f, 0.0f, 0.3f);
	//glBegin(GL_LINE_STRIP);
	//glVertex3f(m_right - fMargin, m_top - fMargin, 0.0f);
	//glVertex3f(m_right - fMargin, m_bottom + fMargin, 0.0f);
	//glVertex3f(m_right - 10.0f, m_bottom + fMargin, 0.0f);
	//glVertex3f(m_right - 10.0f, m_top - fMargin, 0.0f);
	//glVertex3f(m_right - fMargin, m_top - fMargin, 0.0f);
	//glEnd();
	

	glEnable(GL_DEPTH_TEST);
}


void CImageView::DrawDebugInfo()
{

	if (m_pPhotoImg->GetSrcIplImage()){
		glColor3f(0.0f, 0.0f, 1.0f);

		CString strDebug;
		POINT3D pos;
		mtSetPoint3D(&pos, 10.0f, m_nHeight - 50, 0.0f);
		gl_DrawText(pos, m_strMousePos, m_LogFont, 2, m_pBmpInfo, m_CDCPtr);

		// Image Angle Info ==//
		pos.y += 20;
		strDebug.Format(L"Rotation Angle: %3.1f degree", m_pPhotoImg->GetImgAngle());
		gl_DrawText(pos, strDebug, m_LogFont, 2, m_pBmpInfo, m_CDCPtr);
	}


}

void CImageView::Render2D()
{
	//int pointSize = m_iconSize / 100;
	//if (pointSize < 4)
	//	pointSize = 4;


	
	glPointSize(5);

	if (m_bIsThreadEnd == false){
		glClearColor(0.7f, 0.7f, 0.7f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		if ((m_iFrameCnt / 5) % 2 == 0){
			glColor3f(0.99f, 0.99f, 0.2f);
		}
		else{
			glColor3f(0.0f, 0.0f, 0.0f);
		}
		POINT3D pos;
		mtSetPoint3D(&pos, m_nWidth*0.5f, m_nHeight*0.5f, 0);
		gl_DrawText(pos, L"Initializing...", m_LogFontBig, 1, m_pBmpInfo, m_CDCPtr);
	}



	if (m_pPhotoImg){
		m_pPhotoImg->DrawThumbNail(1.0f);

		if (m_pPhotoImg->IsCropImage() == false){
			DrawCropArea();


			glLineWidth(2.0f);
			glColor3f(0.0f, 1.0f, 0.0f);
			//glBegin(GL_POINTS);
			//for (int i = 0; i < m_faceLandmarkDraw.size(); i++){
			//	glVertex3f(m_faceLandmarkDraw[i].x, m_faceLandmarkDraw[i].y, m_faceLandmarkDraw[i].z);
			//}
			//glEnd();


			//glBegin(GL_LINES);

			glLineStipple(2, 0xAAAA);
			glEnable(GL_LINE_STIPPLE);
			glBegin(GL_LINES);
			for (int i = 0; i < 4; i++){
				m_guideLine[i].DrawLine();
			}
			glEnd();

			// Image Cross Line ==============================//
			glColor3f(1.0f, 0.0f, 0.0f);
			glBegin(GL_LINES);

			glVertex3f(m_guidePosDraw[_LEFT_EYE].x, m_guidePosDraw[_LEFT_EYE].y, 0.0f);
			glVertex3f(m_guidePosDraw[_RIGHT_EYE].x, m_guidePosDraw[_RIGHT_EYE].y, 0.0f);

			glVertex3f(m_guidePosDraw[_TOP_EYE].x, m_guidePosDraw[_TOP_EYE].y, 0.0f);
			glVertex3f(m_guidePosDraw[_BOTTOM_EYE].x, m_guidePosDraw[_BOTTOM_EYE].y, 0.0f);
			glEnd();
			//==================================================

			glDisable(GL_LINE_STIPPLE);
			glLineWidth(1.0f);

			glColor3f(1.0f, 0.0f, 0.0f);
			glBegin(GL_POINTS);
			glVertex3f(m_guidePosDraw[_FCENTER].x, m_guidePosDraw[_FCENTER].y, 0.0f);
			glEnd();


			glEnable(GL_TEXTURE_2D);
			for (int i = 0; i < 4; i++){
				if (i == m_selButtonId){
					m_guideLine[i].DrawButtions(0.99f, 0.99f, 0.99f);
				}
				else{
					m_guideLine[i].DrawButtions(0.8f, 0.8f, 0.8f);
				}
			}
			glDisable(GL_TEXTURE_2D);

			//glPointSize(10);
			//glBegin(GL_LINE_STRIP);

			//for (int i = 0; i < 4; i++){
			//	glVertex3f(m_pPhotoImg->m_tmpVDraw[i].x, m_pPhotoImg->m_tmpVDraw[i].y, 0.0f);
			//}
			//glVertex3f(m_pPhotoImg->m_tmpVDraw[0].x, m_pPhotoImg->m_tmpVDraw[0].y, 0.0f);

			//glEnd();
			//		glPopAttrib();
			
			glPointSize(1.0f);
		}


		else{
			DrawDebugInfo();

			if (m_bBlurMode){
				glColor4f(0.0f, 0.0f, 1.0f, 0.5f);
				DrawCircle(m_curPos, m_cursorSizeForDisp);
			}

			if (m_bStampMode){
				POINT3D tPos;
				mtSetPoint3D(&tPos, m_curPos.x, m_nHeight - m_curPos.y, 0.0f);
				
				if (m_bStampCopied){
					glColor4f(1.0f, 0.0f, 0.0f, 0.5f);
					gl_DrawText(tPos, L"Stamp", m_LogFontBig, 1, m_pBmpInfo, m_CDCPtr);
				}
				else{
					glColor4f(0.0f, 0.0f, 1.0f, 0.5f);
					gl_DrawText(tPos, L"Copy", m_LogFontBig, 1, m_pBmpInfo, m_CDCPtr);
				}				
				
				DrawCircle(m_curPos, m_cursorSizeForDisp);
			}
		}

	}
}


void CImageView::InitGLview(int _nWidth, int _nHeight)
{
	m_nWidth = _nWidth;
	m_nHeight = _nHeight;

	mtSetPoint3D(&m_lookAt, 0.0f, 0.0f, 0.0f);

	m_cameraPri.InitializeCamera(30.0f, 0.0f, 0.0f, m_lookAt, _nWidth, _nHeight);
	m_cameraPri.SetInitLevelHeight(1000);

	glDisable(GL_LIGHTING);
	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);

	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);


	glEnable(GL_POINT_SMOOTH);
	glEnable(GL_LINE_SMOOTH);


	//SetClassLong(m_hWnd,
	//	GCL_HCURSOR,
	//	(LONG)LoadCursor(AfxGetInstanceHandle(),
	//	MAKEINTRESOURCE(IDC_CURSOR1)));


//	CMainFrame* pM = (CMainFrame*)AfxGetMainWnd();
//	SetTreeDragItem(pM->GetViewFiewCtrl()->GetImageList(), pM->GetViewFiewCtrl()->GetRootItem(), pM->GetViewFiewCtrl()->GetTreeViewCtrl());
	
		

	DragAcceptFiles();

	glGetIntegerv(GL_MAX_TEXTURE_SIZE, &m_maxTextureSize); 

	
	//m_bIsThreadEnd = true;
	//BeginWaitCursor();
	//ThreadFaceDataLoad();
	//EndWaitCursor();
	
		
	//m_bIsThreadEnd = false;
	//m_pThread = AfxBeginThread(MyThread, this);
	//m_pThread->m_bAutoDelete = FALSE;
	//m_pThread->ResumeThread();

	//m_bIsThreadEnd = true;
	CWinThread* pl;
	m_bIsThreadEnd = false;
	pl = AfxBeginThread(MyThread, this);

//	CloseHandle(pl);
		
	m_glHScrollBar.SetRange(-90.0f, 90.0f, 10.0f);
	m_glHScrollBar.SetValue(0);
	

	m_pPhotoImg = new CSNImage;

	m_guideLine[0].Init(0.0f, 1.0f, 0.0f, 30, 0);
	m_guideLine[1].Init(0.0f, 1.0f, 0.0f, 30, 0);
	m_guideLine[2].Init(0.0f, 1.0f, 0.0f, 30, 0);
	m_guideLine[3].Init(1.0f, 0.0f, 0.0f, 30, 1);

	GLuint tid = Load4ChannelImage("./data/arrow_green.tiff");
//	int tid = 0;
//	IplImage *pimg = cvLoadImage("./data/arrow_red.tiff", CV_LOAD_IMAGE_UNCHANGED);


	m_guideLine[0].SetButtonTexId(tid);
	m_guideLine[1].SetButtonTexId(tid);
	m_guideLine[2].SetButtonTexId(tid);

	tid = Load4ChannelImage("./data/arrow_red.tiff");
	m_guideLine[3].SetButtonTexId(tid);

	//===============================================//
	SetTimer(_RENDER, 50, NULL);
}

void CImageView::SetPhotoIDimg(CString strPath)
{
	CMainFrame* pM = (CMainFrame*)AfxGetMainWnd();
	if (m_bIsThreadEnd == true){
		m_fDeSkewAngle = 0.0f;
		m_pPhotoImg->SetRotateionAngle(m_fDeSkewAngle);
		pM->SetImageRotateValue(m_fDeSkewAngle);
		pM->SetSliderStatus(false);


		BeginWaitCursor();
		// Load Phto ID image=============================//
		//if (m_pPhotoImg){
		////	GLuint texid = m_pPhotoImg->GetTexId();
		////	if (texid != 0)	glDeleteTextures(1, &texid);
		//	delete m_pPhotoImg;
		//	m_pPhotoImg = NULL;
		//}

		//m_pPhotoImg = new CSNImage;
		POINT3D pos;
		mtSetPoint3D(&pos, 0, 0, 0);
		m_pPhotoImg->SetPosition(pos);
		LoadSNImage(strPath, m_pPhotoImg);
	//	m_pPhotoImg->SetRotateionAngle(m_fDeSkewAngle);

		m_iconSize = m_nWidth;
		ReSizeIcon();
	}



	
	
	if (m_pPhotoImg){		
	//	pM->SetImageRotateValue(m_fDeSkewAngle);
		//m_pPhotoImg->SetRotateionAngle(m_fDeSkewAngle);
		//RotateImage(0, true);

		//if ((m_fDeSkewAngle > 0.1f) || (m_fDeSkewAngle < 0.1f)){
		//	m_pPhotoImg->SetRotateionAngle(m_fDeSkewAngle);
		//	RotateImage(0, true);
		//}

		//m_pPhotoImg->SetRotateionAngle(m_fDeSkewAngle);
		
		//pM->SetImageRotateValue(m_fDeSkewAngle);
		ReSizeIcon();		
	}


	EndWaitCursor();
}

void CImageView::MouseWheel(short zDelta)
{
	wglMakeCurrent(m_CDCPtr->GetSafeHdc(), m_hRC);	

	//m_iconSize += zDelta*0.1f;
	//if (m_iconSize < _MIN_ICON_SIZE)
	//	m_iconSize = _MIN_ICON_SIZE;
	//if (m_iconSize > m_nWidth)
	//	m_iconSize = m_nWidth;

	ReSizeIcon();
}


void CImageView::ReSizeIcon()
{
	if (m_pPhotoImg){

		// Resize Image?? move this code!!//
		if (m_nWidth < m_nHeight)
			m_iconSize = m_nWidth;
		else
			m_iconSize = m_nHeight;
		//==============================//

		//m_iconSize *= 0.90f;

		m_pPhotoImg->SetSize(m_pPhotoImg->GetWidth(), m_pPhotoImg->GetHeight(), m_iconSize);
		POINT3D sPnt;
		sPnt.x = m_nWidth*0.5f;
		sPnt.y = m_nHeight*0.5f;
		sPnt.z = 0.0f;
		m_pPhotoImg->SetPosition(sPnt);

		//for (int i = 0; i < m_faceLandmark.size(); i++){
		//	m_faceLandmarkDraw[i] = m_pPhotoImg->convertImageToScreenSpace(m_faceLandmark[i], m_nWidth, m_nHeight, true);
		//}

		for (int i = 0; i < 4; i++){  // from 0 to eye top
			m_guidePosDraw[i] = m_pPhotoImg->convertImageToScreenSpace(m_pPhotoImg->m_guidePos[i], m_nWidth, m_nHeight, true);
		}

		// Boundary //
		for (int i = 0; i < 4; i++){
			m_vecOutBounderyDraw[i] = m_pPhotoImg->convertImageToScreenSpace(m_pPhotoImg->m_vecOutBoundery[i], m_nWidth, m_nHeight, true);
			m_vecInBounderyDraw[i] = m_pPhotoImg->convertImageToScreenSpace(m_pPhotoImg->m_vecInBoundery[i], m_nWidth, m_nHeight, true);
		}

		// Guide Lines =======================
		POINT2D tmpV;
		for (int i = 0; i < 4; i++){
			tmpV = m_pPhotoImg->convertImageToScreenSpace(m_guideLine[i].GetStartPnt(), m_nWidth, m_nHeight, true);
			m_guideLine[i].SetDrawStartPnt(tmpV.x, tmpV.y);

			tmpV = m_pPhotoImg->convertImageToScreenSpace(m_guideLine[i].GetEndPnt(), m_nWidth, m_nHeight, true);
			m_guideLine[i].SetDrawEndPnt(tmpV.x, tmpV.y);
		}

		SetCropArea();


		// Update Cursor Size ///
		POINT2D v1, v2;
		mtSetPoint2D(&v1, 0, 0);
		mtSetPoint2D(&v2, m_cursorSize*0.5f, 0);
		v1 = m_pPhotoImg->convertImageToScreenSpace(v1, m_nWidth, m_nHeight, false);
		v2 = m_pPhotoImg->convertImageToScreenSpace(v2, m_nWidth, m_nHeight, false);
		m_cursorSizeForDisp = v2.x - v1.x;

	}

	m_right = m_left + m_nWidth;
	m_top = m_bottom + m_nHeight;
	m_cameraPri.SetProjectionMatrix(30.0f, 0.0f, 0.0f, m_nWidth, m_nHeight);
//	m_cameraPri.SetModelViewMatrix(m_cameraPri.GetLookAt(), 0.0f, 0.0f);
}

void CImageView::OnSize(UINT nType, int cx, int cy)
{
	COGLWnd::OnSize(nType, cx, cy);

	// TODO: Add your message handler code here
	wglMakeCurrent(m_CDCPtr->GetSafeHdc(), m_hRC);
	m_nWidth = cx*m_fScreenScale;
	m_nHeight = cy*m_fScreenScale;

	//m_cx = cx;
	//m_cy = cy;
	
	

	

	m_glHScrollBar.SetSize(cx - 50, 50, cx - 20, cy - 50);

//	m_cameraPri.SetProjectionMatrix(30.0f, 0.0f, 0.0f, cx, cy);
//	m_cameraPri.SetModelViewMatrix(m_cameraPri.GetLookAt(), 0.0f, 0.0f);

	ReSizeIcon();
}

GLuint CImageView::Load4ChannelImage(char* sz)
{
	wglMakeCurrent(m_CDCPtr->GetSafeHdc(), m_hRC);
	GLuint nTexId = 0;
	//USES_CONVERSION;
	//char* sz = T2A(strPath);

	IplImage *pimg = cvLoadImage(sz, CV_LOAD_IMAGE_UNCHANGED);
	if (pimg){
		//	cvShowImage(sz, pimg);
		cvCvtColor(pimg, pimg, CV_BGRA2RGBA);

		// glupload Image - Thumnail image=======================================================//
		glGenTextures(1, &nTexId);
		glBindTexture(GL_TEXTURE_2D, nTexId);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);

		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, 0x812F);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, 0x812F);
		//glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
		//glTexImage2D(GL_TEXTURE_2D, 0, 4, m_texture->sizeX,m_texture->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE,m_texture->data);
		gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGBA, pimg->width, pimg->height, GL_RGBA, GL_UNSIGNED_BYTE, pimg->imageData);
		//glTexImage2D(GL_TEXTURE_2D,
		//	0,
		//	GL_RGBA,
		//	pimg->width,
		//	pimg->height,
		//	0,
		//	GL_RGBA,
		//	GL_UNSIGNED_BYTE,
		//	pimg->imageData
		//	);
		//======================================================================================//
		cvReleaseImage(&pimg);
	}
	return nTexId;
}


GLuint CImageView::LoadSNImage(CString strPath)
{
	wglMakeCurrent(m_CDCPtr->GetSafeHdc(), m_hRC);
	GLuint nTexId = 0;
	USES_CONVERSION;
	char* sz = T2A(strPath);

	IplImage *pimg = cvLoadImage(sz);
	if (pimg){
		//	cvShowImage(sz, pimg);
		cvCvtColor(pimg, pimg, CV_BGR2RGB);

		// glupload Image - Thumnail image=======================================================//
		glGenTextures(1, &nTexId);
		glBindTexture(GL_TEXTURE_2D, nTexId);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);

		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, 0x812F);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, 0x812F);
		//glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
		//glTexImage2D(GL_TEXTURE_2D, 0, 3, m_texture->sizeX,m_texture->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE,m_texture->data);
		gluBuild2DMipmaps(GL_TEXTURE_2D, 3, pimg->width, pimg->height, GL_RGB, GL_UNSIGNED_BYTE, pimg->imageData);
		//======================================================================================//
		cvReleaseImage(&pimg);
	}
	return nTexId;
}

bool CImageView::LoadSNImage(CString strPath, CSNImage* pInfo)
{
//	wglMakeCurrent(m_CDCPtr->GetSafeHdc(), m_hRC);
	USES_CONVERSION;
	char* sz = T2A(strPath);

	IplImage *pimg = cvLoadImage(sz);	
	if (pimg){

		IplImage* pImgrgb=cvCloneImage(pimg);
		cvCvtColor(pimg, pImgrgb, CV_BGR2RGB);
		cvReleaseImage(&pimg);


		pInfo->SetSrcIplImage(pImgrgb);
		pInfo->SetImgSize(pImgrgb->width, pImgrgb->height);
		pInfo->SetSize(pImgrgb->width, pImgrgb->height, m_iconSize);
		//pInfo->SetGLTexture();


		// glupload Image - Thumnail image=======================================================//
		//GLuint tid = 0;
		//glGenTextures(1, &tid);
		//glBindTexture(GL_TEXTURE_2D, tid);
		//glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		//glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);

		//glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, 0x812F);
		//glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, 0x812F);
		////glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
		////glTexImage2D(GL_TEXTURE_2D, 0, 3, m_texture->sizeX,m_texture->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE,m_texture->data);
		//gluBuild2DMipmaps(GL_TEXTURE_2D, 3, pImgrgb->width, pImgrgb->height, GL_RGB, GL_UNSIGNED_BYTE, pImgrgb->imageData);
		//======================================================================================//
	//	cvReleaseImage(&pImgrgb);


	//	pInfo->SetThTex(tid);
		FaceDetection(pImgrgb);
		return true;
	}
	else{
		return false;
	}
	
}


void CImageView::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	wglMakeCurrent(m_CDCPtr->GetSafeHdc(), m_hRC);


	if (GetCapture() && (m_selButtonId>-1)){
		ReleaseCapture();

		m_selButtonId = -1;
		//ReSizeIcon();

		//m_fMoveSpeed = point.y - m_preMmousedown.y;
	}

	COGLWnd::OnLButtonUp(nFlags, point);
}


void CImageView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	wglMakeCurrent(m_CDCPtr->GetSafeHdc(), m_hRC);



	if (m_pPhotoImg){
		POINT2D curPos;
		curPos.x = (float)point.x;
		curPos.y = (float)point.y;

		
		m_curPos = curPos;

		curPos = m_pPhotoImg->convertScreenToImageSpace(curPos, m_nWidth, m_nHeight);
		m_strMousePos.Format(_T("[%d, %d]"), (int)curPos.x, (int)curPos.y);

	//	m_curPos = m_pPhotoImg->convertImageToScreenSpace(curPos, m_nWidth, m_nHeight, true);
		
	}


	if (GetCapture()){
		float incre;

		switch (m_selButtonId){
		case 0:
		case 1:
		case 2:
			incre = (point.y - m_mousedown.y) / m_fImgDetectScale;
			m_guideLine[m_selButtonId].SetIncrement(0, incre);

			break;
		case 3:
			float s = m_pPhotoImg->GetImgWScale();
			incre = (point.x - m_mousedown.x) / m_fImgDetectScale;
			m_guideLine[m_selButtonId].SetIncrement(incre, 0);

			break;
		}

		//SetCropArea();
		ReSizeIcon();
		m_mousedown = point;

		//m_centerx -= (point.x - m_mousedown.x);
		//m_centery += (point.y - m_mousedown.y);
		//m_left = m_centerx - m_nWidth*0.5f;
		//m_right = m_centerx + m_nWidth*0.5f;
		//m_top = m_centery + m_nHeight*0.5f;
		//m_bottom = m_centery - m_nHeight*0.5f;


		//m_bottom += (point.y - m_mousedown.y)*m_fScreenScale;
		//if (m_bottom > 0.0f)
		//	m_bottom = 0.0f;
		//if (m_bottom < m_fDataLastPos)
		//	m_bottom = m_fDataLastPos;


		//// Set Wnd rect =======//
		//m_right = m_left + m_nWidth;
		//m_top = m_bottom + m_nHeight;

		//m_preMmousedown = m_mousedown;
		//m_mousedown = point;

		if ((point.x < 0) || (point.y < 0) || (point.x > m_nWidth) || (point.y > m_nHeight)){
			ReleaseCapture();
		}


		Render();
	}	

	COGLWnd::OnMouseMove(nFlags, point);
}


BOOL CImageView::OnEraseBkgnd(CDC* pDC)
{
	// TODO: Add your message handler code here and/or call default

	return COGLWnd::OnEraseBkgnd(pDC);
}


void CImageView::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: Add your message handler code here and/or call default
	if (nIDEvent == _RENDER){
		m_right = m_left + m_nWidth;
		m_top = m_bottom + m_nHeight;
		Render();
		
		if (m_bIsThreadEnd == false){
			m_iFrameCnt++;
		}
		//else{
		//	CloseHandle(g_pl);
		//}
	}


	if (nIDEvent == _ADDIMG){
		GenerateThumbnail();		
	}

	if (nIDEvent == _SEARCHIMG){

	}

	if (nIDEvent == _UPDATE_IMAGE){
		wglMakeCurrent(m_CDCPtr->GetSafeHdc(), m_hRC);
		SetCropArea();
		ReSizeIcon();
		Render();
		KillTimer(_UPDATE_IMAGE);
	}
	COGLWnd::OnTimer(nIDEvent);
}


POINT3D CImageView::GetColor(float fvalue)
{
	int idx = fvalue * 10;
	if (idx<0)
		idx = 0;
	if (idx>9)
		idx = 9;

	return m_result_color[idx];
}


void CImageView::GenerateThumbnail()
{
	//int cnt = 0;
	//for (; m_addCnt < m_vecImageData.size(); m_addCnt++){
	//	CSNImage* pImg = m_vecImageData[m_addCnt];
	//	LoadSNImage(pImg->GetPath(), pImg, 128);
	//	cnt++;
	//	if (cnt>10){
	//		break;
	//	}
	//}

	//if (m_addCnt >= m_vecImageData.size()){
	//	KillTimer(_ADDIMG);
	//}

	//m_bNeedPrepare = true;
	//float complete = (float)m_addCnt / (float)m_vecImageData.size();

	//CString str;
	//str.Format(_T("Generating thumbnails.....%d"), int(complete * 100));
	//str += _T("%");
	//str += _T(" completed.");

	//CMainFrame* pM = (CMainFrame*)AfxGetMainWnd();
	//pM->AddOutputString(str, true);
}



void CImageView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	wglMakeCurrent(m_CDCPtr->GetSafeHdc(), m_hRC);

	m_mousedown = point;
	m_preMmousedown = m_mousedown;
//	m_fMoveSpeed = 0.0f;
	SetCapture();

	if (select_object_2d(point.x, point.y, 2, 2, _PICK_SELECT) > 0){
		//if (m_pCurrSelImg != NULL){
		//	m_pCurrSelImg->SetSelecttion(false);
		//}
		//m_pCurrSelImg = GetSNImageByIndex((int)m_sellBuffer[3]);
		//m_pCurrSelImg->SetSelecttion(true);

		//m_centerx = m_pCurrSelImg->GetPos().x;
		//m_centery = m_pCurrSelImg->GetPos().y;
	}



	if (m_bBlurMode){
		if (m_pPhotoImg){
			POINT2D curPos = m_pPhotoImg->convertScreenToImageSpace(m_curPos, m_nWidth, m_nHeight);
			cv::Rect rect(curPos.x - m_cursorSize*0.5f, curPos.y - m_cursorSize*0.5f, m_cursorSize, m_cursorSize);
			m_pPhotoImg->BlurImage(rect, cv::Size(10, 10));
		}
	}

	if (m_bStampMode){
		POINT2D curPos = m_pPhotoImg->convertScreenToImageSpace(m_curPos, m_nWidth, m_nHeight);
		cv::Rect rect(curPos.x - m_cursorSize*0.5f, curPos.y - m_cursorSize*0.5f, m_cursorSize, m_cursorSize);

		if (m_bStampCopied == false){
			// Copy image
			//m_imgStampcut.release();
			//m_pPhotoImg->CpoyForStamp(rect, m_imgStampcut);
			m_rectForStamp = rect;
			m_bStampCopied = true;
		}
		else{
			// paste image
			m_pPhotoImg->StampImage(m_rectForStamp, rect, cv::Size(10, 10));
		}
	}
	
	//PrepareRender();
	//Render();
	COGLWnd::OnLButtonDown(nFlags, point);
}




int CImageView::select_object_2d(int x, int y, int rect_width, int rect_height, _PICKMODE _mode)
{
	m_selButtonId = -1;
	GLuint selectBuff[1024];
	memset(&selectBuff, 0, sizeof(GLuint) * SEL_BUFF_SIZE);

	GLint hits, viewport[4];
	hits = 0;

	glSelectBuffer(SEL_BUFF_SIZE, selectBuff);
	glGetIntegerv(GL_VIEWPORT, viewport);

	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glRenderMode(GL_SELECT);
	glLoadIdentity();
	gluPickMatrix(x, viewport[3] - y, rect_width, rect_height, viewport);
	gluOrtho2D(m_left, m_right, m_bottom, m_top);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	//======Render For Picking========//
//	switch (m_renderMode){
	//case _BYGROUP:
	//	DrawImageByGroupForPicking();
	//	break;
	//case _BYORDER:
	//	DrawImageByOrderForPicking();
	//	break;
	//}

	//glPushName(1000);
	//if (m_b_show_book_case == false)
	//	m_button[0]->DrawButton(0);		// open book case;
	//else
	//	m_button[0]->DrawButton(1);
	//glPopName();

	//for (int i = 1; i<m_button.size(); i++)
	//{
	//	glPushName(i + 1000);
	//	m_button[i]->DrawButton(0);
	//	glPopName();
	//}

	
	for (int i = 0; i < 4; i++){
		glPushName(i + 1000);
		m_guideLine[i].DrawButtions(1.0f, 1.0f, 1.0f);
		glPopName();
	}

	hits = glRenderMode(GL_RENDER);
	if (hits>0)
	{
		int selid = (int)selectBuff[3];
		m_selButtonId = selid - 1000;
	}
	//else
	//{
	//	if (selmode == 1)
	//	{

	//	}
	//}

	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	return hits;
}


bool CImageView::process_select(GLuint* index, int hit_num, int selmode)
{
	int selid = 0;
	for (int i = 0; i < hit_num; i++){
		selid = (int)index[i*4+3];
	}
	return true;
}




void CImageView::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	if (select_object_2d(point.x, point.y, 2, 2, _PICK_SELECT) > 0){
		//if (m_pCurrSelImg != NULL){
		//	m_pCurrSelImg->SetSelecttion(false);
		//}
		//m_pCurrSelImg = GetSNImageByIndex((int)m_sellBuffer[3]);
		//m_pCurrSelImg->SetSelecttion(true);	

		//pView->ShowCNSDlg(m_Threshold*100);
		//pView->SetDlgImagePath(m_pCurrSelImg->GetPath());
	}

	COGLWnd::OnLButtonDblClk(nFlags, point);
}



CBitmap* CImageView::GetLogCBitmap(CString strFile)
{
	IplImage* tmp = cvLoadImage((CStringA)strFile);	

	if (tmp){
		IplImage *img = cvCreateImage(cvSize(32, 32), tmp->depth, tmp->nChannels);
		cvResize(tmp, img);


		CDC dc;
		CDC memDC;

		CBitmap* newBmp = new CBitmap;
		CBitmap* pOldBmp;

		if (!dc.CreateDC(_T("DISPLAY"), NULL, NULL, NULL))
			return NULL;

		if (!memDC.CreateCompatibleDC(&dc))
			return NULL;

		int w, h;
		int nWidth = img->width;
		int nHeight = img->height;
		BYTE* pSrcBits = (BYTE *)img->imageData;
		BYTE* pBmpBits = (BYTE *)malloc(sizeof(BYTE)*nWidth*nHeight * 4);

		
		// IplImage에 저장된 값을 직접 읽어서 
		// 비트맵 데이터를 만듬 
		for (h = 0; h < nHeight; ++h)
		{
			BYTE* pSrc = pSrcBits + img->widthStep * h;
			BYTE* pDst = pBmpBits + nWidth * 4 * h;
			for (w = 0; w < nWidth; ++w)
			{
				*(pDst++) = *(pSrc++);
				*(pDst++) = *(pSrc++);
				*(pDst++) = *(pSrc++);
				*(pDst++) = 0;
			}
		}
		//		memDC.CreateCompatibleDC(pDC);
		newBmp->CreateCompatibleBitmap(&dc, nWidth, nHeight);
		// 위에서 만들어진 데이터를 가지고 
		// 비트맵을 만듬 
		newBmp->SetBitmapBits(nWidth*nHeight * 4, pBmpBits);
		pOldBmp = memDC.SelectObject(newBmp);


		memDC.SelectObject(pOldBmp);
		memDC.DeleteDC();
		dc.DeleteDC();

		free(pBmpBits);
		cvReleaseImage(&img);
		cvReleaseImage(&tmp);


		return newBmp;
	}
	else{
		return NULL;
	}
}

bool CImageView::FaceDetection(IplImage* pImg)
{
	Mat oimage, image;
	oimage = cvarrToMat(pImg);
	m_fImgDetectScale = (float)oimage.cols / 400.0f;
	if (m_fImgDetectScale < 1.0f)
		m_fImgDetectScale = 1.0f;

	int newSizeW = (float)oimage.cols / m_fImgDetectScale;
	int newSizeH = (float)oimage.rows / m_fImgDetectScale;


	

	if (m_pPhotoImg->GetSrcIplImage()){


		m_pPhotoImg->SetBoundary(newSizeW, newSizeH);
		//mtSetPoint2D(&m_pPhotoImg->m_tmpV[0], 0, 0);
		//mtSetPoint2D(&m_pPhotoImg->m_tmpV[1], newSizeW, 0);
		//mtSetPoint2D(&m_pPhotoImg->m_tmpV[2], newSizeW, newSizeH);
		//mtSetPoint2D(&m_pPhotoImg->m_tmpV[3], 0, newSizeH);

		m_pPhotoImg->SetBoundary(newSizeW, newSizeH);

		m_pPhotoImg->SetDetectScale(m_fImgDetectScale);



		resize(oimage, image, Size(newSizeW, newSizeH));

		dlib::frontal_face_detector detector = dlib::get_frontal_face_detector();


		dlib::cv_image<dlib::bgr_pixel> cimg(image);
		std::vector<dlib::rectangle> dets = detector(cimg);
		std::vector<dlib::full_object_detection> shapes;

		// Draw circles on the detected faces
		m_faceLandmark.clear();
		m_faceLandmarkDraw.clear();
		for (int i = 0; i < dets.size(); i++)
		{
			dlib::full_object_detection shape = m_sp(cimg, dets[i]);
			for (int j = 0; j < shape.num_parts(); j++){

				POINT2D pnt;
				mtSetPoint2D(&pnt, shape.part(j).x(), shape.part(j).y());
				m_faceLandmark.push_back(pnt);
				m_faceLandmarkDraw.push_back(pnt);
			}
		}


		for (int i = 0; i < _LNADMARK_POS_NUM; i++){
			mtSetPoint2D(&m_pPhotoImg->m_guidePos[i], 0.0f, 0.0f);
		}



		if (m_faceLandmark.size()>67){
//=================================================================================================
			m_guideLine[_FACEBOTTOM].SetStartPnt(0.0f, m_faceLandmark[8].y, 0.0f);
			m_guideLine[_FACEBOTTOM].SetEndPnt(newSizeW, m_faceLandmark[8].y, 0.0f);
//=================================================================================================
			m_pPhotoImg->m_guidePos[_CHIN] = m_faceLandmark[8];
			m_pPhotoImg->m_guidePos[_NOSE] = m_faceLandmark[33];
		//	m_pPhotoImg->m_guidePos[_LIP].y = (m_faceLandmark[48].y + m_faceLandmark[54].y)*0.5f;

			for (int i = 36; i < 42; i++){
				m_pPhotoImg->m_guidePos[_LEFT_EYE].x += m_faceLandmark[i].x;
				m_pPhotoImg->m_guidePos[_LEFT_EYE].y += m_faceLandmark[i].y;
			}
			for (int i = 42; i < 48; i++){
				m_pPhotoImg->m_guidePos[_RIGHT_EYE].x += m_faceLandmark[i].x;
				m_pPhotoImg->m_guidePos[_RIGHT_EYE].y += m_faceLandmark[i].y;
			}

			m_pPhotoImg->m_guidePos[_LEFT_EYE].x = (int)(m_pPhotoImg->m_guidePos[_LEFT_EYE].x*0.16666f);
			m_pPhotoImg->m_guidePos[_LEFT_EYE].y = (int)(m_pPhotoImg->m_guidePos[_LEFT_EYE].y*0.16666f);

			m_pPhotoImg->m_guidePos[_RIGHT_EYE].x = (int)(m_pPhotoImg->m_guidePos[_RIGHT_EYE].x*0.16666f);
			m_pPhotoImg->m_guidePos[_RIGHT_EYE].y = (int)(m_pPhotoImg->m_guidePos[_RIGHT_EYE].y*0.16666f);


			//===========================================================================
			m_pPhotoImg->m_guidePos[_EYE_CENTER].x = (m_pPhotoImg->m_guidePos[_LEFT_EYE].x + m_pPhotoImg->m_guidePos[_RIGHT_EYE].x)*0.5f;
			m_pPhotoImg->m_guidePos[_EYE_CENTER].y = (m_pPhotoImg->m_guidePos[_LEFT_EYE].y + m_pPhotoImg->m_guidePos[_RIGHT_EYE].y)*0.5f;			
			//m_pPhotoImg->m_guidePos[_EYE_CENTER].y = (m_pPhotoImg->m_guidePos[_EYE_CENTER].y + m_pPhotoImg->m_guidePos[_NOSE].y)*0.5f;
			//==========================================================================


			m_pPhotoImg->m_guidePos[_FCENTER] = m_pPhotoImg->m_guidePos[_EYE_CENTER];
			m_pPhotoImg->m_guidePos[_FCENTER].y = (m_pPhotoImg->m_guidePos[_EYE_CENTER].y + m_pPhotoImg->m_guidePos[_NOSE].y)*0.5f;

//=================================================================================================
			m_guideLine[_FACECENTER].SetStartPnt(0.0f, m_pPhotoImg->m_guidePos[_EYE_CENTER].y, 0.0f);
			m_guideLine[_FACECENTER].SetEndPnt(newSizeW, m_pPhotoImg->m_guidePos[_EYE_CENTER].y, 0.0f);

			m_guideLine[_VERTICENTER].SetStartPnt(m_pPhotoImg->m_guidePos[_EYE_CENTER].x, 0.0f, 0.0f);
			m_guideLine[_VERTICENTER].SetEndPnt(m_pPhotoImg->m_guidePos[_EYE_CENTER].x, newSizeH, 0.0f);
//=================================================================================================


			float facewidth = (m_faceLandmarkDraw[16].x - m_faceLandmarkDraw[0].x);
			float faceheight = 1.65f * facewidth;
			m_pPhotoImg->m_guidePos[_TOPHEAD].y = m_pPhotoImg->m_guidePos[_CHIN].y - faceheight;

//=================================================================================================
			m_guideLine[_FACETOP].SetStartPnt(0.0f, m_pPhotoImg->m_guidePos[_TOPHEAD].y, 0.0f);
			m_guideLine[_FACETOP].SetEndPnt(newSizeW, m_pPhotoImg->m_guidePos[_TOPHEAD].y, 0.0f);
//=================================================================================================
			// Find eye guide line=============================================
			POINT3D eDir;
			eDir.x = m_pPhotoImg->m_guidePos[_LEFT_EYE].x - m_pPhotoImg->m_guidePos[_RIGHT_EYE].x;
			eDir.y = m_pPhotoImg->m_guidePos[_LEFT_EYE].y - m_pPhotoImg->m_guidePos[_RIGHT_EYE].y;
			eDir.z = 0;
			eDir = mtNormalize(eDir);
			float d = -m_pPhotoImg->m_guidePos[_RIGHT_EYE].x / eDir.x;

			m_pPhotoImg->m_guidePos[_LEFT_EYE].x = m_pPhotoImg->m_guidePos[_RIGHT_EYE].x + d*eDir.x;
			m_pPhotoImg->m_guidePos[_LEFT_EYE].y = m_pPhotoImg->m_guidePos[_RIGHT_EYE].y + d*eDir.y;

			eDir.x = -eDir.x;
			eDir.y = -eDir.y;
			d = (newSizeW - m_pPhotoImg->m_guidePos[_RIGHT_EYE].x) / eDir.x;

			m_pPhotoImg->m_guidePos[_RIGHT_EYE].x = m_pPhotoImg->m_guidePos[_RIGHT_EYE].x + d*eDir.x;
			m_pPhotoImg->m_guidePos[_RIGHT_EYE].y = m_pPhotoImg->m_guidePos[_RIGHT_EYE].y + d*eDir.y;

			POINT3D pDir;		// up vector //
			pDir.x = -eDir.y;
			pDir.y = eDir.x;
			pDir.z = 0;

			POINT3D uDir;
			mtSetPoint3D(&uDir, 0.0f, 1.0f, 0.0f);
			float dotVal = mtDot(uDir, pDir);
			m_fDeSkewAngle = acos(dotVal) * 180.0f / _PI;
			if (pDir.x > uDir.x)
				m_fDeSkewAngle *= -1.0f;

			d = -m_pPhotoImg->m_guidePos[_EYE_CENTER].y / pDir.y;
			m_pPhotoImg->m_guidePos[_TOP_EYE].x = m_pPhotoImg->m_guidePos[_EYE_CENTER].x + pDir.x*d;
			m_pPhotoImg->m_guidePos[_TOP_EYE].y = m_pPhotoImg->m_guidePos[_EYE_CENTER].y + pDir.y*d;


			pDir.x = -pDir.x;
			pDir.y = -pDir.y;
			d = (newSizeH - m_pPhotoImg->m_guidePos[_EYE_CENTER].y) / pDir.y;
			m_pPhotoImg->m_guidePos[_BOTTOM_EYE].x = m_pPhotoImg->m_guidePos[_EYE_CENTER].x + pDir.x*d;
			m_pPhotoImg->m_guidePos[_BOTTOM_EYE].y = m_pPhotoImg->m_guidePos[_EYE_CENTER].y + pDir.y*d;

			//=================================================================
		}

		
		SetCropArea();
		m_pPhotoImg->RestoreGuidePos();
	}

	//CMainFrame* pM = (CMainFrame*)AfxGetMainWnd();
	//pM->SetImageRotateValue(m_fDeSkewAngle);


	oimage.release();
	image.release();


//	m_pPhotoImg->SetRotateionAngle(m_fDeSkewAngle);
	
//	ReSizeIcon();
	return true;
}

void CImageView::SetCropArea()
{
	// 0: bottom, 1: eye, 2: top, 3: vcenter ;;
	float fTop = m_guideLine[2].GetCurrPos().y;
	float fBot = m_guideLine[0].GetCurrPos().y;

	float nPos = m_pPhotoImg->m_guidePos[_NOSE].y;
	float fCenterY = (m_guideLine[1].GetCurrPos().y + nPos)*0.5f;
	float fCenterX = m_guideLine[3].GetCurrPos().x;

	m_pPhotoImg->SetCropArea(fTop, fBot, fCenterX, fCenterY);
}

//POINT2D CImageView::convertScreenToImageSpace(POINT2D pnt)
//{
//	POINT2D curPos;
//	if (m_pPhotoImg){	
//
//		m_fXScale = (float)m_pPhotoImg->GetImgWidth() / m_iconSize;
//		m_fYScale = (float)m_pPhotoImg->GetImgHeight() / m_iconSize;
//
//		float xOffset = m_nWidth - (m_pPhotoImg->GetLeftTop().x + m_nWidth*0.5f);
//		float yOffset = m_nHeight - (m_pPhotoImg->GetLeftTop().y + m_nHeight*0.5f);
//
//		curPos.x = ((pnt.x - xOffset)*m_fXScale) ;
//		curPos.y = ((pnt.y - yOffset)*m_fYScale) ;
//	}
//	return curPos;
//}
//
//POINT2D CImageView::convertImageToScreenSpace(POINT2D pnt)
//{
//	POINT2D curPos;
//	if (m_pPhotoImg){
//
////		float fxDetectScale = (float)m_pPhotoImg->GetImgWidth() / (float)FACE_DETECT_SIZE;
////		float fyDetectScale = (float)m_pPhotoImg->GetImgHeight() / (float)FACE_DETECT_SIZE;
//
//		// restore original size //
//		pnt.x = pnt.x*m_fImgDetectScale;
//		pnt.y = pnt.y*m_fImgDetectScale;
//		pnt.y = m_pPhotoImg->GetImgHeight() - pnt.y;
//
//		m_fXScale = (float)m_pPhotoImg->GetImgWidth() / (m_pPhotoImg->GetLeftTop().x * 2);
//		m_fYScale = (float)m_pPhotoImg->GetImgHeight() / (m_pPhotoImg->GetLeftTop().y * 2);
//
//		float xOffset = m_nWidth - (m_pPhotoImg->GetLeftTop().x + m_nWidth*0.5f);
//		float yOffset = m_nHeight - (m_pPhotoImg->GetLeftTop().y + m_nHeight*0.5f);
//
//		curPos.x = pnt.x / m_fXScale + xOffset;
//		curPos.y = pnt.y / m_fYScale + yOffset;
//	}
//	return curPos;
//}

void CImageView::OnDropFiles(HDROP hDropInfo)
{
	// TODO: Add your message handler code here and/or call default
	//UINT i = 0;
	//UINT uCount = DragQueryFile(hDropInfo, 0xFFFFFFFF, NULL, 0);
	//TCHAR buffer[256];

	//CString strPath;
	//for (i = 0; i < uCount; i++){
	//	DragQueryFile(hDropInfo, i, buffer, 255);
	//	strPath = buffer;

	////	SetPhotoIDimg(strPath);

	//	break;
	//}
	COGLWnd::OnDropFiles(hDropInfo);
}


void CImageView::ThreadFaceDataLoad()
{
	USES_CONVERSION;
	char* sz = T2A(L"./data/shape_predictor_68_face_landmarks.dat");
	dlib::deserialize(sz) >> m_sp;

	m_bIsThreadEnd = true;

	ExitThread(1);
}

float CImageView::GetImgAngle()
{
	if (m_pPhotoImg){
		return m_pPhotoImg->GetImgAngle();
	}
	else{
		return 0.0f;
	}
}

float CImageView::RotateImage(float fAngle, bool IsRedetect)
{
	if (m_pPhotoImg){
		if (IsRedetect){

			CMainFrame* pM = (CMainFrame*)AfxGetMainWnd();
		//	m_pPhotoImg->SetRotateionAngle(m_fDeSkewAngle);
			//RotateImage(0, true);

			//if ((m_fDeSkewAngle > 0.1f) || (m_fDeSkewAngle < 0.1f)){
			//	m_pPhotoImg->SetRotateionAngle(m_fDeSkewAngle);
			//	RotateImage(0, true);
			//}

			//float dAngle = -(m_fDeSkewAngle + fAngle);
			
			m_pPhotoImg->RotateImage(fAngle, m_nWidth, m_nHeight, true, m_pPhotoImg->GetSrcIplImage());
			FaceDetection(m_pPhotoImg->GetSrcCopyIplImage());

			//if ((m_fDeSkewAngle > 0.1f) || (m_fDeSkewAngle < 0.1f)){
			//	m_pPhotoImg->SetRotateionAngle(m_fDeSkewAngle);
			//	RotateImage(0, true);
			//}

		//	pM->SetImageRotateValue(m_fDeSkewAngle);
		//	pM->SetImageRotateValue(fAngle);
			ReSizeIcon();

		//	m_pPhotoImg->SetImgDrawAngle(0.0f);
		}
		else{
			m_pPhotoImg->RotateImage(fAngle, m_nWidth, m_nHeight, false, m_pPhotoImg->GetSrcIplImage());
		}		
	}

	return m_fDeSkewAngle;
}
UINT MyThread(LPVOID lpParam)
{
	CImageView* pClass = (CImageView*)lpParam;
	pClass->ThreadFaceDataLoad();
	return 0L;
}



void CImageView::OnNcDestroy()
{
	COGLWnd::OnNcDestroy();

	// TODO: Add your message handler code here
	//if (m_CDCPtr){
	//	m_CDCPtr->DeleteDC();
	//	delete m_CDCPtr;
	//}
}

void CImageView::SetUserCursorSize(int _size)
{
	m_cursorSize = _size;
	POINT2D v1, v2;
	mtSetPoint2D(&v1, 0, 0);
	mtSetPoint2D(&v2, m_cursorSize*0.5f, 0);
	v1 = m_pPhotoImg->convertImageToScreenSpace(v1, m_nWidth, m_nHeight, false);
	v2 = m_pPhotoImg->convertImageToScreenSpace(v2, m_nWidth, m_nHeight, false);
	m_cursorSizeForDisp = v2.x - v1.x;

	if (m_bStampCopied){
		m_bStampCopied = false;
	}
}

void CImageView::ChangeBrightness(float _value, bool IsApply)
{
	if (m_pPhotoImg){
		m_pPhotoImg->ChangeBrightness(_value, IsApply);
	}
}
void CImageView::ChangeContrast(float _value, bool IsApply)
{
	if (m_pPhotoImg){
		m_pPhotoImg->ChangeConstrast(_value, IsApply);
	}
}

void CImageView::DrawCropArea()
{
		glEnable(GL_DEPTH_TEST);
		glColor4f(0.0f, 0.0f, 0.0f, 0.0f);
		glBegin(GL_QUADS);
		// inner //
		glVertex3f(m_vecInBounderyDraw[0].x, m_vecInBounderyDraw[0].y, 1.0f);
		glVertex3f(m_vecInBounderyDraw[1].x, m_vecInBounderyDraw[1].y, 1.0f);
		glVertex3f(m_vecInBounderyDraw[2].x, m_vecInBounderyDraw[2].y, 1.0f);
		glVertex3f(m_vecInBounderyDraw[3].x, m_vecInBounderyDraw[3].y, 1.0f);		
		glEnd();


		glColor4f(0.0f, 0.0f, 0.0f, 0.5f);
		glBegin(GL_QUADS);
		//// outter //
		glVertex3f(m_vecOutBounderyDraw[3].x, m_vecOutBounderyDraw[3].y, 0.5f);
		glVertex3f(m_vecOutBounderyDraw[2].x, m_vecOutBounderyDraw[2].y, 0.5f);
		glVertex3f(m_vecOutBounderyDraw[1].x, m_vecOutBounderyDraw[1].y, 0.5f);
		glVertex3f(m_vecOutBounderyDraw[0].x, m_vecOutBounderyDraw[0].y, 0.5f);	

		glEnd();

		glDisable(GL_DEPTH_TEST);



		glColor4f(0.0f, 0.0f, 0.0f, 0.9f);
		glBegin(GL_LINE_STRIP);
		// inner //
		glVertex3f(m_vecInBounderyDraw[0].x, m_vecInBounderyDraw[0].y, 1.0f);
		glVertex3f(m_vecInBounderyDraw[1].x, m_vecInBounderyDraw[1].y, 1.0f);
		glVertex3f(m_vecInBounderyDraw[2].x, m_vecInBounderyDraw[2].y, 1.0f);
		glVertex3f(m_vecInBounderyDraw[3].x, m_vecInBounderyDraw[3].y, 1.0f);
		glVertex3f(m_vecInBounderyDraw[0].x, m_vecInBounderyDraw[0].y, 1.0f);
		glEnd();


		
		glBegin(GL_LINE_STRIP);
		//// outter //
		glVertex3f(m_vecOutBounderyDraw[3].x, m_vecOutBounderyDraw[3].y, 0.5f);
		glVertex3f(m_vecOutBounderyDraw[2].x, m_vecOutBounderyDraw[2].y, 0.5f);
		glVertex3f(m_vecOutBounderyDraw[1].x, m_vecOutBounderyDraw[1].y, 0.5f);
		glVertex3f(m_vecOutBounderyDraw[0].x, m_vecOutBounderyDraw[0].y, 0.5f);
		glVertex3f(m_vecOutBounderyDraw[3].x, m_vecOutBounderyDraw[3].y, 0.5f);

		glEnd();
}

IplImage* CImageView::GetPrintPhoto()
{
	if (m_pPhotoImg){
		return m_pPhotoImg->GetPrintImg(m_fImgDetectScale);
	}
	else{
		return NULL;
	}
}

void CImageView::SetCropPhoto()
{
	if (m_pPhotoImg){
	//	m_pPhotoImg->GetCropImg(m_fImgDetectScale);
		m_pPhotoImg->SetCropImg(m_fImgDetectScale);
	}

}

void CImageView::BlurPhoto(int _size)
{
	if (m_pPhotoImg){
		//	m_pPhotoImg->GetCropImg(m_fImgDetectScale);
		m_bBlurMode = true;
		m_bStampMode = false;

		// Update Cursor Size ///
		POINT2D v1, v2;
		mtSetPoint2D(&v1, 0, 0);
		mtSetPoint2D(&v2, m_cursorSize*0.5f, 0);
		v1 = m_pPhotoImg->convertImageToScreenSpace(v1, m_nWidth, m_nHeight, false);
		v2 = m_pPhotoImg->convertImageToScreenSpace(v2, m_nWidth, m_nHeight, false);
		m_cursorSizeForDisp = v2.x - v1.x;
	}
}


void CImageView::StampImage()
{
	if (m_pPhotoImg){
		//	m_pPhotoImg->GetCropImg(m_fImgDetectScale);
		m_bBlurMode = false;
		m_bStampMode = true;

		if (m_bStampCopied){
			m_bStampCopied = false;
		}

		// Update Cursor Size ///
		POINT2D v1, v2;
		mtSetPoint2D(&v1, 0, 0);
		mtSetPoint2D(&v2, m_cursorSize*0.5f, 0);
		v1 = m_pPhotoImg->convertImageToScreenSpace(v1, m_nWidth, m_nHeight, false);
		v2 = m_pPhotoImg->convertImageToScreenSpace(v2, m_nWidth, m_nHeight, false);
		m_cursorSizeForDisp = v2.x - v1.x;
	}

}

void CImageView::OnRButtonDown(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default

	m_bBlurMode = false;
	m_bStampMode = false;

	if (m_bStampCopied){
		m_bStampCopied = false;
	}

	COGLWnd::OnRButtonDown(nFlags, point);
}


void CImageView::SetPhotoFomat(_PHOTOID_FORMAT _format)
{
	if (m_pPhotoImg){
		m_pPhotoImg->SetPhotoFomat(_format);

		//wglMakeCurrent(m_CDCPtr->GetSafeHdc(), m_hRC);
		//ReSizeIcon();
		//Render();

		SetTimer(_UPDATE_IMAGE, 500, NULL);
	}

}

void CImageView::Undo()
{
	if (m_pPhotoImg){
		m_pPhotoImg->Undo();
	}

}