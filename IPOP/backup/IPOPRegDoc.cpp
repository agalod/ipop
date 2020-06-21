// IPOPDoc.cpp : Implementierung der Klasse CIPOPRegDoc
//

#include "stdafx.h"
#include "IPOPApp.h"

#include "IPOPRegDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CIPOPRegDoc

IMPLEMENT_DYNCREATE(CIPOPRegDoc, CDocument)

BEGIN_MESSAGE_MAP(CIPOPRegDoc, CDocument)
	//{{AFX_MSG_MAP(CIPOPRegDoc)
		// HINWEIS - Hier werden Mapping-Makros vom Klassen-Assistenten eingefügt und entfernt.
		//    Innerhalb dieser generierten Quelltextabschnitte NICHTS VERÄNDERN!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CIPOPRegDoc Konstruktion/Destruktion

CIPOPRegDoc::CIPOPRegDoc()
{
	// ZU ERLEDIGEN: Hier Code für One-Time-Konstruktion einfügen
	m_pRegPointPair=0;
}

CIPOPRegDoc::~CIPOPRegDoc()
{
	((CIPOPApp*) AfxGetApp())->m_Display_pRegistrationDoc = 0;
}

BOOL CIPOPRegDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// ZU ERLEDIGEN: Hier Code zur Reinitialisierung einfügen
	// (SDI-Dokumente verwenden dieses Dokument)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CIPOPRegDoc Serialisierung

void CIPOPRegDoc::Serialize(CArchive& ar)
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
// CIPOPRegDoc Diagnose

#ifdef _DEBUG
void CIPOPRegDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CIPOPRegDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CIPOPRegDoc Befehle

CImageServer* CIPOPRegDoc::GetImageServer()
{
	return &m_ImageServer;
}
#define INITMAT INITCVMAT
#define INITCVMAT(mat,r,c)\
CvMat mat = cvMat(r,c,CV_MAT64D,NULL);cvmAlloc(&mat);

#define FREE(mat) cvmFree(&mat);

#ifndef MYFUNCS
#define MYFUNCS
static void Transform3DPt( double mat[9], double pt[3], double retpt[3] ){
	for(int i=0; i<3;i++){
		retpt[i] = pt[0] * mat[i*3+0] + pt[1] * mat[i*3+1] + pt[2] * mat[i*3+2]; 
	}
}

static void Mult3Mats( double mat1[9], double mat2[9], double retmat[9] ){
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

static void CrossProduct3DPt( double pt1[3], double pt2[3], double retpt[3] ){
	retpt[0] = pt1[1]*pt2[2] - pt1[2]*pt2[1];
	retpt[1] = pt1[2]*pt2[0] - pt1[0]*pt2[2];
	retpt[2] = pt1[0]*pt2[1] - pt1[1]*pt2[0];
}

static double Norm3DPt( double pt[3] ){
	return ( sqrt( pow(pt[0],2) + pow(pt[1],2) + pow(pt[2],2) ) );
}
#endif







