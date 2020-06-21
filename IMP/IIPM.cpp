// CIIPM.cpp: Implementierung der Klasse CIIPM.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h" 
#include "IIPM.h"

#ifdef _DEBUG 
#undef THIS_FILE 
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW 
#endif

//////////////////////////////////////////////////////

CIIPM::CIIPM() {
	fParameters_IIPM.DistanceMatrix_Max = 50;
	fParameters_IIPM.Iterations_Max = 100;
	fParameters_IIPM.Translation_Min = 0;
	fParameters_IIPM.Weight_TH = 1;
	fDistances_Sum = 0; fbFixedCorrespondences = 0;
	fNumIterations = 0; }  


CIIPM::~CIIPM(){
}


void CIIPM::Transform_Pts_Obj(GCV_MATRIX3D &mat){
	for( int i=0; i<fPts_Obj_Init.size(); i++ ){
		fPts_Obj_Current[i] = TransformVector(mat, fPts_Obj_Init[i]);
	}}


void CIIPM::Calc_DistanceMatrix(){
	if(fbFixedCorrespondences)
		for(int i=0; i != fPts_Obj_Current.size(); i++)
			fDistance_Matrix(i,i) = DistanceLinePoint( fPts_Img[i], fPts_Obj_Current[i]);
	else
	for(int i=0; i != fPts_Obj_Current.size(); i++)
		for(int j=0; j != fPts_Img.size(); j++)
			fDistance_Matrix(i,j) = DistanceLinePoint( fPts_Img[j], fPts_Obj_Current[i]); }


//; FOR EVERY PROJECTION- RAY A 3D- OBJECT- POINT IS BEING FOUND
void CIIPM::Calc_CorrespondingPoints(){
	fPts_Corresponding.clear();	fDistances_Sum = 0; double Min = 99999999; 
	int size = fPts_Obj_Current.size(), oppos=0, prpos=0, xc=0, counter=0;
	GCV_LINE3D PPair; GCV_VECTOR3D projraynorm;
	if(fbFixedCorrespondences)
		for(int i=0; i != fPts_Obj_Current.size(); i++) {
			fDistances_Sum += fDistance_Matrix(i,i);//fDistances[i] = 
			PPair.pt1 = fPts_Obj_Current[i];
			projraynorm = fPts_Img[i]/Magnitude(fPts_Img[i]);
			PPair.pt2 = ( projraynorm * fPts_Obj_Current[i] ) // length ...
				* projraynorm; // ... times the vector
			fPts_Corresponding.push_back(PPair); }
	else 
			do{ Min = fDistance_Matrix.MinValue(oppos, prpos);
    		//; Calculates the minimum in each column
			if( Min == 999999 || counter>=size ) break;
			for(xc=0;xc<fPts_Img.size();xc++) 
				fDistance_Matrix(oppos,xc)=999999;//;fill the row with high #´s
			fDistances[counter] = Min; fDistances_Sum += Min;
			PPair.pt1 = fPts_Obj_Current[oppos];
			projraynorm = fPts_Img[prpos]/Magnitude(fPts_Img[prpos]);
			PPair.pt2 = ( projraynorm * fPts_Obj_Current[oppos] ) // length ...
				* projraynorm; // ... times the vector
			fPts_Corresponding.push_back(PPair);counter++;
		}while(1); }


void CIIPM::Calc_MeansXandYPoints() {
	fMeanXPoints.clear(); fMeanYPoints.clear();
	for(int i=0; i<fPts_Corresponding.size(); i++)
		for(int j=0;j<3;j++){
		fMeanXPoints(j) += fPts_Corresponding[i].pt1(j); 
		fMeanYPoints(j) += fPts_Corresponding[i].pt2(j); }
	fMeanXPoints /= fPts_Corresponding.size();
	fMeanYPoints /= fPts_Corresponding.size(); }
    


void CIIPM::Calc_CrossCorrelation_Matrix(){
	fCrossCorrelation_Matrix = ZeroMatrix();
	for(int i=0; i<fPts_Corresponding.size(); i++)
		fCrossCorrelation_Matrix  = MatrixAdd(fCrossCorrelation_Matrix,
			( TranspProduct( (fPts_Corresponding[i].pt2 - fMeanYPoints),
			(fPts_Corresponding[i].pt1 - fMeanXPoints) )));}


void CIIPM::Calc_Transformation_Matrix() {
	static GCV_MATRIX3D Rot_Current, Rot_Overall; int j=0, i=0;
	static double data[9];	GCV_VECTOR3D TransVec, w_vec;	
	static lti::singularValueDecomp<double> ltisvd;
	static lti::matrix<double> u(3,3), v(3,3), r(3,3), x(3,3);
	static lti::vector<double> w(3);
	//; BEGIN LTI-LIB CALCULATIONS
	for( i=0; i<3; i++) for( j=0; j<3; j++) x.at(j,i) = fCrossCorrelation_Matrix(j,i);
	ltisvd.apply(x,u,w,v); 
	for( i=0; i<3; i++) w_vec(i) = w[i]; u.multiply(v.transpose());
	for( i=0; i<3; i++) for( j=0; j<3; j++) Rot_Current(i,j) = u.at(i,j);
	//; END LTI-LIB CALCULATIONS

/*	//; BEGIN OpenCV CALCULATIONS
	static double X_data[9], U_data[9], S_data[9], V_data[9], R_data[9];
	static CvMat X = cvMat( 3, 3, CV_64FC1, X_data ), U = cvMat( 3, 3, CV_64FC1, U_data ),
				 S = cvMat( 3, 3, CV_64FC1, S_data ), V = cvMat( 3, 3, CV_64FC1, V_data ),
				 R = cvMat( 3, 3, CV_64FC1, R_data );
	for( i=0; i<3; i++) for( j=0; j<3; j++) X_data[j+i*3] = fCrossCorrelation_Matrix(i,j);
		//cvmSet(&X,i,j,fCrossCorrelation_Matrix(i,j));
	cvSVD(&X, &S, &U, &V, CV_SVD_V_T | CV_SVD_MODIFY_A); cvmMul(&U,&V,&R);
	for( i=0; i<3; i++) for( j=0; j<3; j++) Rot_Current(i,j) = cvmGet(&R,i,j);
	//; END OpenCV CALCULATIONS*/

	Rot_Current = MatrixMult(Rot_Current, Rot_Current); //; build square
	fTrans_Overall.SetRotation(MatrixMult(Rot_Current, fTrans_Overall.GetRotation()));
	fTrans_Overall.SetTranslation(fMeanYPoints); }
		

void CIIPM::Reset(){
	fTrans_Overall=IdentityMatrix(); fPts_Corresponding.clear(); fPts_Img.clear(); }


void CIIPM::Calc_RegIIPM_Update() {
	Transform_Pts_Obj(fTrans_Overall); if( fPts_Img.size()==0 ) return;
	Calc_DistanceMatrix(); Calc_CorrespondingPoints(); Calc_MeansXandYPoints(); }


void CIIPM::Calc_RegIIPM_OneStep() {
	if( fPts_Img.size()==0 ) return;
	Calc_CrossCorrelation_Matrix(); Calc_Transformation_Matrix(); 
	CIIPM::Calc_RegIIPM_Update(); fNumIterations++; }


void CIIPM::Calc_RegIIPM_Init() {
	fNumIterations=0; if(fPts_Obj_Init.size()==0 ){
		AfxMessageBox("Fehler: fPts_Obj_Init.size()==0"); return; }
	fTrans_Overall = fTrans_Init; fPts_Obj_Current = fPts_Obj_Init;
	CIIPM::Calc_RegIIPM_Update(); }
