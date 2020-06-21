// IPOP3DDoc.cpp: Implementierung der Klasse CIPOP3DDoc.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "IPOPApp.h"
#include "IPOP3DDoc.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Konstruktion/Destruktion
//////////////////////////////////////////////////////////////////////

CIPOP3DDoc::CIPOP3DDoc()
{
}

CIPOP3DDoc::~CIPOP3DDoc()
{
}

void CIPOP3DDoc::SetCameraStruct( D3DCAMERA cam)
{
	//if(!m_Camera) AfxMessageBox("Fehler in CIPOP3DDoc::SetCameraStruct(D3DCAMERA* m_Camera): m_Camera==0");
	//; all values in mm * 10
	m_Camera = cam; int scal = 1;
	m_Lines1.RemoveAll();
	D3DVECTORPAIR line;
	line.Pt1(2) = line.Pt2(2) = - m_Camera.FocalLength * scal;

	float halfwidth=(m_Camera.PixNumX - m_Camera.PrincipalPointX)*(m_Camera.CellSizeX/2000)*scal, 
		halfheight=line.Pt1(1)=(m_Camera.PixNumY - m_Camera.PrincipalPointY)*(m_Camera.CellSizeY/2000)*scal;

	line.Pt1(0)=-halfwidth; line.Pt1(1)=halfheight; 
	line.Pt2(0)= halfwidth; line.Pt2(1)=halfheight; 
	m_Lines1.Add(line);

	line.Pt1(0)=-halfwidth; line.Pt1(1)=-halfheight; 
	line.Pt2(0)=halfwidth; line.Pt2(1)=-halfheight; 
	m_Lines1.Add(line);

	line.Pt1(0)=halfwidth; line.Pt1(1)=halfheight; 
	line.Pt2(0)=halfwidth; line.Pt2(1)=-halfheight; 
	m_Lines1.Add(line);

	line.Pt1(0)=-halfwidth; line.Pt1(1)=halfheight; 
	line.Pt2(0)=-halfwidth; line.Pt2(1)=-halfheight; 
	m_Lines1.Add(line);
}



void CIPOP3DDoc::SetImagepointlist(CArray <CPoint,CPoint&> *aList)
{
	//; all values in mm * 10
	//; Image Points
	m_Points1.RemoveAll(); float xval=0, yval=0; int scal = 1;
	D3DVECTOR pt; pt(2) = - m_Camera.FocalLength*scal;
	m_Lines2.RemoveAll(); int t=100;
	D3DVECTORPAIR line; line.Pt2(2) = - m_Camera.FocalLength*t;
	for(int i=0;i<aList->GetSize();i++){
		//xval=aList->GetAt(i).x; yval=aList->GetAt(i).y;
		pt(0) = (aList->GetAt(i).x - m_Camera.PrincipalPointX) * (m_Camera.CellSizeX/2000)*scal;
		pt(1) = - (aList->GetAt(i).y - m_Camera.PrincipalPointY) * (m_Camera.CellSizeY/2000)*scal;
		m_Points1.Add(pt);
		line.Pt2(0) = pt(0) * t;
		line.Pt2(1) = pt(1) * t;
		m_Lines2.Add(line);
	}
	//; Projection Rays
	
/*	line.Pt2(0) = (aList.GetAt(0).x - m_Camera.PrincipalPointX) * (m_Camera.CellSizeX/2000) * t;
	line.Pt2(1) = - (aList.GetAt(0).y - m_Camera.PrincipalPointY) * (m_Camera.CellSizeY/2000) * t;
	m_Lines2.Add(line);

	line.Pt2(0) = (aList.GetAt(size-1).x - m_Camera.PrincipalPointX) * (m_Camera.CellSizeX/2000) * t;
	line.Pt2(1) = - (aList.GetAt(size-1).y - m_Camera.PrincipalPointY) * (m_Camera.CellSizeY/2000) * t;
	m_Lines2.Add(line);*/
}

void CIPOP3DDoc::SetObjectpointlist(const CArray <CPoint,CPoint&> &aList)
{
	//; all values in mm * 10
	m_Points2.RemoveAll(); float xval=0, yval=0;
	D3DVECTOR pt; pt(2) = 0;
	for(int i=0;i<aList.GetSize();i++){
		xval=aList.GetAt(i).x; yval=aList.GetAt(i).y;
		pt(0) = aList.GetAt(i).x; pt(1) = aList.GetAt(i).y;
		m_Points2.Add(pt);
	}
}

void CIPOP3DDoc::SetSensingArea()
{
	
}

void CIPOP3DDoc::SetProjectionRays()
{
	
}
