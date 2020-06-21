// RegIIPM.h: Schnittstelle für die Klasse CIIPM.
//
// Written by Alexander M. Roehnisch, WZL-RWTH, Aachen, Germany, 2005
// on the basis of the work of Wunsch & Hinzinger´s CIIPM-Paper from 1996
//////////////////////////////////////////////////////////////////////

#ifndef _IIPM_H
#define _IIPM_H

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


//#include "Camera.h"

#include "iostream.h"

class CIIPM  
{
public:

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
	void Set_AbortionCriteria(int aMaxIter, float aMinDistance, float aMinTranslation);
    void Set_Params_Camera(D3DCAMERA CamParams);
    void Set_Calibration_Matrix(float aTransCalibration[4][4]);
	//;------------------------------------------------------------------
	//;---------------------------------------------------------------
	//; Main Processing Functions
	//;---------------------------------------------------------------
	//;---------------------------------------------------------------
	//; Transformation Methods 
	//; (transforming the Object Points)
	void Transform_MoveObjectToProjectionAxis();
	void Transform_Pts_Obj();
	void Transform_Pts_Test(D3DVECTOR aTransVec);
	void Transform_Pts_Test(D3DMATRIX aRotMat);
	void Transform_Pts_Fixed(D3DMATRIX aRotMat);
	//;---------------------------------------------------------------
	//;---------------------------------------------------------------
	//; Auxilary Calculations
	void	Calc_Undistortion();
	void	Calc_Transformation_Matrix();
	void	Calc_CrossCorrelation_Matrix();
	void	Calc_WeightedMeans();
	void	Calc_CorrespondingPoints();
	void	Calc_DistanceMatrix();
	void	Calc_Calibration(D3DMATRIX aMachineTrans);
	void	Calc_Weights();
	int		Calc_RegIIPM();
	//;---------------------------------------------------------------
	//;---------------------------------------------------------------
	//; Conversions
	void Convert_PtsImg_To_ProjectionRays();
	void Convert_MxArray(mxArray* aSourceArray, D3DMATRIX& aDestMatrix);
	void Convert_ToCameraCS(D3DMATRIX &aTransMachineInit);
	void Convert_ToMachineCS();
	//;---------------------------------------------------------------
	//; Data- Retrieving
	D3DMATRIX& Get_TransCamera()  { return fTrans_Overall; }
	//; Adding Points

	struct structParameters{
		bool MoveGravityCenter;
		bool Calibration;
	}fParameters;
	struct structThresholds{
		int Iterations_Max;	
		int DistanceMatrix_Max;
		float Translation_Min;	
		float Weight_TH;
	}fThresholds;

	float fDistances[500], fAnglesEuler[3], fPreTransGravity[2];
	//; a matrix in CameraCoord.System (CS), which performs the current transformation
	D3DMATRIXBIG fDistance_Matrix;

	//D3DMATRIX
	//; these are 4x4 matrices having the 3x3 rotmatrix left- up,
	//; the translation vector right- up and the bottom row as 0-0-0-1.
	//; you can translate and rotate a 4x4 vector (fourth coordinate set to 1)
	//; simultaneously by multiplying it with them.
	//; the elements of each matrix is accessed by "matrix(column, row)"
	//; as an x-y- diagram
	D3DMATRIXVECTOR fTrans_Camera_Struct;
	D3DMATRIX	fTrans_Camera, fTrans_Machine, fTrans_Init, fTrans_Overall, 
				fTrans_MachineInit, fCalib_Trans_CS_TO_MS, 
				fCalib_Trans_MS_TO_CS, fCrossCorrelation_Matrix;
	D3DVECTOR fTransl_Nominal, fRot_Nominal;
	D3DVECTORPAIR fWeightedMeans;
	D3DCAMERA fCamera;

	//; the average of each coordinate of each Corresponding- PointPair is calculated
	//; and saved in the PointPair fWeightedMeans 
	vector< D3DVECTOR > fPts_Obj, fPts_Img, fRays_Projection, 
									fPts_Fixed, fPts_Test;
	vector< D3DVECTORPAIR > fPts_Corresponding;
	vector< float> fWeights;
	//various
	//D3DMATRIX temp3mat;
	D3DVECTOR dummy;
};

#endif // _IIPM_H
