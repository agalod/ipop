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

double MedianValue(list<double> aList){
	aList.sort(); int index=0;
	vector<double> Vec;
	list<double>::iterator listiter = aList.begin();
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

		
double MeanValue(double* aField, int num){
	double ret=0;
	for(int i=0;i<num;i++) ret+=aField[i];
	return ret/=num;}

void ErrorHandler(const char * message , bool value){
	int a=0; _exit(-1);}

//////////////////////////////////////////////////////

CIIPM::CIIPM(){
	fParameters_IIPM.Calibration=1;
	fParameters_IIPM.DistanceMatrix_Max = 50;
	fParameters_IIPM.Iterations_Max = 100;
	fParameters_IIPM.Translation_Min = 0;
	fParameters_IIPM.Weight_TH = 1;
	fDistances_Sum = 0;
	fNumIterations = 0;
}  
CIIPM::~CIIPM(){}


void CIIPM::Transform_Pts_Test(D3DVECTOR aTransVec){	
	for( int i=0; i<fPts_Test.size(); i++ )fPts_Test[i] = aTransVec + fPts_Test[i];}

void CIIPM::Transform_Pts_Test(D3DMATRIX aRotMat){
	for( int i=0; i<fPts_Test.size(); i++ )fPts_Test[i] = TransformVector(fPts_Test[i],aRotMat);}

void CIIPM::Transform_Pts_Fixed(D3DMATRIX aRotMat){
	for( int i=0; i<fPts_Fixed.size(); i++ )fPts_Fixed[i] = TransformVector(fPts_Fixed[i],aRotMat);}


void CIIPM::Transform_Pts_Obj(){
	for( int i=0; i<fPts_Obj_Current.size(); i++ ){
		fPts_Obj_Current[i] = TransformVector(fRot_Etalon_Current, fPts_Obj_Current[i]-fWeightedMeans.pt1);
		fPts_Obj_Current[i] += fWeightedMeans.pt2;
	}}

void CIIPM::Transform_Pts_Obj(D3DMATRIX &mat){
	for( int i=0; i<fPts_Obj_Init.size(); i++ ){
		fPts_Obj_Current[i] = TransformVector(mat, fPts_Obj_Init[i]);
	}}


void CIIPM::Calc_DistanceMatrix(){
	for(int i=0; i != fPts_Obj_Current.size(); i++)
		for(int j=0; j != fPts_Img.size(); j++){
			fDistance_Matrix(i,j) = DistanceLinePoint( fPts_Img[j], fPts_Obj_Current[i]);}}


void CIIPM::Calc_CorrespondingPoints(){
	//; Calculates the minimum in each column
	fPts_Corresponding.clear();	D3DVECTOR ObjPt;
	fDistances_Sum = 0;
	//; the 4-dim fPts_Obj[index] has to be converted into a 3-dim ObjPt3
	//; because the vectorproduct and other calculations are only 
	//; possible in 3-dim space.
	double Min = 99999999.f, Tmp = 0, Lotfusspunkt = 0;
	D3DVECTORLINE PPair; D3DVECTOR projraynorm, objptimg;
	int index = 0, size = fPts_Img.size();
	int oppos=0, prpos=0, xc=0, yc=0, counter=0;
	do{
		Min = fDistance_Matrix.MinValue(oppos, prpos);
		if( Min == 999999) break;
		for(xc=0;xc<fPts_Img.size();xc++) 
			fDistance_Matrix(oppos,xc)=999999;//;fill the row with high #´s
		{
			fDistances[counter] = Min;
			fDistances_Sum += Min;
			PPair.pt1 = fPts_Obj_Current[oppos];
			projraynorm = fPts_Img[prpos]/Magnitude(fPts_Img[prpos]);
			PPair.pt2 = ( projraynorm * fPts_Obj_Current[oppos] ) * projraynorm;
			fPts_Corresponding.push_back(PPair);counter++;}}while(1);}


void CIIPM::Calc_WeightedMeans(){
	double accu1=0, accu2=0, accu3=0, accu4=0, accu5=0, accu6=0, sumweights=0, weight_i=0;
	int size = fPts_Corresponding.size();
	if(fWeights.size()==fPts_Corresponding.size())
		for(int i=0; i<size; i++){
			weight_i = fWeights[i];
			accu1 += weight_i * fPts_Corresponding[i].pt1(0); 
			accu2 += weight_i * fPts_Corresponding[i].pt1(1); 
			accu3 += weight_i * fPts_Corresponding[i].pt1(2); 
			accu4 += weight_i * fPts_Corresponding[i].pt2(0); 
			accu5 += weight_i * fPts_Corresponding[i].pt2(1); 
			accu6 += weight_i * fPts_Corresponding[i].pt2(2); 
			sumweights += weight_i;	}
	else for(int i=0; i<size; i++){
		accu1 += fPts_Corresponding[i].pt1(0); accu2 += fPts_Corresponding[i].pt1(1); 
		accu3 += fPts_Corresponding[i].pt1(2); 
		accu4 += fPts_Corresponding[i].pt2(0); 
		accu5 += fPts_Corresponding[i].pt2(1); accu6 += fPts_Corresponding[i].pt2(2); 
		sumweights++;}
	fWeightedMeans.pt1(0) = accu1/sumweights;fWeightedMeans.pt1(1) = accu2/sumweights;
	fWeightedMeans.pt1(2) = accu3/sumweights;fWeightedMeans.pt2(0) = accu4/sumweights;
	fWeightedMeans.pt2(1) = accu5/sumweights;fWeightedMeans.pt2(2) = accu6/sumweights;}
    


void CIIPM::Calc_CrossCorrelation_Matrix(){
	fCrossCorrelation_Matrix = ZeroMatrix();
	int size = fPts_Corresponding.size();
	double weight_i = 0; D3DVECTOR xnorm, ynorm;
	if(fWeights.size()==size){//; if weights have been calculated
		for(int i=0; i<size; i++){
			weight_i = fWeights[i];
 			xnorm = fPts_Corresponding[i].pt1 - fWeightedMeans.pt1;
			ynorm = fPts_Corresponding[i].pt2 - fWeightedMeans.pt2;
			fCrossCorrelation_Matrix = MatrixAdd( fCrossCorrelation_Matrix,
				MatrixMult(weight_i, ( TransposeProduct (
				(fPts_Corresponding[i].pt2 - fWeightedMeans.pt2), 
				( fPts_Corresponding[i].pt1 - fWeightedMeans.pt1 ) ) )));}}
		else{//;in the first iteration, no weights have been calculated yet
		for(int i=0; i<size; i++){
			fCrossCorrelation_Matrix  = MatrixAdd(fCrossCorrelation_Matrix,
				( TransposeProduct( (fPts_Corresponding[i].pt2 - fWeightedMeans.pt2),
				(fPts_Corresponding[i].pt1 - fWeightedMeans.pt1) 
				
				)));}}}


void CIIPM::Calc_Transformation_Matrix(){

	//; INIT & ERRORCATCHING
	static double data[9];	D3DVECTOR TransVec, w_vec;	
	static D3DMATRIX tempmat1, tempmat2, v_mat; int j=0, i=0;
	static lti::singularValueDecomp<double> ltisvd;
	static lti::matrix<double> u(3,3), v(3,3), r(3,3), x(3,3);
	static lti::vector<double> w(3);

	//; CALC
		//; Begin lti
		for( i=0; i<3; i++) for( j=0; j<3; j++) x.at(j,i) = fCrossCorrelation_Matrix(j,i);
		ltisvd.apply(x,u,w,v); 
		for( i=0; i<3; i++) w_vec(i) = w[i];
		u.multiply(v.transpose());
		for( i=0; i<3; i++) for( j=0; j<3; j++) fRot_Etalon_Current(i,j) = u.at(i,j);
		//; End lti

	fRot_Etalon_Current = MatrixMult(fRot_Etalon_Current, fRot_Etalon_Current);
	fRot_Etalon_Overall = MatrixMult(fRot_Etalon_Current, fRot_Etalon_Overall);
	fTransl_Etalon_Overall = fTransl_Etalon_Current = fWeightedMeans.pt2;
	fTrans_Etalon_Overall = MergeMatrix(fTransl_Etalon_Overall, fRot_Etalon_Overall);

	RotMatToXYZEuler(fRot_Etalon_Overall,fEuler_Etalon.rot_x, 
		fEuler_Etalon.rot_y, fEuler_Etalon.rot_z );
	fEuler_Etalon.trans_x = fTransl_Etalon_Overall(0);
	fEuler_Etalon.trans_y = fTransl_Etalon_Overall(1);
	fEuler_Etalon.trans_z = fTransl_Etalon_Overall(2);

	Update_Euler_Machine(); Update_Euler_Workpiece();
		
	//; EXIT
}


void CIIPM::Reset(){
	fTrans_Etalon_Init=fTrans_Etalon_Overall=fRot_Etalon_Overall=IdentityMatrix();
	//for(int i=0; i<3; i++)fAnglesEuler[i]=0;
	fPts_Corresponding.clear();	fPts_Img.clear();
	//fPts_Obj.clear();fRays_Projection.clear();
	fPts_Test.clear();fPts_Fixed.clear();	fWeights.clear();
	fParameters_IIPM.Calibration = 1;}


void CIIPM::Calc_Weights(){
	if(fPts_Corresponding.size()==0)	{
		MessageBox(0, "Es ist ein Fehler in der Funktion 'CIIPM::CalcWeights()' aufgetreten. (fPts_Corresponding.size()==0)", "Fehler!", MB_OKCANCEL);
		return;	}
	fWeights.clear();
	D3DVECTOR difvec, vec4, Pt1;
	double abseik = 0, absval = 0, medianeik = 0, weight_i = 0,
		sigmaquadrat=0, temp=0, one=1, val=0;
	int index = 0;
	vector< double > eiksvec, eiksvectemp; 
	list< double > eikslist;
	for(int i=0; i< fPts_Corresponding.size(); i++)	{
		eiksvec.push_back(fDistances[i]);
		eikslist.push_back(eiksvec[i]);	}
	medianeik = MedianValue(eikslist);
	sigmaquadrat = ( medianeik /0.6745 ) ;
	for( i=0; i<eiksvec.size(); i++){
		val=abs(eiksvec[i])/ medianeik;
		if( val > fParameters_IIPM.Weight_TH ){
			temp =eiksvec[i];
			weight_i = ( medianeik )/  (eiksvec[i]);
			fWeights.push_back( weight_i );}
		else{
			fWeights.push_back(one);}}}



void CIIPM::Set_AbortionCriteria(int aMaxIter, double aMaxDistance, double aMinTranslation){
	fParameters_IIPM.Iterations_Max = aMaxIter;	fParameters_IIPM.DistanceMatrix_Max = aMaxDistance;	fParameters_IIPM.Translation_Min = aMinTranslation;}


void CIIPM::Set_Pts_Obj(vector< D3DVECTOR >& aObj){
	fPts_Obj_Init = fPts_Obj_Current = aObj;
}


void CIIPM::Set_Pts_Img(vector< D3DVECTOR >& aObj){
	}

void CIIPM::Set_Init_Transformation(D3DMATRIX InitTranslation)
{
	fTrans_Etalon_Init = InitTranslation;
}

void CIIPM::Calc_RegIIPM_Update()
{
	EulerToMatrix(fEuler_Etalon, fTrans_Etalon_Overall);
	SplitMatrix(fTrans_Etalon_Overall, fTransl_Etalon_Overall, fRot_Etalon_Overall);
	Transform_Pts_Obj(fTrans_Etalon_Overall);
	Update_Euler_Machine(); Update_Euler_Workpiece();

	Calc_DistanceMatrix();
	Calc_CorrespondingPoints();//; for every projection- ray a 3D- Object- Point is being found
	Calc_WeightedMeans();
}

void CIIPM::Calc_RegIIPM_OneStep()
{
	Calc_CrossCorrelation_Matrix(); 
	Calc_Transformation_Matrix(); Transform_Pts_Obj();
	Calc_DistanceMatrix();
	Calc_CorrespondingPoints();//; for every projection- ray a 3D- Object- Point is being found
	Calc_WeightedMeans();
	fNumIterations++; 
}

bool CIIPM::Calc_RegIIPM_Init()
{
	//; INITIALISIERUNG UND FEHLERABFRAG
	fNumIterations=0;
	if(fPts_Obj_Init.size()==0 || fPts_Img.size()==0)	{
		MessageBox(0,"Fehler in der Funktion CIIPM::Calc_RegIIPM_Init(). (fPts_Obj_Init.size()==0 || fPts_Img.size()==0)", "Fehler!", MB_OKCANCEL);
		return 0;}
	
	//; BERECHNUNG
	EulerToMatrix(fEuler_Etalon, fTrans_Etalon_Overall);
	SplitMatrix(fTrans_Etalon_Overall, fTransl_Etalon_Overall, fRot_Etalon_Overall);
	Transform_Pts_Obj(fTrans_Etalon_Overall);
	Update_Euler_Machine(); Update_Euler_Workpiece();

	Calc_DistanceMatrix();
	Calc_CorrespondingPoints();//; for every projection- ray a 3D- Object- Point is being found
	Calc_WeightedMeans();
}


void CIIPM::Update_Euler_Machine()
{
	D3DMATRIX etalon_mat, machineref_rel, machineref_abs;
	D3DMATRIXVECTOR machineref_rel_split, machineref_abs_split;

	EulerToMatrix(fEuler_MachineRef_Rel, machineref_rel);
	SplitMatrix(machineref_rel, machineref_rel_split);

	machineref_abs_split.M = fRot_Etalon_Overall * machineref_rel_split.M;
	machineref_abs_split.V = machineref_rel_split.V + fTransl_Etalon_Overall;

	machineref_abs = MergeMatrix(machineref_abs_split.V, machineref_abs_split.M);
	MatrixToEuler(machineref_abs, fEuler_MachineRef_Abs);
}

void CIIPM::Update_Euler_Workpiece()
{
	D3DMATRIX etalon_mat, workpiece_rel, workpiece_abs, machineref_abs;
	D3DMATRIXVECTOR workpiece_rel_split, workpiece_abs_split, machineref_abs_split;

	EulerToMatrix(fEuler_MachineRef_Abs, machineref_abs);
	SplitMatrix(machineref_abs, machineref_abs_split);
	EulerToMatrix(fEuler_Workpiece_Rel, workpiece_rel);
	SplitMatrix(workpiece_rel, workpiece_rel_split);

	workpiece_abs_split.M = workpiece_rel_split.M * machineref_abs_split.M;
	workpiece_abs_split.V = workpiece_rel_split.V + machineref_abs_split.V;

	workpiece_abs = MergeMatrix(workpiece_abs_split.V, workpiece_abs_split.M);
	MatrixToEuler(workpiece_abs, fEuler_Workpiece_Abs);

}
