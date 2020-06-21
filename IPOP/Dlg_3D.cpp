// Dlg_3D.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "IPOPApp.h"
#include "Dlg_3D.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
  
/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CDlg_3D 
  

CDlg_3D::CDlg_3D(CWnd* pParent /*=NULL*/)
	: CDialog(CDlg_3D::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlg_3D)
	m_bPerspFront = 1;
	m_bPerspBack = FALSE;
	m_bPerspLeft = FALSE;
	m_bPerspRight = FALSE;
	m_bDraw_ProjRays = 1;
	m_bDraw_CalPoints = 1;
	m_bDraw_Distances = 1;
	//}}AFX_DATA_INIT
}


void CDlg_3D::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlg_3D)
	DDX_Check(pDX, IDC_3D_PERSP_FRONT, m_bPerspFront);
	DDX_Check(pDX, IDC_3D_PERSP_BACK, m_bPerspBack);
	DDX_Check(pDX, IDC_3D_PERSP_LEFT, m_bPerspLeft);
	DDX_Check(pDX, IDC_3D_PERSP_RIGHT, m_bPerspRight);
	DDX_Check(pDX, IDC_3D_DRAW_PROJRAYS, m_bDraw_ProjRays);
	DDX_Check(pDX, IDC_3D_DRAW_CALPOINTS, m_bDraw_CalPoints);
	DDX_Check(pDX, IDC_3D_DRAW_DISTANCES, m_bDraw_Distances);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlg_3D, CDialog)
	//{{AFX_MSG_MAP(CDlg_3D)
	ON_BN_CLICKED(IDC_3D_PERSP_FRONT, On3dPerspFront)
	ON_BN_CLICKED(IDC_3D_PERSP_LEFT, On3dPerspLeft)
	ON_BN_CLICKED(IDC_3D_PERSP_RIGHT, On3dPerspRight)
	ON_BN_CLICKED(IDC_3D_PERSP_BACK, On3dPerspBack)
	ON_BN_CLICKED(IDC_3D_DRAW_PROJRAYS, On3dDrawProjrays)
	ON_BN_CLICKED(IDC_3D_DRAW_CALPOINTS, On3dDrawCalpoints)
	ON_BN_CLICKED(IDC_3D_DRAW_DISTANCES, On3dDrawDistances)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten CDlg_3D 


void CDlg_3D::On3dPerspFront() 
{
	// TODO: Code für die Behandlungsroutine der Steuerelement-Benachrichtigung hier einfügen
	//; standard view is down the negative z- axis looking perpendicular
	//; on the regular xy- plane ( x right, y up )  
	m_Disp_3D_pDoc->SetFrontView();
	m_Disp_3D_pDoc->UpdateAllViews(0);
}

//DEL void CDlg_3D::On3dPerspCamera() 
//DEL {
//DEL 	// TODO: Code für die Behandlungsroutine der Steuerelement-Benachrichtigung hier einfügen
//DEL 	m_Disp_3D_pDoc->m_ViewDirection.eye(0) = 0; m_Disp_3D_pDoc->m_ViewDirection.eye(1) = 0; 
//DEL 	m_Disp_3D_pDoc->m_ViewDirection.eye(2) = 0;
//DEL 	m_Disp_3D_pDoc->m_angle = 180; 
//DEL 	//m_Disp_3D_pDoc->m_center(0) = 0; m_Disp_3D_pDoc->m_center(1) = 10*sin(Pi/8);	m_Disp_3D_pDoc->m_center(2) = 10*cos(Pi/20);
//DEL 
//DEL 	m_Disp_3D_pDoc->UpdateAllViews(0);
//DEL 	
//DEL }

void CDlg_3D::On3dPerspLeft() 
{
	// TODO: Code für die Behandlungsroutine der Steuerelement-Benachrichtigung hier einfügen
	m_Disp_3D_pDoc->SetLeftView();
	m_Disp_3D_pDoc->UpdateAllViews(0);
	
}

void CDlg_3D::On3dPerspRight() 
{
	// TODO: Code für die Behandlungsroutine der Steuerelement-Benachrichtigung hier einfügen
	m_Disp_3D_pDoc->SetRightView();
	m_Disp_3D_pDoc->UpdateAllViews(0);
	
}

void CDlg_3D::On3dPerspBack() 
{
	// TODO: Code für die Behandlungsroutine der Steuerelement-Benachrichtigung hier einfügen
	m_Disp_3D_pDoc->SetBackView();
	m_Disp_3D_pDoc->UpdateAllViews(0);
	
}

//DEL void CDlg_3D::On3dPerspStart() 
//DEL {
//DEL 	// TODO: Code für die Behandlungsroutine der Steuerelement-Benachrichtigung hier einfügen
//DEL 	CIPOPApp* pApp = (CIPOPApp*) AfxGetApp();
//DEL 	m_Disp_3D_pDoc->m_ViewDirection.eye(0) = 0; m_Disp_3D_pDoc->m_ViewDirection.eye(1) = 0; 
//DEL 	m_Disp_3D_pDoc->m_ViewDirection.eye(2) = -350;
//DEL 	m_Disp_3D_pDoc->m_angle = 180; 
//DEL 	m_Disp_3D_pDoc->UpdateAllViews(0);
//DEL 	
//DEL }

void CDlg_3D::On3dDrawProjrays() 
{
	// TODO: Code für die Behandlungsroutine der Steuerelement-Benachrichtigung hier einfügen
	if(m_Disp_3D_pDoc->m_Vectors_p_b[0]) m_Disp_3D_pDoc->m_Vectors_p_b[0] = 0;
	else m_Disp_3D_pDoc->m_Vectors_p_b[0] = 3;
	m_Disp_3D_pDoc->UpdateAllViews(0);
}

void CDlg_3D::On3dDrawCalpoints() 
{
	// TODO: Code für die Behandlungsroutine der Steuerelement-Benachrichtigung hier einfügen
	if(m_Disp_3D_pDoc->m_Points_p_b[0]) m_Disp_3D_pDoc->m_Points_p_b[0] = 0;
	else m_Disp_3D_pDoc->m_Points_p_b[0] = 3;
	m_Disp_3D_pDoc->UpdateAllViews(0);
	
}
 
void CDlg_3D::On3dDrawDistances() 
{
	// TODO: Code für die Behandlungsroutine der Steuerelement-Benachrichtigung hier einfügen
	if(m_Disp_3D_pDoc->m_Lines_p_b[0]) m_Disp_3D_pDoc->m_Lines_p_b[0] = 0;
	else m_Disp_3D_pDoc->m_Lines_p_b[0] = 3;
	m_Disp_3D_pDoc->UpdateAllViews(0);
	
}
