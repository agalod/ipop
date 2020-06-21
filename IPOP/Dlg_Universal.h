#if !defined(AFX_DLG_UNIVERSAL_H__CE1FDFDE_2EDD_4B5F_96BD_4E6E76615886__INCLUDED_)
#define AFX_DLG_UNIVERSAL_H__CE1FDFDE_2EDD_4B5F_96BD_4E6E76615886__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Dlg_Universal.h : Header-Datei
//

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CDlg_Universal 

#include "resource.h"

class CDlg_Universal : public CDialog
{
// Konstruktion
public:
	CDlg_Universal(CWnd* pParent = NULL);   // Standardkonstruktor

// Dialogfelddaten
	//{{AFX_DATA(CDlg_Universal)
	enum { IDD = IDD_DLG_UNIVERSAL };
	CString	m_Text1;
	CString	m_Text2;
	double	m_Edit1;
	double	m_Edit2;
	//}}AFX_DATA


// Überschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktionsüberschreibungen
	//{{AFX_VIRTUAL(CDlg_Universal)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
	//}}AFX_VIRTUAL

// Implementierung
protected:

	// Generierte Nachrichtenzuordnungsfunktionen
	//{{AFX_MSG(CDlg_Universal)
		// HINWEIS: Der Klassen-Assistent fügt hier Member-Funktionen ein
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // AFX_DLG_UNIVERSAL_H__CE1FDFDE_2EDD_4B5F_96BD_4E6E76615886__INCLUDED_
