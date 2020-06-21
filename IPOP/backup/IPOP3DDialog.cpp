// 3DDialog.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "IPOPApp.h"
#include "IPOP3DDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CIPOP3DDialog 


CIPOP3DDialog::CIPOP3DDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CIPOP3DDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(CIPOP3DDialog)
	m_bPerspFront = FALSE;
	m_bPerspCamera = FALSE;
	m_bPerspLeft = FALSE;
	m_bPerspRight = FALSE;
	//}}AFX_DATA_INIT
}


void CIPOP3DDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CIPOP3DDialog)
	DDX_Check(pDX, IDC_3D_PERSP_FRONT, m_bPerspFront);
	DDX_Check(pDX, IDC_3D_PERSP_CAMERA, m_bPerspCamera);
	DDX_Check(pDX, IDC_3D_PERSP_LEFT, m_bPerspLeft);
	DDX_Check(pDX, IDC_3D_PERSP_RIGHT, m_bPerspRight);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CIPOP3DDialog, CDialog)
	//{{AFX_MSG_MAP(CIPOP3DDialog)
	ON_BN_CLICKED(IDC_3D_PERSP_FRONT, On3dPerspFront)
	ON_BN_CLICKED(IDC_3D_PERSP_CAMERA, On3dPerspCamera)
	ON_BN_CLICKED(IDC_3D_PERSP_LEFT, On3dPerspLeft)
	ON_BN_CLICKED(IDC_3D_PERSP_RIGHT, On3dPerspRight)
	ON_BN_CLICKED(IDC_3D_PERSP_BACK, On3dPerspBack)
	ON_BN_CLICKED(IDC_3DDialog_StartView, On3dPerspStart)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten CIPOP3DDialog 


//DEL BOOL CIPOP3DDialog::Create(CView *p3DView) 
//DEL {
//DEL 	// TODO: Speziellen Code hier einfügen und/oder Basisklasse aufrufen
//DEL 	m_Display_3D_pView = (CIPOP3DView*) p3DView;
//DEL 	m_Display_3D_pDoc = (CIPOP3DDoc*) p3DView->GetDocument();
//DEL 	return CDialog::Create(IDD_3DView,0);
//DEL }



void CIPOP3DDialog::On3dPerspFront() 
{
	// TODO: Code für die Behandlungsroutine der Steuerelement-Benachrichtigung hier einfügen
	//; standard view is down the negative z- axis looking perpendicular
	//; on the regular xy- plane ( x right, y up )  
	CIPOPApp* pApp = (CIPOPApp*) AfxGetApp();
	m_Display_3D_pDoc->m_eye(0) = 0; m_Display_3D_pDoc->m_eye(1) = 0; m_Display_3D_pDoc->m_eye(2) = 350;
	m_Display_3D_pDoc->m_angle = 180; 
	if(m_Display_3D_pView) m_Display_3D_pView->Invalidate(0);
}

void CIPOP3DDialog::On3dPerspCamera() 
{
	// TODO: Code für die Behandlungsroutine der Steuerelement-Benachrichtigung hier einfügen
	m_Display_3D_pDoc->m_eye(0) = 0; m_Display_3D_pDoc->m_eye(1) = 0; m_Display_3D_pDoc->m_eye(2) = 0;
	m_Display_3D_pDoc->m_angle = 180; 
	//m_Display_3D_pDoc->m_center(0) = 0; m_Display_3D_pDoc->m_center(1) = 10*sin(Pi/8);	m_Display_3D_pDoc->m_center(2) = 10*cos(Pi/20);

	if(m_Display_3D_pView) m_Display_3D_pView->Invalidate(0);
	
}

void CIPOP3DDialog::On3dPerspLeft() 
{
	// TODO: Code für die Behandlungsroutine der Steuerelement-Benachrichtigung hier einfügen
	CIPOPApp* pApp = (CIPOPApp*) AfxGetApp();
	m_Display_3D_pDoc->m_eye(0) = -500; m_Display_3D_pDoc->m_eye(1) = 0; m_Display_3D_pDoc->m_eye(2) = -600;//-600;
	m_Display_3D_pDoc->m_angle = 90; 
	if(m_Display_3D_pView) m_Display_3D_pView->Invalidate(0);
	
}

void CIPOP3DDialog::On3dPerspRight() 
{
	// TODO: Code für die Behandlungsroutine der Steuerelement-Benachrichtigung hier einfügen
	CIPOPApp* pApp = (CIPOPApp*) AfxGetApp();
	m_Display_3D_pDoc->m_eye(0) = 500; m_Display_3D_pDoc->m_eye(1) = 0; m_Display_3D_pDoc->m_eye(2) = -350;
	m_Display_3D_pDoc->m_angle = -90; 
	if(m_Display_3D_pView) m_Display_3D_pView->Invalidate(0);
	
}

void CIPOP3DDialog::On3dPerspBack() 
{
	// TODO: Code für die Behandlungsroutine der Steuerelement-Benachrichtigung hier einfügen
	CIPOPApp* pApp = (CIPOPApp*) AfxGetApp();
	m_Display_3D_pDoc->m_eye(0) = 0; m_Display_3D_pDoc->m_eye(1) = 0; m_Display_3D_pDoc->m_eye(2) =  - 350;
	m_Display_3D_pDoc->m_angle = 0; 
	if(m_Display_3D_pView) m_Display_3D_pView->Invalidate(0);
	
}

void CIPOP3DDialog::On3dPerspStart() 
{
	// TODO: Code für die Behandlungsroutine der Steuerelement-Benachrichtigung hier einfügen
	CIPOPApp* pApp = (CIPOPApp*) AfxGetApp();
	m_Display_3D_pDoc->m_eye(0) = 0; m_Display_3D_pDoc->m_eye(1) = 0; m_Display_3D_pDoc->m_eye(2) = -350;
	m_Display_3D_pDoc->m_angle = 180; 
	if(m_Display_3D_pView) m_Display_3D_pView->Invalidate(0);
	
}

void CIPOP3DDialog::Set3DViewAndDoc(CIPOP3DView* pView, CIPOP3DDoc* pDoc)
{
	m_Display_3D_pDoc = pDoc;
	m_Display_3D_pView = pView;
}
