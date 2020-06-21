// ChildFrm.cpp : Implementierung der Klasse CChildFrame
//

#include "stdafx.h"
#include "IPOPApp.h"

#include "ChildFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
  
/////////////////////////////////////////////////////////////////////////////
// CChildFrame

IMPLEMENT_DYNCREATE(CChildFrame, CMDIChildWnd)

BEGIN_MESSAGE_MAP(CChildFrame, CMDIChildWnd)
	//{{AFX_MSG_MAP(CChildFrame)
	ON_WM_KEYDOWN()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CChildFrame Konstruktion/Destruktion

CChildFrame::CChildFrame()
{
	// ZU ERLEDIGEN: Hier Code zur Member-Initialisierung einf�gen
	
}

CChildFrame::~CChildFrame()
{
}

BOOL CChildFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	// ZU ERLEDIGEN: �ndern Sie hier die Fensterklasse oder das Erscheinungsbild, indem Sie
	//  CREATESTRUCT cs modifizieren.

	if( !CMDIChildWnd::PreCreateWindow(cs) )
		return FALSE;

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CChildFrame Diagnose

#ifdef _DEBUG
void CChildFrame::AssertValid() const
{
	CMDIChildWnd::AssertValid();
}

void CChildFrame::Dump(CDumpContext& dc) const
{
	CMDIChildWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CChildFrame Nachrichten-Handler

void CChildFrame::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	// TODO: Code f�r die Behandlungsroutine f�r Nachrichten hier einf�gen und/oder Standard aufrufen
	CIPOPApp* pApp = (CIPOPApp*) AfxGetApp();
	if (nChar==unsigned(VK_SPACE))	pApp->SnapAndReg();	
	CMDIChildWnd::OnKeyDown(nChar, nRepCnt, nFlags);
}
