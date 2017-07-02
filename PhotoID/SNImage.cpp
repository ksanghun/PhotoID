#include "stdafx.h"
#include "SNImage.h"




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

	glGenTextures(1, &thTexId);
	m_fImgAngle = 0.0f;
	m_fSrcBrightness = 0.0f;
	m_fSrcContrast = 1.0f;
	m_imgRectSize = 0;
	m_fImgAngle = 0.0f;
	m_fImgDrawAngle = 0.0f;




	



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

	m_pSrcImg = pimg;

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



	CvMat M = cvMat(2, 3, CV_32F, m_matRot);
	int w = pimg->width;
	int h = pimg->height;
	float angleRadians = 0.0f;
	m_matRot[0] = (float)(cos(angleRadians));
	m_matRot[1] = (float)(sin(angleRadians));
	m_matRot[3] = -m_matRot[1];
	m_matRot[4] = m_matRot[0];
	m_matRot[2] = w*0.5f;
	m_matRot[5] = h*0.5f;


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
	float fMargin = 0.5f;
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


	m_fXScale = w*2.0f / (float)nImgWidth;
	m_fYScale = h*2.0f / (float)nImgHeight;

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
		glBegin(GL_LINE_STRIP);		
		glVertex3f(m_vertex[0].x, m_vertex[0].y, m_vertex[0].z);	
		glVertex3f(m_vertex[1].x, m_vertex[1].y, m_vertex[1].z);	
		glVertex3f(m_vertex[2].x, m_vertex[2].y, m_vertex[2].z);	
		glVertex3f(m_vertex[3].x, m_vertex[3].y, m_vertex[3].z);
		glVertex3f(m_vertex[0].x, m_vertex[0].y, m_vertex[0].z);
		glEnd();

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
	// glupload Image - Thumnail image=======================================================//
	glBindTexture(GL_TEXTURE_2D, thTexId);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, 0x812F);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, 0x812F);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	//glTexImage2D(GL_TEXTURE_2D, 0, 3, m_texture->sizeX,m_texture->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE,m_texture->data);
	gluBuild2DMipmaps(GL_TEXTURE_2D, 3, pimg->width, pimg->height, GL_RGB, GL_UNSIGNED_BYTE, pimg->imageData);
	//======================================================================================//
}

void CSNImage::RotateImage(float _fAngle, int nWidth, int nHeight, bool IsRot, IplImage* pImg)
{
	if (pImg){

		//	float fAngleDiff = _fAngle;
		float fAngleDiff = _fAngle - m_fImgDeskewAngle;
		

		m_fImgDrawAngle = _fAngle;
		
		// Rotate Image //

		if (IsRot){
			m_fImgDrawAngle = 0.0f;
			m_fImgAngle = fAngleDiff;

			//float m[6];// , mat[9];
			CvMat M = cvMat(2, 3, CV_32F, m_matRot);
			int w = pImg->width;
			int h = pImg->height;
			float angleRadians = fAngleDiff * ((float)CV_PI / 180.0f);
			m_matRot[0] = (float)(cos(angleRadians));
			m_matRot[1] = (float)(sin(angleRadians));
			m_matRot[3] = -m_matRot[1];
			m_matRot[4] = m_matRot[0];
			m_matRot[2] = w*0.5f;
			m_matRot[5] = h*0.5f;


			//===============================//
			//POINT2D iCenter, sCenter;
			//mtSetPoint2D(&iCenter, m[2], m[5]);
			//sCenter = convertImageToScreenSpace(iCenter, nWidth, nHeight, false);
			//mat[0] = (float)(cos(angleRadians));
			//mat[3] = (float)(sin(angleRadians));
			//mat[1] = -m[1];
			//mat[4] = m[0];
			//mat[2] = (float)nImgWidth*0.5f / m_fImgDetectScale;
			//mat[5] = (float)nImgWidth*0.5f / m_fImgDetectScale;

			//mat[6] = 0.0f;
			//mat[7] = 0.0f;
			//mat[8] = 1.0f;

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


			//	return imageRotated;
			//===================//
			//		m_fCurrImgAngle = _fAngle;


			// Rotate LandMark Point //
			//for (int i = 0; i < _LNADMARK_POS_NUM; i++){
			//	float in[3] = { m_guidePosOri[i].x - mat[2], m_guidePosOri[i].y - mat[5], 1.0f };
			//	float out[3] = { 0.0f, 0.0f, 0.0f };

			//	mtMultMatrixVec(static_cast<const float*>(mat), static_cast<const float*>(in), out, 3);
			//	m_guidePos[i].x = out[0];
			//	m_guidePos[i].y = out[1];
			//}

			m_fImgDrawAngle = 0.0f;
		}
		//else{
		//	m_fImgDrawAngle = m_fImgAngle;
		//}
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
	m_fImgDeskewAngle += _fangle; 
//	m_fImgAngle += m_fImgDeskewAngle;
}

void CSNImage::ChangeBrightness(IplImage* pSrc, IplImage* pDst, float _value)
{
	// rotation first //
//	ChangeRotation(pSrc, pDst);

	// brightness first //
	//m_fSrcBrightness = _value;

	float fDiff = _value - m_fSrcBrightness;

	CvScalar brVal = cvScalarAll(fDiff);
	cvAddS(pSrc, brVal, pDst, NULL);

	//// contrast //
	//IplImage *pTempImg = cvCreateImage(cvGetSize(pDst), IPL_DEPTH_8U, pDst->nChannels);
	//cvSet(pTempImg, cvScalarAll(1), NULL);
	//cvMul(pDst, pTempImg, pDst, m_fSrcContrast);
	//cvReleaseImage(&pTempImg);

	m_fSrcBrightness = _value;

	SetGLTexture(pDst);
}

void CSNImage::ChangeConstrast(IplImage* pSrc, IplImage* pDst, float _value)
{
	// rotation first
	//	ChangeRotation(pSrc, pDst);


	CvScalar brVal = cvScalarAll(m_fSrcBrightness);
	cvAddS(pSrc, brVal, pDst, NULL);

	float diffCont = _value / m_fSrcContrast;
	


	IplImage *pTempImg = cvCreateImage(cvGetSize(pSrc), IPL_DEPTH_8U, pSrc->nChannels);
	cvSet(pTempImg, cvScalarAll(1), NULL);
	cvMul(pSrc, pTempImg, pDst, diffCont);
	cvReleaseImage(&pTempImg);

	SetGLTexture(pDst);

	m_fSrcContrast = _value;

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

//void CSNImage::SetCropArea(int faceTop, int faceBottom)
//{
////	float faceLength = m_guidePos[_FACE]
//
//
//	m_rectCrop.set(x1, x2, y1, y2);
//	m_rectCrop.width = x2 - x1;
//	m_rectCrop.height = y2 - y1;
//}