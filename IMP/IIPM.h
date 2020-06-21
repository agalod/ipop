// RegIIPM.h: Schnittstelle für die Klasse CIIPM.
//
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
//-----------------------------------------------------------------------------
// Written by cand.ing. Alexander M.Roehnisch @ WZL-RWTH, Aachen, Germany, 2005
// on the basis of the work of Wunsch & Hinzinger´s IIPM-Paper from 1996
//-----------------------------------------------------------------------------
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////

#ifndef _IIPM_H
#define _IIPM_H

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

    
class CIIPM  
{
public:
	//;---------------------------------------------------------------
	//CONSTRUCTION/ DECONSTRUCTION
	CIIPM(); virtual ~CIIPM();
	//;---------------------------------------------------------------
	//; RESET FUNCTIONS 
	void Reset();
	//;---------------------------------------------------------------
	//;---------------------------------------------------------------
	//;---------------------------------------------------------------
	//; MAIN PROCESSING FUNCTIONS
	virtual void Calc_RegIIPM_Update();
	virtual void Calc_RegIIPM_Init();
	virtual void Calc_RegIIPM_OneStep();
	//;---------------------------------------------------------------
	//;---------------------------------------------------------------
	//; TRANSFORMATION METHODS 
	//; (TRANSFORMING THE OBJECT POINTS)
	virtual void Transform_Pts_Obj(GCV_MATRIX3D &mat);
	//;---------------------------------------------------------------
	//;---------------------------------------------------------------
	//; AUXILARY CALCULATIONS
	virtual void	Calc_Transformation_Matrix();
	virtual void	Calc_CrossCorrelation_Matrix();
	virtual void	Calc_MeansXandYPoints();
	virtual void	Calc_CorrespondingPoints();
	virtual void	Calc_DistanceMatrix();
	//;---------------------------------------------------------------
	//;---------------------------------------------------------------
	//; MEMBERS
	//;---------------------------------------------------------------
	struct structParameters{
		bool	MoveGravityCenter;
		int		Iterations_Max;	
		int		DistanceMatrix_Max;
		double	Translation_Min;	
		double	Weight_TH;
	}fParameters_IIPM;
	double fDistances[500], fDistances_Sum;
	//; a matrix in CameraCoord.System (CS), which performs the current transformation
	GCV_CAMERA   fCamera;
	GCV_MATRIXBIG fDistance_Matrix;
	//; GCV_MATRIX3D´s are 4x4 matrices having the 3x3 rotmatrix left- up,
	//; the translation vector right- up and the bottom row as 0-0-0-1.
	//; you can translate and rotate a 4x4 vector (fourth coordinate set to 1)
	//; simultaneously by multiplying it with them.
	//; the elements of each matrix is accessed by "matrix(column, row)"
	//; as an x-y- diagram
	GCV_MATRIX3D fTrans_Init, fTrans_Overall, fCrossCorrelation_Matrix;
	//; the average of each coordinate of each Corresponding- PointPair is calculated
	//; and saved in the PointPair fMeansXandY 
	GCV_VECTOR3D fMeanXPoints, fMeanYPoints, fTransl_Current, fTransl_Overall;
	vector< GCV_VECTOR3D >		fPts_Img, fPts_Obj_Init, fPts_Obj_Current;
	vector< GCV_LINE3D >		fPts_Corresponding;
	//various
	int fNumIterations; bool fbFixedCorrespondences;
};

#endif // _IIPM_H
