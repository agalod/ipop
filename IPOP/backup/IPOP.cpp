// IPOP.cpp: Implementierung der Klasse CIPOP.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "IPOP.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Konstruktion/Destruktion
//////////////////////////////////////////////////////////////////////

CIPOP::CIPOP()
{
}

CIPOP::~CIPOP()
{
}



void CIPOP::InitWorkpiece()
{

}





void CIPOP::Calc_WorkpiecePosition(D3DVECTORPAIR PiercingPts)
{
	
}


void CIPOP::Calc_RetrievePoints(lti::channel Image)
{
	lti::thresholding binarizer;
	binarizer.apply(Image,Image,100, 255, true, false, 1.0f, 0.0f);
	lti::cannyEdges canny;
	lti::cannyEdges::parameters params;
	canny.apply(Image,Image);
	lti::orientedHLTransform hough;

	//BinarizeImage(Image); EdgeFilterImage(Image);
	//HoughTransformImage(Image); GetLines(Image); GetCrossings(Image);
}


void CIPOP::Calc_InverseProjection()
{
	//CrossingLinePlane();
}


void CIPOP::Calculate_OneStep()
{
	//Calc_Plane();
	//InitWorkpiece();
	//RetrievePPoints();
	//IProjectPPoints();
	//Calc_WorkpiecePosition();
	Calc_RegIIPM_OneStep();

}

/*void CIPOP::Plane_FindCorners(int cols, int rows)
{
	CListImage *imgList = &(pApp->m_pPicDoc->m_CListImage);

	int t,i,currPoint; CvPoint2D32f pt; CString picname;
	m_Img_Size.width = imgList->GetHead()->width; m_Img_Size.height = imgList->GetHead()->height;
	IplImage* greyimg, *img;
	//**************************************************************
	// allocate memory for the array of inner points 
	m_Corners = (CvPoint2D32f *)malloc((m_Img_NumPoints + 1) * sizeof(CvPoint2D32f)); 
	// allocate memory for camera calibration
	m_useIntrinsicGuess = 0; 
	
	//ALGORITHM
	pApp->FreeVec2Point(m_Pts_Vec2);	
	// loop through the images
	POSITION pos = imgList->GetHeadPosition();
	for ( i = 0; i < imgList->GetCount(); i++ )
	{
		m_Corners_Num = m_Corners_maxNum; 
		img = imgList->GetNext(pos);
		greyimg = cvCreateImageHeader(m_Img_Size,IPL_DEPTH_8U,1); 
		cvCreateImageData(greyimg);
		cvCvtColor(img, greyimg, CV_RGB2GRAY); // convert color image to grey
		m_Img_Tmp = cvCloneImage(greyimg);
		
		// Find Corners
		//int cvFindChessBoardCornerGuesses(IplImage* img, IplImage* thresh, CvSize
		//etalonSize, CvPoint2D32f* corners, int *cornerCount );
		
		
		cvFindChessBoardCornerGuesses(greyimg, m_Img_Tmp, m_Storage, cvSize 
			(rows,cols),m_Corners, &m_Corners_Num);
		
		//Find sub-corners
		cvFindCornerSubPix(m_Img_Tmp, m_Corners, m_Corners_Num, cvSize 
			(2,2), cvSize
			(-1, -1), cvTermCriteria (CV_TERMCRIT_ITER | CV_TERMCRIT_EPS, 100, 
			0.1));
		
		//draw a circle and put the corner number at each subcorner found
		if(m_Pts_Vec.size()) pApp->FreePointVec(m_Pts_Vec);
		//if(i){pt = new CvPoint2D32f;	pt->x = 0; pt->y = 0; m_Pts_Vec.push_back(pt);}
		for( t = 0; t < m_Corners_Num; t++ ) {
			pt.x  = m_Corners[t].x;
			pt.y  = m_Corners[t].y;
			m_Pts_Vec.push_back(pt);
		}
		m_Pts_Vec2.push_back(m_Pts_Vec);
	}		
	m_Corners_Found = 1;
	cvReleaseImage(&greyimg);
	//cvReleaseImage(&img);
	//	SortCorners();
	
} 
*/


D3DPLANE& CIPOP::Calc_Plane(const vector <D3DVECTOR> &Points)
{
	Calc_RegIIPM();
	D3DPLANE plane;
	//d3d::ConvertTransformationToPlane(Get_TransCamera(),m_Plane);
	return plane;
}

void CIPOP::Set_Params_Camera(D3DCAMERA CamParams)
{
	m_Camera = CamParams;
}



void CIPOP::Set_Calibration_ObjectPoints(const vector < D3DVECTOR > &Points)
{
	//this->m_pCalibration_ObjectPoints = Points;
	D3DVECTOR vec;
	fPts_Obj.clear(); 
	for(int i=0;i<Points.size();i++){
		vec(0) = Points[i].x; vec(1) = Points[i].y; vec(2) = (Points)[i].z;
		fPts_Obj.push_back(vec); }
}

void CIPOP::Set_Calibration_ImagePoints(vector<CPoint> *Points)
{
	//this->m_pCalibration_ImagePoints = Points;
	D3DVECTOR vec; vec(2) = m_Camera.FocalLength;
	fPts_Img.clear(); 
	for(int i=0;i<(*Points).size();i++){
		vec(0) = (*Points)[i].x; vec(1) = (*Points)[i].y; 	
		fPts_Img.push_back(vec); }

}

void CIPOP::Set_Calibration_InitTrafo(D3DMATRIX &Trafo)
{
	fTrans_Init = Trafo;
}

void CIPOP::Calculate_Init()
{
	Calc_RegIIPM_Init();
}

vector< D3DVECTOR >* CIPOP::GetPtsObj()
{
	return &fPts_Obj;
}

vector< D3DVECTOR >* CIPOP::GetPtsImg()
{
	return &fPts_Img;
}

vector< D3DVECTOR >* CIPOP::GetRaysProjection()
{
	return &fRays_Projection;
}

vector< D3DVECTORPAIR >* CIPOP::GetCorrespondingPoints()
{
	return &fPts_Corresponding;
}

void CIPOP::Reset()
{
	CIIPM::Reset();
}
