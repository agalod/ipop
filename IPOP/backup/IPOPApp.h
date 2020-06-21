// IPOPApp.h : Haupt-Header-Datei für die Anwendung IPOP
//

#if !defined(AFX_IPOP_H__DF5D1CC2_AF63_470F_A847_563C27A893B9__INCLUDED_)
#define AFX_IPOP_H__DF5D1CC2_AF63_470F_A847_563C27A893B9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // Hauptsymbole
//#include "IPOP3DView.h"
//#include "IPOP3DDoc.h"
#include "IPOPDoc.h"
#include "IPOPView.h"
//#include "IPOP3DDoc.h"
#include "3DView.h"
#include "3DDoc.h"

#include "IPOPCameraDlg.h"
#include "CheckBoardDialog.h"

/////////////////////////////////////////////////////////////////////////////
// CIPOPApp:
// Siehe IPOP.cpp für die Implementierung dieser Klasse
//

class CIPOPApp : public CWinApp
{
public:
	void Calc_Calibrate_OneStep();
	D3DCAMERA GetCameraStruct();
	void SetUp3DView();
	void Create3DView();
	void Calc_Calibrate_Init();
	CRecentFileList* GetRecentFileList();
	CIPOPApp(); 
	void LoadBmps();
	void LoadBmp(CString str);
	void CreatePicView();

// Überladungen
	// Vom Klassenassistenten generierte Überladungen virtueller Funktionen
	//{{AFX_VIRTUAL(CIPOPApp)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	//}}AFX_VIRTUAL

	C3DView*	m_Display_3D_pView;
	C3DDoc*		m_Display_3D_pDoc;

	CIPOPDoc*		m_Display_pPicDoc;
	CIPOPView*		m_Display_pPicView;

	CMultiDocTemplate*  m_Template_pPic;
	CMultiDocTemplate*	m_Template_p3D;

	CIPOPCameraDlg m_Dlg_CamParams;
	CCheckBoardDialog* m_Dlg_Calibration;

	CIPOP m_IPOP;


	//{{AFX_MSG(CIPOPApp)
	afx_msg void OnAppAbout();
	afx_msg void OnUpdateFileMruFile1(CCmdUI* pCmdUI);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // !defined(AFX_IPOP_H__DF5D1CC2_AF63_470F_A847_563C27A893B9__INCLUDED_)
