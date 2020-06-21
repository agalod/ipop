#if !defined(AFX_3DDIALOG_H__C55A015D_0322_46A5_A622_594C3A238540__INCLUDED_)
#define AFX_3DDIALOG_H__C55A015D_0322_46A5_A622_594C3A238540__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// 3DDialog.h : Header-Datei
//
#include "IPOP3DDoc.h"
#include "resource.h"
//#include "IPOP3DView.h"
#include "IPOP3DDoc.h"

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CIPOP3DDialog 

class CIPOP3DDialog : public CDialog
{     
// Konstruktion
public:
	CIPOP3DDialog(CWnd* pParent = NULL);   // Standardkonstruktor
	CIPOP3DView* m_Display_3D_pView;
	CIPOP3DDoc* m_Display_3D_pDoc;
	D3DMATRIX m_RotationMatrix;

// Dialogfelddaten
	//{{AFX_DATA(CIPOP3DDialog)
	enum { IDD = IDD_3DView };
	BOOL	m_bPerspFront;
	BOOL	m_bPerspCamera;
	BOOL	m_bPerspLeft;
	BOOL	m_bPerspRight;
	//}}AFX_DATA


// Überschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktionsüberschreibungen
	//{{AFX_VIRTUAL(CIPOP3DDialog)
	public:
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
	//}}AFX_VIRTUAL

// Implementierung
public:
	void Set3DViewAndDoc(CIPOP3DView* pView, CIPOP3DDoc* pDoc);

	// Generierte Nachrichtenzuordnungsfunktionen
	//{{AFX_MSG(CIPOP3DDialog)
	afx_msg void On3dPerspFront();
	afx_msg void On3dPerspCamera();
	afx_msg void On3dPerspLeft();
	afx_msg void On3dPerspRight();
	afx_msg void On3dPerspBack();
	afx_msg void On3dPerspStart();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // AFX_3DDIALOG_H__C55A015D_0322_46A5_A622_594C3A238540__INCLUDED_
