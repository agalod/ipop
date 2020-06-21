// RegIIPM.h: Schnittstelle für die Klasse CIIPM.
//
// Written by A.Roehnisch at WZL-RWTH, Aachen, Germany, 2005
// on the basis of the work of Wunsch & Hinzinger´s CIIPM-Paper from 1996
//////////////////////////////////////////////////////////////////////

#ifndef _IIPM_H
#define _IIPM_H

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

    
class CIIPM  
{
public:
	void Update_Euler_Workpiece();
	void Update_Euler_Machine();

	void Calc_RegIIPM_Update();
	bool Calc_RegIIPM_Init();
	void Calc_RegIIPM_OneStep();
	void Set_Init_Transformation(D3DMATRIX InitTranslation);

	//Construction/ Deconstruction
	CIIPM();
	virtual ~CIIPM();

	//ofstream fOutputStream;
	//;---------------------------------------------------------------
	//; Reset Functions 
	void Reset();
	//;---------------------------------------------------------------
	//;---------------------------------------------------------------
	//; DATA SETTING
	void Set_Pts_Obj(vector< D3DVECTOR  >& aObj); 
	void Set_Pts_Img(vector< D3DVECTOR   >& aImgPts);
	void Set_AbortionCriteria(int aMaxIter, double aMinDistance, double aMinTranslation);
	//;------------------------------------------------------------------
	//;---------------------------------------------------------------
	//; Main Processing Functions
	//;---------------------------------------------------------------
	//;---------------------------------------------------------------
	//; Transformation Methods 
	//; (transforming the Object Points)
	void Transform_Pts_Obj(D3DMATRIX &mat);
	void Transform_Pts_Obj();
	void Transform_Pts_Test(D3DVECTOR aTransVec);
	void Transform_Pts_Test(D3DMATRIX aRotMat);
	void Transform_Pts_Fixed(D3DMATRIX aRotMat);
	//;---------------------------------------------------------------
	//;---------------------------------------------------------------
	//; Auxilary Calculations
	void	Calc_Transformation_Matrix();
	void	Calc_CrossCorrelation_Matrix();
	void	Calc_WeightedMeans();
	void	Calc_CorrespondingPoints();
	void	Calc_DistanceMatrix();
	void	Calc_Weights();
	//;---------------------------------------------------------------
	//;---------------------------------------------------------------
	//; Conversions
	//;---------------------------------------------------------------
	//; Data- Retrieving
	//; Adding Points

	struct structParameters{
		bool	MoveGravityCenter;
		bool	Calibration;
		int		Iterations_Max;	
		int		DistanceMatrix_Max;
		double	Translation_Min;	
		double	Weight_TH;
	}fParameters_IIPM;

	double fDistances[500], fDistances_Sum;
	//; a matrix in CameraCoord.System (CS), which performs the current transformation
	D3DMATRIXBIG fDistance_Matrix;

	//D3DMATRIX
	//; these are 4x4 matrices having the 3x3 rotmatrix left- up,
	//; the translation vector right- up and the bottom row as 0-0-0-1.
	//; you can translate and rotate a 4x4 vector (fourth coordinate set to 1)
	//; simultaneously by multiplying it with them.
	//; the elements of each matrix is accessed by "matrix(column, row)"
	//; as an x-y- diagram
	D3DCAMERA   fCamera;
	D3DMATRIX	fTrans_Etalon_Init, fTrans_Etalon_Overall, 
				fCrossCorrelation_Matrix, fRot_Etalon_Overall,
				fRot_Etalon_Current;
	D3DVECTOR	fTransl_Etalon_Overall, fTransl_Etalon_Current;
	D3DEULER	fEuler_Etalon, fEuler_MachineRef_Abs, fEuler_MachineRef_Rel,
				fEuler_Workpiece_Abs, fEuler_Workpiece_Rel;

	//; the average of each coordinate of each Corresponding- PointPair is calculated
	//; and saved in the PointPair fWeightedMeans 
	D3DVECTORLINE fWeightedMeans;

	vector< D3DVECTOR >		fPts_Img;
	vector< D3DVECTOR >		fPts_Fixed, fPts_Test, 
							fPts_Obj_Init, fPts_Obj_Current;
	vector< D3DVECTORLINE >		fPts_Corresponding;
	vector< double>			fWeights;

	//various
	int fNumIterations;
};

#endif // _IIPM_H
