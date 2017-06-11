// Sanghun Kim //

#include "stdafx.h"
#include "ImageView.h"
#include "resource.h"
#include "ViewTree.h"
#include "MainFrm.h"
#include "PhotoIDView.h"




enum TIMEREVNT { _RENDER=100, _ADDIMG , _SEARCHIMG};
#define _MIN_ICON_SIZE 16
#define FACE_DETECT_SIZE 100

using namespace cv;


CImageView::CImageView()
{
	memset(&m_LogFont, 0, sizeof(m_LogFont));
//	strcpy((char*)m_LogFont.lfFaceName, ("Arial"));
	m_LogFont.lfCharSet = ANSI_CHARSET;
	m_LogFont.lfHeight = -10;
	m_LogFont.lfWidth = 0;
	//	m_LogFont.lfWeight = FW_BOLD;
	

	memset(&m_LogFontBig, 0, sizeof(m_LogFontBig));
	//	strcpy((char*)m_LogFont.lfFaceName, ("Arial"));
	m_LogFontBig.lfCharSet = ANSI_CHARSET;
	m_LogFontBig.lfHeight = -15;
	m_LogFontBig.lfWidth = 0;
	m_LogFont.lfWeight = FW_BOLD;


	m_pBmpInfo = (BITMAPINFO *)malloc(sizeof(BITMAPINFOHEADER) + (sizeof(RGBQUAD) * 256));


	m_nWidth = 0;
	m_nHeight = 0;


//	m_dragOper.init();
	m_mouseMode = 0;


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
}


CImageView::~CImageView()
{
	delete m_pBmpInfo;
	//std::map<unsigned long, CSNImage*>::iterator iter = m_mapImageData.begin();
	//for (; iter != m_mapImageData.end(); iter++){

	//	GLuint tex = iter->second->GetTxTex();
	//	glDeleteTextures(1, &tex);
	//	delete iter->second;
	//}
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
END_MESSAGE_MAP()



void CImageView::ReleaseImageData()
{
	//std::map<unsigned long, CSNImage*> m_mapImageData;
	//std::map<unsigned long, _vecSNImage> m_mapGrupImg;
	//_vecSNImage m_vecImageData;

	if (m_pPhotoImg){
		GLuint texid = m_pPhotoImg->GetTexId();
		if (texid != 0)	glDeleteTextures(1, &texid);
		delete m_pPhotoImg;
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



void CImageView::Render()
{
	wglMakeCurrent(m_CDCPtr->GetSafeHdc(), m_hRC);

	glClearColor(0.7f, 0.7f, 0.7f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	Render2D();

	SwapBuffers(m_CDCPtr->GetSafeHdc());
}

void CImageView::Render2D()
{

	


	//int pointSize = m_iconSize / 100;
	//if (pointSize < 4)
	//	pointSize = 4;

	glLineWidth(2.0f);
	glPointSize(3);

	gl_PushOrtho(m_left, m_right, m_bottom, m_top);


	if (m_bIsThreadEnd == false){
		glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glColor3f(0.9f, 0.2f, 0.2f);
		POINT3D pos;
		mtSetPoint3D(&pos, m_nWidth*0.5f, m_nHeight*0.5f, 0);
		gl_DrawText(pos, L"Initilizing...", m_LogFontBig, 1, m_pBmpInfo, m_CDCPtr);
	}



	if (m_pPhotoImg){
		m_pPhotoImg->DrawThumbNail(1.0f);
	}

	


	glColor3f(0.0f, 1.0f, 0.0f);
	glBegin(GL_POINTS);
	for (int i = 0; i < m_faceLandmarkDraw.size(); i++){
		glVertex3f(m_faceLandmarkDraw[i].x, m_faceLandmarkDraw[i].y, m_faceLandmarkDraw[i].z);
	}
	glEnd();



	// Draw Lines //
	glBegin(GL_LINES);
	glVertex3f(0.0f, m_guidePosDraw[_CHIN].y, 0.0f);
	glVertex3f(m_nWidth, m_guidePosDraw[_CHIN].y, 0.0f);

	glVertex3f(0.0f, m_guidePosDraw[_LIP].y, 0.0f);
	glVertex3f(m_nWidth, m_guidePosDraw[_LIP].y, 0.0f);

	glVertex3f(0.0f, m_guidePosDraw[_NOSE].y, 0.0f);
	glVertex3f(m_nWidth, m_guidePosDraw[_NOSE].y, 0.0f);

	glVertex3f(0.0f, m_guidePosDraw[_EYE_CENTER].y, 0.0f);
	glVertex3f(m_nWidth, m_guidePosDraw[_EYE_CENTER].y, 0.0f);

	glVertex3f(0.0f, m_guidePosDraw[_TOPHEAD].y, 0.0f);
	glVertex3f(m_nWidth, m_guidePosDraw[_TOPHEAD].y, 0.0f);

	glEnd();


	glColor3f(1.0f, 0.0f, 0.0f);
	glBegin(GL_LINES);
	
	glVertex3f(m_guidePosDraw[_LEFT_EYE].x, m_guidePosDraw[_LEFT_EYE].y, m_guidePosDraw[_LEFT_EYE].z);
	glVertex3f(m_guidePosDraw[_RIGHT_EYE].x, m_guidePosDraw[_RIGHT_EYE].y, m_guidePosDraw[_RIGHT_EYE].z);

	glEnd();



	gl_PopOrtho();

	glLineWidth(1.0f);
	glPointSize(1.0f);
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

	

	
		
	//m_bIsThreadEnd = false;
	//m_pThread = AfxBeginThread(MyThread, this);
	//m_pThread->m_bAutoDelete = FALSE;
	//m_pThread->ResumeThread();


	m_bIsThreadEnd = false;
	CWinThread* pl = AfxBeginThread(MyThread, this);
//	CloseHandle(pl);
		
	
	//===============================================//
	SetTimer(_RENDER, 30, NULL);
}

void CImageView::SetPhotoIDimg(CString strPath)
{
	// Load Phto ID image=============================//
	if (m_pPhotoImg){
		GLuint texid = m_pPhotoImg->GetTexId();
		if (texid != 0)	glDeleteTextures(1, &texid);
		delete m_pPhotoImg;
		m_pPhotoImg = NULL;
	}

	m_pPhotoImg = new CSNImage;
	POINT3D pos;
	mtSetPoint3D(&pos, 0, 0, 0);
	m_pPhotoImg->SetPosition(pos);
	LoadSNImage(strPath, m_pPhotoImg);

	m_iconSize = m_nWidth;
	ReSizeIcon();

}

void CImageView::MouseWheel(short zDelta)
{
	wglMakeCurrent(m_CDCPtr->GetSafeHdc(), m_hRC);	

	m_iconSize += zDelta*0.1f;
	if (m_iconSize < _MIN_ICON_SIZE)
		m_iconSize = _MIN_ICON_SIZE;
	if (m_iconSize > m_nWidth)
		m_iconSize = m_nWidth;

	ReSizeIcon();
}


void CImageView::ReSizeIcon()
{
	if (m_pPhotoImg){

		if (m_nWidth < m_nHeight)
			m_iconSize = m_nWidth;
		else
			m_iconSize = m_nHeight;

		m_pPhotoImg->SetSize(m_pPhotoImg->GetWidth(), m_pPhotoImg->GetHeight(), m_iconSize);
		POINT3D sPnt;
		sPnt.x = m_nWidth*0.5f;
		sPnt.y = m_nHeight*0.5f;
		sPnt.z = 0.0f;
		m_pPhotoImg->SetPosition(sPnt);

		for (int i = 0; i < m_faceLandmarkDraw.size(); i++){
			m_faceLandmarkDraw[i] = convertImageToScreenSpace(m_faceLandmark[i]);			
		}

		for (int i = 0; i < 7; i++){
			m_guidePosDraw[i] = convertImageToScreenSpace(m_guidePos[i]);
			}




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
	

//	m_cameraPri.SetProjectionMatrix(30.0f, 0.0f, 0.0f, cx, cy);
//	m_cameraPri.SetModelViewMatrix(m_cameraPri.GetLookAt(), 0.0f, 0.0f);

	ReSizeIcon();
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
	wglMakeCurrent(m_CDCPtr->GetSafeHdc(), m_hRC);
	USES_CONVERSION;
	char* sz = T2A(strPath);

	IplImage *pimg = cvLoadImage(sz);	
	if (pimg){

		cvCvtColor(pimg, pimg, CV_BGR2RGB);

		pInfo->SetImgSize(pimg->width, pimg->height);
		pInfo->SetSize(pimg->width, pimg->height, m_iconSize);		


		// glupload Image - Thumnail image=======================================================//
		GLuint tid = 0;
		glGenTextures(1, &tid);
		glBindTexture(GL_TEXTURE_2D, tid);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);

		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, 0x812F);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, 0x812F);
		//glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
		//glTexImage2D(GL_TEXTURE_2D, 0, 3, m_texture->sizeX,m_texture->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE,m_texture->data);
		gluBuild2DMipmaps(GL_TEXTURE_2D, 3, pimg->width, pimg->height, GL_RGB, GL_UNSIGNED_BYTE, pimg->imageData);
		//======================================================================================//

		pInfo->SetThTex(tid);


		FaceDetection(pimg);

		cvReleaseImage(&pimg);		
		return true;
	}
	else{
		return false;
	}
	
}


void CImageView::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	if (GetCapture()){
		ReleaseCapture();
		//m_fMoveSpeed = point.y - m_preMmousedown.y;
	}

	COGLWnd::OnLButtonUp(nFlags, point);
}


void CImageView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default


	//if (m_pPhotoImg){
	//	POINT3D curPos;
	//	curPos.x = (float)point.x;
	//	curPos.y = (float)point.y;
	//	curPos.z = 0.0f;

	//	curPos = convertScreenToImageSpace(curPos);
	//	m_strMousePos.Format(_T("[%d, %d]"), (int)curPos.x, (int)curPos.y);
	//}

	
	//if (GetCapture()){		

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

	//	Render();
	//}	

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
		
		//if (m_bIsThreadEnd == true){
		//	EndWaitCursor();
		//	m_bIsThreadEnd = false;
		//	TRACE(L"File Loaded...");
		//}
	}


	if (nIDEvent == _ADDIMG){
		GenerateThumbnail();		
	}

	if (nIDEvent == _SEARCHIMG){

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

	//if (select_object_2d(point.x, point.y, 2, 2, _PICK_SELECT) > 0){
	//	if (m_pCurrSelImg != NULL){
	//		m_pCurrSelImg->SetSelecttion(false);
	//	}
	//	m_pCurrSelImg = GetSNImageByIndex((int)m_sellBuffer[3]);
	//	m_pCurrSelImg->SetSelecttion(true);

	//	//m_centerx = m_pCurrSelImg->GetPos().x;
	//	//m_centery = m_pCurrSelImg->GetPos().y;
	//}

	//PrepareRender();
	//Render();
	COGLWnd::OnLButtonDown(nFlags, point);
}




int CImageView::select_object_2d(int x, int y, int rect_width, int rect_height, _PICKMODE _mode)
{
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

	hits = glRenderMode(GL_RENDER);
	//if (hits>0)
	//{
	//	process_select(selectBuff, hits, selmode);
	//	int a = 0;
	//}
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
	m_fImgDetectScale = (float)oimage.cols / 350.0f;
	if (m_fImgDetectScale < 1.0f)
		m_fImgDetectScale = 1.0f;

	int newSizeW = (float)oimage.cols / m_fImgDetectScale;
	int newSizeH = (float)oimage.rows / m_fImgDetectScale;

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

			POINT3D pnt;
			mtSetPoint3D(&pnt, shape.part(j).x(), shape.part(j).y(), 0);
			m_faceLandmark.push_back(pnt);
			m_faceLandmarkDraw.push_back(pnt);
		}
	}

//	imshow("Detected Face", image);

	for (int i = 0; i < 7; i++){
		mtSetPoint3D(&m_guidePos[i], 0.0f, 0.0f, 0.0f);
	}

	if (m_faceLandmark.size()>67){
		m_guidePos[_CHIN] = m_faceLandmark[8];
		m_guidePos[_NOSE] = m_faceLandmark[33];
		m_guidePos[_LIP].y = (m_faceLandmark[48].y + m_faceLandmark[54].y)*0.5f;

		for (int i = 36; i < 42; i++){
			m_guidePos[_LEFT_EYE].x += m_faceLandmark[i].x;
			m_guidePos[_LEFT_EYE].y += m_faceLandmark[i].y;
		}
		for (int i = 42; i < 48; i++){
			m_guidePos[_RIGHT_EYE].x += m_faceLandmark[i].x;
			m_guidePos[_RIGHT_EYE].y += m_faceLandmark[i].y;
		}

		m_guidePos[_LEFT_EYE].x *= 0.16666f;
		m_guidePos[_LEFT_EYE].y *= 0.16666f;

		m_guidePos[_RIGHT_EYE].x *= 0.16666f;
		m_guidePos[_RIGHT_EYE].y *= 0.16666f;


		m_guidePos[_EYE_CENTER].x = (m_guidePos[_LEFT_EYE].x + m_guidePos[_RIGHT_EYE].x)*0.5f;
		m_guidePos[_EYE_CENTER].y = (m_guidePos[_LEFT_EYE].y + m_guidePos[_RIGHT_EYE].y)*0.5f;

		float facewidth = (m_faceLandmarkDraw[16].x - m_faceLandmarkDraw[0].x);
		float faceheight = 1.618f * facewidth;
		m_guidePos[_TOPHEAD].y = m_guidePos[_CHIN].y - faceheight;
	}



	ReSizeIcon();
	return true;
}

POINT3D CImageView::convertScreenToImageSpace(POINT3D pnt)
{
	POINT3D curPos;
	if (m_pPhotoImg){		

		m_fXScale = (float)m_pPhotoImg->GetImgWidth() / (m_pPhotoImg->GetLeftTop().x*m_fImgDetectScale);
		m_fYScale = (float)m_pPhotoImg->GetImgHeight() / (m_pPhotoImg->GetLeftTop().y*m_fImgDetectScale);

		float xOffset = m_nWidth - (m_pPhotoImg->GetLeftTop().x + m_nWidth*0.5f);
		float yOffset = m_nHeight - (m_pPhotoImg->GetLeftTop().y + m_nHeight*0.5f);

		curPos.x = (pnt.x - xOffset)*m_fXScale;
		curPos.y = (pnt.y - yOffset)*m_fYScale;
		curPos.z = 0.0f;
	}
	return curPos;
}

POINT3D CImageView::convertImageToScreenSpace(POINT3D pnt)
{
	POINT3D curPos;
	if (m_pPhotoImg){

//		float fxDetectScale = (float)m_pPhotoImg->GetImgWidth() / (float)FACE_DETECT_SIZE;
//		float fyDetectScale = (float)m_pPhotoImg->GetImgHeight() / (float)FACE_DETECT_SIZE;

		// restore original size //
		pnt.x = pnt.x*m_fImgDetectScale;
		pnt.y = pnt.y*m_fImgDetectScale;
		pnt.y = m_pPhotoImg->GetImgHeight() - pnt.y;

		m_fXScale = (float)m_pPhotoImg->GetImgWidth() / (m_pPhotoImg->GetLeftTop().x * 2);
		m_fYScale = (float)m_pPhotoImg->GetImgHeight() / (m_pPhotoImg->GetLeftTop().y * 2);

		float xOffset = m_nWidth - (m_pPhotoImg->GetLeftTop().x + m_nWidth*0.5f);
		float yOffset = m_nHeight - (m_pPhotoImg->GetLeftTop().y + m_nHeight*0.5f);

		curPos.x = pnt.x / m_fXScale + xOffset;
		curPos.y = pnt.y / m_fYScale + yOffset;
		curPos.z = 0.0f;
	}
	return curPos;
}

void CImageView::OnDropFiles(HDROP hDropInfo)
{
	// TODO: Add your message handler code here and/or call default
	UINT i = 0;
	UINT uCount = DragQueryFile(hDropInfo, 0xFFFFFFFF, NULL, 0);
	TCHAR buffer[256];

	CString strPath;
	for (i = 0; i < uCount; i++){
		DragQueryFile(hDropInfo, i, buffer, 255);
		strPath = buffer;

		SetPhotoIDimg(strPath);

		break;
	}


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

UINT MyThread(LPVOID lpParam)
{
	CImageView* pClass = (CImageView*)lpParam;
	pClass->ThreadFaceDataLoad();
	return 0L;
}