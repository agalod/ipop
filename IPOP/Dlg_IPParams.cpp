// Dlg_IPParams.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "ipop.h"
#include "Dlg_IPParams.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CDlg_IPParams 


CDlg_IPParams::CDlg_IPParams(CWnd* pParent /*=NULL*/)
	: CDialog(CDlg_IPParams::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlg_IPParams)
	m_BinThreshold = 190;
	m_bHoughAccu180 = FALSE;
	m_bHoughAccu360 = 1;
	m_bHoughAccu540 = FALSE;
	m_bShowSteps = FALSE;
	m_HoughSensivity = 16;
	//}}AFX_DATA_INIT
}


void CDlg_IPParams::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlg_IPParams)
	DDX_Text(pDX, IDC_IPPARAMS_BINTHRESH, m_BinThreshold);
	DDV_MinMaxInt(pDX, m_BinThreshold, 0, 255);
	DDX_Check(pDX, IDC_IPPARAMS_HOUGHACCU180, m_bHoughAccu180);
	DDX_Check(pDX, IDC_IPPARAMS_HOUGHACCU360, m_bHoughAccu360);
	DDX_Check(pDX, IDC_IPPARAMS_HOUGHACCU540, m_bHoughAccu540);
	DDX_Check(pDX, IDC_IPPARAMS_SHOWSTEPS, m_bShowSteps);
	DDX_Text(pDX, IDC_IPPARAMS_HOUGHSENSIVITY, m_HoughSensivity);
	DDV_MinMaxDouble(pDX, m_HoughSensivity, 0., 30.);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlg_IPParams, CDialog)
	//{{AFX_MSG_MAP(CDlg_IPParams)
	ON_BN_CLICKED(IDC_IPPARAMS_HOUGHACCU180, OnIpparamsHoughaccu180)
	ON_BN_CLICKED(IDC_IPPARAMS_HOUGHACCU360, OnIpparamsHoughaccu360)
	ON_BN_CLICKED(IDC_IPPARAMS_HOUGHACCU540, OnIpparamsHoughaccu540)
	ON_BN_CLICKED(IDC_IPPARAMS_SHOWSTEPS, OnIpparamsShowsteps)
	ON_EN_CHANGE(IDC_IPPARAMS_BINTHRESH, OnChangeIpparamsBinthresh)
	ON_EN_CHANGE(IDC_IPPARAMS_HOUGHSENSIVITY, OnChangeIpparamsHoughsensivity)
	ON_BN_CLICKED(IDC_IPPARAMS_HOUGHSENSIVITY_POS, OnIpparamsHoughsensivityPos)
	ON_BN_CLICKED(IDC_IPPARAMS_HOUGHSENSIVITY_NEG, OnIpparamsHoughsensivityNeg)
	ON_BN_CLICKED(IDC_IPPARAMS_BINTHRESH_POS, OnIpparamsBinthreshPos)
	ON_BN_CLICKED(IDC_IPPARAMS_BINTHRESH_NEG, OnIpparamsBinthreshNeg)
	ON_WM_CANCELMODE()
	ON_WM_CLOSE()
	ON_WM_DESTROY()
	ON_WM_KILLFOCUS()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten CDlg_IPParams 

void CDlg_IPParams::OnIpparamsHoughaccu180() 
{
	// TODO: Code für die Behandlungsroutine der Steuerelement-Benachrichtigung hier einfügen
	//if(m_bHoughAccu180) {m_bHoughAccu180=0;m_bHoughAccu360=1;m_bHoughAccu540=1;}
	 {m_bHoughAccu180=1;m_bHoughAccu360=0;m_bHoughAccu540=0;}
	UpdateData(0);
}

void CDlg_IPParams::OnIpparamsHoughaccu360() 
{
	// TODO: Code für die Behandlungsroutine der Steuerelement-Benachrichtigung hier einfügen
	//if(m_bHoughAccu360) {m_bHoughAccu360=0;m_bHoughAccu180=1;m_bHoughAccu540=1;}
	 {m_bHoughAccu360=1;m_bHoughAccu180=0;m_bHoughAccu540=0;}
	UpdateData(0);
}

void CDlg_IPParams::OnIpparamsHoughaccu540() 
{
	// TODO: Code für die Behandlungsroutine der Steuerelement-Benachrichtigung hier einfügen
	//if(m_bHoughAccu540) {m_bHoughAccu540=0;m_bHoughAccu180=1;m_bHoughAccu360=1;}
	 {m_bHoughAccu540=1;m_bHoughAccu180=0;m_bHoughAccu360=0;}
	UpdateData(0);
}

void CDlg_IPParams::OnIpparamsShowsteps() 
{
	// TODO: Code für die Behandlungsroutine der Steuerelement-Benachrichtigung hier einfügen
	if(m_bShowSteps) m_bShowSteps=0;
	else m_bShowSteps=1;	UpdateData(0);
}

void CDlg_IPParams::OnChangeIpparamsBinthresh() 
{
	// TODO: Wenn dies ein RICHEDIT-Steuerelement ist, sendet das Steuerelement diese

	// Benachrichtigung nicht, bevor Sie nicht die Funktion CDialog::OnInitDialog()

	// überschreiben und CRichEditCrtl().SetEventMask() aufrufen, wobei

	// eine ODER-Operation mit dem Attribut ENM_CHANGE und der Maske erfolgt.

	

	// TODO: Fügen Sie hier Ihren Code für die Benachrichtigungsbehandlungsroutine des Steuerelements hinzu
	UpdateData(1);
	
}

void CDlg_IPParams::OnChangeIpparamsHoughsensivity() 
{
	// TODO: Wenn dies ein RICHEDIT-Steuerelement ist, sendet das Steuerelement diese

	// Benachrichtigung nicht, bevor Sie nicht die Funktion CDialog::OnInitDialog()

	// überschreiben und CRichEditCrtl().SetEventMask() aufrufen, wobei

	// eine ODER-Operation mit dem Attribut ENM_CHANGE und der Maske erfolgt.

	

	// TODO: Fügen Sie hier Ihren Code für die Benachrichtigungsbehandlungsroutine des Steuerelements hinzu
	UpdateData(1);

	
}

void CDlg_IPParams::OnIpparamsHoughsensivityPos() 
{
	// TODO: Code für die Behandlungsroutine der Steuerelement-Benachrichtigung hier einfügen
	m_HoughSensivity += 0.3; UpdateData(0);
}

void CDlg_IPParams::OnIpparamsHoughsensivityNeg() 
{
	// TODO: Code für die Behandlungsroutine der Steuerelement-Benachrichtigung hier einfügen
	m_HoughSensivity -= 0.3; UpdateData(0);
}

void CDlg_IPParams::OnIpparamsBinthreshPos() 
{
	// TODO: Code für die Behandlungsroutine der Steuerelement-Benachrichtigung hier einfügen
	m_BinThreshold += 5; 
	if(m_BinThreshold >255) m_BinThreshold =255;
	UpdateData(0);
	
}

void CDlg_IPParams::OnIpparamsBinthreshNeg() 
{
	// TODO: Code für die Behandlungsroutine der Steuerelement-Benachrichtigung hier einfügen
	m_BinThreshold -= 5; UpdateData(0);
	
}

void CDlg_IPParams::OnClose() 
{
	// TODO: Code für die Behandlungsroutine für Nachrichten hier einfügen und/oder Standard aufrufen
	
	CDialog::OnClose();
}

void CDlg_IPParams::OnCancelMode() 
{
	CDialog::OnCancelMode();
	
	// TODO: Code für die Behandlungsroutine für Nachrichten hier einfügen
	
}

void CDlg_IPParams::OnDestroy() 
{
	CDialog::OnDestroy();
	
	// TODO: Code für die Behandlungsroutine für Nachrichten hier einfügen
	
}
  
void CDlg_IPParams::OnKillFocus(CWnd* pNewWnd) 
{
	File_Save();
	CDialog::OnKillFocus(pNewWnd);
	
	// TODO: Code für die Behandlungsroutine für Nachrichten hier einfügen
	
}

double CDlg_IPParams::File_ReadLine(const CString &line)
{
	char val[1000]; int begin=0, end=0;
	begin = line.Find(';')+1;
	end = line.Find(';',begin);
	for(int i=begin, j=0;i<end;++i,j++)
		val[j] = line[i];
	val[i] = '\0'; 	return atof(val); }


void CDlg_IPParams::File_Load()
{
	m_File.Abort();
	CString Fullpath, CurrLine, search_str; CFileException error; 
	char text[100];

	if(!m_File.Open( m_Ini_Verzeichnis + "BVParameter.ini", CFile::modeRead, &error))	{
		afxDump << "File could not be opened " << error.m_cause << "\n";
		sprintf( text,"%s konnte nicht geöffnet werden!", Fullpath );
		AfxMessageBox(text); return;	}

	DWORD length = m_File.GetLength();
	
	do{
		// Zeile aus Ini-Datei lesen und auf gesuchten Text untersuchen
		m_File.ReadString(CurrLine);
		if(CurrLine.Find("Binarisierung") != -1) {
			m_File.ReadString(CurrLine); 
			m_BinThreshold = File_ReadLine(CurrLine); }
		if(CurrLine.Find("Houghtransformation") != -1) {
			m_File.ReadString(CurrLine); 
			m_HoughSensivity = File_ReadLine(CurrLine); }
		if(CurrLine.Find("Zwischenschritte anzeigen:") != -1) {
			m_File.ReadString(CurrLine); 
			m_bShowSteps = File_ReadLine(CurrLine); }
	}while(m_File.GetPosition()!=length);

	m_File.Close(); UpdateData(0);  
}

void CDlg_IPParams::File_Save()
{
	CFileException error; CString str;
	CStringArray	StringArray;
	if( !m_File.Open( m_Ini_Verzeichnis + "BVParameter.ini", CFile::modeCreate | CFile::modeWrite, &error)){ 
		AfxMessageBox( "Datei konnte nicht erstellt werden!" );	return ; }

    StringArray.RemoveAll();	
	str.Format("Schwellwert zur Binarisierung:");			StringArray.Add(str);
	str.Format("x: \t ;%i;", m_BinThreshold);				StringArray.Add(str);
	str.Format(""); StringArray.Add(str);
	str.Format("Empfindlichkeit der Houghtransformation:");	StringArray.Add(str);
	str.Format("\t ;%.1f;", m_HoughSensivity);				StringArray.Add(str);
	str.Format(""); StringArray.Add(str);
	str.Format("Zwischenschritte anzeigen:");				StringArray.Add(str);
	str.Format("\t ;%i;", m_bShowSteps);					StringArray.Add(str);
	str.Format(""); StringArray.Add(str);

	for( int i = 0; i<StringArray.GetSize(); i++ ){
		m_File.WriteString(StringArray.GetAt(i));
		m_File.WriteString("\n");
	}
	m_File.Close();

}

