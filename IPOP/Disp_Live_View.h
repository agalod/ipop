///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
//-----------------------------------------------------------------------------
// Written by cand.ing. Alexander M.Roehnisch @ WZL-RWTH, Aachen, Germany, 2005
//-----------------------------------------------------------------------------
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
#if !defined(AFX_LIVEVIEW_H__709A5E5B_ABFD_4C01_A019_E5CC211BD220__INCLUDED_)
#define AFX_LIVEVIEW_H__709A5E5B_ABFD_4C01_A019_E5CC211BD220__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Disp_Live_View.h : Header-Datei
//

/////////////////////////////////////////////////////////////////////////////
// Ansicht CDisp_Live_View 

class CDisp_Live_View : public CView
{
protected:
	CDisp_Live_View();           // Dynamische Erstellung verwendet geschützten Konstruktor
	DECLARE_DYNCREATE(CDisp_Live_View)
	void FitWindow(int width, int height);

// Attribute
public:

// Operationen
public:

// Überschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktionsüberschreibungen
	//{{AFX_VIRTUAL(CDisp_Live_View)
	protected:
	virtual void OnDraw(CDC* pDC);      // Überschrieben zum Zeichnen dieser Ansicht
	//}}AFX_VIRTUAL

// Implementierung
protected:
	virtual ~CDisp_Live_View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generierte Nachrichtenzuordnungsfunktionen
public:
	bool Init_PXC();
	//{{AFX_MSG(CDisp_Live_View)
	afx_msg void OnPxcGrabFrame();
	afx_msg void OnPxcCam1();
	afx_msg void OnPxcCam2();
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // AFX_LIVEVIEW_H__709A5E5B_ABFD_4C01_A019_E5CC211BD220__INCLUDED_
