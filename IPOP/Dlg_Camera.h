///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
//-----------------------------------------------------------------------------
// Written by cand.ing. Alexander M.Roehnisch @ WZL-RWTH, Aachen, Germany, 2005
//-----------------------------------------------------------------------------
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
#if !defined(AFX_Dlg_Camera_H__0CE86C4F_1705_4D06_A363_79D1AB552BB6__INCLUDED_)
#define AFX_Dlg_Camera_H__0CE86C4F_1705_4D06_A363_79D1AB552BB6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Dlg_Camera.h : Header-Datei
//

#include "resource.h"
#include "Ini_Camera.h"


/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CDlg_Camera 



class CDlg_Camera : public CDialog
{
// Konstruktion
public:
	void File_Save();
	double File_ReadLine(const CString &line);
	void File_Load();
	void Set_Data(double* CameraMat, double* Distortion, double* CellSize, int* PicSize);
	CDlg_Camera(CWnd* pParent = NULL);   // Standardkonstruktor

	CStdioFile		m_File;
	CString m_Ini_Verzeichnis;

// Dialogfelddaten
	//{{AFX_DATA(CDlg_Camera)
	enum { IDD = IDD_DLG_CAMPARAMS };
/*	double	m_FocusLength;
	int		m_PixNumX;
	int		m_PixNumY;
	double	m_dPrincipalPtX;
	double	m_dPrincipalPtY;
	double	m_dCellSizeX;
	double	m_dCellSizeY;
	double	m_dDistortion[4];
	double	m_dCameraMat[9];*/
	GCV_CAMERA* m_Camera;
	//}}AFX_DATA
	//CIni_Camera*	m_pIniFile; 

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
	afx_msg void On_Calc_FocLen();
	afx_msg void On_Change_FocLen();
	afx_msg void OnKillFocus(CWnd* pNewWnd);

	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // AFX_Dlg_Camera_H__0CE86C4F_1705_4D06_A363_79D1AB552BB6__INCLUDED_
