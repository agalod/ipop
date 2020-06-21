// IPOPCameraDlg.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "kaz.h"
#include "IPOPCameraDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CIPOPCameraDlg 


CIPOPCameraDlg::CIPOPCameraDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CIPOPCameraDlg::IDD, pParent)
{
	CKAZApp* pApp = (CKAZApp*) AfxGetApp();
	//{{AFX_DATA_INIT(CIPOPCameraDlg)
	//m_CCDWidth = pApp->m_BV_pObjectRegistration->fWidthCCD;
	//m_CCDHeight = pApp->m_BV_pObjectRegistration->fHeightCCD;
	//m_FocusLength = pApp->m_BV_pObjectRegistration->fFocalLen;
	m_FocusLength = 0;
	m_PixNumX = 0;
	m_PixNumY = 0;
	m_dPrincipalPtX=0;
	m_dPrincipalPtY=0;
	m_dCellSizeX = pApp->m_BV_pObjectRegistration->fCellSizeX;
	m_dCellSizeY = pApp->m_BV_pObjectRegistration->fCellSizeY;
	//m_iPicSizeY = 0;
	//m_iPicSizeX = 0;
	m_dDistortion[0] = 0.0;
	m_dDistortion[1] = 0.0;
	m_dDistortion[2] = 0.0;
	m_dDistortion[3] = 0.0;
	m_dCameraMat[0] = 0.0;
	m_dCameraMat[1] = 0.0;
	m_dCameraMat[2] = 0.0;
	m_dCameraMat[3] = 0.0;
	m_dCameraMat[4] = 0.0;
	m_dCameraMat[5] = 0.0;
	m_dCameraMat[6] = 0.0;
	m_dCameraMat[7] = 0.0;
	m_dCameraMat[8] = 0.0;
	//}}AFX_DATA_INIT
	//OnCalcPixSize();
	m_pIniFile = 0;
	m_FocusLength = m_dCameraMat[4] * m_dCellSizeX / 1000.0;
}


void CIPOPCameraDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CIPOPCameraDlg)
	//DDX_Text(pDX, IDC_BV_CAMPARAM_CCDX, m_CCDWidth);
	//DDX_Text(pDX, IDC_BV_CAMPARAM_CCDY, m_CCDHeight);
	DDV_MinMaxDouble(pDX, m_FocusLength, 0., 200.);
	DDX_Text(pDX, IDC_BV_CAMPARAM_PIXNUMX, m_PixNumX);
	DDX_Text(pDX, IDC_BV_CAMPARAM_PIXNUMY, m_PixNumY);
	DDX_Text(pDX, IDC_BV_CAMPARAM_FOCLEN, m_FocusLength);
	DDX_Text(pDX, IDC_CAMPARAM_OFFSETX, m_dPrincipalPtX);
	DDX_Text(pDX, IDC_CAMPARAM_OFFSETY, m_dPrincipalPtY);
	DDX_Text(pDX, IDC_BV_CAMPARAM_PIXSIZEX, m_dCellSizeX);
	DDX_Text(pDX, IDC_BV_CAMPARAM_PIXSIZEY, m_dCellSizeY);
	//DDX_Text(pDX, IDC_BV_CAMPARAM_PICSIZEY, m_iPicSizeY);
	//DDX_Text(pDX, IDC_BV_CAMPARAM_PICSIZEX, m_iPicSizeX);
	DDX_Text(pDX, IDC_CAMPARAM_DIST1, m_dDistortion[0]);
	DDX_Text(pDX, IDC_CAMPARAM_DIST2, m_dDistortion[1]);
	DDX_Text(pDX, IDC_CAMPARAM_DIST3, m_dDistortion[2]);
	DDX_Text(pDX, IDC_CAMPARAM_DIST4, m_dDistortion[3]);
	DDX_Text(pDX, IDC_CAMPARAM_CAMMAT1, m_dCameraMat[0]);
	DDX_Text(pDX, IDC_CAMPARAM_CAMMAT2, m_dCameraMat[1]);
	DDX_Text(pDX, IDC_CAMPARAM_CAMMAT3, m_dCameraMat[2]);
	DDX_Text(pDX, IDC_CAMPARAM_CAMMAT4, m_dCameraMat[3]);
	DDX_Text(pDX, IDC_CAMPARAM_CAMMAT5, m_dCameraMat[4]);
	DDX_Text(pDX, IDC_CAMPARAM_CAMMAT6, m_dCameraMat[5]);
	DDX_Text(pDX, IDC_CAMPARAM_CAMMAT7, m_dCameraMat[6]);
	DDX_Text(pDX, IDC_CAMPARAM_CAMMAT8, m_dCameraMat[7]);
	DDX_Text(pDX, IDC_CAMPARAM_CAMMAT9, m_dCameraMat[8]);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CIPOPCameraDlg, CDialog)
	//{{AFX_MSG_MAP(CIPOPCameraDlg)
	ON_BN_CLICKED(IDC_BV_CAMPARAM_LOADDATA, On_LoadCalibData)
	ON_BN_CLICKED(IDC_BV_CAMPARAM_CALCFOCLEN, On_Calc_FocLen)
	//ON_EN_CHANGE(IDC_BV_CAMPARAM_PIXSIZEX, On_Calc_FocLen)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten CIPOPCameraDlg 

//DEL void CIPOPCameraDlg::On_CalcPixSize() 
//DEL {
//DEL 	// TODO: Code für die Behandlungsroutine der Steuerelement-Benachrichtigung hier einfügen
//DEL 	if(this->m_hWnd) UpdateData(1); //retrieve data from the dialog
//DEL 	m_dPixSizeX = m_CCDWidth / m_PixNumX;
//DEL 	m_dPixSizeY = m_CCDHeight / m_PixNumY;
//DEL 	if(this->m_hWnd) UpdateData(0); //update data to the dialog
//DEL 
//DEL }

void CIPOPCameraDlg::On_LoadCalibData() 
{
	CKAZApp* pApp = ((CKAZApp*)AfxGetApp());
	SetCurrentDirectory(pApp->GetIniVerzeichnis());
	m_pIniFile = pApp->m_Inifile_pCamera;
	m_pIniFile->INI_LesenFileDialog();
	for(int i=0;i<4;i++)
		m_dDistortion[i] = m_pIniFile->m_Int_Dist[i];
	for(i=0;i<9;i++)
		m_dCameraMat[i] = m_pIniFile->m_Int_CameraMat[i];
	m_PixNumX = m_pIniFile->m_Int_ImageSize[0];
	m_PixNumY = m_pIniFile->m_Int_ImageSize[1];
	m_dPrincipalPtX = m_pIniFile->m_Int_CameraMat[2];
	m_dPrincipalPtY = m_pIniFile->m_Int_CameraMat[5];
	UpdateData(0); // show new data in dialog
	On_Calc_FocLen();	

}

void CIPOPCameraDlg::On_Calc_FocLen()
{
	double tmp;
	tmp = m_dCameraMat[0] * m_dCellSizeX;
	UpdateData(1); // get new data from dialog
	m_FocusLength = m_dCameraMat[0] * m_dCellSizeX / 1000.0;
	UpdateData(0); // show new data in dialog

}

void CIPOPCameraDlg::Set_Data(double* CameraMat, double* Distortion, double* CellSize, int* PicSize )
{
	for(int i=0; i<9;i++)
		m_dCameraMat[i] = CameraMat[i];
	for(i=0;i<4;i++)
		m_dDistortion[i] = Distortion[i];
	m_dCellSizeX = CellSize[0];
	m_dCellSizeY = CellSize[1];
	m_PixNumX = PicSize[0];
	m_PixNumY = PicSize[1];

	m_FocusLength = CameraMat[0] * m_dCellSizeX / 1000;
	m_dPrincipalPtX = CameraMat[2];
	m_dPrincipalPtY = CameraMat[5];

}

void CIPOPCameraDlg::OnOK()
{
	UpdateData(1);
	CKAZApp* pApp = ((CKAZApp*)AfxGetApp());
	m_pIniFile = pApp->m_Inifile_pCamera;

	m_pIniFile->Set_FocLen(m_FocusLength);
	m_pIniFile->Set_CameraMat(m_dCameraMat);
	m_pIniFile->Set_CellSize(m_dCellSizeX,m_dCellSizeY);
	m_pIniFile->Set_DistortionVec(m_dDistortion);

	CDialog::OnOK();
}


