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
	D3DVECTORLINE* GetPiercingPoints();
	void Calc_PiercingPoints();
	void UpdatePlane();
	void Reset();
	vector< D3DVECTORLINE >*  GetCorrespondingPoints();
	vector< D3DVECTOR >* GetPtsObj();
	void Calculate_Init();
	void Set_Calibration_InitTrafo(D3DMATRIX &Trafo);
	void Calculate_OneStep();
	CIPOP();
	virtual ~CIPOP();

	//D3DCAMERA m_Camera;
	D3DPLANE m_Plane;
	D3DVECTORLINE m_WorkpiecePoints;
	//D3DPLANE m_Plane;
	//D3DMATRIX m_Init_Transformation;
	//vector< D3DVECTOR, D3DVECTOR& > m_Pts_Obj, m_Pts_Img; 
	//vector < CPoint, CPoint& > *m_pCalibration_ObjectPoints,
	//	*m_pCalibration_ImagePoints;


};

#endif // !defined(AFX_IPOP_H__DE93C761_5E56_4F24_BEA7_7EF3EBE7ABF0__INCLUDED_)
