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

float MedianValue(list<float> aList){
	aList.sort(); int index=0;
	vector<float> Vec;
	list<float>::iterator listiter = aList.begin();
	for( int i=0; i<aList.size(); i++, listiter++)
		Vec.push_back(*listiter);
	if( (Vec.size()%2)==1){//; uneven number
		index = ( Vec.size() + 1 ) / 2;
		//; calculate the middle position
		return Vec[index-1];}
	else{//; even number
		index = Vec.size() / 2;
		//; calculate the middle position
		return ( Vec[index-1] + Vec[index] ) / 2;	}}; 

		
float MeanValue(float* aField, int num){
	float ret=0;
	for(int i=0;i<num;i++) ret+=aField[i];
	return ret/=num;}

void ErrorHandler(const char * message , bool value){
	int a=0; _exit(-1);}

//////////////////////////////////////////////////////

CIIPM::CIIPM(){
fParameters.Calibration=1;
fThresholds.DistanceMatrix_Max = 50;
fThresholds.Iterations_Max = 100;
fThresholds.Translation_Min = 0;
fThresholds.Weight_TH = 1;
//fThresholds.
}  
CIIPM::~CIIPM(){}


void CIIPM::Transform_Pts_Test(D3DVECTOR aTransVec){	
	for( int i=0; i<fPts_Test.size(); i++ )fPts_Test[i] = aTransVec + fPts_Test[i];}

void CIIPM::Transform_Pts_Test(D3DMATRIX aRotMat){
	for( int i=0; i<fPts_Test.size(); i++ )fPts_Test[i] = TransformVector(fPts_Test[i],aRotMat);}

void CIIPM::Transform_Pts_Fixed(D3DMATRIX aRotMat){
	for( int i=0; i<fPts_Fixed.size(); i++ )fPts_Fixed[i] = TransformVector(fPts_Fixed[i],aRotMat);}


void CIIPM::Transform_Pts_Obj(){
	fTrans_Overall = MatrixMult(fTrans_Camera , fTrans_Overall);
	for( int i=0; i<fPts_Obj.size(); i++ ){
		fPts_Obj[i] = TransformVector(fTrans_Camera_Struct.M, fPts_Obj[i]-fWeightedMeans.Pt1);
		fPts_Obj[i]+=fWeightedMeans.Pt2;}
}

void CIIPM::Calc_Calibration( D3DMATRIX aTransMachineInit ){
	//; DECLARATIONS
	D3DMATRIX OverallRot, MachineRot, MachineRotInv, Rot_MS_TO_CS, Rot_CS_TO_MS;
	D3DVECTOR OverallTransl, MachineTransl, TranslCalib_MS_TO_CS;
	D3DMATRIXVECTOR TransOverall, TransMachineInit;
	TransOverall = SplitMatrix(fTrans_Overall);
	TransMachineInit = SplitMatrix(aTransMachineInit);
	MachineRotInv = MatrixInverse(TransMachineInit.M);   
	//;                Trans  read: Trans_B_TO_A (B in reference to A)
	//;              B      
	//; THE CALIBRATION ROTATIONMATRIX
	//; TRANSFORMATION FROM CAMERA-CS TO MACHINE-CS
	Rot_MS_TO_CS = MatrixMult(TransOverall.M, MachineRotInv);
	//; THE CALIBRATION ROTATIONMATRIX- INVERSE. 
	//; TRANSFORMATION FROM MACHINE-CS TO CAMERA-CS.
	Rot_CS_TO_MS = MatrixInverse(Rot_MS_TO_CS);
	//; CALCULATE THE TRANSLATION- vector FROM CS TO MS
	TranslCalib_MS_TO_CS = TransOverall.V - (TransformVector(Rot_MS_TO_CS , TransMachineInit.V)); 
	//; MERGE TO 4X4- MATRIX AND CALCULATE THE INVERSE
	fCalib_Trans_MS_TO_CS = MergeMatrix(TranslCalib_MS_TO_CS, Rot_MS_TO_CS);
	fCalib_Trans_CS_TO_MS = MatrixInverse(fCalib_Trans_MS_TO_CS);// = TempMat * aTransMachineInit.Inv() * fTrans_Overall;
	//; SET THE NOMINALPOSITION AND ROTATION
	fTransl_Nominal[0] = fTrans_Overall(3,0); fTransl_Nominal[1] = fTrans_Overall(3,1); fTransl_Nominal[2] = fTrans_Overall(3,2);
	RotMatToXYZEuler(fTrans_Overall,fTransl_Nominal[0], fTransl_Nominal[1], fTransl_Nominal[2]);}



void CIIPM::Convert_ToMachineCS(){	
	//; declarations and matrix- splitting
	D3DMATRIX TransCSystemRot, RotOverall, RotMachine;
	D3DVECTOR TranslOverall, TranslMachine;
	fTrans_Machine = MatrixMult(fCalib_Trans_CS_TO_MS , fTrans_Overall);}


//DEL void CIIPM::push_back_ObjPt(float  aX, float  aY, float  aZ){
//DEL 	D3DVECTOR myPt;	myPt(0) = aX;	myPt(1) = aY;	myPt(2) = aZ; myPt(3) = 1;
//DEL 	fPts_Obj.push_back(myPt);}


//DEL void CIIPM::push_back_TestPt(float  aX, float  aY, float  aZ){
//DEL 	D3DVECTOR myPt;	myPt(0) = aX;	myPt(1) = aY;	myPt(2) = aZ; myPt(3) = 1;
//DEL 	fPts_Test.push_back(myPt);}


//DEL void CIIPM::push_back_FixedPt(float  aX, float  aY, float  aZ){
//DEL 	D3DVECTOR myPt;	myPt(0) = aX;	myPt(1) = aY;	myPt(2) = aZ; myPt(3) = 1;
//DEL 	fPts_Fixed.push_back(myPt);}


//DEL void CIIPM::push_back_ImgPt(int  aX, int  aY){
//DEL 	D3DVECTOR myPt(aX, aY, 0); fPts_Img.push_back(myPt);}


//DEL void CIIPM::Set_MaxIter(int  aMaxIter){
//DEL 	fThresholds.Iterations_Max = aMaxIter;}


//;*******************************************************

int CIIPM::Calc_RegIIPM(){   
   //mlfSetErrorHandler(ErrorHandler);
	//fOutputStream.open("c:\\file.txt", ios::out);
	float mean = 0;	int Num_Iteration=0;
	if(fPts_Obj.size()==0 || fPts_Img.size()==0)	{
		MessageBox(0,"Fehler in der Funktion CIIPM::RegIIPM(). (fPts_Obj.size()==0 || fPts_Img.size()==0)", "Fehler!", MB_OKCANCEL);
		return 0;}
	fTrans_Overall = IdentityMatrix();	fTrans_Camera  = fTrans_Init;
	Transform_Pts_Obj(); Convert_PtsImg_To_ProjectionRays();
	//; initial transformation
	if(MessageBox(0,"Drücken sie OK um die Berechnung zu starten.", "Title", MB_OKCANCEL)==IDCANCEL)
		return 0; 
	if(fParameters.MoveGravityCenter)
		Transform_MoveObjectToProjectionAxis();
	do{
		//fOutputStream <<endl<< "Durchlauf "<<Num_Iteration<<":"<<endl;
		Calc_DistanceMatrix();
		Calc_CorrespondingPoints();//; for every projection- ray a 3D- Object- Point is being found
		Calc_Weights();	Calc_WeightedMeans();
		//; the average of each coordinate of each Corresponding- PointPair is calculated
		//; and saved in the PointPair fWeightedMeans 
		Calc_CrossCorrelation_Matrix(); Calc_Transformation_Matrix(); Transform_Pts_Obj();
		Num_Iteration++; mean=MeanValue(fDistances,fPts_Corresponding.size());
	}while( !( Num_Iteration > fThresholds.Iterations_Max ) && ! ( sqrt(  pow(fTrans_Camera(3,0),2) + pow(fTrans_Camera(3,1),2) + pow(fTrans_Camera(3,2),2) ) < fThresholds.Translation_Min ) &&
		!(mean<fThresholds.Translation_Min ));return 1;}
	//CalcCalibration(mat);
	//fOutputStream.close();
//;*******************************************************

   

void CIIPM::Calc_DistanceMatrix(){
	for(int i=0; i != fPts_Obj.size(); i++)
		for(int j=0; j != fRays_Projection.size(); j++){
			fDistance_Matrix(i,j) = DistanceLinePoint( fRays_Projection[j], fPts_Obj[i]);}}



//DEL float CIIPM::Calc_DistanceLinePoint( D3DVECTOR& aProjR, D3DVECTOR& aObjP){
//DEL 	float distance = Magnitude(CrossProduct(aObjP, aProjR)) / Magnitude(aProjR);
//DEL 	return distance;}


void CIIPM::Calc_CorrespondingPoints(){
	//; Calculates the minimum in each column
	fPts_Corresponding.clear();	D3DVECTOR ObjPt;
	//; the 4-dim fPts_Obj[index] has to be converted into a 3-dim ObjPt3
	//; because the vectorproduct and other calculations are only 
	//; possible in 3-dim space.
	float Min = 99999999.f, Tmp = 0, Lotfusspunkt = 0;
	D3DVECTORPAIR PPair; D3DVECTOR projraynorm, objptimg;
	int index = 0, size = fRays_Projection.size();
	int oppos=0, prpos=0, xc=0, yc=0, counter=0;
	do{
		Min = fDistance_Matrix.MinValue(oppos, prpos);
		if( Min == 999999) break;
		for(xc=0;xc<fPts_Obj.size();xc++) 
			fDistance_Matrix(oppos,xc)=999999;//;fill the row with high #´s
		//for(yc=0;yc<fRays_Projection.size();yc++)
		//	fDistance_Matrix(yc,prpos)=999999;//;fill the column with high #´s
		if(Min>fThresholds.DistanceMatrix_Max);
		else{
			fDistances[counter] = Min;
			PPair.Pt1 = fPts_Obj[oppos];
			projraynorm = fRays_Projection[prpos]/Magnitude(fRays_Projection[prpos]);
			//PPair.Pt2 = ( fPts_Obj[oppos].z / fCamera.FocalLength ) * fRays_Projection[prpos];


			PPair.Pt2 = ( projraynorm * fPts_Obj[oppos] ) * projraynorm;
			//			/ SquareMagnitude(fRays_Projection[prpos]) ) * (projraynorm);
						//* (fRays_Projection[prpos]/Magnitude(fRays_Projection[prpos]) );//;Lotfusspunkt
			//PPair.Pt2 = ( fRays_Projection[prpos]/Magnitude(fRays_Projection[prpos]))
			//			*fPts_Obj[oppos]) - pow(Min,2) );//;Lotfusspunkt
			fPts_Corresponding.push_back(PPair);counter++;}}while(1);}




void CIIPM::Convert_PtsImg_To_ProjectionRays(){
//; THIS FUNCTION TRANSFORMS THE POINTS FROM SENSORSYSTEM TO CAMERASYSTEM 
//; (CENTERED COORDINATES (CAMERA COORDINATE SYSTEM; 0,0 IS IN THE CENTER OF THE IMAGE )
	float x_pix = 0, y_pix = 0, x_mm = 0, y_mm = 0;
	fRays_Projection.clear();D3DVECTOR Point;
	if(fPts_Img.size())
	//; TRANSFORMATION TO CENTERED COORDINATES
	//; ATTENTION! THE INTERSECTIONS COME WITH "ZERO UP"
	for( int i=0; i<fPts_Img.size(); i++)		{
		fPts_Img[i](0) = fPts_Img[i](0) - fCamera.PrincipalPointX; 
		fPts_Img[i](1) = fPts_Img[i](1) - fCamera.PrincipalPointY ;}
	for(int i=0; i<fPts_Img.size(); i++){
		x_pix = fPts_Img[i](0); y_pix = fPts_Img[i](1);
		x_mm = x_pix * fCamera.CellSizeX/1000; y_mm = y_pix * fCamera.CellSizeY/1000;
		Point(0) = x_mm ; Point(1) = y_mm; Point(2) = fCamera.FocalLength;
	    fRays_Projection.push_back(Point);}}



void CIIPM::Calc_WeightedMeans(){
	float accu1=0, accu2=0, accu3=0, accu4=0, accu5=0, accu6=0, sumweights=0, weight_i=0;
	int size = fPts_Corresponding.size();
	if(fWeights.size()==fPts_Corresponding.size())
		for(int i=0; i<size; i++){
			weight_i = fWeights[i];
			accu1 += weight_i * fPts_Corresponding[i].Pt1(0); 
			accu2 += weight_i * fPts_Corresponding[i].Pt1(1); 
			accu3 += weight_i * fPts_Corresponding[i].Pt1(2); 
			accu4 += weight_i * fPts_Corresponding[i].Pt2(0); 
			accu5 += weight_i * fPts_Corresponding[i].Pt2(1); 
			accu6 += weight_i * fPts_Corresponding[i].Pt2(2); 
			sumweights += weight_i;	}
	else for(int i=0; i<size; i++){
		accu1 += fPts_Corresponding[i].Pt1(0); accu2 += fPts_Corresponding[i].Pt1(1); 
		accu3 += fPts_Corresponding[i].Pt1(2); 
		accu4 += fPts_Corresponding[i].Pt2(0); 
		accu5 += fPts_Corresponding[i].Pt2(1); accu6 += fPts_Corresponding[i].Pt2(2); 
		sumweights++;}
	fWeightedMeans.Pt1(0) = accu1/sumweights;fWeightedMeans.Pt1(1) = accu2/sumweights;
	fWeightedMeans.Pt1(2) = accu3/sumweights;fWeightedMeans.Pt2(0) = accu4/sumweights;
	fWeightedMeans.Pt2(1) = accu5/sumweights;fWeightedMeans.Pt2(2) = accu6/sumweights;}



void CIIPM::Calc_CrossCorrelation_Matrix(){
	fCrossCorrelation_Matrix = ZeroMatrix();
	int size = fPts_Corresponding.size();
	float weight_i = 0; D3DVECTOR xnorm, ynorm;
	if(fWeights.size()==size){//; if weights have been calculated
		for(int i=0; i<size; i++){
			weight_i = fWeights[i];
 			xnorm = fPts_Corresponding[i].Pt1 - fWeightedMeans.Pt1;
			ynorm = fPts_Corresponding[i].Pt2 - fWeightedMeans.Pt2;
			fCrossCorrelation_Matrix = MatrixAdd( fCrossCorrelation_Matrix,
				weight_i * ( TranspProduct (
				(fPts_Corresponding[i].Pt2 - fWeightedMeans.Pt2), 
				( fPts_Corresponding[i].Pt1 - fWeightedMeans.Pt1 ) ) ));}}
		else{//;in the first iteration, no weights have been calculated yet
		for(int i=0; i<size; i++){
			fCrossCorrelation_Matrix  = MatrixAdd(fCrossCorrelation_Matrix,
				( TranspProduct( (fPts_Corresponding[i].Pt2 - fWeightedMeans.Pt2),
				(fPts_Corresponding[i].Pt1 - fWeightedMeans.Pt1) 
				
				)));}}}
			//	( TranspProduct( (fPts_Corresponding[i].Pt1 - fWeightedMeans.Pt1), 
			//	(fPts_Corresponding[i].Pt2 - fWeightedMeans.Pt2))));}}//}




void CIIPM::Calc_Transformation_Matrix(){
	double data[9];	D3DVECTOR TransVec;	D3DMATRIX RotMat,RotOverall; int j=0, i=0;
	for( i=0; i<3; i++)for( j=0; j<3; j++)data[i*3+j] = fCrossCorrelation_Matrix(i,j);
	mxArray *X=0;mxArray *S, *V;mxArray *U = 0, *s = 0, *R = 0, *result = 0;
	mlfAssign( &X, mlfDoubleMatrix(3,3,data,0) );
	//; the CrossCorrMatrix is being copied to an mxArray 
	//; ( the matlab datastructure for a matrix )
	mlfAssign(&U, mlfSvd( &S, &V, X, 0 ) );mlfAssign( &R, mlfMtimes(V, mlfTranspose(U)) );
	Convert_MxArray(R, RotMat);
	TransVec = fWeightedMeans.Pt1 - TransformVector(RotMat,fWeightedMeans.Pt2);
	//i=2; j=2; RotMat(i,j) *= -1;
	//; multiply the overall rot from right to left
	
	fTrans_Camera_Struct.M = RotMat; fTrans_Camera_Struct.V = TransVec;
	i=0;  TransVec(i) *= -1;
	i=1;  TransVec(i) *= -1;
	i=2;  TransVec(i) *= -1;
	fTrans_Camera = MergeMatrix(TransVec, RotMat);
	mxDestroyArray(X);	mxDestroyArray(S);	mxDestroyArray(V);
	mxDestroyArray(U);	mxDestroyArray(s);	mxDestroyArray(R);}


void CIIPM::Convert_MxArray( mxArray* aSourceArray, D3DMATRIX& aDestMatrix ){
	float value = 0;	mxArray* result = 0; aDestMatrix=IdentityMatrix();
	for(int j=0; j<3; j++) for( int i=0; i<3; i++){
		result = mlfIndexRef( aSourceArray, "(?,?)", mlfScalar(j+1), mlfScalar(i+1) );
		value = *(mxGetPr( result ));
		aDestMatrix(j,i) = value;}
	mxDestroyArray(result);}


void CIIPM::Transform_MoveObjectToProjectionAxis(){
//; the object is moved in x/y-dir by the difference of ObjGravCenter
//; and projected ImgGravCenter. first the ObjPts-GravityCenter is calculated.
//; second the ImgPts-GravityCenter, third the ImgPts-GravityCenter-coordinates
//; are projected with similar-triangle-method to the z-position of the object
//; fourth, the object is moved in x/y-direction by the difference of ObjGravCenter
//; and projected ImgGravCenter.
	float Accu_X = 0, Accu_Y = 0, temp_x=0, temp_y=0, 
		PreTransGravityX=0, PreTransGravityY=0;
	for(int i=0; i<fPts_Obj.size(); i++)	{//;Gravity of ObjPts in x/y
		Accu_X += fPts_Obj[i](0);Accu_Y += fPts_Obj[i](1);	}
	Accu_X /= fPts_Obj.size();Accu_Y /= fPts_Obj.size();
	float img_mean_x=0, img_mean_y=0, alpha_rad=0, beta_rad = 0;
	for( i=0; i<fPts_Img.size(); i++){//;Gravity of ImgPts
		img_mean_x += fPts_Img[i](0) * fCamera.CellSizeX/1000.0;
		img_mean_y += fPts_Img[i](1) * fCamera.CellSizeY/1000.0;	}
	img_mean_x /= fPts_Img.size();img_mean_y /= fPts_Img.size();
	temp_x = -fTrans_Camera(3,2) * img_mean_x/fCamera.FocalLength;
	temp_y = -fTrans_Camera(3,2) * img_mean_y/fCamera.FocalLength;
	PreTransGravityX = temp_x - Accu_X; PreTransGravityY = temp_y - Accu_Y;
	fTrans_Camera= IdentityMatrix();
	fTrans_Camera(3,0)=PreTransGravityX;fTrans_Camera(3,1)=PreTransGravityY;
	Transform_Pts_Obj();}


//DEL void CIIPM::Set_InitRotEuler(float PsiGrad, float ThetaGrad, float PhiGrad)
//DEL {
//DEL 	float psi = PsiGrad/180 * pi, phi =PhiGrad/180 * pi,theta = ThetaGrad/180 * pi;
//DEL 	//; translation in rad
//DEL 	//; the rotation is an adapted euler rotation in xy'x''- direction 
//DEL 	//; 1: rotation around the basis x-axis by psi
//DEL 	//; 2: rotation around the new y-axis by theta
//DEL 	//; 3: rotation around the new x-axis by phi
//DEL 	fTrans_Init(0,0) =  cos(theta);	fTrans_Init(1,0) =  sin(theta) * sin(phi);
//DEL 	fTrans_Init(2,0) =  sin(theta) * cos(phi);
//DEL 	fTrans_Init(0,1) =  sin(theta) * sin(psi);
//DEL 	fTrans_Init(1,1) =  cos(psi)   * cos(phi) - cos(theta) * sin(psi) * sin(phi);
//DEL 	fTrans_Init(2,1) = -cos(psi)   * sin(phi) - cos(theta) * sin(psi) * cos(phi);
//DEL 	fTrans_Init(0,2) = -sin(theta) * cos(psi);
//DEL 	fTrans_Init(1,2) =  sin(psi)   * cos(phi) + cos(theta) * cos(psi) * sin(phi);
//DEL 	fTrans_Init(2,2) = -sin(psi)   * sin(phi) + cos(theta) * cos(psi) * cos(phi);}



//DEL void CIIPM::Set_Params_Camera(float afocuslength, float aCellSizeX, float aCellSizeY, 
//DEL 								int aPixNumX, int aPixNumY, float aPrincipalPointX, 
//DEL 								float aPrincipalPointY){
//DEL 	fCamera.CellSizeX = aCellSizeX;fCamera.CellSizeY = aCellSizeY;
//DEL 	fCamera.FocalLength  = afocuslength; fCamera.PixNumX = aPixNumX;
//DEL 	fCamera.PixNumY = aPixNumY;
//DEL 	fCamera.PrincipalPointX = aPrincipalPointX;
//DEL 	fCamera.PrincipalPointY = aPrincipalPointY;}


void CIIPM::Convert_ToCameraCS(D3DMATRIX &aTransMachineInit){
	aTransMachineInit = MatrixMult(fCalib_Trans_MS_TO_CS , aTransMachineInit);}


void CIIPM::Reset(){
	fTrans_Camera=fTrans_Init=fTrans_Machine=fTrans_Overall=IdentityMatrix();
	for(int i=0; i<3; i++)fAnglesEuler[i]=0;
	fPts_Corresponding.clear();	fPts_Img.clear();
	fPts_Obj.clear();fRays_Projection.clear();
	fPts_Test.clear();fPts_Fixed.clear();	fWeights.clear();
	fParameters.Calibration = 1;}


//DEL void CIIPM::Set_TransInit(D3DMATRIX aTransInit){
//DEL 	fTrans_Init = aTransInit;}


//DEL void CIIPM::Calc_AngleAndAxisFromRotMat(float &aAngleGrad, D3DVECTOR &aDirection, const D3DMATRIX aRotMat){
//DEL 	float aAngle = acos( 0.5 * ( aRotMat(0,0) + aRotMat(1,1) + aRotMat(2,2) - 1 ) );
//DEL 	aAngleGrad = aAngle * 180/pi;
//DEL 	aDirection(0) = ( 1/(2*sin(aAngle)) ) * ( aRotMat(1,2) - aRotMat(2,1) );
//DEL 	aDirection(1) = ( 1/(2*sin(aAngle)) ) * ( aRotMat(2,0) - aRotMat(0,2) );
//DEL 	aDirection(2) = ( 1/(2*sin(aAngle)) ) * ( aRotMat(0,1) - aRotMat(1,0) );}


void CIIPM::Calc_Weights(){
	if(fPts_Corresponding.size()==0)	{
		MessageBox(0, "Es ist ein Fehler in der Funktion 'CIIPM::CalcWeights()' aufgetreten. (fPts_Corresponding.size()==0)", "Fehler!", MB_OKCANCEL);
		return;	}
	fWeights.clear();
	D3DVECTOR difvec, vec4, Pt1;
	float abseik = 0, absval = 0, medianeik = 0, weight_i = 0,
		sigmaquadrat=0, temp=0, one=1, val=0;
	int index = 0;
	vector< float > eiksvec, eiksvectemp; list< float > eikslist;
	for(int i=0; i< fPts_Corresponding.size(); i++)	{
		eiksvec.push_back(fDistances[i]);
		eikslist.push_back(eiksvec[i]);	}
	medianeik = MedianValue(eikslist);
	sigmaquadrat = ( medianeik /0.6745 ) ;
	for( i=0; i<eiksvec.size(); i++){
		val=abs(eiksvec[i])/ medianeik;
		if( val > fThresholds.Weight_TH ){
			temp =eiksvec[i];
			weight_i = ( medianeik )/  (eiksvec[i]);
			fWeights.push_back( weight_i );}
			//fOutputStream  << eiksvec[i] << ", "<< weight_i<<endl;
		else{
			fWeights.push_back(one);}}}
			//fOutputStream << eiksvec[i]<< ", " << 1 << endl;



/*void CIIPM::Set_InputData(vector< D3DVECTOR, D3DVECTOR& > aObjPts, const vector< D3DVECTOR, D3DVECTOR& >& aImgPts, float* aNomTrans, float* aNomRot){
	if(fParameters.Calibration){
		fCalib_Trans_CS_TO_MS= IdentityMatrix();fCalib_Trans_MS_TO_CS= IdentityMatrix();}
	fTrans_Init= IdentityMatrix();
	fPts_Obj.clear(); for(int i=0;i<aObjPts.size();i++) fPts_Obj.push_back(aObjPts[i]);
	fPts_Img.clear(); for(i=0;i<aImgPts.size();i++) fPts_Img.push_back(aImgPts[i]);
	XYZEulerToRotMat(aNomRot[0], aNomRot[1], aNomRot[2], fTrans_Init);
	fTrans_Init(3,0) = aNomTrans[0];	fTrans_Init(3,1) = aNomTrans[1];
	fTrans_Init(3,2) = aNomTrans[2];	fTrans_Init(3,3) = 1;
	//; if the system is calibrated, then the nominalposition is 
	//; given in machine coordinates, and have to be converted in 
	//; camera coordinates
	if(!fParameters.Calibration){//; convert prepositioning- machine- coordinates to camera-coordinates
		fTrans_Init = fCalib_Trans_MS_TO_CS * fTrans_Init;}
	Transform_Pts_Fixed(fCalib_Trans_MS_TO_CS);}
*/


void CIIPM::Set_AbortionCriteria(int aMaxIter, float aMaxDistance, float aMinTranslation){
	fThresholds.Iterations_Max = aMaxIter;	fThresholds.DistanceMatrix_Max = aMaxDistance;	fThresholds.Translation_Min = aMinTranslation;}

//DEL  void CIIPM::Set_ProjectionData(int aPixNumX, int aPixNumY, float aFocalLength) {
//DEL  	fCamera.PixNumX = aPixNumX; 	fCamera.PixNumY = aPixNumY; 	fCamera.FocalLength = aFocalLength; }

//DEL void CIIPM::Set_NominalPosition(float *aNomTrans, float *aNomRot){
//DEL 	fTransl_Nominal[0] = aNomTrans[0];	fTransl_Nominal[1] = aNomTrans[1];
//DEL 	fTransl_Nominal[2] = aNomTrans[2];	fTransl_Nominal[0] = aNomRot[0];
//DEL 	fTransl_Nominal[1] = aNomRot[1];	fTransl_Nominal[2] = aNomRot[2];}

 void CIIPM::Set_Calibration_Matrix(float aTransCalibration[4][4]){
 	for(int i=0; i<4; i++)	for(int j=0; j<4; j++)
 		fCalib_Trans_MS_TO_CS(i,j) = aTransCalibration[i][j];
 	fCalib_Trans_CS_TO_MS = MatrixInverse(fCalib_Trans_MS_TO_CS); }


void CIIPM::Set_Pts_Obj(vector< D3DVECTOR >& aObj){
	}


void CIIPM::Set_Pts_Img(vector< D3DVECTOR >& aObj){
	}



void CIIPM::Calc_Undistortion(){
	D3DVECTOR xn(2), xd, dx, xp, vec;	D3DMATRIX KK;
	float r2=0, r4=0, r6=0, x=0, y=0;	vec(2)=1;	
	if(fPts_Img.size())
	for( int i=0; i<fPts_Img.size(); i++){		
		xn(0) = x = fPts_Img[i](0)/fCamera.FocalLength;
		xn(1) = y = fPts_Img[i](1)/fCamera.FocalLength;
		r2 = pow(xn(0),2) + pow(xn(1),2);
		r4 = pow(r2,2);
		r6 = r2 * r4;
		dx(0) = 2*fCamera.DistortionParameters[3]*x*y + fCamera.DistortionParameters[4]*(r2 + 2*pow(x,2));
		dx(1) = fCamera.DistortionParameters[3]*(r2 + 2*pow(y,2)) + 2*fCamera.DistortionParameters[4]*x*y;  
		xd=(1 + fCamera.DistortionParameters[1]*r2 + fCamera.DistortionParameters[2]*r4 + fCamera.DistortionParameters[5]*r6) * xn + dx ;
		xp = TransformVector(KK, xd);
		fPts_Img[i](0) = xp(0);fPts_Img[i](1) = xp(1);}}

 void CIIPM::Set_Params_Camera(D3DCAMERA CamParams)
 {
 	fCamera = CamParams;
 }

void CIIPM::Set_Init_Transformation(D3DMATRIX InitTranslation)
{
	fTrans_Init = InitTranslation;
}

void CIIPM::Calc_RegIIPM_OneStep()
{
		//Calc_DistanceMatrix();
		//Calc_CorrespondingPoints();//; for every projection- ray a 3D- Object- Point is being found
		Calc_Weights();	Calc_WeightedMeans();
		//; the average of each coordinate of each Corresponding- PointPair is calculated
		//; and saved in the PointPair fWeightedMeans 
		Calc_CrossCorrelation_Matrix(); Calc_Transformation_Matrix(); Transform_Pts_Obj();
		float mean=MeanValue(fDistances,fPts_Corresponding.size());
		Calc_DistanceMatrix();
		Calc_CorrespondingPoints();//; for every projection- ray a 3D- Object- Point is being found
		//Num_Iteration++; 
}

bool CIIPM::Calc_RegIIPM_Init()
{
	float mean = 0;	int Num_Iteration=0;
	if(fPts_Obj.size()==0 || fPts_Img.size()==0)	{
		MessageBox(0,"Fehler in der Funktion CIIPM::RegIIPM(). (fPts_Obj.size()==0 || fPts_Img.size()==0)", "Fehler!", MB_OKCANCEL);
		return 0;}
	//fTrans_Overall = IdentityMatrix();	fTrans_Camera  = fTrans_Init;
	for( int i=0; i<fPts_Obj.size(); i++ )
		fPts_Obj[i] = TransformVector(fTrans_Init, fPts_Obj[i]);

	//Transform_Pts_Obj(); 
	Convert_PtsImg_To_ProjectionRays();
	//; initial transformation
	if(fParameters.MoveGravityCenter)
		Transform_MoveObjectToProjectionAxis();
	Calc_DistanceMatrix();
	Calc_CorrespondingPoints();//; for every projection- ray a 3D- Object- Point is being found

}
