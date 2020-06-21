/* ----------------------------------------------------------------------- *
 * G L S a m p l e 4 V i e w . h
 *
 * interface of the CDisp_3D_View class
 *
 * Copyright 1996 by Interface Technologies, Inc. All Rights Reserved.
 * 3D Authored by N. Alan Oursland
 * ----------------------------------------------------------------------- */

#ifndef _3DVIEW_H
#define _3DVIEW_H

#include "Disp_3D_Doc.h"
#include "resource.h"




class CDisp_3D_View : public CView
{
public:

// Operations
	CDisp_3D_View();
	DECLARE_DYNCREATE(CDisp_3D_View)

	BOOL CreateViewGLContext(HDC hDC);
	BOOL SetWindowPixelFormat(HDC hDC);
	void FitWindow(int width, int height);

// Attributes
	int m_GLPixelIndex,m_timer;
	HGLRC m_hGLContext;
	bool m_Mode_Calibration;

public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDisp_3D_View)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual CDisp_3D_Doc* GetDocument();
	protected:
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CDisp_3D_View();
#ifdef _DEBUG
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CDisp_3D_View)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnPaint();
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnDlg_3D();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnCalibrate_Onestep();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
#ifndef _DEBUG  // debug version in Disp_3D_View.cpp
inline CDisp_3D_Doc* CDisp_3D_View::GetDocument()
   { return (CDisp_3D_Doc*)m_pDocument; }
#endif

#endif 



/////////////////////////////////////////////////////////////////////////////
