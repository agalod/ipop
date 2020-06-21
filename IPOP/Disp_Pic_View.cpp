// Disp_Pic_View.cpp : Implementierung der Klasse CDisp_Pic_View
//

#include "stdafx.h"
#include "IPOPApp.h"

#include "Disp_Pic_Doc.h"
#include "Disp_Pic_View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDisp_Pic_View
  
IMPLEMENT_DYNCREATE(CDisp_Pic_View, CView)

BEGIN_MESSAGE_MAP(CDisp_Pic_View, CView)
	//{{AFX_MSG_MAP(CDisp_Pic_View)
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
	ON_COMMAND(ID_REGISTRIEREN_VORVERARBEITUNG, OnRegIPPreprocess)
	ON_COMMAND(ID_VIEW_MODEK, OnViewModek)
	ON_COMMAND(ID_VIEW_MODER, OnViewModer)
	ON_COMMAND(ID_PICVIEW_SAVEBMP, OnPicviewSavebmp)
	ON_COMMAND(ID_REG_EROSION, OnRegErosion)
	ON_COMMAND(ID_VIEW_CALIBRATE_INIT, OnCalibrate_Init)
	ON_COMMAND(ID_REG_FLOODFILL, OnRegFloodfill)
	//}}AFX_MSG_MAP
	// Standard-Druckbefehle
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDisp_Pic_View Konstruktion/Destruktion

CDisp_Pic_View::CDisp_Pic_View()
{
	// ZU ERLEDIGEN: Hier Code zur Konstruktion einfügen,
	m_ptidx = 0;

}

CDisp_Pic_View::~CDisp_Pic_View()
{
	((CIPOPApp*) AfxGetApp())->m_Disp_pPicView = 0;
}

BOOL CDisp_Pic_View::PreCreateWindow(CREATESTRUCT& cs)
{
	// ZU ERLEDIGEN: Ändern Sie hier die Fensterklasse oder das Erscheinungsbild, indem Sie
	//  CREATESTRUCT cs modifizieren.

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CDisp_Pic_View Zeichnen

void CDisp_Pic_View::DC_DrawPoint(CPoint Point, const color num ){
	CDC* pDC = GetDC();
	CPen blue(PS_SOLID, 1, 0xFFFF00);	CPen green(PS_SOLID, 1, 0x00FF00 );
	CPen red(PS_SOLID, 1, 0x0000FF );
	switch (num)	{
	case 0: pDC->SelectObject(&red); break;	case 1: pDC->SelectObject(&green); break;
	case 2: pDC->SelectObject(&blue); break;	default: pDC->SelectObject(&red); break;	}
	int x = Point.x, y = Point.y;
	pDC->MoveTo( x - 5, y );	pDC->LineTo( x + 5, y );
	pDC->MoveTo( x, y + 5 );	pDC->LineTo( x, y - 5 );}


void CDisp_Pic_View::DC_DrawPoint(GCV_POINT2D &Point, const color num ){
	CDC* pDC = GetDC();
	CPen blue(PS_SOLID, 2, 0xFFFF00);	CPen green(PS_SOLID, 2, 0x00FF00 );
	CPen red(PS_SOLID, 2, 0x0000FF );
	switch (num)	{
	case 0: pDC->SelectObject(&red); break;
	case 1: pDC->SelectObject(&green); break;
	case 2: pDC->SelectObject(&blue); break;
	default: pDC->SelectObject(&red); break;	}
	int x = Point.x, y = Point.y;
	pDC->MoveTo( x - 5, y );	pDC->LineTo( x + 5, y );
	pDC->MoveTo( x, y + 5 );	pDC->LineTo( x, y - 5 );}


void CDisp_Pic_View::DC_DrawPoint(GCV_VECTOR3D &Point, const color num ){
	CDC* pDC = GetDC();	
	CPen blue(PS_SOLID, 2, 0xFFFF00); CPen green(PS_SOLID, 2, 0x00FF00 );
	CPen red(PS_SOLID, 2, 0x0000FF );
	switch (num)	{
	case 0: pDC->SelectObject(&red); break;
	case 1: pDC->SelectObject(&green); break;
	case 2: pDC->SelectObject(&blue); break;
	default: pDC->SelectObject(&red); break; }
	int x = Point(0), y = Point(1);
	pDC->MoveTo( x - 5, y );	pDC->LineTo( x + 5, y );
	pDC->MoveTo( x, y + 5 );	pDC->LineTo( x, y - 5 ); }


void CDisp_Pic_View::DC_DrawCoordinate(CPoint& Point){
	CDC* pDC = GetDC();	CPen newPen(PS_DASHDOTDOT, 3, 0x00FF00);
	pDC->SelectObject(&newPen);	int x = Point.x, y = Point.y;
	CString text;	text.Format("x: %d; y: %d", x, y ); pDC->TextOut(x,y,text);  }


void CDisp_Pic_View::DC_DrawIndex(GCV_POINT2D& Point, int aIdx){
	CDC* pDC = GetDC();	CPen newPen(PS_DASHDOTDOT, 3, 0x00FF00);
	pDC->SelectObject(&newPen);	int x = Point.x, y = Point.y;
	CString text;	text.Format("%d", aIdx); 	pDC->TextOut(x+5,y+5,text);  }


void CDisp_Pic_View::DC_DrawIndex(GCV_VECTOR3D& Point, int aIdx){
	CDC* pDC = GetDC();	CPen newPen(PS_DASHDOTDOT, 3, 0x00FF00);
	pDC->SelectObject(&newPen);	int x = Point(0), y = Point(1);
	CString text;	text.Format("%d", aIdx); 	pDC->TextOut(x+5,y+5,text);  }


void CDisp_Pic_View::DC_DrawIndex(CPoint& Point, int aIdx){
	CDC* pDC = GetDC();	CPen newPen(PS_DASHDOTDOT, 3, 0x00FF00);
	pDC->SelectObject(&newPen);	int x = Point.x, y = Point.y;
	CString text;	text.Format("%d", aIdx); 	pDC->TextOut(x+5,y+5,text);  }


void CDisp_Pic_View::DC_DrawLine(CPoint& p0, CPoint& p1, int Farbe ){	
	CDC* pDC = GetDC();	int HexaFarbe;
	switch(Farbe){
	case(0): HexaFarbe = 0x0000FF; break;
	case(1): HexaFarbe = 0x00FF00; break;
	case(2): HexaFarbe = 0xFF0000; break;	}
	CPen pen(PS_SOLID, 1, HexaFarbe); 	pDC->SelectObject(&pen);
	pDC->MoveTo( p0 );	pDC->LineTo( p1 );}


void CDisp_Pic_View::DC_DrawLine(GCV_POINT2D Pt1, GCV_POINT2D Pt2, int Farbe ){	
	CDC* pDC = GetDC();	int HexaFarbe;
	switch(Farbe){
	case(0): HexaFarbe = 0x0000FF; break;
	case(1): HexaFarbe = 0x00FF00; break;
	case(2): HexaFarbe = 0xFF0000; break;	}
	CPen pen(PS_SOLID, 1, HexaFarbe); 
	CPoint p0(Pt1.x,Pt1.y), p1(Pt2.x,Pt2.y);
	pDC->SelectObject(&pen);pDC->MoveTo( p0 );	pDC->LineTo( p1 );}


void CDisp_Pic_View::DC_DrawLine(GCV_LINE2D &line, int Farbe ){	
	CDC* pDC = GetDC();	int HexaFarbe;
	switch(Farbe){
	case(0): HexaFarbe = 0x0000FF; break;
	case(1): HexaFarbe = 0x00FF00; break;
	case(2): HexaFarbe = 0xFF0000; break;	}
	CPen pen(PS_SOLID, 2, HexaFarbe); 
	CPoint p0(line.pt1.x,line.pt1.y), p1(line.pt2.x,line.pt2.y);
	pDC->SelectObject(&pen); pDC->MoveTo( p0 );	pDC->LineTo( p1 ); }


void CDisp_Pic_View::DC_DrawLine(GCV_LINE3D &line, int Farbe ){	
	CDC* pDC = GetDC();	int HexaFarbe;
	switch(Farbe){
	case(0): HexaFarbe = 0x0000FF; break;
	case(1): HexaFarbe = 0x00FF00; break;
	case(2): HexaFarbe = 0xFF0000; break;	}
	CPen pen(PS_SOLID, 2, HexaFarbe); pDC->SelectObject(&pen);
	CPoint p0(line.pt1.x,line.pt1.y), p1(line.pt2.x,line.pt2.y);
	pDC->MoveTo( p0 );	pDC->LineTo( p1 );	}


void CDisp_Pic_View::DC_DrawCircle(CPoint& p0, CPoint& p1){	
	double x0 = p0.x, y0 =  p0.y, x1 = p1.x, y1 =  p1.y;
	CDC* pDC = GetDC();	CPen bluepen(PS_SOLID, 3, 0xFF0000);
	pDC->SelectObject(GetStockObject( NULL_BRUSH ));
	pDC->SelectObject(&bluepen);
	pDC->Ellipse(CRect(x0, y0, x1, y1)); }


void CDisp_Pic_View::OnDraw(CDC* pDC) {
	CIPOPApp* pApp = (CIPOPApp*) AfxGetApp();
	CDisp_Pic_Doc* pDoc = GetDocument(); 
	pDC->SetTextColor(0x00FF00); RECT rect; GetClientRect(&rect);
	GCV_QUAD2D* quad = &(pDoc->m_Etalon_Corners);
	if(! pDoc->CList_GetCount() ) return; pDoc->SetTitle();
	//; DISPLAY IMAGE
	if(pDoc->CList_GetCurrentImage()){	
		pDoc->CList_GetCurrentImage()->Show(pDC->GetSafeHdc(),0,0,
		pDoc->CList_GetCurrentImage()->Width(),	pDoc->CList_GetCurrentImage()->Height());}
	GCV_VECTOR3D zero3dpt; int PtNum=0;	GCV_POINT2D zeropt, pt;
	//; DRAWS INFOS IN REGISTERMODE
	if(pDoc->m_Mode){ 
		if(m_ptidx==5)	pDC->TextOut(0,0,"linken Punkt klicken");
		if(m_ptidx==6)	pDC->TextOut(rect.right-140,0,"rechten Punkt klicken");
		for(int i=0;i<pDoc->m_Lines.size();i++){
			if(pDoc->m_Lines[i].show) {DC_DrawLine(pDoc->m_Lines[i], red); 
			DC_DrawIndex(pDoc->m_Lines[i].pt1, i);}}
		if( !( pDoc->m_Workpiece_Points.pt1 == zeropt ||
			pDoc->m_Workpiece_Points.pt2 == zeropt ) ){
			DC_DrawPoint(pDoc->m_Workpiece_Points.pt1,red);
			DC_DrawPoint(pDoc->m_Workpiece_Points.pt2,red);
			DC_DrawLine(pDoc->m_Workpiece_Points, red); } }
	//; DRAWS INFOS IN CALIBRATIONMODE
	else{ //; Kalibriermodus
		if(m_ptidx==1)	
			pDC->TextOut(0,0,"links-oben klicken");
		if(m_ptidx==2)	pDC->TextOut(rect.right-140,0,"rechts-oben klicken");
		if(m_ptidx==3)	pDC->TextOut(rect.right-140,rect.bottom-30,"rechts-unten klicken");
		if(m_ptidx==4)	pDC->TextOut(0,rect.bottom-30,"links-unten klicken");
		if(m_ptidx==6)	pDC->TextOut(0,0,"Eckpunkte anklicken");
		if(quad->pt1!=zeropt&&quad->pt2!=zeropt)
			DC_DrawLine(quad->pt1, quad->pt2,blue);
		if(quad->pt2!=zeropt&&quad->pt3!=zeropt)
			DC_DrawLine(quad->pt2, quad->pt3,blue);
		if(quad->pt3!=zeropt&&quad->pt4!=zeropt)
			DC_DrawLine(quad->pt3, quad->pt4,blue);
		if(quad->pt4!=zeropt&&quad->pt1!=zeropt)
			DC_DrawLine(quad->pt4, quad->pt1,blue);
		for( PtNum=0; PtNum<pDoc->m_Etalon_Points_Image.size(); PtNum++){
			pt= (pDoc->m_Etalon_Points_Image)[PtNum];
			DC_DrawPoint(pt,green);
			DC_DrawIndex(pt,PtNum+1);}	} }

/////////////////////////////////////////////////////////////////////////////
// CDisp_Pic_View Drucken

BOOL CDisp_Pic_View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// Standardvorbereitung
	return DoPreparePrinting(pInfo);
}

void CDisp_Pic_View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// ZU ERLEDIGEN: Zusätzliche Initialisierung vor dem Drucken hier einfügen
}

void CDisp_Pic_View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// ZU ERLEDIGEN: Hier Bereinigungsarbeiten nach dem Drucken einfügen
}

/////////////////////////////////////////////////////////////////////////////
// CDisp_Pic_View Diagnose

#ifdef _DEBUG
void CDisp_Pic_View::AssertValid() const
{
	CView::AssertValid();
}

void CDisp_Pic_View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CDisp_Pic_Doc* CDisp_Pic_View::GetDocument() // Die endgültige (nicht zur Fehlersuche kompilierte) Version ist Inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CDisp_Pic_Doc)));
	return (CDisp_Pic_Doc*)m_pDocument;
}
#endif //_DEBUG

void CDisp_Pic_View::OnCalibrate_Init(){
	//; Legen sie das Kalibriermuster auf den Werkzeugtisch.");
	//; Klicken sie die vier Umrandungspunkte an.");
	CIPOPApp* pApp = (CIPOPApp*) AfxGetApp();
	pApp->Calc_Calibrate_Init();
}


void CDisp_Pic_View::OnRegister(){
	//pApp->m_pIPOP->Register(pApp->GrabFrame());
	//GetDocument()->ShowResult();

}

void CDisp_Pic_View::FitWindow(int width, int height)
{
	this->GetParent()->SetWindowPos( NULL, 0, 0, width+10, height+30, SWP_NOMOVE | SWP_SHOWWINDOW | SWP_NOZORDER );			
	Invalidate( FALSE );
}



void CDisp_Pic_View::On_ViewBack() 
{
	// TODO: Code für Befehlsbehandlungsroutine hier einfügen
	GetDocument()->CList_BrowseBackward();
	FitWindow(GetDocument()->Image_Width(), GetDocument()->Image_Height());
	GetDocument()->SetTitle();
}

void CDisp_Pic_View::On_ViewForward() 
{
	// TODO: Code für Befehlsbehandlungsroutine hier einfügen
	GetDocument()->CList_BrowseForward();
	FitWindow(GetDocument()->Image_Width(), 
		GetDocument()->Image_Height());
	GetDocument()->SetTitle();
}

void CDisp_Pic_View::OnLButtonDown(UINT nFlags, CPoint pt) 
{
	//; push_backs an intersectionpoint to the houghclassobject if left clicked on it.
	CIPOPApp* pApp = (CIPOPApp*) AfxGetApp();
	CDisp_Pic_Doc* pDoc = (CDisp_Pic_Doc*)GetDocument();
	GCV_POINT2D  point = pt, zeropt; GCV_IMAGEPOINT3D imagepoint; 
	imagepoint.camera = pApp->m_IPOP.fCamera;
	imagepoint = point; 

	switch(m_ptidx)
	{
	case 1: pDoc->m_Etalon_Corners.pt1 = point; break;
	case 2: pDoc->m_Etalon_Corners.pt2 = point; break;
	case 3: pDoc->m_Etalon_Corners.pt3 = point; break;
	case 4: pDoc->m_Etalon_Corners.pt4 = point; 
		if(pDoc->m_Etalon_Corners.pt1.x ==0 ||pDoc->m_Etalon_Corners.pt2.x==0||pDoc->m_Etalon_Corners.pt3.x==0||pDoc->m_Etalon_Corners.pt4.x==0)
			AfxMessageBox("Es sind nicht alle vier Punkte definiert!");  
		else
		{ pDoc->Image_DefineGrid(); m_ptidx=0;} break;
	case 5: pDoc->m_Workpiece_Points.pt1.x = point.x; 
			pDoc->m_Workpiece_Points.pt1.y = point.y; 
			if( !( pDoc->m_Workpiece_Points.pt1 == zeropt ||
				pDoc->m_Workpiece_Points.pt2 == zeropt ) ){
				pApp->m_IPOP.Calc_PiercingPoints(pDoc->m_Workpiece_Points);
				pApp->m_Dlg_Pose->UpdateData(0);}
			break;
	case 6: pDoc->m_Workpiece_Points.pt2.x = point.x; 
			pDoc->m_Workpiece_Points.pt2.y = point.y; 
			if( !( pDoc->m_Workpiece_Points.pt1 == zeropt ||
				pDoc->m_Workpiece_Points.pt2 == zeropt ) ){
				pApp->m_IPOP.Calc_PiercingPoints(pDoc->m_Workpiece_Points);
				pApp->m_Dlg_Pose->UpdateData(0);}
			break;
	}
	Invalidate(1);
	CView::OnLButtonDown(nFlags, pt);
/*	case 5: pDoc->m_Workpiece_Points.pt1.x = point.x; 
			pDoc->m_Workpiece_Points.pt1.y = point.y; 
			pDoc->m_Workpiece_Points_Camera->pt1 = imagepoint.vector;
			break;
	case 6: pDoc->m_Workpiece_Points.pt2.x = point.x; 
			pDoc->m_Workpiece_Points.pt2.y = point.y; 
			pDoc->m_Workpiece_Points_Camera->pt2 = imagepoint.vector;
			pApp->m_IPOP.Calc_PiercingPoints();
			pApp->m_Dlg_Pose->UpdateData(0);
			break;*/
}


void CDisp_Pic_View::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	// TODO: Code für die Behandlungsroutine für Nachrichten hier einfügen und/oder Standard aufrufen
	CIPOPApp* pApp = (CIPOPApp*) AfxGetApp();
	CDisp_Pic_Doc* pDoc = (CDisp_Pic_Doc*)GetDocument(); int a=0;
	if(nChar== unsigned('K'))
		pDoc->m_Mode = 0;
	if(nChar== unsigned('R'))
		pDoc->m_Mode = 1;

	if(!pDoc->m_Mode){
		if(nChar== VK_F1)
			m_ptidx=1; //AfxMessageBox("Geben sie nun den 1. Punkt ein!");break;
		if(nChar== VK_F2)
			m_ptidx=2; //AfxMessageBox("Geben sie nun den 1. Punkt ein!");break;
		if(nChar== VK_F3)
			m_ptidx=3; //AfxMessageBox("Geben sie nun den 3. Punkt ein!");break;
		if(nChar== VK_F4)
			m_ptidx=4; //AfxMessageBox("Geben sie nun den 4. Punkt ein!");break;
		if(nChar== VK_F5){
			pDoc->m_Etalon_Corners.clear(); pDoc->m_Etalon_Points_Image.clear(); 
		}			   //AfxMessageBox("Geben sie nun den 4. Punkt ein!");break;
	}
	else{
		if(nChar== VK_F1)
			m_ptidx=5; //AfxMessageBox("Geben sie nun den 1. Punkt ein!");break;
		if(nChar== VK_F2)
			m_ptidx=6; //AfxMessageBox("Geben sie nun den 1. Punkt ein!");break;
	}
	switch(nChar){
	case VK_LEFT:
		On_ViewBack(); break;
	case VK_RIGHT:
		On_ViewForward(); break;
	case VK_UP:
		pDoc->DeleteCurrentImage(); Invalidate(1); 
		FitWindow(GetDocument()->Image_Width(), GetDocument()->Image_Height()); break;
	case VK_SPACE: 
		pApp->SnapAndReg(); break;
	}

	Invalidate(1);
	CView::OnKeyDown(nChar, nRepCnt, nFlags);
	
}





void CDisp_Pic_View::OnRButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Code für die Behandlungsroutine für Nachrichten hier einfügen und/oder Standard aufrufen
	CDisp_Pic_Doc* pDoc = (CDisp_Pic_Doc*)GetDocument();
	pDoc->m_Etalon_Points_Image.clear();
	Invalidate(1);
	CView::OnRButtonDown(nFlags, point);
}

void CDisp_Pic_View::OnSysKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	// TODO: Code für die Behandlungsroutine für Nachrichten hier einfügen und/oder Standard aufrufen
	
	CView::OnSysKeyDown(nChar, nRepCnt, nFlags);
}

void CDisp_Pic_View::OnRegIpBinarize() 
{
	// TODO: Code für Befehlsbehandlungsroutine hier einfügen
	CDisp_Pic_Doc* pDoc = (CDisp_Pic_Doc*)GetDocument();
	pDoc->Apply_Binarization();
	Invalidate(1);
	
}

void CDisp_Pic_View::OnRegIpHough() 
{
	// TODO: Code für Befehlsbehandlungsroutine hier einfügen
	CDisp_Pic_Doc* pDoc = (CDisp_Pic_Doc*)GetDocument();
	pDoc->Apply_Hough();
	Invalidate(1);
}

void CDisp_Pic_View::OnRegIpEdge() 
{
	// TODO: Code für Befehlsbehandlungsroutine hier einfügen
	CDisp_Pic_Doc* pDoc = (CDisp_Pic_Doc*)GetDocument();
	pDoc->Apply_Edgefilter();
	Invalidate(1);
}

void CDisp_Pic_View::OnRegErosion() 
{
	// TODO: Code für Befehlsbehandlungsroutine hier einfügen
	CDisp_Pic_Doc* pDoc = (CDisp_Pic_Doc*)GetDocument();
	pDoc->Apply_Erosion();
	Invalidate(1);
	
}

void CDisp_Pic_View::OnRegIPPreprocess() 
{
	// TODO: Code für Befehlsbehandlungsroutine hier einfügen
	CDisp_Pic_Doc* pDoc = (CDisp_Pic_Doc*)GetDocument();
	pDoc->Apply_Preprocess();
	FitWindow(GetDocument()->Image_Width(), GetDocument()->Image_Height());
	GetDocument()->SetTitle();
	Invalidate(1);
}

void CDisp_Pic_View::OnViewModek() 
{
	// TODO: Code für Befehlsbehandlungsroutine hier einfügen
	CDisp_Pic_Doc* pDoc = (CDisp_Pic_Doc*)GetDocument();
	pDoc->m_Mode = 0; pDoc->SetTitle(); Invalidate(1);
}

void CDisp_Pic_View::OnViewModer() 
{
	// TODO: Code für Befehlsbehandlungsroutine hier einfügen
	CDisp_Pic_Doc* pDoc = (CDisp_Pic_Doc*)GetDocument();
	pDoc->m_Mode = 1; pDoc->SetTitle(); Invalidate(1);
	
}

void CDisp_Pic_View::OnPicviewSavebmp() 
{
	// TODO: Code für Befehlsbehandlungsroutine hier einfügen
	CDisp_Pic_Doc* pDoc = (CDisp_Pic_Doc*)GetDocument();
	pDoc->CList_SaveCurrentImage();
}



void CDisp_Pic_View::OnRegFloodfill() 
{
	// TODO: Code für Befehlsbehandlungsroutine hier einfügen
	CDisp_Pic_Doc* pDoc = (CDisp_Pic_Doc*)GetDocument();
	pDoc->Apply_FloodFill();
	Invalidate(1);
	
}
