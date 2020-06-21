// IPOP.cpp : Legt das Klassenverhalten für die Anwendung fest.
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "IPOPApp.h"
#include "MainFrm.h"
#include "ChildFrm.h"
/////////////////////////////////////////////////////////////////////////////
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
/////////////////////////////////////////////////////////////////////////////
// CIPOPApp
BEGIN_MESSAGE_MAP(CIPOPApp, CWinApp)
	//{{AFX_MSG_MAP(CIPOPApp)
	ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
	//}}AFX_MSG_MAP
	// Dateibasierte Standard-Dokumentbefehle
	ON_COMMAND(ID_FILE_NEW, CWinApp::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, CWinApp::OnFileOpen)
	// Standard-Druckbefehl "Seite einrichten"
	ON_COMMAND(ID_FILE_PRINT_SETUP, CWinApp::OnFilePrintSetup)
END_MESSAGE_MAP()
/////////////////////////////////////////////////////////////////////////////
// CIPOPApp Konstruktion
CIPOPApp::CIPOPApp() {
	// ZU ERLEDIGEN: Hier Code zur Konstruktion einfügen
	// Alle wichtigen Initialisierungen in InitInstance platzieren
	m_Disp_pPicDoc = 0; m_Disp_pPicView = 0; }
/////////////////////////////////////////////////////////////////////////////
// Das einzige CIPOPApp-Objekt
CIPOPApp theApp;
/////////////////////////////////////////////////////////////////////////////
// CIPOPApp Initialisierung

BOOL CIPOPApp::InitInstance() {
	AfxEnableControlContainer();
	// Standardinitialisierung
	// Wenn Sie diese Funktionen nicht nutzen und die Größe Ihrer fertigen 
	//  ausführbaren Datei reduzieren wollen, sollten Sie die nachfolgenden
	//  spezifischen Initialisierungsroutinen, die Sie nicht benötigen, entfernen.
#ifdef _AFXDLL
	Enable3dControls();			// Diese Funktion bei Verwendung von MFC in gemeinsam genutzten DLLs aufrufen
#else
	Enable3dControlsStatic();	// Diese Funktion bei statischen MFC-Anbindungen aufrufen
#endif
	// Ändern des Registrierungsschlüssels, unter dem unsere Einstellungen gespeichert sind.
	// ZU ERLEDIGEN: Sie sollten dieser Zeichenfolge einen geeigneten Inhalt geben
	// wie z.B. den Namen Ihrer Firma oder Organisation.
	SetRegistryKey(_T("Local AppWizard-Generated Applications"));
	LoadStdProfileSettings();  // Standard INI-Dateioptionen laden (einschließlich MRU)
	// Dokumentvorlagen der Anwendung registrieren. Dokumentvorlagen
	//  dienen als Verbindung zwischen Dokumenten, Rahmenfenstern und Ansichten.
	m_Template_pPic = new CMultiDocTemplate(
		IDR_IPOPTYPE,
		RUNTIME_CLASS(CDisp_Pic_Doc),
		RUNTIME_CLASS(CChildFrame), // Benutzerspezifischer MDI-Child-Rahmen
		RUNTIME_CLASS(CDisp_Pic_View));
	AddDocTemplate(m_Template_pPic);
	m_Template_pLive = new CMultiDocTemplate(
		IDR_IPOPTYPE,
		RUNTIME_CLASS(CDisp_Live_Doc),
		RUNTIME_CLASS(CChildFrame), // Benutzerspezifischer MDI-Child-Rahmen
		RUNTIME_CLASS(CDisp_Live_View));
	AddDocTemplate(m_Template_pLive);
	m_Template_p3D = new CMultiDocTemplate(
		IDR_IPOPTYPE,
		RUNTIME_CLASS(CDisp_3D_Doc),
		RUNTIME_CLASS(CChildFrame), // custom MDI child frame
		RUNTIME_CLASS(CDisp_3D_View));
	AddDocTemplate(m_Template_p3D);
	// Haupt-MDI-Rahmenfenster erzeugen
	CMainFrame* pMainFrame = new CMainFrame;
	if (!pMainFrame->LoadFrame(IDR_MAINFRAME)) return FALSE; m_pMainWnd = pMainFrame;
	// Befehlszeile parsen, um zu prüfen auf Standard-Umgebungsbefehle DDE, Datei offen
	CCommandLineInfo cmdInfo; ParseCommandLine(cmdInfo);
	// Das Hauptfenster ist initialisiert und kann jetzt angezeigt und aktualisiert werden.
	pMainFrame->ShowWindow(SW_SHOWMAXIMIZED); pMainFrame->UpdateWindow();
	char verz[300];	GetCurrentDirectory(300, verz);
	CString Ini_Verzeichnis(verz); Ini_Verzeichnis  += "\\Ini\\";
	m_Dlg_Etalon = new CDlg_Etalon;
	m_Dlg_Etalon->Create(IDD_DLG_CHECKBOARD, 0);
	m_Dlg_Etalon->UpdatePoints();
	m_Dlg_IPParams = new CDlg_IPParams;
	m_Dlg_IPParams->Create(IDD_DLG_IP_PARAMS, 0);
	m_Dlg_IPParams->m_Ini_Verzeichnis = Ini_Verzeichnis;
	m_Dlg_IPParams->File_Load();
	m_Dlg_CamParams = new CDlg_Camera;
	m_Dlg_CamParams->m_Ini_Verzeichnis = Ini_Verzeichnis;
	m_Dlg_CamParams->m_Camera = &(m_IPOP.fCamera);
	m_Dlg_CamParams->Create(IDD_DLG_CAMPARAMS, AfxGetMainWnd());
	m_Dlg_CamParams->File_Load();
	m_Dlg_Pose = new CDlg_Pose;
	m_Dlg_Pose->m_Ini_Verzeichnis = Ini_Verzeichnis;
	m_Dlg_Pose->m_pCamPos = &(m_IPOP.fEuler_Etalon);
	m_Dlg_Pose->m_pMachineRef = &(m_IPOP.fEuler_Machine_Rel);
	m_Dlg_Pose->m_pWorkpiece = &(m_IPOP.fEuler_Workpiece_Rel);
	m_Dlg_Pose->m_pNumIterations = &(m_IPOP.fNumIterations);
	m_Dlg_Pose->m_pDistances_Sum = &(m_IPOP.fDistances_Sum);
	m_Dlg_Pose->Create(IDD_DLG_POSE, 0);
	m_Dlg_Pose->File_Load();
	return TRUE; }

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg-Dialog für Info über Anwendung

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();
// Dialogdaten
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA
	// Überladungen für virtuelle Funktionen, die vom Anwendungs-Assistenten erzeugt wurden
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
	//}}AFX_VIRTUAL
// Implementierung
protected:
	//{{AFX_MSG(CAboutDlg)
		// Keine Nachrichten-Handler
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP() 
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD){
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT 
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX){
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// Keine Nachrichten-Handler
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

// Anwendungsbefehl zum Ausführen des Dialogfelds
void CIPOPApp::OnAppAbout() {
	CAboutDlg aboutDlg; aboutDlg.DoModal(); }

/////////////////////////////////////////////////////////////////////////////
// CIPOPApp-Nachrichtenbehandlungsroutinen
void CIPOPApp::LoadBmp(CString str) {
	CImage* ImgTmp = new CImage();
	if(!m_Disp_pPicDoc) CreatePicView();
	//if(!(ImgTmp->Load(str,0)) ){ 
	if(!(ImgTmp->LoadRect(str,0,cvRect(4,4,760,568))) ){ 
		AfxMessageBox("Das angegebene Bild wurde nicht gefunden!"); return;}
	m_Disp_pPicDoc->CList_AppendImage(ImgTmp, str);
	m_Disp_pPicDoc->SetTitle();
	m_Disp_pPicView->FitWindow(ImgTmp->Width(),ImgTmp->Height());
	AddToRecentFileList(str); }


void CIPOPApp::LoadBmps() {
	// TODO: Code für Befehlsbehandlungsroutine hier einfügen
	CString Fullpath; 
	CImage* ImgTmp[30];	int i=0;
	for(i=0;i<30;i++)
		ImgTmp[i]=0;
	static char BASED_CODE szFilter[] = 
		"All Files (*.*)|*.*|Image Files (*.jpg)|*.jpg|Image Files (*.bmp)|*.bmp|Image Files (*.gif)|*.gif|Image Files (*.tif)|*.tif|Image Files (*.png)|*.png||";
	CFileDialog Dlg( 1, (LPCTSTR) &"*", NULL, OFN_ALLOWMULTISELECT | OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, szFilter );
	//Dlg.m_ofn.lpstrInitialDir = "e:\\daten\\eigene bilder";
	if(Dlg.DoModal()==IDOK)
	{
		if(!m_Disp_pPicDoc) CreatePicView();
		POSITION pos = Dlg.GetStartPosition(); i=0;
		while(pos){
			if(i>29) {AfxMessageBox("Too many Pictures selected!");break;}
			Fullpath = Dlg.GetNextPathName(pos);
			//if(!(cimg.Load(Fullpath,1))){ // LOAD NEXT IMAGE
			//	AfxMessageBox("Das angegebene Bild wurde nicht gefunden!"); return;}
			ImgTmp[i] = new CImage();
			if(!(ImgTmp[i]->Load(Fullpath,0)) ){ // LOAD NEXT IMAGE
				AfxMessageBox("Das angegebene Bild wurde nicht gefunden!"); return;}
			else {
				//ImgTmp = cvCloneImage((cimg.GetImage()));
				//m_pImageVec->push_back(ImgTmp);
				//ImgTmp->CopyOf(m_CImg);
				m_Disp_pPicDoc->CList_AppendImage(ImgTmp[i], Fullpath);
				m_Disp_pPicDoc->SetTitle();
				m_Disp_pPicView->FitWindow(ImgTmp[i]->Width(),ImgTmp[i]->Height());
				m_Disp_pPicView->Invalidate(1);
				AddToRecentFileList(Fullpath); } i++; }} }


void CIPOPApp::CreatePicView() {
	if(m_Disp_pPicDoc||m_Disp_pPicView) return; CDocument* pDoc;
	pDoc = m_Template_pPic->OpenDocumentFile(NULL);
	POSITION pos  = pDoc->GetFirstViewPosition();
	m_Disp_pPicView  = (CDisp_Pic_View*) pDoc->GetNextView( pos );
	m_Disp_pPicDoc   = (CDisp_Pic_Doc*) pDoc;
	m_Disp_pPicDoc->m_Etalon_Cols = &(m_Dlg_Etalon->m_iEtalonX);
	m_Disp_pPicDoc->m_Etalon_Rows = &(m_Dlg_Etalon->m_iEtalonY); }


void CIPOPApp::CreateDisp_Live_View() {
	if(m_Disp_pLiveDoc||m_Disp_pLiveView) return;
	CDocument* pDoc;
	pDoc = m_Template_pLive->OpenDocumentFile(NULL);
	POSITION pos  = pDoc->GetFirstViewPosition();
	m_Disp_pLiveView  = (CDisp_Live_View*) pDoc->GetNextView( pos );
	m_Disp_pLiveDoc   = (CDisp_Live_Doc*) pDoc;
	m_Disp_pLiveDoc->SetTitle("Live-Ansicht");
	m_Disp_pLiveView->Init_PXC(); }


void CIPOPApp::CreateDisp_3D_View() {  
	if(m_Disp_3D_pView) return;
	m_Disp_3D_pView = 0; m_Disp_3D_pDoc = 0; CDocument* pDoc;
	pDoc = m_Template_p3D->OpenDocumentFile(NULL);
	POSITION pos  = pDoc->GetFirstViewPosition();
	m_Disp_3D_pView  = (CDisp_3D_View*) pDoc->GetNextView( pos );
	m_Disp_3D_pDoc   = (CDisp_3D_Doc*) pDoc;
	m_Disp_3D_pView->FitWindow(350,350);
	m_Dlg_3D = new CDlg_3D(); m_Dlg_3D->m_Disp_3D_pDoc = m_Disp_3D_pDoc;
	m_Dlg_3D->Create(IDD_DLG_3D, 0); m_Dlg_3D->ShowWindow(SW_SHOW); }


int CIPOPApp::ExitInstance() {
	// TODO: Speziellen Code hier einfügen und/oder Basisklasse aufrufen
	if(m_Dlg_CamParams) delete m_Dlg_CamParams;	if(m_Dlg_Etalon) delete m_Dlg_Etalon; 
	if(m_Dlg_Pose) delete m_Dlg_Pose; if(m_Dlg_3D) delete m_Dlg_3D;
	if(m_Dlg_IPParams) delete m_Dlg_IPParams; 
	return CWinApp::ExitInstance();
}


CRecentFileList* CIPOPApp::GetRecentFileList() {
	return m_pRecentFileList; }


void CIPOPApp::Calc_Calibrate_Init() {
	//; SETUP IPOP CALCULATION CLASS
	m_IPOP.Reset();
	m_Disp_pPicDoc->Image_DefineGrid();
	m_IPOP.fPts_Obj_Init = m_Dlg_Etalon->m_Points;
	m_IPOP.fPts_Img = m_Disp_pPicDoc->m_Etalon_Points_Camera; 
	//; SETUP 3D VIEW
	CreateDisp_3D_View();
	//; OBJEKTPUNKTE	
	m_Disp_3D_pDoc->m_Vec_p_Points.push_back(&(m_IPOP.fPts_Obj_Current)); 
	//; KORRESPONDIERENDE PUNKTE
	m_Disp_3D_pDoc->m_Vec_p_Lines.push_back(&(m_IPOP.fPts_Corresponding)); 
	//; DURCHSTOßPUNKTE
	//m_Disp_3D_pDoc->m_p_Lines.push_back(&(m_IPOP.m_WorkpieceObjectPoints)); 
	//m_Disp_3D_pDoc->m_Lines_p_b[0]=2;
	//; BILDPUNKTE BZW. PROJEKTIONSSTRAHLEN
	m_Disp_3D_pDoc->m_Vec_p_Vectors.push_back(&(m_IPOP.fPts_Img)); 
	//; GEWICHTETE SCHWERPUNKTE
	m_Disp_3D_pDoc->m_Vec_p_Point.push_back( &(m_IPOP.fMeanXPoints) );
	//; KOORDINATENSYSTEME
	m_Disp_3D_pDoc->m_Vec_p_Frames.push_back( &(m_IPOP.fTrans_Overall) );
	m_Disp_3D_pDoc->m_Frames_p_b[0]=2;
	m_Disp_3D_pDoc->m_Vec_p_Frames.push_back( &(m_IPOP.fTrans_Machine) );
	m_Disp_3D_pDoc->m_Frames_p_b[1]=1;
	m_Disp_3D_pDoc->m_Vec_p_Frames.push_back( &(m_IPOP.fTrans_Workpiece) );
	m_Disp_3D_pDoc->m_Frames_p_b[2]=3;
	m_IPOP.Calc_RegIIPM_Init(); m_IPOP.Update_Plane(); 

	GCV_POINT2D zeropt;
	if( !( m_Disp_pPicDoc->m_Workpiece_Points.pt1 == zeropt || 
		m_Disp_pPicDoc->m_Workpiece_Points.pt2 == zeropt ) ){
		m_IPOP.Calc_PiercingPoints(m_Disp_pPicDoc->m_Workpiece_Points);
		m_Dlg_Pose->UpdateData(0); } }


void CIPOPApp::Calc_Calibrate_OneStep() {
	m_IPOP.Calc_RegIIPM_OneStep(); m_Dlg_Pose->UpdateData(0);
	m_IPOP.Update_Plane(); }


void CIPOPApp::VideoGrabFrame(){
	CreateDisp_Live_View();	CreatePicView();
	m_Disp_pLiveView->OnPxcGrabFrame(); }

void CIPOPApp::VideoInit() {
	CreateDisp_Live_View();
	m_Disp_pLiveView->Init_PXC(); }

void CIPOPApp::SnapAndReg() {
	CreateDisp_Live_View();	
	CreatePicView();
	m_Disp_pLiveView->OnPxcGrabFrame();
	int count = m_Disp_pPicDoc->CList_GetCount();
	if(!(m_Disp_pPicDoc->CList_GetCount())) return;
	m_Disp_pPicDoc->Apply_Preprocess(); }

