// IPOPRegView.cpp : Implementierung der Klasse CIPOPRegView
//

#include "stdafx.h"
#include "IPOPApp.h"

#include "IPOPDoc.h"
#include "IPOPRegView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CIPOPRegView

IMPLEMENT_DYNCREATE(CIPOPRegView, CView)

BEGIN_MESSAGE_MAP(CIPOPRegView, CView)
	//{{AFX_MSG_MAP(CIPOPRegView)
	ON_COMMAND(ID_VIEW_CALIBRATE, OnCalibrate_Init)
	ON_COMMAND(ID_VIEW_REGISTER, OnRegister)
	ON_COMMAND(ID_VIEW_BACK, On_ViewBack)
	ON_COMMAND(ID_VIEW_FORWARD, On_ViewForward)
	ON_WM_LBUTTONDOWN()
	ON_WM_KEYDOWN()
	ON_WM_RBUTTONDOWN()
	ON_WM_SYSKEYDOWN()
	ON_COMMAND(ID_REG_IP_BINARIZE, OnRegIpBinarize)
	ON_COMMAND(ID_REG_IP_HOUGH, OnRegIpHough)
	ON_COMMAND(ID_REG_IP_EDGE, OnRegIpEdge)
	ON_COMMAND(ID_VIEW_CALIBRATE_INIT, OnCalibrate_Init)
	ON_COMMAND(ID_REGISTRIEREN_VORVERARBEITUNG, OnRegistrierenVorverarbeitung)
	//}}AFX_MSG_MAP
	// Standard-Druckbefehle
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CIPOPRegView Konstruktion/Destruktion

CIPOPRegView::CIPOPRegView()
{
	// ZU ERLEDIGEN: Hier Code zur Konstruktion einfügen,
	m_ptidx = 1;

}

CIPOPRegView::~CIPOPRegView()
{
	((CIPOPApp*) AfxGetApp())->m_Display_pRegistrationView = 0;
}

BOOL CIPOPRegView::PreCreateWindow(CREATESTRUCT& cs)
{
	// ZU ERLEDIGEN: Ändern Sie hier die Fensterklasse oder das Erscheinungsbild, indem Sie
	//  CREATESTRUCT cs modifizieren.

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CIPOPRegView Zeichnen

void CIPOPRegView::DC_DrawPoint(CPoint Point, const color num )
{
	CDC* pDC = GetDC();
	CPen blue(PS_SOLID, 1, 0xFFFF00);
	CPen green(PS_SOLID, 1, 0x00FF00 );
	CPen red(PS_SOLID, 1, 0x0000FF );
	switch (num)
	{
	case 0: pDC->SelectObject(&red); break;
	case 1: pDC->SelectObject(&green); break;
	case 2: pDC->SelectObject(&blue); break;
	default: pDC->SelectObject(&red); break;
	}
	
	int x = Point.x, y = Point.y;
	pDC->MoveTo( x - 5, y );
	pDC->LineTo( x + 5, y );
	pDC->MoveTo( x, y + 5 );
	pDC->LineTo( x, y - 5 );
}


void CIPOPRegView::DC_DrawCoordinate(CPoint& Point)
{
	CDC* pDC = GetDC();
	CPen newPen(PS_DASHDOTDOT, 3, 0x00FF00);
	pDC->SelectObject(&newPen);
	int x = Point.x, y = Point.y;
	CString text;
	text.Format("x: %d; y: %d", x, y ); 
	pDC->TextOut(x,y,text);  
}


void CIPOPRegView::DC_DrawIndex(CPoint& Point, int aIdx)
{
	CDC* pDC = GetDC();
	CPen newPen(PS_DASHDOTDOT, 3, 0x00FF00);
	pDC->SelectObject(&newPen);
	int x = Point.x, y = Point.y;
	CString text;
	text.Format("%d", aIdx); 
	pDC->TextOut(x+5,y+5,text);  
	
}
void CIPOPRegView::DC_DrawLine(CPoint& p0, CPoint& p1, int Farbe )
{	
	
	CDC* pDC = GetDC();
	
	//int HexaFarbe;
	//if (Farbe == 1) //gelb
	//	HexaFarbe = 0x00FFFF; 
	//else //blau
	//	HexaFarbe = 0xFF0000;
	CPen bluepen(PS_SOLID, 1, 0xFF0000); 
	
	pDC->SelectObject(&bluepen);
	pDC->MoveTo( p0 );
	pDC->LineTo( p1 );
	
}

void CIPOPRegView::DC_DrawCircle(CPoint& p0, CPoint& p1)
{	
	double x0 = p0.x, y0 =  p0.y, x1 = p1.x, y1 =  p1.y;
	
	CDC* pDC = GetDC();
	CPen bluepen(PS_SOLID, 3, 0xFF0000);
	
	pDC->SelectObject(GetStockObject( NULL_BRUSH ));
	
	pDC->SelectObject(&bluepen);
	pDC->Ellipse(CRect(x0, y0, x1, y1));
	
}

void CIPOPRegView::OnDraw(CDC* pDC)
{
	pDC->SetTextColor(0x00FF00);
	CIPOPRegDoc* pDoc = GetDocument(); RECT rect; GetClientRect(&rect);
	CImageServer* iserver = pDoc->GetImageServer();
	if(! iserver->CList_GetCount() ) return;
	if(iserver->CList_GetCurrentImage()){	
		iserver->CList_GetCurrentImage()->Show(pDC->GetSafeHdc(),0,0,iserver->CList_GetCurrentImage()->Width(),
			iserver->CList_GetCurrentImage()->Height());}

	if(m_ptidx==1)	pDC->TextOut(0,0,"linken Punkt klicken");
	if(m_ptidx==2)	pDC->TextOut(rect.right-140,0,"rechten Punkt klicken");

	CPoint pt1(pDoc->m_pRegPointPair->Pt1.x, pDoc->m_pRegPointPair->Pt1.y);
	CPoint pt2(pDoc->m_pRegPointPair->Pt2.x, pDoc->m_pRegPointPair->Pt2.y);
	DC_DrawPoint(pt1,red); DC_DrawPoint(pt2,red);
	ASSERT_VALID(pDoc);
	//pDoc->SetTitle("Registrierbild");
	// ZU ERLEDIGEN: Hier Code zum Zeichnen der ursprünglichen Daten hinzufügen
}

/////////////////////////////////////////////////////////////////////////////
// CIPOPRegView Drucken

BOOL CIPOPRegView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// Standardvorbereitung
	return DoPreparePrinting(pInfo);
}

void CIPOPRegView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// ZU ERLEDIGEN: Zusätzliche Initialisierung vor dem Drucken hier einfügen
}

void CIPOPRegView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// ZU ERLEDIGEN: Hier Bereinigungsarbeiten nach dem Drucken einfügen
}

/////////////////////////////////////////////////////////////////////////////
// CIPOPRegView Diagnose

#ifdef _DEBUG
void CIPOPRegView::AssertValid() const
{
	CView::AssertValid();
}

void CIPOPRegView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CIPOPRegDoc* CIPOPRegView::GetDocument() // Die endgültige (nicht zur Fehlersuche kompilierte) Version ist Inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CIPOPRegDoc)));
	return (CIPOPRegDoc*)m_pDocument;
}
#endif //_DEBUG

void CIPOPRegView::OnCalibrate_Init(){
	//; Legen sie das Kalibriermuster auf den Werkzeugtisch.");
	//; Klicken sie die vier Umrandungspunkte an.");
	CIPOPApp* pApp = (CIPOPApp*) AfxGetApp();
	pApp->Calc_Calibrate_Init();
}


void CIPOPRegView::OnRegister(){
	//pApp->m_pIPOP->Register(pApp->GrabFrame());
	//GetDocument()->ShowResult();

}

void CIPOPRegView::FitWindow(int width, int height)
{
	this->GetParent()->SetWindowPos( NULL, 0, 0, width+10, height+30, SWP_NOMOVE | SWP_SHOWWINDOW | SWP_NOZORDER );			
	this->GetParentOwner()->Invalidate( FALSE );
}



void CIPOPRegView::On_ViewBack() 
{
	// TODO: Code für Befehlsbehandlungsroutine hier einfügen
	GetDocument()->GetImageServer()->CList_BrowseBackward();
	FitWindow(GetDocument()->GetImageServer()->Image_Width(), GetDocument()->GetImageServer()->Image_Height());
	GetDocument()->SetTitle("Registrierbild:  " + GetDocument()->GetImageServer()->CList_GetCurrentImageName());
}

void CIPOPRegView::On_ViewForward() 
{
	// TODO: Code für Befehlsbehandlungsroutine hier einfügen
	GetDocument()->GetImageServer()->CList_BrowseForward();
	FitWindow(GetDocument()->GetImageServer()->Image_Width(), GetDocument()->GetImageServer()->Image_Height());
	GetDocument()->SetTitle("Registrierbild:  " + GetDocument()->GetImageServer()->CList_GetCurrentImageName());
}

void CIPOPRegView::OnLButtonDown(UINT nFlags, CPoint point) 
{
	//; push_backs an intersectionpoint to the houghclassobject if left clicked on it.
	//CIPOPApp* pApp = (CIPOPApp*) AfxGetApp();
	CIPOPRegDoc* pDoc = (CIPOPRegDoc*)GetDocument();
	CIPOPApp* pApp = (CIPOPApp*) AfxGetApp();

	switch(m_ptidx)
	{
	case 1: pDoc->m_pRegPointPair->Pt1.x = point.x; 
			pDoc->m_pRegPointPair->Pt1.y = point.y; break;
	case 2: pDoc->m_pRegPointPair->Pt2.x = point.x; 
			pDoc->m_pRegPointPair->Pt2.y = point.y; 
			pApp->m_IPOP.Calc_PiercingPoints();
			break;
	}
	Invalidate(1);
	CView::OnLButtonDown(nFlags, point);
}


void CIPOPRegView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	// TODO: Code für die Behandlungsroutine für Nachrichten hier einfügen und/oder Standard aufrufen
	CIPOPDoc* pDoc = (CIPOPDoc*)GetDocument(); int a=0;
	switch(nChar)
	{
	case VK_F1:
		m_ptidx=1; break; //AfxMessageBox("Geben sie nun den 1. Punkt ein!");break;
	case VK_F2:
		m_ptidx=2; break;//AfxMessageBox("Geben sie nun den 2. Punkt ein!");break;
	case VK_LEFT:
		On_ViewBack(); break;
	case VK_RIGHT:
		On_ViewForward(); break;
	case VK_UP:
		//OnDeleteImage(); break;
	default:
		break;
	}
	Invalidate(1);
	CView::OnKeyDown(nChar, nRepCnt, nFlags);
	
}





void CIPOPRegView::OnRButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Code für die Behandlungsroutine für Nachrichten hier einfügen und/oder Standard aufrufen
	CIPOPDoc* pDoc = (CIPOPDoc*)GetDocument();
	Invalidate(1);
	CView::OnRButtonDown(nFlags, point);
}

void CIPOPRegView::OnSysKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	// TODO: Code für die Behandlungsroutine für Nachrichten hier einfügen und/oder Standard aufrufen
	
	CView::OnSysKeyDown(nChar, nRepCnt, nFlags);
}

void CIPOPRegView::OnRegIpBinarize() 
{
	// TODO: Code für Befehlsbehandlungsroutine hier einfügen
	
}

void CIPOPRegView::OnRegIpHough() 
{
	// TODO: Code für Befehlsbehandlungsroutine hier einfügen
	
}

void CIPOPRegView::OnRegIpEdge() 
{
	// TODO: Code für Befehlsbehandlungsroutine hier einfügen
	
}

void CIPOPRegView::OnRegistrierenVorverarbeitung() 
{
	// TODO: Code für Befehlsbehandlungsroutine hier einfügen
	
}
