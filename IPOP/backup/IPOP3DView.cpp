// IPOP3DView.cpp: Implementierung der Klasse CIPOP3DView.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "IPOPApp.h"
#include "IPOP3DView.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Konstruktion/Destruktion
//////////////////////////////////////////////////////////////////////

CIPOP3DView::CIPOP3DView()
{

}

CIPOP3DView::~CIPOP3DView()
{
	CIPOPApp* pApp = (CIPOPApp*) AfxGetApp();
	pApp->m_Display_3D_pView = 0;
	C3DView::~C3DView();

}

void CIPOP3DView::OnDestroy()
{
	CIPOPApp* pApp = (CIPOPApp*) AfxGetApp();
	pApp->m_Display_3D_pView = 0;
	C3DView::~C3DView();

}
