// CheckBoardDialog.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "CheckBoardDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CCheckBoardDialog 


CCheckBoardDialog::CCheckBoardDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CCheckBoardDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(CCheckBoardDialog)
	m_iEtalonX = 3;
	m_iEtalonY = 3;
	m_fEtalon_Width = 70.0f;
	m_Euler.rot_X = -60.0f;
	m_Euler.rot_Y = 0.0f;
	m_Euler.rot_Z = 0.0f;
	m_Euler.trans_x = -70.0f;
	m_Euler.trans_y = -65.0f;
	m_Euler.trans_z = 1150.0f;
	//}}AFX_DATA_INIT

	UpdatePoints();
}


void CCheckBoardDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCheckBoardDialog)
	DDX_Text(pDX, IDC_CAMCAL_ETALONX, m_iEtalonX);
	DDX_Text(pDX, IDC_CAMCAL_ETALONY, m_iEtalonY);
	DDX_Text(pDX, IDC_CAMCAL_ETALONWIDTH, m_fEtalon_Width);
	DDX_Text(pDX, IDC_CAL_RotationX, m_Euler.rot_X);
	DDX_Text(pDX, IDC_CAL_RotationY, m_Euler.rot_Y);
	DDX_Text(pDX, IDC_CAL_RotationZ, m_Euler.rot_Z);
	DDX_Text(pDX, IDC_CAL_TranslationX, m_Euler.trans_x);
	DDX_Text(pDX, IDC_CAL_TranslationY, m_Euler.trans_y);
	DDX_Text(pDX, IDC_CAL_TranslationZ, m_Euler.trans_z);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CCheckBoardDialog, CDialog)
	//{{AFX_MSG_MAP(CCheckBoardDialog)
	ON_BN_CLICKED(ID_CALIB_UPDATE, OnUpdate)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten CCheckBoardDialog 

/*void CCheckBoardDialog::OnCalibLoadImage() 
{
	// TODO: Code für die Behandlungsroutine der Steuerelement-Benachrichtigung hier einfügen
	//m_CamCal.LoadShowIPLImage();
}

void CCheckBoardDialog::OnCalibCalcCornerguesses() 
{
	// TODO: Code für die Behandlungsroutine der Steuerelement-Benachrichtigung hier einfügen
	UpdateData(1);
	//m_CamCal.FindInnerCorners(m_iEtalonX, m_iEtalonY);
}

void CCheckBoardDialog::OnCamcalUpdate() 
{
	// TODO: Code für die Behandlungsroutine der Steuerelement-Benachrichtigung hier einfügen
	//UpdateData(1);
}*/

void CCheckBoardDialog::OnOK()
{
	CDialog::OnOK();
	UpdatePoints();
}

void CCheckBoardDialog::UpdatePoints()
{
	m_Points.clear();
	D3DVECTOR pt;
	for(int i=0; i<m_iEtalonX;i++){
		for(int j=0; j<m_iEtalonY;j++){
			pt(0)=i*m_fEtalon_Width; pt(1)=j*m_fEtalon_Width;
			m_Points.push_back(pt);}}
	d3d::XYZEulerToRotMat(m_Euler.rot_X, m_Euler.rot_Y, m_Euler.rot_Z, m_InitTrafo);
	m_InitTrafo._14 = m_Euler.trans_x;
	m_InitTrafo._24 = m_Euler.trans_y;
	m_InitTrafo._34 = m_Euler.trans_z;
}

void CCheckBoardDialog::OnUpdate() 
{
	// TODO: Code für die Behandlungsroutine der Steuerelement-Benachrichtigung hier einfügen
	UpdateData(1);
	UpdatePoints();
}

vector <D3DVECTOR>& CCheckBoardDialog::GetPointList()
{
	vector <D3DVECTOR> Points;
	for(int i=0;i<m_Points.size();i++)
		Points.push_back(m_Points[i]);
	return Points;		
}
