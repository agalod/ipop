// Dlg_Etalon.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "IPOPApp.h"
#include "Dlg_Etalon.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CDlg_Etalon 
  

CDlg_Etalon::CDlg_Etalon(CWnd* pParent /*=NULL*/)
	: CDialog(CDlg_Etalon::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlg_Etalon)
	m_iEtalonX = 3;
	m_iEtalonY = 3;
	m_fEtalon_Width = 105.0f;
	//}}AFX_DATA_INIT
	//UpdatePoints();
}


void CDlg_Etalon::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlg_Etalon)
	DDX_Text(pDX, IDC_CAMCAL_ETALONX, m_iEtalonX);
	DDX_Text(pDX, IDC_CAMCAL_ETALONY, m_iEtalonY);
	DDX_Text(pDX, IDC_CAMCAL_ETALONWIDTH, m_fEtalon_Width);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlg_Etalon, CDialog)
	//{{AFX_MSG_MAP(CDlg_Etalon)
	ON_BN_CLICKED(ID_CALIB_UPDATE, OnUpdate)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten CDlg_Etalon 

/*void CDlg_Etalon::OnCalibLoadImage() 
{
	// TODO: Code für die Behandlungsroutine der Steuerelement-Benachrichtigung hier einfügen
	//m_CamCal.LoadShowIPLImage();
}

void CDlg_Etalon::OnCalibCalcCornerguesses() 
{
	// TODO: Code für die Behandlungsroutine der Steuerelement-Benachrichtigung hier einfügen
	UpdateData(1);
	//m_CamCal.FindInnerCorners(m_iEtalonX, m_iEtalonY);
}

void CDlg_Etalon::OnCamcalUpdate() 
{
	// TODO: Code für die Behandlungsroutine der Steuerelement-Benachrichtigung hier einfügen
	//UpdateData(1);
}*/

vector <GCV_VECTOR3D>& CDlg_Etalon::GetPointList()
{
	vector <GCV_VECTOR3D> Points;
	for(int i=0;i<m_Points.size();i++)
		Points.push_back(m_Points[i]);
	return Points;		
}

void CDlg_Etalon::OnOK()
{
	CDialog::OnOK();
	UpdatePoints();
}

void CDlg_Etalon::UpdatePoints()
{
	if(m_iEtalonX%2 !=1 || m_iEtalonY%2 !=1){
		AfxMessageBox("Geben sie eine ungerade Zahl ein."); return;}
	CIPOPApp* pApp = (CIPOPApp*) AfxGetApp();
	m_Points.clear();
	GCV_VECTOR3D pt;
	for(int i=-m_iEtalonX/2; i<=m_iEtalonX/2;i++){
		for(int j=-m_iEtalonY/2; j<=m_iEtalonY/2;j++){
			//if(i==1 && j==1) 
			//	break;
			pt(0)=i*m_fEtalon_Width; pt(1)=j*m_fEtalon_Width;
			m_Points.push_back(pt);}}
	//d3d::XYZEulerToRotMat(m_pEuler->rot_x, m_pEuler->rot_y, m_pEuler->rot_z, m_InitTrafo);
	//m_InitTrafo._14 = m_pEuler->trans_x;
	//m_InitTrafo._24 = m_pEuler->trans_y;
	//m_InitTrafo._34 = m_pEuler->trans_z;
	if(pApp->m_Disp_3D_pView) pApp->Calc_Calibrate_Init();

}

void CDlg_Etalon::OnUpdate() 
{
	// TODO: Code für die Behandlungsroutine der Steuerelement-Benachrichtigung hier einfügen
	UpdateData(1);
	UpdatePoints();
}
