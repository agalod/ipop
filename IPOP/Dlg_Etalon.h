///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
//-----------------------------------------------------------------------------
// Written by cand.ing. Alexander M.Roehnisch @ WZL-RWTH, Aachen, Germany, 2005
//-----------------------------------------------------------------------------
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
#if !defined(AFX_DLG_ETALON_H__765FA380_6A9C_11D7_8BE0_0000F4C3D5FC__INCLUDED_)
#define AFX_DLG_ETALON_H__765FA380_6A9C_11D7_8BE0_0000F4C3D5FC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Dlg_Etalon.h : Header-Datei
//

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CDlg_Etalon 


#include "resource.h"


class CDlg_Etalon : public CDialog
{
// Konstruktion
public:
	vector < GCV_VECTOR3D >& GetPointList();
	void UpdatePoints();
	void OnOK();
	CDlg_Etalon(CWnd* pParent = NULL);   // Standardkonstruktor
	vector < GCV_VECTOR3D > m_Points;
// Dialogfelddaten
	//{{AFX_DATA(CDlg_Etalon)
	enum { IDD = IDD_DLG_CHECKBOARD };
	int		m_iEtalonX;
	int		m_iEtalonY;
	double	m_fEtalon_Width;
	//}}AFX_DATA

// Überschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktionsüberschreibungen
	//{{AFX_VIRTUAL(CDlg_Etalon)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
	//}}AFX_VIRTUAL

// Implementierung
protected:

	// Generierte Nachrichtenzuordnungsfunktionen
	//{{AFX_MSG(CDlg_Etalon)
	afx_msg void OnUpdate();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // AFX_Dlg_Etalon_H__765FA380_6A9C_11D7_8BE0_0000F4C3D5FC__INCLUDED_
