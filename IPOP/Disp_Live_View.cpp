// Disp_Live_View.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "ipop.h"
#include "Disp_Live_View.h"
#include "Disp_Live_Doc.h"
#include "IPOPApp.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDisp_Live_View

IMPLEMENT_DYNCREATE(CDisp_Live_View, CView)

CDisp_Live_View::CDisp_Live_View()
{
}

CDisp_Live_View::~CDisp_Live_View()
{
	CDisp_Live_Doc* pDoc = (CDisp_Live_Doc*)GetDocument();
	((CIPOPApp*) AfxGetApp())->m_Disp_pLiveView = 0;
}


BEGIN_MESSAGE_MAP(CDisp_Live_View, CView)
	//{{AFX_MSG_MAP(CDisp_Live_View)
	ON_COMMAND(ID_VIDEO_GRABFRAME, OnPxcGrabFrame)
	ON_COMMAND(ID_PXC_CAM1, OnPxcCam1)
	ON_COMMAND(ID_PXC_CAM2, OnPxcCam2)
	ON_WM_KEYDOWN()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Zeichnung CDisp_Live_View 

void CDisp_Live_View::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// ZU ERLEDIGEN: Code zum Zeichnen hier einfügen
}

/////////////////////////////////////////////////////////////////////////////
// Diagnose CDisp_Live_View

#ifdef _DEBUG
void CDisp_Live_View::AssertValid() const
{
	CView::AssertValid();
}

void CDisp_Live_View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten CDisp_Live_View 

void CDisp_Live_View::FitWindow(int width, int height)
{
	CDisp_Live_Doc* pDoc = (CDisp_Live_Doc*) GetDocument();
	this->GetParent()->SetWindowPos( NULL, 0, 0, width+10, height+30, SWP_NOMOVE | SWP_SHOWWINDOW | SWP_NOZORDER );			
	pDoc->SetTitle("Live Camera");
	this->GetParentOwner()->Invalidate( FALSE );
}

void CDisp_Live_View::OnPxcGrabFrame() 
{
	// TODO: Code für Befehlsbehandlungsroutine hier einfügen
	CDisp_Live_Doc* pDoc = (CDisp_Live_Doc*) GetDocument();
	if(!pDoc->m_Grabber_PXC->IsInitialised()) return;
	if(pDoc->m_Grabber_PXC->GetGrabberStatus()!=kGrabberInitialized)
		Init_PXC();
	pDoc->m_Grabber_PXC->SaveBmp("PXCgrabbed.bmp");
	((CIPOPApp*) AfxGetApp())->LoadBmp("PXCgrabbed.bmp"); }


bool CDisp_Live_View::Init_PXC()
{
	CDisp_Live_Doc* pDoc = (CDisp_Live_Doc*) GetDocument();
	if(!pDoc->m_Grabber_PXC) pDoc->m_Grabber_PXC = new IMG_PXC(768,576);
	if(!pDoc->m_Grabber_PXC->Init()) {
		AfxMessageBox("Initialisierung gescheitert."); return 0; }
	GetParent()->SetWindowPos( NULL, 0, 0, pDoc->m_Grabber_PXC->fImageMaxX+10,
		pDoc->m_Grabber_PXC->fImageMaxY+30, SWP_NOMOVE | SWP_SHOWWINDOW | SWP_NOZORDER );			
	if(!pDoc->m_Grabber_PXC->StartLiveVideo(0,this->m_hWnd,0)) return 0;
	return 1;
}

void CDisp_Live_View::OnPxcCam1() 
{
	// TODO: Code für Befehlsbehandlungsroutine hier einfügen
	CDisp_Live_Doc* pDoc = (CDisp_Live_Doc*) GetDocument();
	if(!pDoc->m_Grabber_PXC->IsInitialised()) return;
	pDoc->m_Grabber_PXC->SelectCamera(1);
	
}

void CDisp_Live_View::OnPxcCam2() 
{
	// TODO: Code für Befehlsbehandlungsroutine hier einfügen
	CDisp_Live_Doc* pDoc = (CDisp_Live_Doc*) GetDocument();
	if(!pDoc->m_Grabber_PXC->IsInitialised()) return;
	pDoc->m_Grabber_PXC->SelectCamera(2);
	
}

void CDisp_Live_View::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	// TODO: Code für die Behandlungsroutine für Nachrichten hier einfügen und/oder Standard aufrufen
	CIPOPApp* pApp = (CIPOPApp*) AfxGetApp();
	if (nChar==unsigned(VK_SPACE)){ 
		if(pApp->m_Disp_pPicDoc) pApp->SnapAndReg();
	}

	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}
