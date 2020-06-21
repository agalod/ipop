// Dlg_Pose.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "IPOPApp.h"
#include "Dlg_Pose.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CDlg_Pose 
  

CDlg_Pose::CDlg_Pose(CWnd* pParent /*=NULL*/)
	: CDialog(CDlg_Pose::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlg_Pose)
		// HINWEIS: Der Klassen-Assistent fügt hier Elementinitialisierung ein
	m_pNumIterations = 0;
	m_pCamPos=0;
	m_increment =5;
	//}}AFX_DATA_INIT
}


void CDlg_Pose::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlg_Pose)
		// HINWEIS: Der Klassen-Assistent fügt hier DDX- und DDV-Aufrufe ein
	DDX_Text(pDX, IDC_CAL_RotationX, m_pCamPos->rot_x);
	DDX_Text(pDX, IDC_CAL_RotationY, m_pCamPos->rot_y);
	DDX_Text(pDX, IDC_CAL_RotationZ, m_pCamPos->rot_z);
	DDX_Text(pDX, IDC_CAL_TranslationX, m_pCamPos->trans_x);
	DDX_Text(pDX, IDC_CAL_TranslationY, m_pCamPos->trans_y);
	DDX_Text(pDX, IDC_CAL_TranslationZ, m_pCamPos->trans_z);
	DDX_Text(pDX, IDC_CAL_NUMIT, *m_pNumIterations);
	DDX_Text(pDX, IDC_CAL_SUMDISTANCES, *m_pDistances_Sum);

	DDX_Text(pDX, IDC_CAL_MACHINEREFX, m_pMachineRef->trans_x );
	//DDX_Text(pDX, IDC_CAL_MACHINEREFX, 6 - 5));
	DDX_Text(pDX, IDC_CAL_MACHINEREFY, m_pMachineRef->trans_y);
	DDX_Text(pDX, IDC_CAL_MACHINEREFROTZ, m_pMachineRef->rot_z);
	DDX_Text(pDX, IDC_CAL_MACHINEREFROTX, m_pMachineRef->rot_x);

	DDX_Text(pDX, IDC_CAL_WORKPIECE_TRANSX, m_pWorkpiece->trans_x);
	DDX_Text(pDX, IDC_CAL_WORKPIECE_TRANSY, m_pWorkpiece->trans_y);
	DDX_Text(pDX, IDC_CAL_WORKPIECE_ROTZ, m_pWorkpiece->rot_z);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CDlg_Pose, CDialog)
	//{{AFX_MSG_MAP(CDlg_Pose)
		// HINWEIS: Der Klassen-Assistent fügt hier Zuordnungsmakros für Nachrichten ein
	ON_BN_CLICKED(IDC_CAL_MACHINEREF_TRANSX_NEG,	On_MachineRef_TransX_Neg)
	ON_BN_CLICKED(IDC_CAL_MACHINEREF_TRANSY_NEG,	On_MachineRef_TransY_Neg)
	ON_BN_CLICKED(IDC_CAL_MACHINEREF_ROTZ_NEG,		On_MachineRef_RotZ_Neg)
	ON_BN_CLICKED(IDC_CAL_MACHINEREF_ROTX_NEG,		On_MachineRef_RotX_Neg)
	ON_BN_CLICKED(IDC_CAL_MACHINEREF_TRANSX_POS,	On_MachineRef_TransX_Pos)
	ON_BN_CLICKED(IDC_CAL_MACHINEREF_TRANSY_POS,	On_MachineRef_TransY_Pos)
	ON_BN_CLICKED(IDC_CAL_MACHINEREF_ROTZ_POS,		On_MachineRef_RotZ_Pos)
	ON_BN_CLICKED(IDC_CAL_MACHINEREF_ROTX_POS,		On_MachineRef_RotX_Pos)

	ON_BN_CLICKED(IDC_CAL_WORKPIECE_TRANSX_NEG, On_Workpiece_TransX_Neg)
	ON_BN_CLICKED(IDC_CAL_WORKPIECE_TRANSY_NEG, On_Workpiece_TransY_Neg)
	ON_BN_CLICKED(IDC_CAL_WORKPIECE_ROTZ_NEG,	On_Workpiece_RotZ_Neg)
	ON_BN_CLICKED(IDC_CAL_WORKPIECE_TRANSX_POS, On_Workpiece_TransX_Pos)
	ON_BN_CLICKED(IDC_CAL_WORKPIECE_TRANSY_POS, On_Workpiece_TransY_Pos)
	ON_BN_CLICKED(IDC_CAL_WORKPIECE_ROTZ_POS,	On_Workpiece_RotZ_Pos)

	ON_EN_CHANGE(IDC_CAL_TranslationX,	OnChange_TransX)
	ON_EN_CHANGE(IDC_CAL_TranslationY,	OnChange_TransY)
	ON_EN_CHANGE(IDC_CAL_TranslationZ,	OnChange_TransZ)
	ON_EN_CHANGE(IDC_CAL_RotationX,		OnChange_RotX)
	ON_EN_CHANGE(IDC_CAL_RotationY,		OnChange_RotY)
	ON_EN_CHANGE(IDC_CAL_RotationZ,		OnChange_RotZ)

	ON_BN_CLICKED(IDC_CAL_TRANSX_NEG,	On_TransX_Neg)
	ON_BN_CLICKED(IDC_CAL_TRANSY_NEG,	On_TransY_Neg)
	ON_BN_CLICKED(IDC_CAL_TRANSZ_NEG,	On_TransZ_Neg)
	ON_BN_CLICKED(IDC_CAL_ROTX_NEG,		On_RotX_Neg)
	ON_BN_CLICKED(IDC_CAL_ROTY_NEG,		On_RotY_Neg)
	ON_BN_CLICKED(IDC_CAL_ROTZ_NEG,		On_RotZ_Neg)
	ON_BN_CLICKED(IDC_CAL_TRANSX_POS,	On_TransX_Pos)
	ON_BN_CLICKED(IDC_CAL_TRANSY_POS,	On_TransY_Pos)
	ON_BN_CLICKED(IDC_CAL_TRANSZ_POS,	On_TransZ_Pos)
	ON_BN_CLICKED(IDC_CAL_ROTX_POS,		On_RotX_Pos)
	ON_BN_CLICKED(IDC_CAL_ROTY_POS,		On_RotY_Pos)
	ON_BN_CLICKED(IDC_CAL_ROTZ_POS,		On_RotZ_Pos)

	ON_BN_CLICKED(IDC_CAL_UPDATE, Update)
	ON_BN_CLICKED(IDC_DLG_POSE_SETASMACHREF, SetAsMachineRef)

	ON_EN_CHANGE(IDC_CAL_MACHINEREFX,		OnChangeMachineRefX)
	ON_EN_CHANGE(IDC_CAL_MACHINEREFY,		OnChangeMachineRefY)
	ON_EN_CHANGE(IDC_CAL_MACHINEREFROTX,	OnChangeMachineRefRotX)
	ON_EN_CHANGE(IDC_CAL_MACHINEREFROTZ,	OnChangeMachineRefRotZ)
	ON_EN_CHANGE(IDC_CAL_WORKPIECE_TRANSX,	OnChangeWorkpiece_TransX)
	ON_EN_CHANGE(IDC_CAL_WORKPIECE_TRANSY,	OnChangeWorkpiece_TransY)
	ON_EN_CHANGE(IDC_CAL_WORKPIECE_ROTZ,	OnChangeWorkpiece_RotZ)
	ON_WM_KILLFOCUS()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten CDlg_Pose 


void CDlg_Pose::OnChangeMachineRefX() 
{
	UpdateData(1);
	Update();
}


void CDlg_Pose::OnChangeMachineRefY() 
{
	UpdateData(1);
	Update();
}


void CDlg_Pose::OnChangeMachineRefRotZ() 
{
	UpdateData(1);
	Update();
}

void CDlg_Pose::OnChangeMachineRefRotX() 
{
	UpdateData(1);
	Update();
}

void CDlg_Pose::OnChangeWorkpiece_TransX() 
{
	UpdateData(1);
	Update();
}


void CDlg_Pose::OnChangeWorkpiece_TransY() 
{
	UpdateData(1);
	Update();
}


void CDlg_Pose::OnChangeWorkpiece_RotZ() 
{
	UpdateData(1);
	Update();
}


void CDlg_Pose::OnChange_RotX() 
{
	UpdateData(1);
	Update();
}

void CDlg_Pose::OnChange_RotY() 
{
	UpdateData(1);
	Update();
}

void CDlg_Pose::OnChange_RotZ() 
{
	UpdateData(1);
	Update();
}
void CDlg_Pose::OnChange_TransX() 
{
	UpdateData(1);
	Update();
}

void CDlg_Pose::OnChange_TransY() 
{
	UpdateData(1);
	Update();
}

void CDlg_Pose::OnChange_TransZ() 
{
	UpdateData(1);
	Update();
}

void CDlg_Pose::On_TransX_Neg() 
{
	// TODO: Code für die Behandlungsroutine der Steuerelement-Benachrichtigung hier einfügen
	CIPOPApp* pApp = (CIPOPApp*) AfxGetApp();
	m_pCamPos->trans_x -= m_increment;
	UpdateData(0);  pApp->m_IPOP.Calc_RegIIPM_Update();	
	
}



void CDlg_Pose::On_TransY_Neg() 
{
	// TODO: Code für die Behandlungsroutine der Steuerelement-Benachrichtigung hier einfügen
	CIPOPApp* pApp = (CIPOPApp*) AfxGetApp();
	m_pCamPos->trans_y -= m_increment;
	UpdateData(0);  pApp->m_IPOP.Calc_RegIIPM_Update();	//UpdatePoints();
	

}

void CDlg_Pose::On_TransZ_Neg() 
{
	// TODO: Code für die Behandlungsroutine der Steuerelement-Benachrichtigung hier einfügen
	CIPOPApp* pApp = (CIPOPApp*) AfxGetApp();
	m_pCamPos->trans_z -= m_increment;
	UpdateData(0);  pApp->m_IPOP.Calc_RegIIPM_Update();	//UpdatePoints();

 }

void CDlg_Pose::On_TransX_Pos() 
{
	// TODO: Code für die Behandlungsroutine der Steuerelement-Benachrichtigung hier einfügen
	CIPOPApp* pApp = (CIPOPApp*) AfxGetApp();
	m_pCamPos->trans_x += m_increment;

	UpdateData(0);  pApp->m_IPOP.Calc_RegIIPM_Update();	//UpdatePoints();

 }

void CDlg_Pose::On_TransY_Pos() 
{
	// TODO: Code für die Behandlungsroutine der Steuerelement-Benachrichtigung hier einfügen
	CIPOPApp* pApp = (CIPOPApp*) AfxGetApp();
	m_pCamPos->trans_y += m_increment;
	UpdateData(0);  pApp->m_IPOP.Calc_RegIIPM_Update();	//UpdatePoints();

 }

void CDlg_Pose::On_TransZ_Pos() 
{
	// TODO: Code für die Behandlungsroutine der Steuerelement-Benachrichtigung hier einfügen
	CIPOPApp* pApp = (CIPOPApp*) AfxGetApp();
	m_pCamPos->trans_z += m_increment;
	UpdateData(0);  pApp->m_IPOP.Calc_RegIIPM_Update(); 	//UpdatePoints();

 }


void CDlg_Pose::On_RotX_Neg() 
{
	// TODO: Code für die Behandlungsroutine der Steuerelement-Benachrichtigung hier einfügen
	CIPOPApp* pApp = (CIPOPApp*) AfxGetApp();
	m_pCamPos->rot_x -= m_increment;
	UpdateData(0);  pApp->m_IPOP.Calc_RegIIPM_Update();	//UpdatePoints();

 }

void CDlg_Pose::On_RotY_Neg() 
{
	// TODO: Code für die Behandlungsroutine der Steuerelement-Benachrichtigung hier einfügen
	CIPOPApp* pApp = (CIPOPApp*) AfxGetApp();
	m_pCamPos->rot_y -= m_increment;
	UpdateData(0);  pApp->m_IPOP.Calc_RegIIPM_Update();	//UpdatePoints();

 }

void CDlg_Pose::On_RotZ_Neg() 
{
	// TODO: Code für die Behandlungsroutine der Steuerelement-Benachrichtigung hier einfügen
	CIPOPApp* pApp = (CIPOPApp*) AfxGetApp();
	m_pCamPos->rot_z -= m_increment;
	UpdateData(0);  pApp->m_IPOP.Calc_RegIIPM_Update();	//UpdatePoints();

 }

void CDlg_Pose::On_RotX_Pos() 
{
	// TODO: Code für die Behandlungsroutine der Steuerelement-Benachrichtigung hier einfügen
	CIPOPApp* pApp = (CIPOPApp*) AfxGetApp();
	m_pCamPos->rot_x += m_increment;
	UpdateData(0);  pApp->m_IPOP.Calc_RegIIPM_Update();	//UpdatePoints();

 }

void CDlg_Pose::On_RotY_Pos() 
{
	// TODO: Code für die Behandlungsroutine der Steuerelement-Benachrichtigung hier einfügen
	CIPOPApp* pApp = (CIPOPApp*) AfxGetApp();
	m_pCamPos->rot_y += m_increment;
	UpdateData(0);  pApp->m_IPOP.Calc_RegIIPM_Update();	//UpdatePoints();

 }

void CDlg_Pose::On_RotZ_Pos() 
{
	// TODO: Code für die Behandlungsroutine der Steuerelement-Benachrichtigung hier einfügen
	CIPOPApp* pApp = (CIPOPApp*) AfxGetApp();
	m_pCamPos->rot_z += m_increment;
	UpdateData(0);  pApp->m_IPOP.Calc_RegIIPM_Update();	//UpdatePoints();
}


void CDlg_Pose::On_MachineRef_TransX_Neg() 
{
	CIPOPApp* pApp = (CIPOPApp*) AfxGetApp();
	m_pMachineRef->trans_x -= m_increment;
	UpdateData(0);  pApp->m_IPOP.Calc_RegIIPM_Update();	//UpdatePoints();
}
void CDlg_Pose::On_MachineRef_TransY_Neg() 
{
	CIPOPApp* pApp = (CIPOPApp*) AfxGetApp();
	m_pMachineRef->trans_y -= m_increment;
	UpdateData(0);  pApp->m_IPOP.Calc_RegIIPM_Update();	//UpdatePoints();
}


void CDlg_Pose::On_MachineRef_RotZ_Neg() 
{
	CIPOPApp* pApp = (CIPOPApp*) AfxGetApp();
	m_pMachineRef->rot_z -= m_increment;
	UpdateData(0);  pApp->m_IPOP.Calc_RegIIPM_Update();	//UpdatePoints();
	
}

void CDlg_Pose::On_MachineRef_RotX_Neg() 
{
	CIPOPApp* pApp = (CIPOPApp*) AfxGetApp();
	m_pMachineRef->rot_x -= m_increment;
	UpdateData(0);  pApp->m_IPOP.Calc_RegIIPM_Update();	//UpdatePoints();
	
}


void CDlg_Pose::On_MachineRef_TransX_Pos() 
{
	CIPOPApp* pApp = (CIPOPApp*) AfxGetApp();
	m_pMachineRef->trans_x += m_increment;
	UpdateData(0);  pApp->m_IPOP.Calc_RegIIPM_Update();	//UpdatePoints();
}

void CDlg_Pose::On_MachineRef_TransY_Pos() 
{	
	CIPOPApp* pApp = (CIPOPApp*) AfxGetApp();
	m_pMachineRef->trans_y += m_increment;
	UpdateData(0);  pApp->m_IPOP.Calc_RegIIPM_Update();	//UpdatePoints();
}


void CDlg_Pose::On_MachineRef_RotZ_Pos() 
{	
	CIPOPApp* pApp = (CIPOPApp*) AfxGetApp();
	m_pMachineRef->rot_z += m_increment;
	UpdateData(0);  pApp->m_IPOP.Calc_RegIIPM_Update();	//UpdatePoints();
	
}

void CDlg_Pose::On_MachineRef_RotX_Pos() 
{	
	CIPOPApp* pApp = (CIPOPApp*) AfxGetApp();
	m_pMachineRef->rot_x += m_increment;
	UpdateData(0);  pApp->m_IPOP.Calc_RegIIPM_Update();	//UpdatePoints();
	
}

void CDlg_Pose::On_Workpiece_TransX_Neg() 
{	
	CIPOPApp* pApp = (CIPOPApp*) AfxGetApp();
	m_pWorkpiece->trans_x -= m_increment;
	UpdateData(0);  
	Update();
}

void CDlg_Pose::On_Workpiece_TransY_Neg() 
{	
	CIPOPApp* pApp = (CIPOPApp*) AfxGetApp();
	m_pWorkpiece->trans_y -= m_increment;
	UpdateData(0);  
	Update();
}

void CDlg_Pose::On_Workpiece_RotZ_Neg() 
{	
	CIPOPApp* pApp = (CIPOPApp*) AfxGetApp();
	m_pWorkpiece->rot_z -= m_increment;
	UpdateData(0);  
	Update();
}

void CDlg_Pose::On_Workpiece_TransX_Pos() 
{	
	CIPOPApp* pApp = (CIPOPApp*) AfxGetApp();
	m_pWorkpiece->trans_x += m_increment;
	UpdateData(0);  
	Update();
}

void CDlg_Pose::On_Workpiece_TransY_Pos() 
{	
	CIPOPApp* pApp = (CIPOPApp*) AfxGetApp();
	m_pWorkpiece->trans_y += m_increment;
	UpdateData(0);  
	Update();
}
void CDlg_Pose::On_Workpiece_RotZ_Pos() 
{	
	CIPOPApp* pApp = (CIPOPApp*) AfxGetApp();
	m_pWorkpiece->rot_z += m_increment;
	UpdateData(0);  
	Update();
}


//DEL void CDlg_Pose::Update_Eulers()
//DEL {
//DEL 	D3DEULER *m_pCamPos, *m_pMachineRef, *m_pWorkpiece;
//DEL 	fEuler_MachineRef_Abs = fEuler_Overall + fEuler_Machine_Rel;
//DEL 	fEuler_Workpiece_Abs = fEuler_MachineRef_Abs + fEuler_Workpiece_Rel;
//DEL 
//DEL }

void CDlg_Pose::UpdateObjectPoints()
{
	CIPOPApp* pApp = (CIPOPApp*) AfxGetApp();

}

void CDlg_Pose::Update()
{
	CIPOPApp* pApp = (CIPOPApp*) AfxGetApp();
	pApp->m_IPOP.Calc_RegIIPM_Update(); 
	File_Save(); }


double CDlg_Pose::File_ReadLine(const CString &line)
{
	char val[1000]; int begin=0, end=0;
	begin = line.Find(';')+1;
	end = line.Find(';',begin);
	for(int i=begin, j=0;i<end;++i,j++)
		val[j] = line[i];
	val[i] = '\0'; 	return atof(val); }


void CDlg_Pose::File_Load()
{
	m_File.Abort();
	CString Fullpath, CurrLine, search_str; CFileException error; 
	char text[100];

	if(!m_File.Open( m_Ini_Verzeichnis + "Lagedaten.ini", 
		CFile::modeRead, &error))	{
		afxDump << "File could not be opened " << error.m_cause << "\n";
		sprintf( text,"%s konnte nicht geöffnet werden!", Fullpath );
		AfxMessageBox(text); return;	}

	DWORD length = m_File.GetLength();
	
	do{
		// Zeile aus Ini-Datei lesen und auf gesuchten Text untersuchen
		m_File.ReadString(CurrLine);

		if(CurrLine.Find("Kalibriermuster:") != -1){
			m_File.ReadString(CurrLine); 
			m_pCamPos->rot_x = File_ReadLine(CurrLine); 
			m_File.ReadString(CurrLine); 
			m_pCamPos->rot_y = File_ReadLine(CurrLine);
			m_File.ReadString(CurrLine); 
			m_pCamPos->rot_z = File_ReadLine(CurrLine);
			m_File.ReadString(CurrLine); 
			m_pCamPos->trans_x = File_ReadLine(CurrLine);
			m_File.ReadString(CurrLine); 
			m_pCamPos->trans_y = File_ReadLine(CurrLine);
			m_File.ReadString(CurrLine); 
			m_pCamPos->trans_z = File_ReadLine(CurrLine);
		}
		else if(CurrLine.Find("Maschinenreferenz:") != -1){
			m_File.ReadString(CurrLine); 
			m_pMachineRef->rot_x = File_ReadLine(CurrLine); 
			m_File.ReadString(CurrLine); 
			m_pMachineRef->rot_z = File_ReadLine(CurrLine);
			m_File.ReadString(CurrLine); 
			m_pMachineRef->trans_x = File_ReadLine(CurrLine);
			m_File.ReadString(CurrLine); 
			m_pMachineRef->trans_y = File_ReadLine(CurrLine);
		}
		else if(CurrLine.Find("Werkstueck:") != -1){
			m_File.ReadString(CurrLine); 
			m_pWorkpiece->rot_z = File_ReadLine(CurrLine);
			m_File.ReadString(CurrLine); 
			m_pWorkpiece->trans_x = File_ReadLine(CurrLine);
			m_File.ReadString(CurrLine); 
			m_pWorkpiece->trans_y = File_ReadLine(CurrLine);
		}
	}while(m_File.GetPosition()!=length);
	
	m_File.Close(); UpdateData(0);  
}

void CDlg_Pose::File_Save()
{
	m_File.Abort();
	CFileException error; CString str;
	CStringArray	StringArray; int idx=0;
	if( !m_File.Open(m_Ini_Verzeichnis + "Lagedaten.ini", 
		CFile::modeCreate | CFile::modeWrite, &error)){ 
		AfxMessageBox( "Datei konnte nicht erstellt werden!" );	return ; }

    StringArray.RemoveAll();	
	str.Format("Kalibriermuster:");							StringArray.Add(str);
	str.Format("rot_x: \t\t ;%.5f;", m_pCamPos->rot_x);			StringArray.Add(str);
	str.Format("rot_y: \t\t ;%.5f;", m_pCamPos->rot_y);			StringArray.Add(str);
	str.Format("rot_z: \t\t ;%.5f;", m_pCamPos->rot_z);			StringArray.Add(str);
	str.Format("trans_x: \t ;%.5f;", m_pCamPos->trans_x);		StringArray.Add(str);
	str.Format("trans_y: \t ;%.5f;", m_pCamPos->trans_y);		StringArray.Add(str);
	str.Format("trans_z: \t ;%.5f;", m_pCamPos->trans_z);		StringArray.Add(str);
	str.Format(""); StringArray.Add(str);

	str.Format("Maschinenreferenz:");						StringArray.Add(str);
	str.Format("rot_x: \t\t ;%.5f;", m_pMachineRef->rot_x);		StringArray.Add(str);
	str.Format("rot_z: \t\t ;%.5f;", m_pMachineRef->rot_z);		StringArray.Add(str);
	str.Format("trans_x: \t ;%.5f;", m_pMachineRef->trans_x);	StringArray.Add(str);
	str.Format("trans_y: \t ;%.5f;", m_pMachineRef->trans_y);	StringArray.Add(str);
	str.Format(""); StringArray.Add(str);

	str.Format("Werkstueck:");								StringArray.Add(str);
	str.Format("rot_z: \t\t ;%.5f;", m_pWorkpiece->rot_z);		StringArray.Add(str);
	str.Format("trans_x: \t ;%.5f;", m_pWorkpiece->trans_x);	StringArray.Add(str);
	str.Format("trans_y: \t ;%.5f;", m_pWorkpiece->trans_y);	StringArray.Add(str);
	str.Format(""); StringArray.Add(str);

	str.Format("Werkstueck, Exportformat:"); StringArray.Add(str);
	str.Format("rot_z:   \t %.5f", m_pWorkpiece->rot_z);
	idx=str.Replace('.', ',');	StringArray.Add(str);
	str.Format("trans_x: \t %.5f", m_pWorkpiece->trans_x);
	idx=str.Replace('.', ',');	StringArray.Add(str);
	str.Format("trans_y: \t %.5f", m_pWorkpiece->trans_y);
	idx=str.Replace('.', ',');	StringArray.Add(str);

	for( int i = 0; i<StringArray.GetSize(); i++ ){
		m_File.WriteString(StringArray.GetAt(i));
		m_File.WriteString("\n");
	}

	
	m_File.Close();



}

void CDlg_Pose::OnKillFocus(CWnd* pNewWnd) 
{
	File_Save();
	CDialog::OnKillFocus(pNewWnd);
	
	// TODO: Code für die Behandlungsroutine für Nachrichten hier einfügen
	
}

void CDlg_Pose::SetAsMachineRef()
{
	CIPOPApp* pApp = (CIPOPApp*) AfxGetApp();
	pApp->m_IPOP.SetWorkpieceAbsToMachineRefAbs();
	UpdateData(0);
}
