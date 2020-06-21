/* ----------------------------------------------------------------------- *
 * G L S a m p l e 4 V i e w . c p p
 *
 * implementation of the C3DView class
 *
 * Copyright 1996 by Interface Technologies, Inc. All Rights Reserved.
 * 3D Authored by N. Alan Oursland
 * ----------------------------------------------------------------------- */

//#include "TOS_IPFileCom_IPApiInterface.h"
#include "stdafx.h"
#include "IPOPApp.h"
#include "3DView.h"



#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// C3DView

IMPLEMENT_DYNCREATE(C3DView, CView)

BEGIN_MESSAGE_MAP(C3DView, CView)
	//{{AFX_MSG_MAP(C3DView)
	ON_WM_CREATE()
	ON_WM_DESTROY()
	ON_WM_SIZE()
	ON_WM_PAINT()
	ON_WM_KEYDOWN()
	ON_WM_TIMER()
	ON_WM_LBUTTONDOWN()
	ON_COMMAND(ID_VIEW_CALIBRATE_ONESTEP, OnCalibrate_Onestep)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// C3DView construction/destruction

C3DView::C3DView(){
	m_hGLContext = NULL; m_GLPixelIndex = 0;	m_timer = 0;
}   


C3DView::~C3DView(){
}


BOOL C3DView::PreCreateWindow(CREATESTRUCT& cs){
	cs.style |= (WS_CLIPCHILDREN | WS_CLIPSIBLINGS);
	return CView::PreCreateWindow(cs);}


/////////////////////////////////////////////////////////////////////////////
// C3DView drawing

void C3DView::OnDraw(CDC* pDC){
//	pDC->TextOut(0,0,"links-unten klicken");
	}

/////////////////////////////////////////////////////////////////////////////
// C3DView diagnostics
#ifdef _DEBUG
//DEL void C3DView::AssertValid() const
//DEL {
//DEL 	CView::AssertValid();
//DEL }

//DEL void C3DView::Dump(CDumpContext& dc) const
//DEL {
//DEL 	CView::Dump(dc);
//DEL }

 C3DDoc* C3DView::GetDocument() // non-debug version is inline
 {
 	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(C3DDoc)));
 	return (C3DDoc*)m_pDocument;
 }
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// C3DView message handlers

BOOL C3DView::SetWindowPixelFormat(HDC hDC)
{

PIXELFORMATDESCRIPTOR pixelDesc;

	pixelDesc.nSize		= sizeof(PIXELFORMATDESCRIPTOR);
	pixelDesc.nVersion	= 1;
	pixelDesc.dwFlags	=	PFD_DRAW_TO_WINDOW | 
							PFD_SUPPORT_OPENGL | 
							PFD_DOUBLEBUFFER | 
							PFD_STEREO_DONTCARE|
							PFD_TYPE_RGBA;  
	pixelDesc.iPixelType		= PFD_TYPE_RGBA;
	pixelDesc.cColorBits		= 32;	pixelDesc.cRedBits		= 8;
	pixelDesc.cRedShift		= 16;	pixelDesc.cGreenBits		= 8;
	pixelDesc.cGreenShift		= 8;	pixelDesc.cBlueBits		= 8;
	pixelDesc.cBlueShift		= 0;	pixelDesc.cAlphaBits		= 0;
	pixelDesc.cAlphaShift		= 0;	pixelDesc.cAccumBits		= 64;	
	pixelDesc.cAccumRedBits		= 16;	pixelDesc.cAccumGreenBits	= 16;
	pixelDesc.cAccumBlueBits	= 16;	pixelDesc.cAccumAlphaBits	= 0;
	pixelDesc.cDepthBits		= 32;	pixelDesc.cStencilBits		= 8;
	pixelDesc.cAuxBuffers		= 0;	pixelDesc.iLayerType		= PFD_MAIN_PLANE;
	pixelDesc.bReserved		= 0;	pixelDesc.dwLayerMask		= 0;
	pixelDesc.dwVisibleMask		= 0;	pixelDesc.dwDamageMask		= 0;
	m_GLPixelIndex = ChoosePixelFormat( hDC, &pixelDesc);
	if (m_GLPixelIndex==0) // Let's choose a default index.
	{	m_GLPixelIndex = 1;	
		if(DescribePixelFormat(hDC,m_GLPixelIndex,sizeof(PIXELFORMATDESCRIPTOR), 
						&pixelDesc)==0)
		{return FALSE;		}	}
	if (SetPixelFormat( hDC, m_GLPixelIndex, &pixelDesc)==FALSE)
	{return FALSE;}	return TRUE;}




int C3DView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;
	HWND hWnd = GetSafeHwnd();
	HDC hDC = ::GetDC(hWnd);
	if (SetWindowPixelFormat(hDC)==FALSE)
		return 0;
	if (CreateViewGLContext(hDC)==FALSE)
		return 0;
	GLfloat LightAmbient[] =  { 1.0f, 1.0f, 1.0f, 0.0f};
	GLfloat LightDiffuse[] =  { 10.0f, 10.0f, 10.0f, 0.0f};
	GLfloat LightSpecular[] = { 0.0f, 0.0f, 0.0f, 0.1f};
	GLfloat LightPosition0[] = { 5.0f, 5.0f, 5.0f, 0.0f}; 
	GLfloat LightPosition1[] = { 5.0f, 5.0f, -5.0f, 0.0f}; 
	GLfloat LightPosition2[] = { -5.0f, 5.0f, -5.0f, 0.0f}; 
	GLfloat LightPosition3[] = { -5.0f, 5.0f, 5.0f, 0.0f}; 

	GLfloat RedSurface[]   = { 10.0f, 0.0f, 0.0f, 1.0f};
	GLfloat GreenSurface[] = { 0.0f, 10.0f, 0.0f, 1.0f};
	GLfloat BlueSurface[]  = { 0.0f, 0.0f, 9.0f, 1.0f};
	GLfloat WhiteSurface[]  = { 10.0f, 10.0f, 10.0f, 1.0f};
	GLfloat DarkGreenSurface[]  = { 0.0f, 0.2f, 0.0f, 1.0f};
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLightfv(GL_LIGHT0, GL_AMBIENT, LightAmbient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, LightDiffuse);
	glLightfv(GL_LIGHT0, GL_POSITION, LightPosition0);
	glEnable(GL_LIGHT0);
	glLightfv(GL_LIGHT2, GL_DIFFUSE, LightDiffuse);
	glLightfv(GL_LIGHT2, GL_POSITION, LightPosition2);
	glEnable(GL_LIGHT2);
	glLightfv(GL_LIGHT3, GL_DIFFUSE, LightDiffuse);
	glLightfv(GL_LIGHT3, GL_POSITION, LightPosition3);
	glEnable(GL_LIGHT3);
	//glLightfv(GL_LIGHT1, GL_AMBIENT, LightAmbient);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, LightDiffuse);
	//glLightfv(GL_LIGHT1, GL_SPECULAR, LightSpecular);
	glLightfv(GL_LIGHT1, GL_POSITION, LightPosition1);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT1);
	//glShadeModel(GL_SMOOTH);
	m_timer = SetTimer(1,1000,0);return 0;}




BOOL C3DView::CreateViewGLContext(HDC hDC){
	m_hGLContext = wglCreateContext(hDC);
	if (m_hGLContext == NULL){return FALSE;}
	if (wglMakeCurrent(hDC, m_hGLContext)==FALSE){return FALSE;}
	return TRUE;}



void C3DView::OnDestroy(){
	if(wglGetCurrentContext()!=NULL){wglMakeCurrent(NULL, NULL);}
	if (m_hGLContext!=NULL){
		wglDeleteContext(m_hGLContext);m_hGLContext = NULL;}
	CView::OnDestroy();}



void C3DView::OnSize(UINT nType, int cx, int cy){
	CView::OnSize(nType, cx, cy);
	GLsizei width, height;GLdouble aspect;
	width = cx;	height = cy;
	if (cy==0)	aspect = (GLdouble)width;
	else aspect = (GLdouble)width/(GLdouble)height;
	glViewport(0, 0, width, height);	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();	
	//; ***********************************
	gluPerspective(45, aspect, 1.0, 2000.0);
	//; ***********************************
	glMatrixMode(GL_MODELVIEW);	glLoadIdentity();
	glDrawBuffer(GL_BACK);	glEnable(GL_LIGHTING);	glEnable(GL_DEPTH_TEST);
	GLfloat lma[] = {0,0,0,1};}



void C3DView::OnPaint(){
	CPaintDC dc(this); // device context for painting
	C3DDoc* pDoc = (C3DDoc*) GetDocument();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	pDoc->RenderScene();SwapBuffers(dc.m_ps.hdc);
	dc.TextOut(0,0,"Perspektive:");
	dc.TextOut(0,15,"Vorne    ");
	dc.TextOut(0,30,"Hinten ");
	dc.TextOut(0,45,"Links   ");
	dc.TextOut(0,60,"Rechts");
}



void C3DView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	// TODO: Code für die Behandlungsroutine für Nachrichten hier einfügen und/oder Standard aufrufen
	//if (nChar==unsigned(VK_UP))MessageBox("Bestätigung","OK",MB_OK|MB_ICONEXCLAMATION);
	C3DDoc* pDoc = (C3DDoc*) GetDocument();
	if (nChar==unsigned(VK_UP)){
		pDoc->m_ViewDirection.eye(0) += 15 * sin( pDoc->m_angle * pi/180);
		pDoc->m_ViewDirection.eye(2) += 15 * cos( pDoc->m_angle * pi/180);
		Invalidate(0);}
	if (nChar==unsigned(VK_DOWN)){
		pDoc->m_ViewDirection.eye(0) -= 15 * sin( pDoc->m_angle * pi/180);
		pDoc->m_ViewDirection.eye(2) -= 15 * cos( pDoc->m_angle * pi/180);
		Invalidate(0);}
	if ( nChar==unsigned(VK_F1) ){pDoc->SetFrontView();}
	if ( nChar==unsigned(VK_F2) ){pDoc->SetBackView();}
	if ( nChar==unsigned(VK_F3) ){pDoc->SetLeftView();}
	if ( nChar==unsigned(VK_F4) ){pDoc->SetRightView();} 
	if ( nChar==(unsigned(VK_LEFT)) ){ 
		pDoc->m_angle -= 2; Invalidate(0);}
	if ( nChar==(unsigned(VK_RIGHT)) ){
		pDoc->m_angle += 2; Invalidate(0);}
	if (nChar==unsigned('A')){
		pDoc->m_ViewDirection.eye(1) += 2;Invalidate(0);}
	if (nChar==unsigned('S')){
		pDoc->m_ViewDirection.eye(1) -= 2;Invalidate(0);}
	if (nChar==unsigned(VK_SPACE)){OnCalibrate_Onestep();}
	InvalidateRect(NULL, FALSE);CView::OnKeyDown(nChar, nRepCnt, nFlags);}



void C3DView::On3DDialog(){
	// TODO: Code für Befehlsbehandlungsroutine hier einfügen
/*	if(m_pDialog->m_hWnd) 
	//; if the Dialog is already created.
		m_pDialog->SetFocus();
	else m_pDialog->Create(this);
	m_pDialog-> ShowWindow(SW_SHOW);*/}



void C3DView::OnTimer(UINT nIDEvent){
	// TODO: Code für die Behandlungsroutine für Nachrichten hier einfügen und/oder Standard aufrufen
	Invalidate(0);CView::OnTimer(nIDEvent);}

void C3DView::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Code für die Behandlungsroutine für Nachrichten hier einfügen und/oder Standard aufrufen
	C3DDoc* pDoc = (C3DDoc*) GetDocument();
	if(point.x<70){
		if(point.y>75){;}
		else if(point.y>60){pDoc->SetRightView();}
		else if(point.y>45){pDoc->SetLeftView();}
		else if(point.y>30){pDoc->SetBackView();}
		else if(point.y>15){pDoc->SetFrontView();}
	}
	CView::OnLButtonDown(nFlags, point);
}

void C3DView::OnCalibrate_Onestep() 
{
	// TODO: Code für Befehlsbehandlungsroutine hier einfügen
	CIPOPApp* pApp = (CIPOPApp*) AfxGetApp();
	pApp->Calc_Calibrate_OneStep();

}
