#if !defined(AFX_BV_CAMPARAMDIALOG_H__0CE86C4F_1705_4D06_A363_79D1AB552BB6__INCLUDED_)
#define AFX_BV_CAMPARAMDIALOG_H__0CE86C4F_1705_4D06_A363_79D1AB552BB6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// BV_CamParamDialog.h : Header-Datei
//

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CIPOPCameraDlg 

class CIPOPCameraDlg : public CDialog
{
// Konstruktion
public:
	void OnOK();
	void Set_Data(double* CameraMat, double* Distortion, double* CellSize, int* PicSize);
	CIPOPCameraDlg(CWnd* pParent = NULL);   // Standardkonstruktor

// Dialogfelddaten
	//{{AFX_DATA(CIPOPCameraDlg)
	enum { IDD = IDD_BV_CAMERA_PARAM };
	double	m_FocusLength;
	int		m_PixNumX;
	int		m_PixNumY;
	double	m_dPrincipalPtX;
	double	m_dPrincipalPtY;
	double	m_dCellSizeX;
	double	m_dCellSizeY;
	double	m_dDistortion[4];
	double	m_dCameraMat[9];
	//}}AFX_DATA
	CIni_Camera*	m_pIniFile; 

// �berschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktions�berschreibungen
	//{{AFX_VIRTUAL(CIPOPCameraDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterst�tzung
	//}}AFX_VIRTUAL

// Implementierung
protected:

	// Generierte Nachrichtenzuordnungsfunktionen
	//{{AFX_MSG(CIPOPCameraDlg)
	afx_msg void On_LoadCalibData();
	afx_msg void On_Calc_FocLen();
	afx_msg void On_Change_FocLen();

	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ f�gt unmittelbar vor der vorhergehenden Zeile zus�tzliche Deklarationen ein.

#endif // AFX_BV_CAMPARAMDIALOG_H__0CE86C4F_1705_4D06_A363_79D1AB552BB6__INCLUDED_
