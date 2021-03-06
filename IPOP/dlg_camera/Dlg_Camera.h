#if !defined(AFX_BV_CAMPARAMDIALOG_H__0CE86C4F_1705_4D06_A363_79D1AB552BB6__INCLUDED_)
#define AFX_BV_CAMPARAMDIALOG_H__0CE86C4F_1705_4D06_A363_79D1AB552BB6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// BV_CamParamDialog.h : Header-Datei
//

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CDlg_Camera 
#include "resource.h"

class CDlg_Camera : public CDialog
{
// Konstruktion
public:
	void OnOK();
	void Set_Data(double* CameraMat, double* Distortion, double* CellSize, int* PicSize);
	CDlg_Camera(CWnd* pParent = NULL);   // Standardkonstruktor

// Dialogfelddaten
	//{{AFX_DATA(CDlg_Camera)
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

// Überschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktionsüberschreibungen
	//{{AFX_VIRTUAL(CDlg_Camera)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
	//}}AFX_VIRTUAL

// Implementierung
protected:

	// Generierte Nachrichtenzuordnungsfunktionen
	//{{AFX_MSG(CDlg_Camera)
	afx_msg void On_LoadCalibData();
	afx_msg void On_Calc_FocLen();
	afx_msg void On_Change_FocLen();

	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // AFX_BV_CAMPARAMDIALOG_H__0CE86C4F_1705_4D06_A363_79D1AB552BB6__INCLUDED_
