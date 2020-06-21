// Dlg_Camera.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "Dlg_Camera.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CDlg_Camera 

 
CDlg_Camera::CDlg_Camera(CWnd* pParent /*=NULL*/)
	: CDialog(CDlg_Camera::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlg_Camera)
	//m_CCDWidth = pApp->m_BV_pObjectRegistration->fWidthCCD;
	//m_CCDHeight = pApp->m_BV_pObjectRegistration->fHeightCCD;
	//m_Camera.FocalLength = pApp->m_BV_pObjectRegistration->fFocalLen;
	m_Camera.FocalLength = 0;
	m_Camera.PixNumX = 752;
	m_Camera.PixNumY = 576;
	m_Camera.PrincipalPointX=0;
	m_Camera.PrincipalPointY=0;
	m_Camera.CellSizeX = 6,5;
	m_Camera.CellSizeY = 8,3;
	//m_iPicSizeY = 0;
	//m_iPicSizeX = 0;
	m_Camera.DistortionParameters[0] = 0.0;
	m_Camera.DistortionParameters[1] = 0.0;
	m_Camera.DistortionParameters[2] = 0.0;
	m_Camera.DistortionParameters[3] = 0.0;
	m_Camera.CameraMatrix[0] = 0.0;
	m_Camera.CameraMatrix[1] = 0.0;
	m_Camera.CameraMatrix[2] = 0.0;
	m_Camera.CameraMatrix[3] = 0.0;
	m_Camera.CameraMatrix[4] = 0.0;
	m_Camera.CameraMatrix[5] = 0.0;
	m_Camera.CameraMatrix[6] = 0.0;
	m_Camera.CameraMatrix[7] = 0.0;
	m_Camera.CameraMatrix[8] = 0.0;
	//}}AFX_DATA_INIT
	//OnCalcPixSize();
//	m_Camera.FocalLength = m_Camera.CameraMatrix[4] * m_Camera.CellSizeX / 1000.0;
	m_pIniFile = new CIni_Camera("./", "camera.ini");
	On_LoadCalibData();
}


void CDlg_Camera::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlg_Camera)
	//DDX_Text(pDX, IDC_BV_CAMPARAM_CCDX, m_CCDWidth);
	//DDX_Text(pDX, IDC_BV_CAMPARAM_CCDY, m_CCDHeight);
	DDV_MinMaxDouble(pDX, m_Camera.FocalLength, 0., 200.);
	DDX_Text(pDX, IDC_BV_CAMPARAM_PIXNUMX, m_Camera.PixNumX);
	DDX_Text(pDX, IDC_BV_CAMPARAM_PIXNUMY, m_Camera.PixNumY);
	DDX_Text(pDX, IDC_BV_CAMPARAM_FOCLEN, m_Camera.FocalLength);
	DDX_Text(pDX, IDC_CAMPARAM_PRINCX, m_Camera.PrincipalPointX);
	DDX_Text(pDX, IDC_CAMPARAM_PRINCY, m_Camera.PrincipalPointY);
	DDX_Text(pDX, IDC_BV_CAMPARAM_PIXSIZEX, m_Camera.CellSizeX);
	DDX_Text(pDX, IDC_BV_CAMPARAM_PIXSIZEY, m_Camera.CellSizeY);
	//DDX_Text(pDX, IDC_BV_CAMPARAM_PICSIZEY, m_iPicSizeY);
	//DDX_Text(pDX, IDC_BV_CAMPARAM_PICSIZEX, m_iPicSizeX);
/*	DDX_Text(pDX, IDC_CAMPARAM_DIST1, m_Camera.DistortionParameters[0]);
	DDX_Text(pDX, IDC_CAMPARAM_DIST2, m_Camera.DistortionParameters[1]);
	DDX_Text(pDX, IDC_CAMPARAM_DIST3, m_Camera.DistortionParameters[2]);
	DDX_Text(pDX, IDC_CAMPARAM_DIST4, m_Camera.DistortionParameters[3]);
	DDX_Text(pDX, IDC_CAMPARAM_CAMMAT1, m_Camera.CameraMatrix[0]);
	DDX_Text(pDX, IDC_CAMPARAM_CAMMAT2, m_Camera.CameraMatrix[1]);
	DDX_Text(pDX, IDC_CAMPARAM_CAMMAT3, m_Camera.CameraMatrix[2]);
	DDX_Text(pDX, IDC_CAMPARAM_CAMMAT4, m_Camera.CameraMatrix[3]);
	DDX_Text(pDX, IDC_CAMPARAM_CAMMAT5, m_Camera.CameraMatrix[4]);
	DDX_Text(pDX, IDC_CAMPARAM_CAMMAT6, m_Camera.CameraMatrix[5]);
	DDX_Text(pDX, IDC_CAMPARAM_CAMMAT7, m_Camera.CameraMatrix[6]);
	DDX_Text(pDX, IDC_CAMPARAM_CAMMAT8, m_Camera.CameraMatrix[7]);
	DDX_Text(pDX, IDC_CAMPARAM_CAMMAT9, m_Camera.CameraMatrix[8]);*/
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlg_Camera, CDialog)
	//{{AFX_MSG_MAP(CDlg_Camera)
	ON_BN_CLICKED(IDC_BV_CAMPARAM_CALCFOCLEN, On_Calc_FocLen)
	//ON_EN_CHANGE(IDC_BV_CAMPARAM_PIXSIZEX, On_Calc_FocLen)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten CDlg_Camera 

//DEL void CDlg_Camera::On_CalcPixSize() 
//DEL {
//DEL 	// TODO: Code für die Behandlungsroutine der Steuerelement-Benachrichtigung hier einfügen
//DEL 	if(this->m_hWnd) UpdateData(1); //retrieve data from the dialog
//DEL 	m_dPixSizeX = m_CCDWidth / m_Camera.PixNumX;
//DEL 	m_dPixSizeY = m_CCDHeight / m_Camera.PixNumY;
//DEL 	if(this->m_hWnd) UpdateData(0); //update data to the dialog
//DEL 
//DEL }

//DEL void CDlg_Camera::On_LoadCalibData() 
//DEL {
//DEL 	CKAZApp* pApp = ((CKAZApp*)AfxGetApp());
//DEL 	SetCurrentDirectory(pApp->GetIniVerzeichnis());
//DEL 	m_pIniFile = pApp->m_Inifile_pCamera;
//DEL 	m_pIniFile->INI_LesenFileDialog();
//DEL 	for(int i=0;i<4;i++)
//DEL 		DistortionParameters[i] = m_pIniFile->m_Int_Dist[i];
//DEL 	for(i=0;i<9;i++)
//DEL 		m_Camera.CameraMatrix[i] = m_pIniFile->m_Int_CameraMat[i];
//DEL 	m_Camera.PixNumX = m_pIniFile->m_Int_ImageSize[0];
//DEL 	m_Camera.PixNumY = m_pIniFile->m_Int_ImageSize[1];
//DEL 	m_Camera.PrincipalPointX = m_pIniFile->m_Int_CameraMat[2];
//DEL 	m_Camera.PrincipalPointY = m_pIniFile->m_Int_CameraMat[5];
//DEL 	UpdateData(0); // show new data in dialog
//DEL 	On_Calc_FocLen();	
//DEL 
//DEL }

void CDlg_Camera::On_Calc_FocLen()
{
	double tmp;
	tmp = m_Camera.CameraMatrix[0] * m_Camera.CellSizeX;
	UpdateData(1); // get new data from dialog
	m_Camera.FocalLength = m_Camera.CameraMatrix[0] * m_Camera.CellSizeX / 1000.0;
	UpdateData(0); // show new data in dialog

}

void CDlg_Camera::Set_Data(double* CameraMat, double* Distortion, double* CellSize, int* PicSize )
{
	for(int i=0; i<9;i++)
		m_Camera.CameraMatrix[i] = CameraMat[i];
	for(i=0;i<4;i++)
		m_Camera.DistortionParameters[i] = Distortion[i];
	m_Camera.CellSizeX = CellSize[0];
	m_Camera.CellSizeY = CellSize[1];
	m_Camera.PixNumX = PicSize[0];
	m_Camera.PixNumY = PicSize[1];

	m_Camera.FocalLength = CameraMat[0] * m_Camera.CellSizeX / 1000;
	m_Camera.PrincipalPointX = CameraMat[2];
	m_Camera.PrincipalPointY = CameraMat[5];

}

 void CDlg_Camera::OnOK()
 {
 	UpdateData(1);
 
 	m_pIniFile->Set_FocLen(m_Camera.FocalLength);
 	m_pIniFile->Set_CameraMat(m_Camera.CameraMatrix);
 	m_pIniFile->Set_CellSize(m_Camera.CellSizeX,m_Camera.CellSizeY);
 	m_pIniFile->Set_DistortionVec(m_Camera.DistortionParameters);
 
 	CDialog::OnOK();
 }


void CDlg_Camera::On_LoadCalibData() 
{
	if(!m_pIniFile->INI_Lesen()){
		AfxMessageBox("Die Camera.ini Datei konnte nicht geöffnet werden."); return;}
	for(int i=0;i<4;i++)
		m_Camera.DistortionParameters[i] = m_pIniFile->m_Int_Dist[i];
	for(i=0;i<9;i++)
		m_Camera.CameraMatrix[i] = m_pIniFile->m_Int_CameraMat[i];
	m_Camera.FocalLength = m_pIniFile->m_Int_FocLen[0];
	m_Camera.PixNumX = m_pIniFile->m_Int_ImageSize[0];
	m_Camera.PixNumY = m_pIniFile->m_Int_ImageSize[1];
	m_Camera.PrincipalPointX = m_pIniFile->m_Int_PrincPt[0];
	m_Camera.PrincipalPointY = m_pIniFile->m_Int_PrincPt[1];
	m_Camera.CellSizeX = m_pIniFile->Get_CellSizeX();
	m_Camera.CellSizeY = m_pIniFile->Get_CellSizeY();
	//UpdateData(0); // show new data in dialog
//	On_Calc_FocLen();	

}
