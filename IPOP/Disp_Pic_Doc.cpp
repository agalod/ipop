// Disp_Pic_Doc.cpp : Implementierung der Klasse CDisp_Pic_Doc
//

#include "stdafx.h"
#include "IPOPApp.h"

#include "Disp_Pic_Doc.h"
#include "Dlg_Universal.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDisp_Pic_Doc
    
IMPLEMENT_DYNCREATE(CDisp_Pic_Doc, CDocument)

BEGIN_MESSAGE_MAP(CDisp_Pic_Doc, CDocument)
	//{{AFX_MSG_MAP(CDisp_Pic_Doc)
		// HINWEIS - Hier werden Mapping-Makros vom Klassen-Assistenten eingefügt und entfernt.
		//    Innerhalb dieser generierten Quelltextabschnitte NICHTS VERÄNDERN!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDisp_Pic_Doc Konstruktion/Destruktion

CDisp_Pic_Doc::CDisp_Pic_Doc()
{
	// ZU ERLEDIGEN: Hier Code für One-Time-Konstruktion einfügen
	m_Etalon_Cols = m_Etalon_Rows = 0;
	m_Mode = 1;
}

CDisp_Pic_Doc::~CDisp_Pic_Doc()
{
	((CIPOPApp*) AfxGetApp())->m_Disp_pPicDoc = 0;
}

BOOL CDisp_Pic_Doc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// ZU ERLEDIGEN: Hier Code zur Reinitialisierung einfügen
	// (SDI-Dokumente verwenden dieses Dokument)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CDisp_Pic_Doc Serialisierung

void CDisp_Pic_Doc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// ZU ERLEDIGEN: Hier Code zum Speichern einfügen
	}
	else
	{
		// ZU ERLEDIGEN: Hier Code zum Laden einfügen
	}
}

/////////////////////////////////////////////////////////////////////////////
// CDisp_Pic_Doc Diagnose

#ifdef _DEBUG
void CDisp_Pic_Doc::AssertValid() const
{
	CDocument::AssertValid();
}

void CDisp_Pic_Doc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CDisp_Pic_Doc Befehle

//DEL CImageServer* CDisp_Pic_Doc::GetImageServer()
//DEL {
//DEL 	return &m_ImageServer;
//DEL }
#define INITMAT INITCVMAT
#define INITCVMAT(mat,r,c)\
CvMat mat = cvMat(r,c,CV_MAT64D,NULL);cvmAlloc(&mat);

#define FREE(mat) cvmFree(&mat);

#ifndef MYFUNCS
#define MYFUNCS
void Transform3DPt( double mat[9], double pt[3], double retpt[3] ){
	for(int i=0; i<3;i++){
		retpt[i] = pt[0] * mat[i*3+0] + pt[1] * mat[i*3+1] + pt[2] * mat[i*3+2]; 
	}
}

void Mult3Mats( double mat1[9], double mat2[9], double retmat[9] ){
	retmat[0] = mat1[0]*mat2[0] + mat1[1] * mat2[3] + mat1[2] * mat2[6]; 
	retmat[1] = mat1[0]*mat2[1] + mat1[1] * mat2[4] + mat1[2] * mat2[7]; 
	retmat[2] = mat1[0]*mat2[2] + mat1[1] * mat2[5] + mat1[2] * mat2[8]; 
	
	retmat[3] = mat1[3]*mat2[0] + mat1[4] * mat2[3] + mat1[5] * mat2[6]; 
	retmat[4] = mat1[3]*mat2[1] + mat1[4] * mat2[4] + mat1[5] * mat2[7]; 
	retmat[5] = mat1[3]*mat2[2] + mat1[4] * mat2[5] + mat1[5] * mat2[8]; 
	
	retmat[6] = mat1[6]*mat2[0] + mat1[7] * mat2[3] + mat1[8] * mat2[6]; 
	retmat[7] = mat1[6]*mat2[1] + mat1[7] * mat2[4] + mat1[8] * mat2[7]; 
	retmat[8] = mat1[6]*mat2[2] + mat1[7] * mat2[5] + mat1[8] * mat2[8];
}

void CrossProduct3DPt( double pt1[3], double pt2[3], double retpt[3] ){
	retpt[0] = pt1[1]*pt2[2] - pt1[2]*pt2[1];
	retpt[1] = pt1[2]*pt2[0] - pt1[0]*pt2[2];
	retpt[2] = pt1[0]*pt2[1] - pt1[1]*pt2[0];
}

double Norm3DPt( double pt[3] ){
	return ( sqrt( pow(pt[0],2) + pow(pt[1],2) + pow(pt[2],2) ) );
}
#endif



void CDisp_Pic_Doc::Image_DefineGrid()
{
/*
MATLAB- CODE
------------
function [XX,H] = projectedGrid ( P1, P2, P3, P4 , (*m_Etalon_Cols), (*m_Etalon_Rows));
% new formalism using homographies
a00 = [P1;1];
a10 = [P2;1];
a11 = [P3;1];
a01 = [P4;1];
% Compute the planart collineation:
[H] = compute_collineation (a00, a10, a11, a01);
% Build the grid using the planar collineation:
x_l = ((0:((*m_Etalon_Cols)-1))'*ones(1,(*m_Etalon_Rows)))/((*m_Etalon_Cols)-1);
y_l = (ones((*m_Etalon_Cols),1)*(0:((*m_Etalon_Rows)-1)))/((*m_Etalon_Rows)-1);
pts = [x_l(:) y_l(:) ones((*m_Etalon_Cols)*(*m_Etalon_Rows),1)]';
XX = H*pts;
	XX = XX(1:2,:) ./ (ones(2,1)*XX(3,:));*/
	
	//; DECLARATIONS
	//; ------------
	CIPOPApp* pApp = (CIPOPApp*) AfxGetApp();
	GCV_CAMERA *camera = (pApp->m_Dlg_CamParams->m_Camera);
	if(m_Etalon_Corners.pt1.x == 0 && m_Etalon_Corners.pt2.x==0 &&
		m_Etalon_Corners.pt3.x==0 && m_Etalon_Corners.pt4.x==0){
		//AfxMessageBox("Definieren sie erst die Eckpunkte.");
		return;}
	int i=0, NumPoints = (*m_Etalon_Cols)*(*m_Etalon_Rows), ptcter=0, three=3; double temp;
	double a00[3],  a10[3],  a11[3],  a01[3];	
	double H[9], Hnorm[9], inv_Hnorm[9], Hrem[9], V1n[3], V2n[3], V1[3], V2[3]; 
	double ptsnorm1[4][2], ptsnorm[4][3], scxx=0, scyy=0, mxx=0, myy=0;
	double alpha_x=0, alpha_y=0, a00n[3], a10n[3], a11n[3], a01n[3];
	double p1[3],p2[3],p3[3],p4[3]; 
	double* x_row = new double[(*m_Etalon_Cols)];
	double* y_col = new double[(*m_Etalon_Rows)];
	CvPoint3D32f* XYZ = new CvPoint3D32f[NumPoints]; //100 * m_Img_Num]; 
	CvPoint2D32f* XY  = new CvPoint2D32f[NumPoints];
	//; -------------
  	a00[0] = m_Etalon_Corners.pt1.x; a00[1] = m_Etalon_Corners.pt1.y; a00[2] = 1;
	a10[0] = m_Etalon_Corners.pt2.x; a10[1] = m_Etalon_Corners.pt2.y; a10[2] = 1;
	a11[0] = m_Etalon_Corners.pt3.x; a11[1] = m_Etalon_Corners.pt3.y; a11[2] = 1;
	a01[0] = m_Etalon_Corners.pt4.x; a01[1] = m_Etalon_Corners.pt4.y; a01[2] = 1;
	//; CALCULATE HNORM
	//; ---------------
	mxx = (a00[0] + a10[0] + a11[0] + a01[0]);
	mxx /= 4.0;
	myy = (a00[1] + a10[1] + a11[1] + a01[1]);
	myy /= 4.0;
	a00n[0] = a00[0] - mxx; a10n[0] = a10[0] - mxx; a11n[0] = a11[0] - mxx; a01n[0] = a01[0] - mxx; 
	a00n[1] = a00[1] - myy; a10n[1] = a10[1] - myy; a11n[1] = a11[1] - myy; a01n[1] = a01[1] - myy; 
	scxx = (double)( abs(a00n[0]) + abs(a10n[0]) + abs(a11n[0]) + abs(a01n[0]) );
	scxx /= 4.0;
	scyy = (double)( abs(a00n[1]) + abs(a10n[1]) + abs(a11n[1]) + abs(a01n[1]) );
	scyy /= 4.0;
 	 Hnorm[0] = 1.0/scxx;	Hnorm[1] = 0;	Hnorm[2] = -mxx/scxx;
	 Hnorm[3] = 0;	Hnorm[4] = (double) 1.0/scyy;	Hnorm[5] = (double) -myy/scyy;
	 Hnorm[6] = 0;	Hnorm[7] = 0;	Hnorm[8] = 1;
	 inv_Hnorm[0] = scxx;	inv_Hnorm[1] = 0;	inv_Hnorm[2] = mxx;
	 inv_Hnorm[3] = 0;	inv_Hnorm[4] = scyy;	inv_Hnorm[5] = myy;
	 inv_Hnorm[6] = 0;	inv_Hnorm[7] = 0;	inv_Hnorm[8] = 1;
	 //; ---------------
	 Transform3DPt(Hnorm,a00,a00n);	Transform3DPt(Hnorm,a10,a10n);
	 Transform3DPt(Hnorm,a11,a11n);	Transform3DPt(Hnorm,a01,a01n);
	 CrossProduct3DPt(a00n,a10n,p1); 
	 CrossProduct3DPt(a01n,a11n,p2);
	 CrossProduct3DPt(a00n,a01n,p3);	
	 CrossProduct3DPt(a10n,a11n,p4);	
	 CrossProduct3DPt( p1, p2, V1n);
	 CrossProduct3DPt( p3, p4, V2n);	
	 Transform3DPt(inv_Hnorm, V1n,V1);
	 Transform3DPt(inv_Hnorm, V2n,V2);
	 temp = Norm3DPt(V1n);
	 V1n[0] /= temp; 	V1n[1] /= temp; 	V1n[2] /= temp;
	 temp = Norm3DPt(V2n);	
	 V2n[0] /= temp; 	V2n[1] /= temp; 	V2n[2] /= temp;
	 alpha_x = (a10n[1]*a00n[0] - a10n[0]*a00n[1]) / (V1n[1]*a10n[0]-V1n[0]*a10n[1]);
	 alpha_y = (a01n[1]*a00n[0] - a01n[0]*a00n[1])/(V2n[1]*a01n[0]-V2n[0]*a01n[1]);
	 Hrem[0] = alpha_x*V1n[0]; Hrem[1] = alpha_y*V2n[0]; Hrem[2] = a00n[0]; 
	 Hrem[3] = alpha_x*V1n[1]; Hrem[4] = alpha_y*V2n[1]; Hrem[5] = a00n[1]; 
	 Hrem[6] = alpha_x*V1n[2]; Hrem[7] = alpha_y*V2n[2]; Hrem[8] = a00n[2]; 
	 Mult3Mats(inv_Hnorm, Hrem, H);
	 for(  int y = 0; y < (*m_Etalon_Rows); y++ ){
		 for(  int x = 0; x < (*m_Etalon_Cols); x++ ){
			 XYZ[ptcter].x = ((double)1.0/((*m_Etalon_Cols)-1))*x;//m_Pts_pObject[currImage][ptcter].x = 
			 XYZ[ptcter].y = ((double)1.0/((*m_Etalon_Rows)-1))*y;//m_Pts_pObject[currImage][ptcter].y = 
			 XYZ[ptcter].z = 1;//  m_Pts_pObject[currImage][ptcter].z = 
			 ptcter++; }}
	 for(  i = 0; i < NumPoints; i++ ){
		 p1[0] = XYZ[i].x; p1[1] = XYZ[i].y; p1[2] = XYZ[i].z; 
		 Transform3DPt(H,p1,p2);
		 XY[i].x = p2[0] / p2[2];
		 XY[i].y = p2[1] / p2[2]; }
	 IplImage* greyimg = cvCreateImageHeader(cvSize(Image_Width(), Image_Height()),IPL_DEPTH_8U,1); 
	 IplImage* greyimgcopy = cvCreateImageHeader(cvSize(Image_Width(), Image_Height()),IPL_DEPTH_8U,1); 
	 cvCreateImageData(greyimg); cvCreateImageData(greyimgcopy);
	 CImage* CurrentImage = CList_GetCurrentImage();
	 if(CurrentImage->Bpp()!=8)
		 cvCvtColor(CurrentImage->GetImage(), greyimg, CV_RGB2GRAY); // convert color image to grey
	 else {greyimg = greyimgcopy = CurrentImage->GetImage();}
	 //Find sub-corners
	 CvMemStorage* memsto = cvCreateMemStorage( 0 );
	 cvFindChessBoardCornerGuesses(greyimg, greyimgcopy, memsto, cvSize(7,10), XY, &NumPoints );
	 cvReleaseMemStorage(&memsto);
	 cvFindCornerSubPix(greyimg, XY, NumPoints, cvSize 
		 (10,10), cvSize
		 (1, 1), cvTermCriteria (CV_TERMCRIT_ITER | CV_TERMCRIT_EPS, 100000, 
		 0.0001));
	 GCV_POINT2D cpt; //m_Etalon_Points.clear();
	 GCV_IMAGEPOINT3D imagepoint; GCV_VECTOR3D vec3d;
	 imagepoint.camera = *camera;
	m_Etalon_Points_Camera.clear();
	m_Etalon_Points_Image.clear();
	 for(  i = 0; i < NumPoints; i++ ){
		 cpt.x=XY[i].x; cpt.y=XY[i].y; 
		 imagepoint = cpt; vec3d = imagepoint.vector;
		 vec3d *= 300;
		 m_Etalon_Points_Camera.push_back(vec3d);
		 m_Etalon_Points_Image.push_back(cpt);
	 }
	 delete[] XYZ; delete[] XY;
	 delete[] x_row; delete[] y_col;
}


void CDisp_Pic_Doc::Apply_Binarization() {
	CWaitCursor waitcursor;
/*	CIPOPApp* pApp = (CIPOPApp*) AfxGetApp();
	CDlg_IPParams* dlg = pApp->m_Dlg_IPParams;
	lti::thresholding::parameters pars;
	pars.lowThreshold = (double)dlg->m_BinThreshold /255.0;
	pars.highThreshold = 1;	pars.keepInRegion = 0;
	lti::thresholding bin;	bin.setParameters(pars);
	lti::channel binimage, erimage, dilimage, srcImage=CList_GetCurrentImageAsLTI();*/
	//bin.apply(CList_GetCurrentImageAsLTI(),binimage);
	//CList_AppendImage(binimage,"Binarisiert"); 	CList_AppendImage(binimage,"Binarisiert"); 

	IplImage iplbinimage; 
	CImage* img0 = CList_GetCurrentImage();
	CImage* img1 = new CImage(); img1->CopyOf(*img0);
	CImage* img2 = new CImage(); img2->CopyOf(*img0);
	CImage* img4 = new CImage(); img4->CopyOf(*img0);
	CImage* img5 = new CImage(); img5->CopyOf(*img0);
	//; BINARISIERUNG
	cvThreshold(img0->GetImage(), img1->GetImage(),150,255,CV_THRESH_BINARY); 
	//CList_AppendImage(img1,"Binarisiert");
	//; ERODIERUNG, 40MAL 
	cvErode(img1->GetImage(),img2->GetImage(), 0,40); 
	//CList_AppendImage(img2,"Erodiert");
	//; EIN WEIßER PUNKT
	img2->Save("CImageServer_SaveIplImage.bmp");
	lti::loadImage loader; 	lti::channel currImage;   
	loader.load("CImageServer_SaveIplImage.bmp",currImage);  // load BMP image
	lti::ipoint ipt = currImage.getIndexOfMaximum(); CvConnectedComp comp;
	//; FLOODFILL
	cvFloodFill(img4->GetImage(),cvPoint(ipt.x,ipt.y),0,3,3,&comp);
	//CList_AppendImage(img4,"Erodiert");
	//; SUBTRAKTION
	iplSubtract(img0->GetImage(),img4->GetImage(),img5->GetImage());
	CList_AppendImage(img5,"CV-Flooded");
	img2->Destroy();
	img1->Destroy();
	img4->Destroy();
	//void cvFloodFill( IplImage* img, CvPoint seedPoint, double newVal, double
	//loDiff, double upDiff, CvConnectedComp* comp, int connectivity=4 );

/*	lti::kernel2D< float > kern(15,15,1.0);
	lti::erosion eros; 	eros.setKernel(kern);
	lti::dilation dil;  dil.setKernel(kern);
	eros.apply(binimage,erimage); 
	CList_AppendImage(erimage,"Erodiert"); */
//	dil.apply(erimage, dilimage);
//	CList_AppendImage(dilimage,"Dilatiert"); 
}


void CDisp_Pic_Doc::Apply_Edgefilter() {
	lti::cannyEdges edgefilter;
	lti::channel8 edgeimage8;
	lti::channel orientationimage, edgeimage;
	edgefilter.apply(CList_GetCurrentImageAsLTI(),edgeimage8,orientationimage);
	edgeimage.castFrom(edgeimage8);
	CList_AppendImage(edgeimage,"Kantengefiltert"); }


void CDisp_Pic_Doc::Apply_Hough()
{
/*	float lines[300]; int numlines=0;
	IplImage* img = CList_GetCurrentImageAsIPL();
	cvHoughLines(img,1,1,50,lines,numlines);*/
	// create default HLT (Hough Line Transform) using default parameters
	CIPOPApp* pApp = (CIPOPApp*) AfxGetApp();
	CDlg_IPParams* dlg = pApp->m_Dlg_IPParams;
	bool showsteps = dlg->m_bShowSteps;
	lti::orientedHLTransform::parameters HTpars;
	HTpars.range = 180;
	if(dlg->m_bHoughAccu180) HTpars.accuracy = 180;
	else if(dlg->m_bHoughAccu540) HTpars.accuracy = 540;
	else HTpars.accuracy = 360;
	lti::orientedHLTransform HLT;
	HLT.setParameters(HTpars);
	lti::gHoughTransform GHT;
	lti::channel32 transformAccu32;
	lti::channel transformAccu, srcImage=CList_GetCurrentImageAsLTI();
	// THE HOUGH TRANSFORM
	HLT.apply(srcImage,
		//CList_GetCurrentImageAsLTI(-1),transformAccu32);
		srcImage,transformAccu32);
	transformAccu.castFrom(transformAccu32);
	CList_AppendImage(transformAccu,"Transform-Akku");
	// Now get the local maxima of the transformAccu
	lti::vector< lti::tpoint<float> > maxpos;
	HLT.getHoughSpacePoints(transformAccu32,maxpos,dlg->m_HoughSensivity);
	GCV_LINE2D line; bool ret=0; m_Lines.clear(); float r=0, theta=0, ymax=0, xmax;
	GCV_LINE2D horlines[2], vertlines[2]; 
	int horidx =0, vertidx=0, maxyidx=0, maxxidx=0;
	list< double > yvallist; lti::ipoint a[300],b[300];
	if(showsteps) line.show=1; else line.show=0;
	if(maxpos.size()>10) AfxMessageBox("Vorsicht: Es wurden mehr als 10 Linien gefunden.");
	for (int i=0;i<maxpos.size();i++){
		r = maxpos.at(i).x; theta = maxpos.at(i).y;
		HLT.getSegmentPoints(srcImage.size(),r,theta,a[i],b[i]);
		line.pt1.x = a[i].x; line.pt1.y = a[i].y;
		line.pt2.x = b[i].x; line.pt2.y = b[i].y;
		
		if(theta>1 && theta<2){
			if(r>ymax && r<280) { maxyidx=horidx; ymax=r;}
			horlines[horidx] = line; horidx++; }
		else if(r<280){
			if(r>xmax) { maxxidx=vertidx; xmax=r;}
			vertlines[vertidx] = line; vertidx++; 
			m_Lines.push_back(line); }	}
	if(maxxidx>1) {AfxMessageBox("Es wurden zuviele vertikale Linien erkannt"); return;}
	m_Lines.clear();
	m_Lines.push_back(horlines[maxyidx]);
	m_Lines.push_back(vertlines[maxxidx]);
	m_Lines.push_back(vertlines[maxxidx^1]);
	//; KREUZPUNKTE
	GCV_POINT2D crosspoint; bool crossing=0;
	//for (i=0;i<maxpos.size();i++)
	//	for (int j=i+1;j<maxpos.size();j++){
	crossing = CalculateCrossPoint(horlines[maxyidx], vertlines[maxxidx^1], crosspoint);
	if(crossing) m_Workpiece_Points.pt1 = crosspoint; 
	crossing = CalculateCrossPoint(horlines[maxyidx], vertlines[maxxidx], crosspoint);
	if(crossing) m_Workpiece_Points.pt2 = crosspoint; }


/*
	CImage* bin = new CImage(); bin->CopyOf(*org);  CImage* bic = new CImage(); bic->CopyOf(*org);
	CImage* ero = new CImage(); ero->CopyOf(*org);	CImage* flo = new CImage(); flo->CopyOf(*org);
	CImage* res = new CImage(); res->CopyOf(*org);	CImage* edg = new CImage(); edg->CopyOf(*org);
	CImage* sub = new CImage(); sub->CopyOf(*org);
	bic->CopyOf(*bin);
	lti::regionGrowing RegGrow; lti::regionGrowing::parameters regparams;

*/

void CDisp_Pic_Doc::Apply_FloodFill() {
	CImage* pic = new CImage(); pic->CopyOf(*CList_GetCurrentImage());
	cvErode(pic->GetImage(),pic->GetImage(), 0,40); 
	CList_AppendImageCopy(pic, "Erodiert");	
	pic->Save("CImageServer_SaveIplImage.bmp");	
	lti::channel currImage; lti::loadImage loader; 	  	
	loader.load("CImageServer_SaveIplImage.bmp",currImage);
	lti::ipoint ipt = currImage.getIndexOfMaximum(); CvConnectedComp comp;
	cvFloodFill(pic->GetImage(),cvPoint(ipt.x,ipt.y),0,7,7,&comp,8);
	CList_AppendImageCopy(pic, "Flooded");	}


void CDisp_Pic_Doc::Apply_Erosion(){
	CImage* pic = new CImage(); pic->CopyOf(*CList_GetCurrentImage());
	cvErode(pic->GetImage(),pic->GetImage(), 0,40); 
	CList_AppendImageCopy(pic, "Erodiert");	}


void CDisp_Pic_Doc::Apply_Preprocess() {
	CWaitCursor waitcursor;	CIPOPApp* pApp = (CIPOPApp*) AfxGetApp();
	CDlg_IPParams* dlg = pApp->m_Dlg_IPParams;	bool showsteps = dlg->m_bShowSteps;

	lti::channel binimage, srcImage=CList_GetCurrentImageAsLTI();
	lti::channel currImage; lti::loadImage loader; 	  	
	lti::thresholding ltibin;	lti::thresholding::parameters pars;
	lti::histograming1D histograming; lti::histogram1D hist;
	lti::histograming1D::parameters histpars;
	lti::cannyEdges edgefilter;	lti::channel8 edgeimage8;
	lti::channel orientationimage, edgeimage;
	CImage* pic = new CImage(); pic->CopyOf(*CList_GetCurrentImage());

	//; BINARISIERUNG
	cvThreshold(pic->GetImage(), pic->GetImage(),dlg->m_BinThreshold,255,CV_THRESH_BINARY); 
	if(showsteps) CList_AppendImageCopy(pic, "Binarisiert"); 
	CImage* bincopy1 = new CImage(); bincopy1->CopyOf(*pic,0);	
	CImage* bincopy2 = new CImage(); bincopy2->CopyOf(*pic,0);	
	//; ERODIERUNG, 40MAL 
	cvErode(pic->GetImage(),pic->GetImage(), 0,40); 
	if(showsteps) CList_AppendImageCopy(pic, "Erodiert");	
	//; EIN WEIßER PUNKT
	pic->Save("CImageServer_SaveIplImage.bmp");	loader.load("CImageServer_SaveIplImage.bmp",currImage);
	lti::ipoint ipt = currImage.getIndexOfMaximum(); CvConnectedComp comp;
	//; FLOODFILL
	cvFloodFill(bincopy1->GetImage(),cvPoint(ipt.x,ipt.y),0,7,7,&comp,8);
	if(showsteps) CList_AppendImageCopy(bincopy1, "Flooded");	
	//; SUBTRAKTION
	iplSubtract(bincopy2->GetImage(),bincopy1->GetImage(),pic->GetImage()); 
	if(showsteps) CList_AppendImageCopy(pic, "Subtrahiert");	
	//cvThreshold(pic->GetImage(), pic->GetImage(),160,255,CV_THRESH_BINARY); 
	CList_AppendImageCopy(pic,"Segmentiert");
	//; KANTENFILTER
//	cvCanny( res->GetImage(), edg->GetImage(), 0.5,1.0 );
	pic->Save("CImageServer_SaveIplImage.bmp");	loader.load("CImageServer_SaveIplImage.bmp",currImage);
	pic->Destroy(); bincopy1->Destroy(); bincopy2->Destroy(); 
	edgefilter.apply(currImage,edgeimage8,orientationimage); edgeimage.castFrom(edgeimage8);
	if(showsteps) CList_AppendImage(edgeimage, "Kantengefiltert");
	//; HOUGHTRANSFORMATION
	lti::orientedHLTransform::parameters HTpars; HTpars.range = 180; HTpars.accuracy = 540;
	//if(dlg->m_bHoughAccu180) HTpars.accuracy = 180;
	//else if(dlg->m_bHoughAccu540) HTpars.accuracy = 540; else HTpars.accuracy = 360;
	lti::orientedHLTransform HLT; HLT.setParameters(HTpars);
	lti::channel32 transformAccu32;	lti::channel transformAccu;
	HLT.apply(edgeimage,orientationimage,transformAccu32);
	//CList_GetCurrentImageAsLTI(-1),transformAccu32);
	//if(showsteps) { transformAccu.castFrom(transformAccu32);
	//	CList_AppendImage(transformAccu,"Transform-Akku"); }
	/////////////////////////////////////////////////////////////////////////////
	//; LINIEN-EXTRAKTION
	// Now get the local maxima of the transformAccu
	lti::vector< lti::tpoint<float> > maxpos;
	HLT.getHoughSpacePoints(transformAccu32,maxpos,dlg->m_HoughSensivity);
	//; 3rd parameter: stdDevFactor::
	//; the average and std. deviation values between all 
	//; detected maxima will be computed. Only those values greater than the 
	//; average plus this parameter multiplied by the std. deviation will 
	//; be considered. Default value 1.0 should be ok.  
	GCV_LINE2D line; bool ret=0; m_Lines.clear(); 
	int horidx =0, vertidx=0, maxyidx=0, maxxidx=0;
	float r=0, theta=0, ymax=-999999, xmax=-999999;	GCV_LINE2D horlines[300], vertlines[300]; 
	list< double > yvallist; lti::ipoint a[300],b[300];	if(showsteps) line.show=1; else line.show=0;
	//if(maxpos.size()>6) AfxMessageBox("Vorsicht: Es wurden mehr als 6 Linien gefunden.");
	m_Lines.clear();
	for (int i=0;i<maxpos.size();i++){
		r = maxpos.at(i).x; theta = maxpos.at(i).y;
		HLT.getSegmentPoints(srcImage.size(),r,theta,a[i],b[i]);
		line.pt1.x = a[i].x; line.pt1.y = a[i].y; line.pt2.x = b[i].x; line.pt2.y = b[i].y;
 		m_Lines.push_back(line);
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
			m_Workpiece_Points.pt1 = crosspoint1; m_Workpiece_Points.pt2 = crosspoint2; }
		else { 
			m_Workpiece_Points.pt2 = crosspoint1; m_Workpiece_Points.pt1 = crosspoint2; }
	if( !( m_Workpiece_Points.pt1 == zeropt || m_Workpiece_Points.pt2 == zeropt ) ){
		pApp->m_IPOP.Calc_PiercingPoints(m_Workpiece_Points);
		pApp->m_Dlg_Pose->UpdateData(0); } 
}



void CDisp_Pic_Doc::SetTitle() {
	char text[300]; CString str=" - ";
	sprintf( text, "Bild %d von %d", CList_GetIndex()+1, CList_GetCount() );
	if(m_Mode==0) CDocument::SetTitle("Kalibriermodus"+
		str+text+str+CList_GetCurrentImageName() );
	else CDocument::SetTitle("Registriermodus" + str + text+str+CList_GetCurrentImageName() ); }


void CDisp_Pic_Doc::DeleteCurrentImage(){
	CList_DeleteCurrImage(); SetTitle(); }


/*
	//; CROPPING, SO THE IMAGEEDGE IS CLEAN, WITHOUT EDGES
	srcImage.copy(srcImage, 2, 574, 4, 766); 
	CList_DeleteCurrImage(); CList_AppendImage(srcImage,"Cropped");
	//int val = cvMean(CList_GetCurrentImage()->GetImage());
	histpars.intervalLow = 200.0/255.0; histpars.intervalHigh = 1.0; 
	histograming.setParameters(histpars);
	histograming.apply(srcImage,hist);
	double val1 = hist.getNumberOfEntries();
//	CString str; str.Format("%d", val); AfxMessageBox(str);
	//pars.lowThreshold = dlg.m_Edit1/255.0;
	//pars.highThreshold = dlg.m_Edit2/255.0;
	pars.lowThreshold = (double)dlg->m_BinThreshold /255.0;
	pars.highThreshold = 1;
	pars.keepInRegion = 0;
	ltibin.setParameters(pars);
	ltibin.apply(srcImage,binimage);
	if(showsteps) CList_AppendImage(binimage,"Binarisiert");
*/


