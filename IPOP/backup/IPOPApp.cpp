// IPOP.cpp : Legt das Klassenverhalten für die Anwendung fest.
//

#include "stdafx.h"
#include "IPOPApp.h"

#include "MainFrm.h"
#include "ChildFrm.h"
#include "IPOPDoc.h"
#include "IPOPView.h"

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
	ON_UPDATE_COMMAND_UI(ID_FILE_MRU_FILE1, OnUpdateFileMruFile1)
	//}}AFX_MSG_MAP
	// Dateibasierte Standard-Dokumentbefehle
	ON_COMMAND(ID_FILE_NEW, CWinApp::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, CWinApp::OnFileOpen)
	// Standard-Druckbefehl "Seite einrichten"
	ON_COMMAND(ID_FILE_PRINT_SETUP, CWinApp::OnFilePrintSetup)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CIPOPApp Konstruktion

CIPOPApp::CIPOPApp()
{
	// ZU ERLEDIGEN: Hier Code zur Konstruktion einfügen
	// Alle wichtigen Initialisierungen in InitInstance platzieren
	m_Display_pPicDoc = 0; m_Display_pPicView = 0;
}

/////////////////////////////////////////////////////////////////////////////
// Das einzige CIPOPApp-Objekt

CIPOPApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CIPOPApp Initialisierung

BOOL CIPOPApp::InitInstance()
{
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
		RUNTIME_CLASS(CIPOPDoc),
		RUNTIME_CLASS(CChildFrame), // Benutzerspezifischer MDI-Child-Rahmen
		RUNTIME_CLASS(CIPOPView));
	AddDocTemplate(m_Template_pPic);

	m_Template_p3D = new CMultiDocTemplate(
		IDR_IPOPTYPE,
		RUNTIME_CLASS(C3DDoc),
		RUNTIME_CLASS(CChildFrame), // custom MDI child frame
		RUNTIME_CLASS(C3DView));
	AddDocTemplate(m_Template_p3D);

	// Haupt-MDI-Rahmenfenster erzeugen
	CMainFrame* pMainFrame = new CMainFrame;
	if (!pMainFrame->LoadFrame(IDR_IPOPTYPE))
		return FALSE;
	m_pMainWnd = pMainFrame;

	// Befehlszeile parsen, um zu prüfen auf Standard-Umgebungsbefehle DDE, Datei offen
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);

	// Verteilung der in der Befehlszeile angegebenen Befehle
//	if (!ProcessShellCommand(cmdInfo))
//		return FALSE;

	// Das Hauptfenster ist initialisiert und kann jetzt angezeigt und aktualisiert werden.
	pMainFrame->ShowWindow(SW_SHOWMAXIMIZED);
	pMainFrame->UpdateWindow();

	m_Dlg_Calibration = new CCheckBoardDialog;
	m_Dlg_Calibration->Create(IDD_DLG_CHECKBOARD, 0);
	m_Dlg_CamParams.Create(IDD_BV_CAMERA_PARAM, AfxGetMainWnd());


	return TRUE;
}


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

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
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
void CIPOPApp::OnAppAbout()
{
	CAboutDlg aboutDlg;   
	aboutDlg.DoModal();
}

/////////////////////////////////////////////////////////////////////////////
// CIPOPApp-Nachrichtenbehandlungsroutinen
void CIPOPApp::LoadBmp(CString str)
{
	CImage* ImgTmp = new CImage();
	if(!m_Display_pPicDoc) CreatePicView();
	if(!(ImgTmp->Load(str,-1)) ){ // LOAD NEXT IMAGE
		AfxMessageBox("Das angegebene Bild wurde nicht gefunden!"); return;}
	m_Display_pPicDoc->CList_AppendImage(ImgTmp, str);
	m_Display_pPicDoc->SetTitle(str);
	m_Display_pPicView->FitWindow(ImgTmp->Width(),ImgTmp->Height());
	AddToRecentFileList(str);

}

void CIPOPApp::LoadBmps() 
{
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
		if(!m_Display_pPicDoc) CreatePicView();
		POSITION pos = Dlg.GetStartPosition(); i=0;
		while(pos){
			if(i>29) {AfxMessageBox("Too many Pictures selected!");break;}
			Fullpath = Dlg.GetNextPathName(pos);
			//if(!(cimg.Load(Fullpath,1))){ // LOAD NEXT IMAGE
			//	AfxMessageBox("Das angegebene Bild wurde nicht gefunden!"); return;}
			ImgTmp[i] = new CImage();
			if(!(ImgTmp[i]->Load(Fullpath,-1)) ){ // LOAD NEXT IMAGE
				AfxMessageBox("Das angegebene Bild wurde nicht gefunden!"); return;}
			else {
				//ImgTmp = cvCloneImage((cimg.GetImage()));
				//m_pImageVec->push_back(ImgTmp);
				//ImgTmp->CopyOf(m_CImg);
				m_Display_pPicDoc->CList_AppendImage(ImgTmp[i], Fullpath);
				m_Display_pPicDoc->SetTitle(Fullpath);
				m_Display_pPicView->FitWindow(ImgTmp[i]->Width(),ImgTmp[i]->Height());
				AddToRecentFileList(Fullpath);
			}
			i++;
		}
	}
}

void CIPOPApp::CreatePicView()
{
	if(m_Display_pPicDoc||m_Display_pPicView) return;
	
	CDocument* pDoc;
	//if(!pos) {
	pDoc = m_Template_pPic->OpenDocumentFile(NULL);
	POSITION pos  = pDoc->GetFirstViewPosition();
	m_Display_pPicView  = (CIPOPView*) pDoc->GetNextView( pos );
	m_Display_pPicDoc   = (CIPOPDoc*) pDoc;
	m_Display_pPicDoc->m_Chessboard_Columns = m_Dlg_Calibration->m_iEtalonX;
	m_Display_pPicDoc->m_Chessboard_Rows = m_Dlg_Calibration->m_iEtalonY;

	
	//m_Display_pPicView->FitWindow();
	
}

void CIPOPApp::Create3DView()
{  
	//if(m_Display_3D_pView||m_Display_3D_pDoc) return;
	m_Display_3D_pView = 0;
	m_Display_3D_pDoc = 0;

	CDocument* pDoc;
	//if(!pos) {
	pDoc = m_Template_p3D->OpenDocumentFile(NULL);
	POSITION pos  = pDoc->GetFirstViewPosition();
	m_Display_3D_pView  = (C3DView*) pDoc->GetNextView( pos );
	m_Display_3D_pDoc   = (C3DDoc*) pDoc;
	//m_Display_3D_pView->Invalidate(0);
	
/*	m_Display_3D_pDialog.Set3DViewAndDoc(m_Display_3D_pView, m_Display_3D_pDoc);
	if(m_Display_3D_pDialog.m_hWnd) 
	//; if the Dialog is already created.
		m_Display_3D_pDialog.SetFocus();
	else
		//m_Display_3D_pDialog.Create((CView*)this);
		m_Display_3D_pDialog.CDialog::Create(IDD_3DView,0);
	m_Display_3D_pDialog. ShowWindow(SW_SHOW);*/

}


int CIPOPApp::ExitInstance() 
{
	// TODO: Speziellen Code hier einfügen und/oder Basisklasse aufrufen
	
	return CWinApp::ExitInstance();
	//if(m_Dlg_CamParams) delete m_Dlg_CamParams;
	if(m_Dlg_Calibration) delete m_Dlg_Calibration;


}

void CIPOPApp::OnUpdateFileMruFile1(CCmdUI* pCmdUI) 
{
	// TODO: Code für die Befehlsbehandlungsroutine zum Aktualisieren der Benutzeroberfläche hier einfügen
	
} 

CRecentFileList* CIPOPApp::GetRecentFileList()
{
	return m_pRecentFileList;
}

void CIPOPApp::Calc_Calibrate_Init()
{
	//; ERRORCATCHER
	if(!m_Display_pPicDoc || !m_Display_pPicDoc->m_Chessboardpointlist.size()){
		AfxMessageBox("Sie müssen erst die Schachbrettpunkte bestimmen."); return; }

	vector < D3DVECTOR > Points; D3DVECTOR pt;
	int length = 320, width=150, height =95;
	pt.x=0;pt.y=0; Points.push_back(pt);
	pt.x=width;pt.y=0; Points.push_back(pt);
	pt.x=0;pt.y=height; Points.push_back(pt);
	pt.x=width;pt.y=height; Points.push_back(pt);

	pt.x=0; pt.y=0; pt.z=length;Points.push_back(pt);
	pt.x=width; pt.y=0;  pt.z=length;Points.push_back(pt);
	pt.x=0; pt.y=height; pt.z=length;Points.push_back(pt);

	
/*
	AddObjPt( 0, 0, 0);
  	AddObjPt(  -m_length, 0, 0);
  	AddObjPt(  -m_length,  -m_width, 0);
  	AddObjPt( 0,  -m_width, 0);
	AddObjPt( 0, 0, -m_height);
  	AddObjPt(  -m_length, -m_width, -m_height);
	if(!m_bIgnore8thPt)
  		AddObjPt(  -m_length, 0, -m_height);
  	AddObjPt( 0, -m_width, -m_height);
	
	*/	
	//; SETUP IPOP CALCULATION CLASS
	m_IPOP.Set_Params_Camera(m_Dlg_CamParams.m_Camera);
	m_Display_pPicDoc->Image_DefineGrid();
	m_IPOP.Set_Calibration_ImagePoints(&(m_Display_pPicDoc->m_Chessboardpointlist));
	m_IPOP.Set_Calibration_ObjectPoints((m_Dlg_Calibration->m_Points));
	//m_IPOP.Set_Calibration_ObjectPoints((Points));
	m_IPOP.Set_Calibration_InitTrafo(m_Dlg_Calibration->m_InitTrafo);


	//; SETUP 3D VIEW
	Create3DView();
	m_Display_3D_pDoc->SetCameraStruct( GetCameraStruct());
	m_Display_3D_pDoc->SetImagepointlist(&(m_Display_pPicDoc->m_Chessboardpointlist));
	m_Display_3D_pDoc->m_pPoints1 = m_IPOP.GetPtsObj();
	m_Display_3D_pDoc->m_pLines1 = m_IPOP.GetCorrespondingPoints();
	//m_Display_3D_pDoc->m_pPoints2 = m_IPOP.GetRaysProjection();

	
	m_IPOP.Calculate_Init();
}


void CIPOPApp::Calc_Calibrate_OneStep()
{
		m_IPOP.Calculate_OneStep();
}


void CIPOPApp::SetUp3DView()
{


}

D3DCAMERA CIPOPApp::GetCameraStruct()
{
	if(m_Dlg_CamParams)
		return (m_Dlg_CamParams.m_Camera);
}

