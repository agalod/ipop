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
    
CIPOP::CIPOP() {
	//; for turning init etalon-CS by x:180 and z:-90 deg
	//; we are doing this, in order to have angles les than 90 deg,
	//; so we have no problems with functions like RotMatToEuler,
	//; which only work for angles less than 90 deg.
	fTrans_Etalon_Turn._11= 0; fTrans_Etalon_Turn._12= 1; fTrans_Etalon_Turn._13= 0; 
	fTrans_Etalon_Turn._21= 1; fTrans_Etalon_Turn._22= 0; fTrans_Etalon_Turn._23= 0; 
	fTrans_Etalon_Turn._31= 0; fTrans_Etalon_Turn._32= 0; fTrans_Etalon_Turn._33=-1; 
	fParams.BinThreshold = 190;	fParams.ShowSteps = FALSE;	fParams.HoughSensivity = 16; 
	m_bInitialised = 0; fParams.NumErosions = 20;}


CIPOP::~CIPOP(){
}


void CIPOP::Update_Plane() {
	m_Plane.Normal(0) = fTrans_Overall(0,2);
	m_Plane.Normal(1) = fTrans_Overall(1,2);
	m_Plane.Normal(2) = fTrans_Overall(2,2);
	m_Plane.OrthDistance = 
		VectorMult(fTrans_Overall.GetTranslation(), m_Plane.Normal); }


void CIPOP::Calc_PiercingPoints(GCV_LINE2D line) {
	GCV_VECTOR3D x,y,z; Update_Plane();	
	fTrans_Workpiece = IdentityMatrix();
	//; CONVERT IMAGEPTS TO OBJECTPOINTS
	m_WorkpieceImagePoints.pt1 = ConvertImagePtToProjectionRay(fCamera, line.pt1);
	m_WorkpieceImagePoints.pt2 = ConvertImagePtToProjectionRay(fCamera, line.pt2);
	m_WorkpieceObjectPoints.pt1 = CalculateCrosspointProjRayPlane(m_WorkpieceImagePoints.pt1, m_Plane);
	m_WorkpieceObjectPoints.pt2 = CalculateCrosspointProjRayPlane(m_WorkpieceImagePoints.pt2, m_Plane);
	//; SET TOGETHER WORKPIECE FRAME
	y = m_WorkpieceObjectPoints.pt2 - m_WorkpieceObjectPoints.pt1; 	y /= Magnitude(y);
	for(int i=0;i<3; i++){
		fTrans_Workpiece(i,1) = y(i);						//; y-Axis
		z(i) = fTrans_Workpiece(i,2) = fTrans_Machine(i,2);	//; z-Axis
		fTrans_Workpiece(i,3) = m_WorkpieceObjectPoints.pt2(i); }	//; Translation
	x = CrossProduct(y,z); 
	for(i=0;i<3; i++) fTrans_Workpiece(i,0) = x(i); //; x-Axis
	//; CALCULATE WORKPIECE_REL
	fTrans_Workpiece_Rel.SetRotation( MatrixTranspose
		(fTrans_Machine.GetRotation()) * fTrans_Workpiece.GetRotation() );
	fTrans_Workpiece_Rel.SetTranslation( TransformVector
		((fTrans_Workpiece.GetTranslation() - fTrans_Machine.GetTranslation()),
		MatrixTranspose(fTrans_Machine.GetRotation())) );
	MatrixToEuler(fTrans_Workpiece_Rel, fEuler_Workpiece_Rel); }


void CIPOP::SetWorkpieceAbsToMachineRefAbs() {
	//; CALCULATE MACHINE REL
	fTrans_Machine = fTrans_Machine * fTrans_Workpiece_Rel;
	fTrans_Etalon_Turned = MatrixMult(fTrans_Overall, fTrans_Etalon_Turn);
	//; SET MACHINE REL TRAFO
	fTrans_Machine_Rel.SetRotation(
		MatrixInverse(fTrans_Etalon_Turned.GetRotation()) * fTrans_Machine.GetRotation() );
	fTrans_Machine_Rel.SetTranslation(
		TransformVector
				((fTrans_Machine.GetTranslation() - fTrans_Etalon_Turned.GetTranslation()),
				MatrixTranspose(fTrans_Etalon_Turned.GetRotation())) );
	MatrixToEuler(fTrans_Machine_Rel, fEuler_Machine_Rel);
	fEuler_Workpiece_Rel.clear(); }


void CIPOP::Update_Euler_Machine() {
	EulerToMatrix(fEuler_Machine_Rel, fTrans_Machine_Rel);
	fTrans_Machine =  MatrixMult(
		MatrixMult(fTrans_Overall,fTrans_Etalon_Turn),fTrans_Machine_Rel); }


void CIPOP::Update_Euler_Workpiece() {
	EulerToMatrix(fEuler_Workpiece_Rel, fTrans_Workpiece_Rel);
	fTrans_Workpiece = MatrixMult(fTrans_Machine, fTrans_Workpiece_Rel); }


void CIPOP::Update_Eulers() {
	MatrixToEuler(fTrans_Overall, fEuler_Etalon);
	Update_Euler_Machine(); Update_Euler_Workpiece(); }


void CIPOP::Calc_RegIIPM_Init(){
	EulerToMatrix(fEuler_Etalon, fTrans_Init);	CIIPM::Calc_RegIIPM_Init();
	Update_Eulers(); m_bInitialised = 1;}


void CIPOP::Calc_RegIIPM_OneStep(){	
	 CIIPM::Calc_RegIIPM_OneStep();	Update_Eulers(); }

void CIPOP::Calc_RegIIPM_XSteps(){
	for(int i=0;i<30;i++)
		CIIPM::Calc_RegIIPM_OneStep();	Update_Eulers(); }

void CIPOP::Calc_RegIIPM_Update(){
	EulerToMatrix(fEuler_Etalon, fTrans_Overall);
	CIIPM::Calc_RegIIPM_Update();
	Update_Eulers(); }


bool CIPOP::Preprocess(CImage* img_input, vector <CImage*> *ResultVec, GCV_LINE2D &Workpiece_Points){
	CWaitCursor waitcursor;	
	lti::channel currImage; lti::loadImage loader; lti::saveImage writer;
	lti::channel8 edgeimage8; lti::channel orientationimage, edgeimage;
	lti::cannyEdges edgefilter;	

	//; BINARISIERUNG
	CImage* img_thresh = new CImage(); img_thresh->CopyOf(*img_input);
	cvThreshold(img_input->GetImage(), img_thresh->GetImage(),fParams.BinThreshold,255,CV_THRESH_BINARY); 
	if(fParams.ShowSteps) ResultVec->push_back(img_thresh); 
	CImage* img_threshcopy = new CImage(); img_threshcopy->CopyOf(*img_thresh,0);	
	
	//; ERODIERUNG, 40MAL 
	CImage* img_erode = new CImage(); img_erode->CopyOf(*img_input);
	cvErode(img_thresh->GetImage(),img_erode->GetImage(),0,fParams.NumErosions); 
	if(fParams.ShowSteps) ResultVec->push_back(img_erode); 
	
	//; EIN WEIßER PUNKT
	img_erode->Save("CImageServer_SaveIplImage.bmp"); loader.load("CImageServer_SaveIplImage.bmp",currImage);
	lti::ipoint ipt = currImage.getIndexOfMaximum(); CvConnectedComp comp;

	//; FLOODFILL
	CImage* img_flood = new CImage(); img_flood->CopyOf(*img_thresh);
	cvFloodFill(img_flood->GetImage(),cvPoint(ipt.x,ipt.y),0,7,7,&comp,8);

	//; SUBTRAKTION
	iplSubtract(img_threshcopy->GetImage(),img_flood->GetImage(),img_flood->GetImage()); 
	if(fParams.ShowSteps) ResultVec->push_back(img_flood); 

	//; KANTENFILTER
	img_flood->Save("CImageServer_SaveIplImage.bmp"); loader.load("CImageServer_SaveIplImage.bmp",currImage);
	edgefilter.apply(currImage,edgeimage8,orientationimage); edgeimage.castFrom(edgeimage8);
	writer.save("CImageServer_SaveLTIImage.bmp", edgeimage );
	CImage* img_edge = new CImage(); img_edge->Load("CImageServer_SaveLTIImage.bmp",0);
	if(fParams.ShowSteps) ResultVec->push_back(img_edge); 
	if(!fParams.ShowSteps){ img_thresh->Destroy();
		img_threshcopy->Destroy();img_erode->Destroy();img_edge->Destroy();}
	
	//; HOUGHTRANSFORMATION
	lti::orientedHLTransform::parameters HTpars; HTpars.range = 180; HTpars.accuracy = 720;
	lti::orientedHLTransform HLT; HLT.setParameters(HTpars);
	lti::channel32 transformAccu32;	lti::channel transformAccu;
	HLT.apply(edgeimage,orientationimage,transformAccu32);

	//; LINIEN-EXTRAKTION
	// Now get the local maxima of the transformAccu
	lti::vector< lti::tpoint<float> > maxpos;
	HLT.getHoughSpacePoints(transformAccu32,maxpos,fParams.HoughSensivity);
	//; 3rd parameter: stdDevFactor::
	//; the average and std. deviation values between all 
	//; detected maxima will be computed. Only those values greater than the 
	//; average plus this parameter multiplied by the std. deviation will 
	//; be considered. Default value 1.0 should be ok.  
	GCV_LINE2D line; bool ret=0; int horidx =0, vertidx=0, maxyidx=0, maxxidx=0;
	float r=0, theta=0, ymax=-999999, xmax=-999999;	GCV_LINE2D horlines[300], vertlines[300]; 
	list< double > yvallist; lti::ipoint a[300],b[300];	
	if(fParams.ShowSteps) line.show=1; else line.show=0;
	//if(maxpos.size()>6) AfxMessageBox("Vorsicht: Es wurden mehr als 6 Linien gefunden.");
	vector <GCV_LINE2D> Lines;
	for (int i=0;i<maxpos.size();i++){
		r = maxpos.at(i).x; theta = maxpos.at(i).y;
		HLT.getSegmentPoints(edgeimage.size(),r,theta,a[i],b[i]);
		line.pt1.x = a[i].x; line.pt1.y = a[i].y; line.pt2.x = b[i].x; line.pt2.y = b[i].y;
 		Lines.push_back(line);
		if(theta>0.5 && theta<2.5){ //; HORIZONTAL
			if(line.pt1.y>570&&line.pt2.y>570)break;
			if(r>ymax) { maxyidx=horidx; ymax=r;}
			horlines[horidx] = line; horidx++; }
		else {//if(r<280){ //; VERTIKAL
			if(r>xmax) { maxxidx=vertidx; xmax=r;}
			vertlines[vertidx] = line; vertidx++;  } }
	if(maxxidx>1) {AfxMessageBox("Es wurden zuviele vertikale Linien erkannt"); }

	//; KREUZPUNKTE
	GCV_POINT2D crosspoint1, crosspoint2, zeropt; bool crossing1=0, crossing2=0;
	crossing1 = CalculateCrossPoint(horlines[maxyidx], vertlines[maxxidx], crosspoint1);
	crossing2 = CalculateCrossPoint(horlines[maxyidx], vertlines[maxxidx^1], crosspoint2);
	if(crossing1 && crossing2)
		if( crosspoint1.x < crosspoint2.y) {
			Workpiece_Points.pt1 = crosspoint1; Workpiece_Points.pt2 = crosspoint2; }
		else { 
			Workpiece_Points.pt2 = crosspoint1; Workpiece_Points.pt1 = crosspoint2; }
	if( !( Workpiece_Points.pt1 == zeropt || Workpiece_Points.pt2 == zeropt ) ){
		Calc_PiercingPoints(Workpiece_Points);	} return 1;}
