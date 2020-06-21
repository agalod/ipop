// IPOP.cpp: Implementierung der Klasse CIPOP.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "IPOP.h"
#include "IPOPApp.h"

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



//DEL void CIPOP::InitWorkpiece()
//DEL {
//DEL 
//DEL }





//DEL void CIPOP::Calc_WorkpiecePosition(D3DVECTORLINE PiercingPts)
//DEL {
//DEL 	
//DEL }


//DEL void CIPOP::Calc_RetrievePoints(lti::channel Image)
//DEL {
//DEL 	lti::thresholding binarizer;
//DEL 	binarizer.apply(Image,Image,100, 255, true, false, 1.0f, 0.0f);
//DEL 	lti::cannyEdges canny;
//DEL 	lti::cannyEdges::parameters params;
//DEL 	canny.apply(Image,Image);
//DEL 	lti::orientedHLTransform hough;
//DEL 
//DEL 	//BinarizeImage(Image); EdgeFilterImage(Image);
//DEL 	//HoughTransformImage(Image); GetLines(Image); GetCrossings(Image);
//DEL }


//DEL void CIPOP::Calc_InverseProjection()
//DEL {
//DEL 	//CrossingLinePlane();
//DEL }


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


//DEL D3DPLANE& CIPOP::Calc_Plane(const vector <D3DVECTOR> &Points)
//DEL {
//DEL 	Calc_RegIIPM();
//DEL 	D3DPLANE plane;
//DEL 	//d3d::ConvertTransformationToPlane(Get_TransCamera(),m_Plane);
//DEL 	return plane;
//DEL }

//DEL void CIPOP::Set_Params_Camera(D3DCAMERA CamParams)
//DEL {
//DEL 	m_Camera = CamParams;
//DEL }



//DEL void CIPOP::Set_Calibration_ObjectPoints(const vector < D3DVECTOR > &Points)
//DEL {
//DEL 	//this->m_pCalibration_ObjectPoints = Points;
//DEL 	D3DVECTOR vec;
//DEL 	fPts_Obj.clear(); 
//DEL 	for(int i=0;i<Points.size();i++){
//DEL 		vec(0) = Points[i].x; vec(1) = Points[i].y; vec(2) = (Points)[i].z;
//DEL 		fPts_Obj.push_back(vec);
//DEL 		}
//DEL }

//DEL void CIPOP::Set_Calibration_ImagePoints(vector<D2DPOINT> *Points)
//DEL {
//DEL 	//this->m_pCalibration_ImagePoints = Points;
//DEL 	D3DVECTOR vec; vec(2) = m_Camera.FocalLength;
//DEL 	fPts_Img.clear(); 
//DEL 	for(int i=0;i<(*Points).size();i++){
//DEL 		vec(0) = (*Points)[i].x; vec(1) = (*Points)[i].y; 	
//DEL 		fPts_Img.push_back(vec); }
//DEL 
//DEL }

void CIPOP::Set_Calibration_InitTrafo(D3DMATRIX &Trafo)
{
	fTrans_Etalon_Init = Trafo;
}

void CIPOP::Calculate_Init()
{
	Calc_RegIIPM_Init();
}

vector< D3DVECTOR >* CIPOP::GetPtsObj()
{
	return &fPts_Obj_Current;
}

//DEL vector< D3DVECTOR >* CIPOP::GetPtsImg()
//DEL {
//DEL 	return &fPts_Img;
//DEL }

//DEL vector< D3DVECTOR >* CIPOP::GetRaysProjection()
//DEL {
//DEL 	return &fRays_Projection;
//DEL }

vector< D3DVECTORLINE >* CIPOP::GetCorrespondingPoints()
{
	return &fPts_Corresponding;
}

void CIPOP::Reset()
{
	CIIPM::Reset();
}

void CIPOP::UpdatePlane()
{
	m_Plane.Normal(0) = fTrans_Etalon_Overall(0,2);
	m_Plane.Normal(1) = fTrans_Etalon_Overall(1,2);
	m_Plane.Normal(2) = fTrans_Etalon_Overall(2,2);
	m_Plane.OrthDistance = VectorMult(fTransl_Etalon_Overall, m_Plane.Normal);
}

void CIPOP::Calc_PiercingPoints()
{
	//; INIT
	D3DMATRIX workpiece_rotmat, machine_rotmat; D3DVECTOR x,y,z;
	
	//; CALCS
	UpdatePlane();	
	CalculateCrosspointLinePlane(m_WorkpiecePoints.pt1, m_Plane, m_WorkpiecePoints.pt1);
	CalculateCrosspointLinePlane(m_WorkpiecePoints.pt2, m_Plane, m_WorkpiecePoints.pt2);

	fEuler_Workpiece_Abs.trans_x = m_WorkpiecePoints.pt2(0);
	fEuler_Workpiece_Abs.trans_y = m_WorkpiecePoints.pt2(1);
	fEuler_Workpiece_Abs.trans_z = m_WorkpiecePoints.pt2(2);

	XYZEulerToRotMat(fEuler_MachineRef_Abs.rot_x, fEuler_MachineRef_Abs.rot_y, 
		fEuler_MachineRef_Abs.rot_z, machine_rotmat);

	y = m_WorkpiecePoints.pt2 - m_WorkpiecePoints.pt1; y /= Magnitude(y);
	workpiece_rotmat(0,1)=y(0); workpiece_rotmat(1,1)=y(1); workpiece_rotmat(2,1)=y(2);

	z(0)=workpiece_rotmat(0,2)=machine_rotmat(0,2); z(1)=workpiece_rotmat(1,2)=machine_rotmat(1,2); 
	z(2)=workpiece_rotmat(2,2)=machine_rotmat(2,2);

	x = CrossProduct(y,z);
	workpiece_rotmat(0,0)=x(0); workpiece_rotmat(1,0)=x(1); workpiece_rotmat(2,0)=x(2);
	RotMatToXYZEuler(workpiece_rotmat,fEuler_Workpiece_Abs.rot_x, 
		fEuler_Workpiece_Abs.rot_y, fEuler_Workpiece_Abs.rot_z);
	fEuler_Workpiece_Rel = fEuler_Workpiece_Abs - fEuler_MachineRef_Abs;
}

D3DVECTORLINE* CIPOP::GetPiercingPoints()
{
	return &m_WorkpiecePoints;
}

//DEL void CIPOP::Save()
//DEL {
//DEL 	CIPOPApp* pApp = (CIPOPApp*) AfxGetApp();
//DEL 
//DEL }
