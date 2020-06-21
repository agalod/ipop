#if !defined(AFX_CHECKBOARDDIALOG_H__765FA380_6A9C_11D7_8BE0_0000F4C3D5FC__INCLUDED_)
#define AFX_CHECKBOARDDIALOG_H__765FA380_6A9C_11D7_8BE0_0000F4C3D5FC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CheckBoardDialog.h : Header-Datei
//

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CCheckBoardDialog 


#include "resource.h"


class CCheckBoardDialog : public CDialog
{
// Konstruktion
public:
	vector < D3DVECTOR >& GetPointList();
	void UpdatePoints();
	void OnOK();
	CCheckBoardDialog(CWnd* pParent = NULL);   // Standardkonstruktor
	vector < D3DVECTOR > m_Points;
	D3DMATRIX m_InitTrafo;
// Dialogfelddaten
	//{{AFX_DATA(CCheckBoardDialog)
	enum { IDD = IDD_DLG_CHECKBOARD };
	int		m_iEtalonX;
	int		m_iEtalonY;
	float	m_fEtalon_Width;
	float	m_InitRotX;
	float	m_InitRotY;
	float	m_InitRotZ;
	float	m_InitTransX;
	float	m_InitTransY;
	float	m_InitTransZ;
	//}}AFX_DATA

// Überschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktionsüberschreibungen
	//{{AFX_VIRTUAL(CCheckBoardDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
	//}}AFX_VIRTUAL

// Implementierung
protected:

	// Generierte Nachrichtenzuordnungsfunktionen
	//{{AFX_MSG(CCheckBoardDialog)
	afx_msg void OnUpdate();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // AFX_CHECKBOARDDIALOG_H__765FA380_6A9C_11D7_8BE0_0000F4C3D5FC__INCLUDED_
