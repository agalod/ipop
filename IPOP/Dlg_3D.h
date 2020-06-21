///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
//-----------------------------------------------------------------------------
// Written by cand.ing. Alexander M.Roehnisch @ WZL-RWTH, Aachen, Germany, 2005
//-----------------------------------------------------------------------------
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
#if !defined(AFX_3DDIALOG_H__C55A015D_0322_46A5_A622_594C3A238540__INCLUDED_)
#define AFX_3DDIALOG_H__C55A015D_0322_46A5_A622_594C3A238540__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Dlg_3D.h : Header-Datei
//
// Written by Alexander M.Roehnisch at WZL-RWTH, Aachen, Germany, 2005
#include "Disp_3D_Doc.h"
#include "resource.h"
/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CDlg_3D 

class CDlg_3D : public CDialog
{
// Konstruktion
public:
	CDlg_3D(CWnd* pParent = NULL);   // Standardkonstruktor
	CDisp_3D_Doc* m_Disp_3D_pDoc;
	//MtqMatrix<double> m_RotationMatrix;

// Dialogfelddaten
	//{{AFX_DATA(CDlg_3D)
	enum { IDD = IDD_Disp_3D_View };
	BOOL	m_bPerspFront;
	BOOL	m_bPerspBack;
	BOOL	m_bPerspLeft;
	BOOL	m_bPerspRight;
	BOOL	m_bDraw_ProjRays;
	BOOL	m_bDraw_CalPoints;
	BOOL	m_bDraw_Distances;
	//}}AFX_DATA


// Überschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktionsüberschreibungen
	//{{AFX_VIRTUAL(CDlg_3D)
	public:
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
	//}}AFX_VIRTUAL

// Implementierung
public:

	// Generierte Nachrichtenzuordnungsfunktionen
	//{{AFX_MSG(CDlg_3D)
	afx_msg void On3dPerspFront();
	afx_msg void On3dPerspLeft();
	afx_msg void On3dPerspRight();
	afx_msg void On3dPerspBack();
	afx_msg void On3dDrawProjrays();
	afx_msg void On3dDrawCalpoints();
	afx_msg void On3dDrawDistances();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // AFX_3DDIALOG_H__C55A015D_0322_46A5_A622_594C3A238540__INCLUDED_
