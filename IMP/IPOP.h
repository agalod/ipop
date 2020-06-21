///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
//-----------------------------------------------------------------------------
// Written by cand.ing. Alexander M.Roehnisch @ WZL-RWTH, Aachen, Germany, 2005
//-----------------------------------------------------------------------------
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
// IPOP.h: Schnittstelle für die Klasse CIPOP.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_IPOP_H__DE93C761_5E56_4F24_BEA7_7EF3EBE7ABF0__INCLUDED_)
#define AFX_IPOP_H__DE93C761_5E56_4F24_BEA7_7EF3EBE7ABF0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "IIPM.h"
     
class CIPOP: public CIIPM  
{
public:
	struct structIPOPParams{
		int	BinThreshold; BOOL ShowSteps; double HoughSensivity; int NumErosions; } fParams;
	bool Preprocess(CImage* img_input, vector <CImage*> *ResultVec, GCV_LINE2D &Workpiece_Points);
	//;---------------------------------------------------------------
	CIPOP(); virtual ~CIPOP();
	//;---------------------------------------------------------------
	//; MAIN PROCESSING FUNCTIONS
	virtual void Calc_RegIIPM_Update();
	virtual void Calc_RegIIPM_Init();
	virtual void Calc_RegIIPM_OneStep();
	virtual void Calc_RegIIPM_XSteps();
	//;---------------------------------------------------------------
	//;---------------------------------------------------------------
	//; EULER FUNCTIONS
	void Update_Euler_Workpiece();
	void Update_Euler_Machine();
	void Update_Eulers();
	//;---------------------------------------------------------------
	//;---------------------------------------------------------------
	//; AUXILARY FUNCTIONS
	void SetWorkpieceAbsToMachineRefAbs();
	void Calc_PiercingPoints(GCV_LINE2D line);
	void Update_Plane();
	//;---------------------------------------------------------------
	//;---------------------------------------------------------------
	//; MEMBERS
	bool m_bInitialised;
	GCV_PLANE3D m_Plane;
	GCV_LINE3D m_WorkpieceImagePoints;
	GCV_LINE3D m_WorkpieceObjectPoints;
	GCV_MATRIX3D fTrans_Etalon_Turn, fTrans_Etalon_Turned, fTrans_Machine_Rel,
				 fTrans_Machine, fTrans_Workpiece, fTrans_Workpiece_Rel;
	GCV_EULER3D	fEuler_Etalon, fEuler_Machine_Rel, fEuler_Workpiece_Rel;
	//;---------------------------------------------------------------
};

#endif // !defined(AFX_IPOP_H__DE93C761_5E56_4F24_BEA7_7EF3EBE7ABF0__INCLUDED_)
