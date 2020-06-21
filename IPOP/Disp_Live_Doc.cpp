// Disp_Live_Doc.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "ipop.h"
#include "Disp_Live_Doc.h"
#include "IPOPApp.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDisp_Live_Doc

IMPLEMENT_DYNCREATE(CDisp_Live_Doc, CDocument)

CDisp_Live_Doc::CDisp_Live_Doc()
{
	m_Grabber_PXC = 0;
}

BOOL CDisp_Live_Doc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;
	return TRUE;
}

CDisp_Live_Doc::~CDisp_Live_Doc()
{
	((CIPOPApp*) AfxGetApp())->m_Disp_pLiveDoc = 0;
}


BEGIN_MESSAGE_MAP(CDisp_Live_Doc, CDocument)
	//{{AFX_MSG_MAP(CDisp_Live_Doc)
		// HINWEIS - Der Klassen-Assistent fügt hier Zuordnungsmakros ein und entfernt diese.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Diagnose CDisp_Live_Doc

#ifdef _DEBUG
void CDisp_Live_Doc::AssertValid() const
{
	CDocument::AssertValid();
}

void CDisp_Live_Doc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// Serialisierung CDisp_Live_Doc 

void CDisp_Live_Doc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// ZU ERLEDIGEN: Code zum Speichern hier einfügen
	}
	else
	{
		// ZU ERLEDIGEN: Code zum Laden hier einfügen
	}
}



void CDisp_Live_Doc::OnCloseDocument() 
{
	// TODO: Speziellen Code hier einfügen und/oder Basisklasse aufrufen
	CIPOPApp* pApp = (CIPOPApp*) AfxGetApp();
	m_Grabber_PXC->StopLiveVideo(pApp->m_Disp_pLiveView->m_hWnd);
	if(m_Grabber_PXC) delete m_Grabber_PXC;
	CDocument::OnCloseDocument();
}
