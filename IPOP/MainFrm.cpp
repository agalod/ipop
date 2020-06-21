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
	ON_COMMAND(ID_MFM_CAMPARAMS, OnCamParams)
	ON_COMMAND(ID_MFM_LASTPIC, OnLastPic)
	ON_COMMAND(ID_MFM_CHESSBPARAMS, OnChessbParams)
	ON_COMMAND(ID_MFM_POSEDLG, OnPoseDlg)
	ON_COMMAND(ID_MFRM_OPEN_CALIMAGE, OnMfrmOpenCalimage)
	ON_COMMAND(ID_MFRM_OPEN_REGIMAGE, OnMfrmOpenRegimage)
	ON_COMMAND(ID_IPPARAMS, OnIpparams)
	ON_COMMAND(ID_VIDEO_START, OnVideoStart)
	ON_COMMAND(ID_VIDEO_GRABFRAME, OnVideoGrabframe)
	ON_COMMAND(ID_VIDEO_SNAPANDREG, OnVideoSnapandreg)
	ON_WM_KEYDOWN()
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


void CMainFrame::OnFileOpen() {
	// TODO: Code für Befehlsbehandlungsroutine hier einfügen
	OnMfrmOpenRegimage(); }


void CMainFrame::OnCamParams() {
	// TODO: Code für Befehlsbehandlungsroutine hier einfügen
	CIPOPApp* pApp = (CIPOPApp*) AfxGetApp();
	pApp->m_Dlg_CamParams->ShowWindow(SW_RESTORE); }


void CMainFrame::OnChessbParams() {
	// TODO: Code für Befehlsbehandlungsroutine hier einfügen
	CIPOPApp* pApp = (CIPOPApp*) AfxGetApp();
	pApp->m_Dlg_Etalon->ShowWindow(SW_RESTORE); }


void CMainFrame::OnPoseDlg() {
	// TODO: Code für Befehlsbehandlungsroutine hier einfügen
	CIPOPApp* pApp = (CIPOPApp*) AfxGetApp();
	pApp->m_Dlg_Pose->ShowWindow(SW_RESTORE);
	pApp->m_Dlg_Pose->UpdateData(0); }


void CMainFrame::OnLastPic() {
	// TODO: Code für Befehlsbehandlungsroutine hier einfügen
	CIPOPApp* pApp = (CIPOPApp*) AfxGetApp();
	CRecentFileList* list = pApp->GetRecentFileList();
	list->ReadList();
	CString str = (*list)[0];
	if(str.GetLength()) pApp->LoadBmp(str); }


void CMainFrame::OnMfrmOpenCalimage() {
	// TODO: Code für Befehlsbehandlungsroutine hier einfügen
	CIPOPApp* pApp = (CIPOPApp*) AfxGetApp();
	pApp->LoadBmps();
	pApp->m_Disp_pPicDoc->m_Mode = 0;
	pApp->m_Disp_pPicDoc->SetTitle(); }


void CMainFrame::OnMfrmOpenRegimage() {
	// TODO: Code für Befehlsbehandlungsroutine hier einfügen
	CIPOPApp* pApp = (CIPOPApp*) AfxGetApp();
	pApp->LoadBmps();
	pApp->m_Disp_pPicDoc->m_Mode = 1;
	pApp->m_Disp_pPicDoc->SetTitle();}


void CMainFrame::OnIpparams() {
	// TODO: Code für Befehlsbehandlungsroutine hier einfügen
	CIPOPApp* pApp = (CIPOPApp*) AfxGetApp();
	pApp->m_Dlg_IPParams->ShowWindow(SW_RESTORE);}


void CMainFrame::OnVideoStart() {
	// TODO: Code für Befehlsbehandlungsroutine hier einfügen
	CIPOPApp* pApp = (CIPOPApp*) AfxGetApp();
	pApp->VideoInit(); }


void CMainFrame::OnVideoGrabframe() {
	// TODO: Code für Befehlsbehandlungsroutine hier einfügen
	CIPOPApp* pApp = (CIPOPApp*) AfxGetApp();
	pApp->VideoGrabFrame(); }


void CMainFrame::OnVideoSnapandreg() {
	// TODO: Code für Befehlsbehandlungsroutine hier einfügen
	CIPOPApp* pApp = (CIPOPApp*) AfxGetApp();
	pApp->SnapAndReg(); }


void CMainFrame::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) {
	// TODO: Code für die Behandlungsroutine für Nachrichten hier einfügen und/oder Standard aufrufen
	CIPOPApp* pApp = (CIPOPApp*) AfxGetApp();
	if (nChar==unsigned(VK_SPACE)){ pApp->SnapAndReg(); }
	CMDIFrameWnd::OnKeyDown(nChar, nRepCnt, nFlags); }
