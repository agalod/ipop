///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
//-----------------------------------------------------------------------------
// Written by cand.ing. Alexander M.Roehnisch @ WZL-RWTH, Aachen, Germany, 2005
//-----------------------------------------------------------------------------
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
// Disp_Pic_View.h : Schnittstelle der Klasse CDisp_Pic_View
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_IPOPVIEW_H__406BB4FE_509E_4311_9380_1DB09FB21528__INCLUDED_)
#define AFX_IPOPVIEW_H__406BB4FE_509E_4311_9380_1DB09FB21528__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000



 class CDisp_Pic_View : public CView
{
protected: // Nur aus Serialisierung erzeugen
	CDisp_Pic_View();
	DECLARE_DYNCREATE(CDisp_Pic_View)

// Attribute
public:
	CDisp_Pic_Doc* GetDocument();
	void FitWindow(int width, int height);
    enum color {  red=0, green=1, blue=2 };
	void DC_DrawLine(CPoint&, CPoint&, int Farbe=0);
	void DC_DrawLine(GCV_LINE2D &line, int Farbe=0);
	void DC_DrawLine(GCV_LINE3D &line, int Farbe=0);
	void DC_DrawLine(GCV_POINT2D Pt1, GCV_POINT2D Pt2, int Farbe );
	void DC_DrawCircle(CPoint&, CPoint&);
	void DC_DrawCoordinate(CPoint& Point);
	void DC_DrawPoint(CPoint Point, const color num);
	void DC_DrawPoint(GCV_POINT2D& Point, const color num);
	void DC_DrawPoint(GCV_VECTOR3D& Point, const color num);
	void DC_DrawIndex(CPoint& Point, int aIdx);
	void DC_DrawIndex(GCV_POINT2D& Point, int aIdx);
	void DC_DrawIndex(GCV_VECTOR3D& Point, int aIdx);

// Operationen
public:
	int m_ptidx;

// Überladungen
	// Vom Klassenassistenten generierte Überladungen virtueller Funktionen
	//{{AFX_VIRTUAL(CDisp_Pic_View)
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
	virtual ~CDisp_Pic_View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generierte Message-Map-Funktionen
protected:
	//{{AFX_MSG(CDisp_Pic_View)
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
	afx_msg void OnRegIPPreprocess();
	afx_msg void OnViewModek();
	afx_msg void OnViewModer();
	afx_msg void OnPicviewSavebmp();
	afx_msg void OnRegErosion();
	afx_msg void OnRegFloodfill();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // Testversion in Disp_Pic_View.cpp
inline CDisp_Pic_Doc* CDisp_Pic_View::GetDocument()
   { return (CDisp_Pic_Doc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // !defined(AFX_IPOPVIEW_H__406BB4FE_509E_4311_9380_1DB09FB21528__INCLUDED_)
