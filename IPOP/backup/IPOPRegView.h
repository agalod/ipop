// IPOPRegView.h : Schnittstelle der Klasse CIPOPRegView
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_IPOPRegView_H__406BB4FE_509E_4311_9380_1DB09FB21528__INCLUDED_)
#define AFX_IPOPRegView_H__406BB4FE_509E_4311_9380_1DB09FB21528__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000




class CIPOPRegView : public CView
{
protected: // Nur aus Serialisierung erzeugen
	CIPOPRegView();
	DECLARE_DYNCREATE(CIPOPRegView)

// Attribute
public:
	CIPOPRegDoc* GetDocument();
	void FitWindow(int width, int height);
    enum color {  red=0, green=1, blue=2 };
	void DC_DrawLine(CPoint&, CPoint&, int Farbe=0);
	void DC_DrawCircle(CPoint&, CPoint&);
	void DC_DrawCoordinate(CPoint& Point);
	void DC_DrawPoint(CPoint Point, const color num);
	void DC_DrawIndex(CPoint& Point, int aIdx);

// Operationen
public:
	int m_ptidx;

// Überladungen
	// Vom Klassenassistenten generierte Überladungen virtueller Funktionen
	//{{AFX_VIRTUAL(CIPOPRegView)
	public:
	virtual void OnDraw(CDC* pDC);  // überladen zum Zeichnen dieser Ansicht
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementierung
public:
	virtual ~CIPOPRegView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generierte Message-Map-Funktionen
protected:
	//{{AFX_MSG(CIPOPRegView)
	afx_msg void OnCalibrate_Init();
	afx_msg void OnRegister();
	afx_msg void On_ViewBack();
	afx_msg void On_ViewForward();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnSysKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnRegIpBinarize();
	afx_msg void OnRegIpHough();
	afx_msg void OnRegIpEdge();
	afx_msg void OnRegistrierenVorverarbeitung();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // Testversion in IPOPRegView.cpp
inline CIPOPRegDoc* CIPOPRegView::GetDocument()
   { return (CIPOPRegDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // !defined(AFX_IPOPRegView_H__406BB4FE_509E_4311_9380_1DB09FB21528__INCLUDED_)
