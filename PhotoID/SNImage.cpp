#include "stdafx.h"
#include "SNImage.h"


#define CANADA_WIDTH_MM 50.0f
#define CANADA_HEIGHT_MM 70.0f
#define DPI300_PIXEL 11.82f

#define PRINT_SIZEW 2418
#define PRINT_SIZEH 1612
#define CANADA_SIZEW 793
#define CANADA_SIZEH 1111
#define CANADA_RATIO 0.7143

CSNImage::CSNImage()
{
	parentCode = 0;
	nWidth=0;
	nHeight=0;
	fARatio=0.0f;

	thTexId = texId = 0;
	m_fRectWidth = 0.0f;

	mtSetPoint3D(&m_vBgColor, 1.0f, 1.0f, 1.0f);
	mtSetPoint3D(&m_pos, -10000, 10000, 0.0f);

	m_fXScale = 1.0f;
	m_fYScale = 1.0f;

	m_imgWScale = 1.0f;
	m_imgHScale = 1.0f;

	m_pSrcImg = NULL;
	m_pSrcImgCopy = NULL;
	m_PrtImg = NULL;

	
	m_fImgAngle = 0.0f;
	m_fSrcBrightness = 0.0f;
	m_fSrcContrast = 1.0f;
	m_imgRectSize = 0;
	m_fImgDrawAngle = 0.0f;




	m_pCropImg = NULL;
	m_pCropImgSmall = NULL;
	m_IsCropImg = false;

	
}


CSNImage::~CSNImage()
{
	if (texId > 0){
		glDeleteTextures(1, &texId);
	}
	if (thTexId > 0){
		glDeleteTextures(1, &thTexId);
	}

	if (m_pSrcImg){
		cvReleaseImage(&m_pSrcImg);
	}

	if (m_pSrcImgCopy){
		cvReleaseImage(&m_pSrcImgCopy);
	}


	if (m_pCropImg){
		cvReleaseImage(&m_pCropImg);
	}

	if (m_pCropImgSmall){
		cvReleaseImage(&m_pCropImgSmall);
	}


	
	//if (m_pSrcImgSmall){
	//	cvReleaseImage(&m_pSrcImgSmall);
	//}
}

//void CSNImage::SetBgColor(float r, float g, float b)
//{
//	//mtSetPoint3D(&m_vBgColor, r,g,b);
//}

void CSNImage::SetSrcIplImage(IplImage* pimg)
{
	if (m_pSrcImg){
		cvReleaseImage(&m_pSrcImg);
	}
	if (m_pSrcImgCopy){
		cvReleaseImage(&m_pSrcImgCopy);
	}
	//if (m_pSrcImgSmall){
	//	cvReleaseImage(&m_pSrcImgSmall);
	//}
	if (m_PrtImg){
		cvReleaseImage(&m_PrtImg);
	}

	m_IsCropImg = false;
	if (m_pCropImg){
		cvReleaseImage(&m_pCropImg);		
	}
	


	m_pSrcImg = pimg;
	m_PrtImg = cvCreateImage(cvSize(PRINT_SIZEW, PRINT_SIZEH), m_pSrcImg->depth, m_pSrcImg->nChannels);
	//int w = pimg->width / 2;
	//int h = pimg->height / 2;

	//m_pSrcImgSmall = cvCreateImage(cvSize(w, h), m_pSrcImg->depth, m_pSrcImg->nChannels);
	//cvResize(m_pSrcImg, m_pSrcImgSmall);
		

	m_pSrcImgCopy = cvCloneImage(m_pSrcImg);

	// TEST //
	//ChangeBrightness(m_pSrcImgCopy, 50);
	//ChangeConstrast(m_pSrcImgCopy, 0.5f);
	
	m_fImgDeskewAngle = 0.0f;
	m_fImgAngle = 0.0f;
	m_fSrcBrightness = 0.0f;
	m_fSrcContrast = 1.0f;



	//CvMat M = cvMat(2, 3, CV_32F, m_matRot);
	//int w = pimg->width;
	//int h = pimg->height;
	//float angleRadians = 0.0f;
	//m_matRot[0] = (float)(cos(angleRadians));
	//m_matRot[1] = (float)(sin(angleRadians));
	//m_matRot[3] = -m_matRot[1];
	//m_matRot[4] = m_matRot[0];
	//m_matRot[2] = w*0.5f;
	//m_matRot[5] = h*0.5f;


	SetGLTexture(m_pSrcImgCopy);
	
}

bool CSNImage::AddMatchedPoint(_MATCHInfo info, int search_size)
{
/*	if (search_size > 0){
		if (IsDuplicate(info.pos, search_size) == false){
			m_matched_pos.push_back(info);			
		}
	}
	else{
		m_matched_pos.push_back(info);
	}*/
	return true;
}

void CSNImage::SetName(CString _strpath, CString _strpname, CString _strname, unsigned long _pcode, unsigned long _nCode)
{
	strPath = _strpath;
	strPName = _strpname;
	strName = _strname;
	parentCode = _pcode;
	nCode = _nCode;

	mtSetPoint3D(&m_pos, 0.0f, 0.0f, 0.0f);

}
void CSNImage::SetSize(unsigned short _w, unsigned short _h, float _size)
{
	m_imgRectSize = _size;
	float fMargin = 0.45f;
	nWidth = _w;
	nHeight = _h;
	fARatio = (float)_w / (float)_h;
	float w, h;

	if (_size > 0){
		if (fARatio <= 1.0f){
			w = _size*fARatio*fMargin;
			h = _size*fMargin;
		}
		else{
			w = _size*fMargin;
			h = (_size / fARatio)*fMargin;
		}
	}
	else{
		w = _w*0.5f;
		h = _h*0.5f;
	}


	//m_fXScale = w*2.0f / (float)nImgWidth;
	//m_fYScale = h*2.0f / (float)nImgHeight;

	mtSetPoint3D(&m_vertex[0], -w, -h, 0.0f);		mtSetPoint2D(&m_texcoord[0], 0.0f, 1.0f);
	mtSetPoint3D(&m_vertex[1], w, -h, 0.0f);		mtSetPoint2D(&m_texcoord[1], 1.0f, 1.0f);
	mtSetPoint3D(&m_vertex[2], w, h, 0.0f);			mtSetPoint2D(&m_texcoord[2], 1.0f, 0.0f);
	mtSetPoint3D(&m_vertex[3], -w, h, 0.0f);		mtSetPoint2D(&m_texcoord[3], 0.0f, 0.0f);


	mtSetPoint3D(&m_vertexBg[0], -_size*0.5f, -_size*0.5f, 0.0f);
	mtSetPoint3D(&m_vertexBg[1], _size*0.5f, -_size*0.5f, 0.0f);
	mtSetPoint3D(&m_vertexBg[2], _size*0.5f, _size*0.5f, 0.0f);
	mtSetPoint3D(&m_vertexBg[3], -_size*0.5f, _size*0.5f, 0.0f);

	m_fRectWidth = _size*fARatio;

	m_imgWScale = w*2.0f / _size;
	m_imgHScale = h*2.0f / _size;


	m_pntLT.x = w;
	m_pntLT.y = h;
	m_pntLT.z = 0;


	//m_fXScale = (float)GetImgWidth() / (GetLeftTop().x * 2);
	//m_fYScale = (float)GetImgHeight() / (GetLeftTop().y * 2);



//	MakeGuideDrawPos();
}


void CSNImage::DrawForPicking()
{
	glPushMatrix();
	glTranslatef(m_pos.x, m_pos.y, m_pos.z);

	// Background//	
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glBegin(GL_QUADS);
	glVertex3f(m_vertexBg[0].x, m_vertexBg[0].y, m_vertexBg[0].z);
	glVertex3f(m_vertexBg[1].x, m_vertexBg[1].y, m_vertexBg[1].z);
	glVertex3f(m_vertexBg[2].x, m_vertexBg[2].y, m_vertexBg[2].z);
	glVertex3f(m_vertexBg[3].x, m_vertexBg[3].y, m_vertexBg[3].z);
	glEnd();
	//==================//
	glPopMatrix();

}

void CSNImage::SetSelecttion(bool _isSel) 
{ 
	if (_isSel == true){
		mtSetPoint3D(&m_vBgColor, 0.1f, 0.99f, 0.1f);
	}
	else{
		mtSetPoint3D(&m_vBgColor, 1.0f, 1.0f, 1.0f);
	}
	m_bIsSelected = _isSel; 
};

void CSNImage::SetTexId(GLuint _texid)
{
	if (_texid != texId){
		if (texId > 0){
			glDeleteTextures(1, &texId);
		}
		texId = _texid;
	}	

}

void CSNImage::DrawImage(float fAlpha)
{
	glPushMatrix();
	glTranslatef(m_pos.x, m_pos.y, m_pos.z);

	glBindTexture(GL_TEXTURE_2D, texId);
	glColor4f(1.0f, 1.0f, 1.0f, fAlpha);

	glEnable(GL_TEXTURE_2D);
	glBegin(GL_QUADS);
	glTexCoord2f(m_texcoord[0].x, m_texcoord[0].y);
	glVertex3f(m_vertex[0].x, m_vertex[0].y, m_vertex[0].z);

	glTexCoord2f(m_texcoord[1].x, m_texcoord[1].y);
	glVertex3f(m_vertex[1].x, m_vertex[1].y, m_vertex[1].z);

	glTexCoord2f(m_texcoord[2].x, m_texcoord[2].y);
	glVertex3f(m_vertex[2].x, m_vertex[2].y, m_vertex[2].z);

	glTexCoord2f(m_texcoord[3].x, m_texcoord[3].y);
	glVertex3f(m_vertex[3].x, m_vertex[3].y, m_vertex[3].z);
	glEnd();

	glDisable(GL_TEXTURE_2D);
	glPopMatrix();
}


void CSNImage::DrawBMPText()
{
	glPushMatrix();	

	glBindTexture(GL_TEXTURE_2D, texId);
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);

	glEnable(GL_TEXTURE_2D);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(m_vertex[0].x, m_vertex[0].y, m_vertex[0].z);

	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(m_vertex[1].x, m_vertex[1].y, m_vertex[1].z);

	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(m_vertex[2].x, m_vertex[2].y, m_vertex[2].z);

	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(m_vertex[3].x, m_vertex[3].y, m_vertex[3].z);
	glEnd();

	glDisable(GL_TEXTURE_2D);
	glPopMatrix();
}


void CSNImage::DrawThumbNail(float fAlpha)
{
	if (thTexId == 0){
		return;
	}
	glPushMatrix();
	
	glTranslatef(m_pos.x, m_pos.y, m_pos.z);
	glRotatef(-m_fImgDrawAngle, 0, 0, 1);

	// Background//
	//glDisable(GL_TEXTURE_2D);
	//glColor4f(m_vBgColor.x, m_vBgColor.y, m_vBgColor.z, 1.0f);
	//glBegin(GL_QUADS);	
	//glVertex3f(m_vertexBg[0].x, m_vertexBg[0].y, m_vertexBg[0].z);
	//glVertex3f(m_vertexBg[1].x, m_vertexBg[1].y, m_vertexBg[1].z);
	//glVertex3f(m_vertexBg[2].x, m_vertexBg[2].y, m_vertexBg[2].z);
	//glVertex3f(m_vertexBg[3].x, m_vertexBg[3].y, m_vertexBg[3].z);
	//glEnd();
	//==================//


	glEnable(GL_TEXTURE_2D);
	if (texId == 0){
		glBindTexture(GL_TEXTURE_2D, thTexId);
	}
	else{
		glBindTexture(GL_TEXTURE_2D, texId);
	}
	glColor4f(1.0f, 1.0f, 1.0f, fAlpha);	

	glBegin(GL_QUADS);

	glTexCoord2f(m_texcoord[0].x, m_texcoord[0].y);
	glVertex3f(m_vertex[0].x, m_vertex[0].y, m_vertex[0].z);

	glTexCoord2f(m_texcoord[1].x, m_texcoord[1].y);
	glVertex3f(m_vertex[1].x, m_vertex[1].y, m_vertex[1].z);

	glTexCoord2f(m_texcoord[2].x, m_texcoord[2].y);
	glVertex3f(m_vertex[2].x, m_vertex[2].y, m_vertex[2].z);

	glTexCoord2f(m_texcoord[3].x, m_texcoord[3].y);
	glVertex3f(m_vertex[3].x, m_vertex[3].y, m_vertex[3].z);
	glEnd();

	glDisable(GL_TEXTURE_2D);
	

	// Detected //
	//if (m_matched_pos.size() > 0 ){
	//	glColor4f(1.0f, 0.2f, 0.1f, fAlpha);
		//glBegin(GL_LINE_STRIP);		
		//glVertex3f(m_vertex[0].x, m_vertex[0].y, m_vertex[0].z);	
		//glVertex3f(m_vertex[1].x, m_vertex[1].y, m_vertex[1].z);	
		//glVertex3f(m_vertex[2].x, m_vertex[2].y, m_vertex[2].z);	
		//glVertex3f(m_vertex[3].x, m_vertex[3].y, m_vertex[3].z);
		//glVertex3f(m_vertex[0].x, m_vertex[0].y, m_vertex[0].z);
		//glEnd();

	//	// Draw detected position //
	//	glColor4f(1.0f, 0.2f, 0.1f, 0.7f);
	//	glPushMatrix();		
	//		glScalef(m_fXScale, m_fYScale, 1.0f);
	//		glTranslatef(-nImgWidth*0.5f, -nImgHeight*0.5f, 0.0f);
	//		glBegin(GL_POINTS);
	//		for (int i = 0; i < m_matched_pos.size(); i++){
	//			glColor4f(m_matched_pos[i].color.x, m_matched_pos[i].color.y, m_matched_pos[i].color.z, 0.7f);
	//			glVertex3f(m_matched_pos[i].pos.x, nImgHeight - m_matched_pos[i].pos.y, 0.0f);
	//		}
	//		glEnd();
	//	glPopMatrix();

	//}


	//glColor3f(0.0f, 1.0f, 0.0f);
	//glBegin(GL_LINES);
	//glVertex3f(-m_drawWidth*0.5f, m_guidePosDraw[_CHIN].y, 0.0f);
	//glVertex3f(m_drawWidth*0.5f, m_guidePosDraw[_CHIN].y, 0.0f);

	//glVertex3f(-m_drawWidth*0.5f, m_guidePos[_EYE_CENTER].y, 0.0f);
	//glVertex3f(m_drawWidth*0.5f, m_guidePos[_EYE_CENTER].y, 0.0f);

	//glVertex3f(-m_drawWidth*0.5f, m_guidePos[_TOPHEAD].y, 0.0f);
	//glVertex3f(m_drawWidth*0.5f, m_guidePos[_TOPHEAD].y, 0.0f);

	//glEnd();
	//		
	glPopMatrix();




}


void CSNImage::SetThTex(GLuint _thtex)
{
	thTexId = _thtex;
}
void CSNImage::SetTex(GLuint _tex)
{
	texId = _tex;
}

void CSNImage::SetPosition(POINT3D pos)
{
	m_pos = pos;
}

void CSNImage::ClearMatchResult()
{
//	m_matched_pos.clear();
}

bool CSNImage::IsDuplicate(POINT3D pos, int search_size)
{
/*	bool IsDup = false;
	for (int i = 0; i < m_matched_pos.size(); i++){
		float fDist = mtDistance(pos, m_matched_pos[i].pos);
		if (fDist < search_size){
			IsDup = true;
			break;
		}
	}
	return IsDup*/
	return false;
}

void CSNImage::SetGLTexture(IplImage* pimg)
{
	SetImgSize(pimg->width, pimg->height);
	SetSize(pimg->width, pimg->height, m_imgRectSize);


	if (thTexId > 0){
		glDeleteTextures(1, &thTexId);
	}
	glGenTextures(1, &thTexId);

	// glupload Image - Thumnail image=======================================================//
	glBindTexture(GL_TEXTURE_2D, thTexId);

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, 0x812F);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, 0x812F);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

	//glTexImage2D(GL_TEXTURE_2D, 0, GL_INTENSITY, pimg->width, pimg->height, 0, GL_LUMINANCE, GL_UNSIGNED_BYTE, pimg->imageData);
	gluBuild2DMipmaps(GL_TEXTURE_2D, 3, pimg->width, pimg->height, GL_RGB, GL_UNSIGNED_BYTE, pimg->imageData);
	//======================================================================================//
}

void CSNImage::RotateImage(float _fAngle, int nWidth, int nHeight, bool IsRot, IplImage* pImg)
{
	if (pImg){
		m_fImgDrawAngle += _fAngle;		
		TRACE(L"%3.2f - %3.2f\n", m_fImgDrawAngle, _fAngle);

		if (IsRot){			
		//	m_fImgAngle = fAngleDiff;
			m_fImgAngle += m_fImgDrawAngle;
			m_fImgDrawAngle = 0.0f;

			//float m[6];// , mat[9];
			CvMat M = cvMat(2, 3, CV_32F, m_matRot);
			int w = pImg->width;
			int h = pImg->height;
		//	float angleRadians = fAngleDiff * ((float)CV_PI / 180.0f);
			float angleRadians = m_fImgAngle * ((float)CV_PI / 180.0f);
			m_matRot[0] = (float)(cos(angleRadians));
			m_matRot[1] = (float)(sin(angleRadians));
			m_matRot[3] = -m_matRot[1];
			m_matRot[4] = m_matRot[0];
			m_matRot[2] = w*0.5f;
			m_matRot[5] = h*0.5f;

			// Make a spare image for the result
			CvSize sizeRotated;
			sizeRotated.width = cvRound(w);
			sizeRotated.height = cvRound(h);


			// Rotate
			IplImage *imageRotated = cvCreateImage(sizeRotated, pImg->depth, pImg->nChannels);
			// Transform the image
			//	cvGetQuadrangleSubPix(m_pSrcImg, imageRotated, &M);
			cvGetQuadrangleSubPix(pImg, imageRotated, &M);

			cvReleaseImage(&m_pSrcImgCopy);
			m_pSrcImgCopy = imageRotated;
			SetGLTexture(m_pSrcImgCopy);

			m_fImgDrawAngle = 0.0f;
		}
	}
}

void CSNImage::RestoreGuidePos()
{
	for (int i = 0; i < _LNADMARK_POS_NUM; i++){
		m_guidePosOri[i] = m_guidePos[i];
	}
}

void CSNImage::ChangeRotation(IplImage* pSrc, IplImage* pDst)
{
//	if ((m_fImgAngle > 0.01f) || (m_fImgAngle < 0.01f)){


		CvMat M = cvMat(2, 3, CV_32F, m_matRot);
		int w = pSrc->width;
		int h = pSrc->height;

		// Make a spare image for the result
		CvSize sizeRotated;
		sizeRotated.width = cvRound(w);
		sizeRotated.height = cvRound(h);

		// Rotate
		IplImage *imageRotated = cvCreateImage(sizeRotated, pSrc->depth, pSrc->nChannels);

		// Transform the image
		cvGetQuadrangleSubPix(pSrc, imageRotated, &M);

		cvReleaseImage(&pDst);
		pDst = imageRotated;
//	}
}


POINT2D CSNImage::convertScreenToImageSpace(POINT2D pnt, int nWidth, int nHeight)
{
	POINT2D curPos;


		//m_fXScale = (float)GetImgWidth() / m_imgRectSize;
	//m_fYScale = (float)GetImgHeight() / m_imgRectSize;

	m_fXScale = (float)GetImgWidth() / (GetLeftTop().x * 2);
	m_fYScale = (float)GetImgHeight() / (GetLeftTop().y * 2);


	float xOffset = nWidth - (GetLeftTop().x + nWidth*0.5f);
	float yOffset = nHeight - (GetLeftTop().y + nHeight*0.5f);

	curPos.x = ((pnt.x - xOffset)*m_fXScale);
	curPos.y = ((pnt.y - yOffset)*m_fYScale);

	return curPos;
}

POINT2D CSNImage::convertImageToScreenSpace(POINT2D pnt, int nWidth, int nHeight, bool IsScaled)
{
	POINT2D curPos;

	if (IsScaled){
		// restore original size //
		pnt.x = pnt.x*m_fImgDetectScale;
		pnt.y = pnt.y*m_fImgDetectScale;

		//=========================//
	}
	pnt.y = GetImgHeight() - pnt.y;

	m_fXScale = (float)GetImgWidth() / (GetLeftTop().x * 2);
	m_fYScale = (float)GetImgHeight() / (GetLeftTop().y * 2);



	float xOffset = nWidth - (GetLeftTop().x + nWidth*0.5f);
	float yOffset = nHeight - (GetLeftTop().y + nHeight*0.5f);

	curPos.x = pnt.x / m_fXScale + xOffset;
	curPos.y = pnt.y / m_fYScale + yOffset;

	return curPos;
}


void CSNImage::SetRotateionAngle(float _fangle)
{ 
//	m_fImgDeskewAngle += _fangle; 
//	m_fImgAngle += m_fImgDeskewAngle;
//	m_fImgDeskewAngle = _fangle;
	m_fImgDrawAngle = _fangle;
}

void CSNImage::ChangeBrightness(float _value, bool IsApply)
{
	if (m_pCropImg == NULL){
		AfxMessageBox(L"Image is not cropped");
	}
	else{
		if (IsApply){
			CvScalar brVal = cvScalarAll(_value);
			cvAddS(m_pCropImg, brVal, m_pCropImg, NULL);

			m_fSrcBrightness = 0;
			SetGLTexture(m_pCropImg);

			// Update small crop image
			cvResize(m_pCropImg, m_pCropImgSmall);
			TRACE(L"Apply Brightness\n");
		}
		else{
			IplImage* pTmp = cvCloneImage(m_pCropImgSmall);
			CvScalar brVal = cvScalarAll(_value);
			cvAddS(m_pCropImgSmall, brVal, pTmp, NULL);

			m_fSrcBrightness = _value;
			SetGLTexture(pTmp);
			cvReleaseImage(&pTmp);

			TRACE(L"Not Apply Brightness\n");
		}
	}
}

void CSNImage::ChangeConstrast(float _value, bool IsApply)
{
	if (m_pCropImg == NULL){
		AfxMessageBox(L"Image is not cropped");
	}
	else{
		if (IsApply){
			IplImage *pTempImg = cvCreateImage(cvGetSize(m_pCropImg), IPL_DEPTH_8U, m_pCropImg->nChannels);
			cvSet(pTempImg, cvScalarAll(1), NULL);
			cvMul(m_pCropImg, pTempImg, m_pCropImg, _value);
			cvReleaseImage(&pTempImg);

			SetGLTexture(m_pCropImg);
			m_fSrcContrast = 0;

			// Update small crop image
			cvResize(m_pCropImg, m_pCropImgSmall);
		}
		else{
			IplImage* pTmp = cvCloneImage(m_pCropImgSmall);
			IplImage *pTempImg = cvCreateImage(cvGetSize(m_pCropImgSmall), IPL_DEPTH_8U, m_pCropImgSmall->nChannels);
			cvSet(pTempImg, cvScalarAll(1), NULL);
			cvMul(m_pCropImgSmall, pTempImg, pTmp, _value);
			cvReleaseImage(&pTempImg);

			SetGLTexture(pTmp);
			m_fSrcContrast = _value;
			cvReleaseImage(&pTmp);
		}
	}
}

void CSNImage::SetBoundary(int _width, int _height)
{
	mtSetPoint2D(&m_vecOutBoundery[0], 0, 0);
	mtSetPoint2D(&m_vecOutBoundery[1], _width, 0);
	mtSetPoint2D(&m_vecOutBoundery[2], _width, _height);
	mtSetPoint2D(&m_vecOutBoundery[3], 0, _height);

	SetInBoundary(_width, _height);
}

void CSNImage::SetInBoundary(int _width, int _height)
{
	int xOffst = 50;
	int yOffset = 50;
	int w = _width*0.5f;
	int h = _height*0.5f;

	mtSetPoint2D(&m_vecInBoundery[0], xOffst, yOffset);
	mtSetPoint2D(&m_vecInBoundery[1], w, yOffset);
	mtSetPoint2D(&m_vecInBoundery[2], w, h);
	mtSetPoint2D(&m_vecInBoundery[3], xOffst, h);

}

void CSNImage::DrawCroppingArea()
{
	//glEnable(GL_DEPTH_TEST);
	//glColor4f(0.0f, 0.0f, 0.0f, 0.0f);
	//glBegin(GL_QUADS);
	//// inner //
	//glVertex3f(m_vecInBounderyDraw[3].x, m_vecInBounderyDraw[3].y, 1.0f);
	//glVertex3f(m_vecInBounderyDraw[2].x, m_vecInBounderyDraw[2].y, 1.0f);
	//glVertex3f(m_vecInBounderyDraw[1].x, m_vecInBounderyDraw[1].y, 1.0f);
	//glVertex3f(m_vecInBounderyDraw[0].x, m_vecInBounderyDraw[0].y, 1.0f);
	//glEnd();


	//glColor4f(0.0f, 0.0f, 0.0f, 0.3f);
	//glBegin(GL_QUADS);
	////// outter //
	//glVertex3f(m_vecOutBounderyDraw[3].x, m_vecOutBounderyDraw[3].y, 0.5f);
	//glVertex3f(m_vecOutBounderyDraw[2].x, m_vecOutBounderyDraw[2].y, 0.5f);
	//glVertex3f(m_vecOutBounderyDraw[1].x, m_vecOutBounderyDraw[1].y, 0.5f);
	//glVertex3f(m_vecOutBounderyDraw[0].x, m_vecOutBounderyDraw[0].y, 0.5f);	

	//glEnd();

	//glDisable(GL_DEPTH_TEST);

}

void CSNImage::SetCropArea(float yFaceBot, float yFaceTop, float xFaceCenter, float yFaceCenter)
{

//	float aRatio = CANADA_WIDTH_MM / CANADA_HEIGHT_MM;

	float cropHeight = (yFaceTop - yFaceBot) * 2;  // face length X 2
	float cropWidth = cropHeight*CANADA_RATIO;
	


	m_rectCrop.set(xFaceCenter - cropWidth*0.5f, xFaceCenter + cropWidth*0.5f,
		yFaceCenter - cropHeight*0.5f, yFaceCenter + cropHeight*0.5f);
	m_rectCrop.width = m_rectCrop.x2 - m_rectCrop.x1;
	m_rectCrop.height =  m_rectCrop.y2 - m_rectCrop.y1;



	mtSetPoint2D(&m_vecInBoundery[0], m_rectCrop.x1, m_rectCrop.y1);
	mtSetPoint2D(&m_vecInBoundery[1], m_rectCrop.x1, m_rectCrop.y2);
	mtSetPoint2D(&m_vecInBoundery[2], m_rectCrop.x2, m_rectCrop.y2);
	mtSetPoint2D(&m_vecInBoundery[3], m_rectCrop.x2, m_rectCrop.y1);


}

IplImage* CSNImage::GetPrintImg(float _fScale)
{
	if (m_pCropImg==NULL){
		//cvReleaseImage(&m_pCropImg);
		//m_pCropImg = NULL;
		return NULL;
	}

//	m_rectCrop.x1 *= _fScale;
//	m_rectCrop.x2 *= _fScale;
//	m_rectCrop.y1 *= _fScale;
//	m_rectCrop.y2 *= _fScale;
//
//	if (m_rectCrop.y1 < 0)					m_rectCrop.y1 = 0;
//	if (m_rectCrop.y2 > m_pSrcImg->height)	m_rectCrop.y2 = m_pSrcImg->height;
//	if (m_rectCrop.x1 < 0)					m_rectCrop.x1 = 0;
//	if (m_rectCrop.x2 > m_pSrcImg->width)	m_rectCrop.x2 = m_pSrcImg->width;
//
//
//	m_rectCrop.width = m_rectCrop.x2 - m_rectCrop.x1;	
//	m_rectCrop.height = m_rectCrop.y2 - m_rectCrop.y1;
//
//	m_pCropImg = cvCreateImage(cvSize(CANADA_SIZEW, CANADA_SIZEH), m_pSrcImg->depth, m_pSrcImg->nChannels);
//	cvSetImageROI(m_pSrcImg, cvRect(m_rectCrop.x1, m_rectCrop.y1, m_rectCrop.width, m_rectCrop.height));		// posx, posy = left - top
////	cvCopy(m_pSrcImg, m_pCropImg);
//	cvResize(m_pSrcImg, m_pCropImg);
//	cvResetImageROI(m_pSrcImg);


	

	
	cvSet(m_PrtImg, cvScalar(255, 255, 255));

//#define PRINT_SIZEW 1800
//#define PRINT_SIZEH 1200
//#define CANADA_SIZEW 590
//#define CANADA_SIZEH 826

	int wMargin = (PRINT_SIZEW - CANADA_SIZEW * 2) / 4;
	int hMargin = (PRINT_SIZEH - CANADA_SIZEW ) / 2;

	cvSetImageROI(m_PrtImg, cvRect(wMargin, hMargin, m_pCropImg->width, m_pCropImg->height));		// posx, posy = left - top
	cvCopy(m_pCropImg, m_PrtImg);
	cvResetImageROI(m_PrtImg);

	DrawCrossMark(50, 1, wMargin - 1, hMargin-1, m_PrtImg);
	DrawCrossMark(50, 1, wMargin + m_pCropImg->width + 1, hMargin - 1, m_PrtImg);
	DrawCrossMark(50, 1, wMargin + m_pCropImg->width + 1, hMargin + m_pCropImg->height + 1, m_PrtImg);
	DrawCrossMark(50, 1, wMargin - 1, hMargin + m_pCropImg->height + 1, m_PrtImg);

	wMargin += (wMargin * 2 + m_pCropImg->width);
	cvSetImageROI(m_PrtImg, cvRect(wMargin, hMargin, m_pCropImg->width, m_pCropImg->height));		// posx, posy = left - top
	cvCopy(m_pCropImg, m_PrtImg);
	cvResetImageROI(m_PrtImg);

DrawCrossMark(50, 1, wMargin - 1, hMargin - 1, m_PrtImg);
DrawCrossMark(50, 1, wMargin + m_pCropImg->width + 1, hMargin - 1, m_PrtImg);
DrawCrossMark(50, 1, wMargin + m_pCropImg->width + 1, hMargin + m_pCropImg->height + 1, m_PrtImg);
DrawCrossMark(50, 1, wMargin - 1, hMargin + m_pCropImg->height + 1, m_PrtImg);

//IplImage* rotated = cvCreateImage(cvSize(m_PrtImg->height, m_PrtImg->width), m_PrtImg->depth, m_PrtImg->nChannels);
//cvTranspose(m_PrtImg, rotated);

//	cvShowImage("Crop img", m_PrtImg);

return m_PrtImg;
}

void CSNImage::DrawCrossMark(int length, int thickness, int _x, int _y, IplImage* pImg)
{
	//	int id = y*matBinary->widthStep + x;
	//	matBinary->imageData[id]
	// x direction //
	for (int x = (_x - length); x < (_x + length); x++){
		int id = _y*pImg->widthStep + x * 3;
		pImg->imageData[id] = 0;
		pImg->imageData[id + 1] = 0;
		pImg->imageData[id + 2] = 0;
	}


	for (int y = (_y - length); y < (_y + length); y++){
		int id = y*pImg->widthStep + _x * 3;
		pImg->imageData[id] = 0;
		pImg->imageData[id + 1] = 0;
		pImg->imageData[id + 2] = 0;
	}

}


void CSNImage::SetCropImg(float _fScale)
{
	if (m_IsCropImg == true) return;

	if (m_pCropImg){
		cvReleaseImage(&m_pCropImg);
		m_pCropImg = NULL;

		cvReleaseImage(&m_pCropImgSmall);
		m_pCropImgSmall = NULL;
	}

	m_rectCrop.x1 *= _fScale;
	m_rectCrop.x2 *= _fScale;
	m_rectCrop.y1 *= _fScale;
	m_rectCrop.y2 *= _fScale;

	if (m_rectCrop.y1 < 0)					m_rectCrop.y1 = 0;
	if (m_rectCrop.y2 > m_pSrcImgCopy->height)	m_rectCrop.y2 = m_pSrcImgCopy->height;
	if (m_rectCrop.x1 < 0)					m_rectCrop.x1 = 0;
	if (m_rectCrop.x2 > m_pSrcImgCopy->width)	m_rectCrop.x2 = m_pSrcImgCopy->width;


	m_rectCrop.width = m_rectCrop.x2 - m_rectCrop.x1;
	m_rectCrop.height = m_rectCrop.y2 - m_rectCrop.y1;

	float fRatio = (float)CANADA_SIZEW / (float)CANADA_SIZEH;
	int sHeight = 200;
	int sWidth = sHeight * fRatio;
	m_pCropImg = cvCreateImage(cvSize(CANADA_SIZEW, CANADA_SIZEH), m_pSrcImgCopy->depth, m_pSrcImgCopy->nChannels);
	m_pCropImgSmall = cvCreateImage(cvSize(sWidth, sHeight), m_pSrcImgCopy->depth, m_pSrcImgCopy->nChannels);
	cvSetImageROI(m_pSrcImgCopy, cvRect(m_rectCrop.x1, m_rectCrop.y1, m_rectCrop.width, m_rectCrop.height));		// posx, posy = left - top
	//	cvCopy(m_pSrcImg, m_pCropImg);
	cvResize(m_pSrcImgCopy, m_pCropImg);
	cvResize(m_pSrcImgCopy, m_pCropImgSmall);
	cvResetImageROI(m_pSrcImgCopy);


	// Set Crop image as main image
	SetGLTexture(m_pCropImg);
	m_IsCropImg = true;



	nImgWidth = m_pCropImg->width;
	nImgHeight = m_pCropImg->height;
}


void CSNImage::CpoyForStamp(cv::Rect targetRect, cv::Mat& stampCut)
{
	if (m_IsCropImg == true){
		cv::Rect cutRect = targetRect;
		int margin = 10;
		cutRect.x -= margin;
		cutRect.y -= margin;
		cutRect.width += margin * 2;
		cutRect.height += margin * 2;

		if ((cutRect.x < 0) || (cutRect.y < 0) ||
			((cutRect.x + cutRect.width) >= nWidth) || ((cutRect.y + cutRect.height) >= nHeight)){
			return;
		}

		cv::Mat imgMat = cv::cvarrToMat(m_pCropImg);
		imgMat(cutRect).copyTo(stampCut);

	}
}


void CSNImage::BlurImage(cv::Rect targetRect, cv::Size blurSize)
{
	if (m_IsCropImg == true){

		cv::Mat imgMat = cv::cvarrToMat(m_pCropImg);
		int orignaltype = imgMat.type();

		cv::Rect cutRect = targetRect;
		int margin = 10;
		cutRect.x -= margin;
		cutRect.y -= margin;
		cutRect.width += margin * 2;
		cutRect.height += margin * 2;


		if ((cutRect.x < 0) || (cutRect.y < 0) ||
			((cutRect.x + cutRect.width) >= nWidth) || ((cutRect.y + cutRect.height) >= nHeight)){
			return;
		}


		cv::Mat mask = cv::Mat::zeros(cv::Size(cutRect.width, cutRect.height), imgMat.type());
		// mask is a disk	
		int radious = targetRect.width / 2;
		circle(mask, cv::Point(cutRect.width / 2, cutRect.height/2), radious, cv::Scalar(255, 255, 255), -1);
		cv::Mat imgBlur, imgOri;
		imgMat(cutRect).copyTo(imgBlur);
		imgMat(cutRect).copyTo(imgOri);

		imgBlur.setTo(255);

	//	cv::Size blurSize(7, 7);
		blur(mask, mask, blurSize);
		blur(imgBlur, imgBlur, blurSize);

		//cv::imshow("blur1", mask);
		//cv::imshow("blur2", imgBlur);

		mask.convertTo(mask, CV_32FC3, 1.0 / 255); // 
		imgBlur.convertTo(imgBlur, CV_32FC3);
		imgOri.convertTo(imgOri, CV_32FC3);

		multiply(mask, imgBlur, imgBlur);
		multiply(cv::Scalar::all(1.0) - mask, imgOri, imgOri);

		cv::Mat ouImage = cv::Mat::zeros(imgOri.size(), imgOri.type());
		add(imgBlur, imgOri, ouImage);

		ouImage.convertTo(ouImage, orignaltype);
		ouImage.copyTo(imgMat(cutRect));

//		cv::imshow("Result", imgMat);

		//cvReleaseImage(&pimg);
		//pimg = new IplImage(ouImage);
//		cvShowImage("cropimg", m_pCropImg);

		SetGLTexture(m_pCropImg);
	}
}
void CSNImage::StampImage(cv::Rect _srcRect, cv::Rect targetRect, cv::Size blurSize)
{
	if (m_IsCropImg == true){

		cv::Mat imgMat = cv::cvarrToMat(m_pCropImg);
		int orignaltype = imgMat.type();

		cv::Rect cutRect = targetRect;
		int margin = 10;
		cutRect.x -= margin;
		cutRect.y -= margin;
		cutRect.width += margin * 2;
		cutRect.height += margin * 2;

		cv::Rect srcRect = _srcRect;
		srcRect.x -= margin;
		srcRect.y -= margin;
		srcRect.width += margin * 2;
		srcRect.height += margin * 2;


		if ((cutRect.x < 0) || (cutRect.y < 0) ||
			((cutRect.x + cutRect.width) >= nWidth) || ((cutRect.y + cutRect.height) >= nHeight)){
			return;
		}


		cv::Mat mask = cv::Mat::zeros(cv::Size(cutRect.width, cutRect.height), imgMat.type());
		// mask is a disk	
		int radious = targetRect.width / 2;
		circle(mask, cv::Point(cutRect.width / 2, cutRect.height / 2), radious, cv::Scalar(255, 255, 255), -1);
		cv::Mat cutImg, srcImg;
		imgMat(cutRect).copyTo(cutImg);
		imgMat(srcRect).copyTo(srcImg);

		//	cv::Size blurSize(7, 7);
		blur(mask, mask, blurSize);

		//cv::imshow("blur1", mask);
		//cv::imshow("blur2", imgBlur);

		mask.convertTo(mask, CV_32FC3, 1.0 / 255); // 
		cutImg.convertTo(cutImg, CV_32FC3);
		srcImg.convertTo(srcImg, CV_32FC3);

		multiply(mask, srcImg, srcImg);
		multiply(cv::Scalar::all(1.0) - mask, cutImg, cutImg);

		cv::Mat ouImage = cv::Mat::zeros(srcImg.size(), srcImg.type());
		add(cutImg, srcImg, ouImage);

		ouImage.convertTo(ouImage, orignaltype);
		ouImage.copyTo(imgMat(cutRect));

		//		cv::imshow("Result", imgMat);

		//cvReleaseImage(&pimg);
		//pimg = new IplImage(ouImage);
		//		cvShowImage("cropimg", m_pCropImg);

		SetGLTexture(m_pCropImg);
	}
}