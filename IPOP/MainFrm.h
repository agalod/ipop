// MainFrm.h : Schnittstelle der Klasse CMainFrame
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MAINFRM_H__DF15FB18_F51A_465C_88C3_35551F8AD847__INCLUDED_)
#define AFX_MAINFRM_H__DF15FB18_F51A_465C_88C3_35551F8AD847__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CMainFrame : public CMDIFrameWnd
{
	DECLARE_DYNAMIC(CMainFrame)
public:
	CMainFrame();

// Attribute
public:

// Operationen
public:

// Überladungen
	// Vom Klassenassistenten generierte Überladungen virtueller Funktionen
	//{{AFX_VIRTUAL(CMainFrame)
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

// Implementierung
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // Eingebundene Elemente der Steuerleiste
	CStatusBar  m_wndStatusBar;
	CToolBar    m_wndToolBar;

// Generierte Message-Map-Funktionen
protected:
	//{{AFX_MSG(CMainFrame)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnFileOpen();
	afx_msg void OnCamParams();
	afx_msg void OnLastPic();
	afx_msg void OnChessbParams();
	afx_msg void OnPoseDlg();
	afx_msg void OnMfrmOpenCalimage();
	afx_msg void OnMfrmOpenRegimage();
	afx_msg void OnIpparams();
	afx_msg void OnVideoStart();
	afx_msg void OnVideoGrabframe();
	afx_msg void OnVideoSnapandreg();
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // !defined(AFX_MAINFRM_H__DF15FB18_F51A_465C_88C3_35551F8AD847__INCLUDED_)
