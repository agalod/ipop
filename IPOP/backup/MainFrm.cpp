// MainFrm.cpp : Implementierung der Klasse CMainFrame
//

#include "stdafx.h"
#include "IPOPApp.h"

#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNAMIC(CMainFrame, CMDIFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CMDIFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_WM_CREATE()
	ON_COMMAND(ID_FILE_OPEN, OnFileOpen)
	ON_COMMAND(ID_MFRM_OPENIMAGE, OnBmpsLoad)
	ON_COMMAND(ID_MFM_CAMPARAMS, OnCamParams)
	ON_COMMAND(ID_FILE_MRU_FILE1, OnFileMruFile1)
	ON_COMMAND(ID_FILE_MRU_FILE2, OnFileMruFile2)
	ON_COMMAND(ID_MFM_LASTPIC, OnLastPic)
	ON_COMMAND(ID_MFM_CHESSBPARAMS, OnChessbParams)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // Statusleistenanzeige
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

/////////////////////////////////////////////////////////////////////////////
// CMainFrame Konstruktion/Zerstörung

CMainFrame::CMainFrame()
{
	// ZU ERLEDIGEN: Hier Code zur Member-Initialisierung einfügen
	
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CMDIFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP
		| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("Symbolleiste konnte nicht erstellt werden\n");
		return -1;      // Fehler bei Erstellung
	}

	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators,
		  sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("Statusleiste konnte nicht erstellt werden\n");
		return -1;      // Fehler bei Erstellung
	}

	// ZU ERLEDIGEN: Löschen Sie diese drei Zeilen, wenn Sie nicht wollen, dass die Symbolleiste
	//  andockbar ist.
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndToolBar);

	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CMDIFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// ZU ERLEDIGEN: Ändern Sie hier die Fensterklasse oder das Erscheinungsbild, indem Sie
	//  CREATESTRUCT cs modifizieren.

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CMainFrame Diagnose

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CMDIFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CMDIFrameWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMainFrame Nachrichten-Handler


void CMainFrame::OnFileOpen() 
{
	// TODO: Code für Befehlsbehandlungsroutine hier einfügen
	OnBmpsLoad();
}

void CMainFrame::OnBmpsLoad() 
{
	// TODO: Code für Befehlsbehandlungsroutine hier einfügen
	CIPOPApp* pApp = (CIPOPApp*) AfxGetApp();
	pApp->LoadBmps();
	
}

void CMainFrame::OnCamParams() 
{
	// TODO: Code für Befehlsbehandlungsroutine hier einfügen
	CIPOPApp* pApp = (CIPOPApp*) AfxGetApp();
//	if(! pApp->m_Dlg_CamParams.m_hWnd) 
//		pApp->m_Dlg_CamParams.Create(IDD_BV_CAMERA_PARAM, this);
	pApp->m_Dlg_CamParams.ShowWindow(SW_RESTORE);
}


void CMainFrame::OnChessbParams() 
{
	// TODO: Code für Befehlsbehandlungsroutine hier einfügen
	CIPOPApp* pApp = (CIPOPApp*) AfxGetApp();
//	if(! pApp->m_Dlg_Calibration->m_hWnd) 
//		pApp->m_Dlg_Calibration->Create(IDD_DLG_CHECKBOARD, this);
	pApp->m_Dlg_Calibration->ShowWindow(SW_RESTORE);
	
}


void CMainFrame::OnFileMruFile1() 
{
	// TODO: Code für Befehlsbehandlungsroutine hier einfügen
	CIPOPApp* pApp = (CIPOPApp*) AfxGetApp();
	CRecentFileList* list = pApp->GetRecentFileList();
	list->ReadList();
	CString str = (*list)[0];
	if(str.GetLength()) pApp->LoadBmp(str);
}

void CMainFrame::OnFileMruFile2() 
{
	// TODO: Code für Befehlsbehandlungsroutine hier einfügen
	CIPOPApp* pApp = (CIPOPApp*) AfxGetApp();
	CRecentFileList* list = pApp->GetRecentFileList();
	list->ReadList();
	CString str = (*list)[0];
	if(str.GetLength()) pApp->LoadBmp(str);
}

void CMainFrame::OnLastPic() 
{
	// TODO: Code für Befehlsbehandlungsroutine hier einfügen
	CIPOPApp* pApp = (CIPOPApp*) AfxGetApp();
	CRecentFileList* list = pApp->GetRecentFileList();
	list->ReadList();
	CString str = (*list)[0];
	if(str.GetLength()) pApp->LoadBmp(str);
	
}

