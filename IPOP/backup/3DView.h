/* ----------------------------------------------------------------------- *
 * G L S a m p l e 4 V i e w . h
 *
 * interface of the C3DView class
 *
 * Copyright 1996 by Interface Technologies, Inc. All Rights Reserved.
 * 3D Authored by N. Alan Oursland
 * ----------------------------------------------------------------------- */

#ifndef _3DVIEW_H
#define _3DVIEW_H

#include "3DDoc.h"
#include "resource.h"




class C3DView : public CView
{
public:

// Operations
	C3DView();
	DECLARE_DYNCREATE(C3DView)

	BOOL CreateViewGLContext(HDC hDC);
	BOOL SetWindowPixelFormat(HDC hDC);

// Attributes
	int m_GLPixelIndex,m_timer;
	HGLRC m_hGLContext;

public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(C3DView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual C3DDoc* GetDocument();
	protected:
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~C3DView();
#ifdef _DEBUG
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(C3DView)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnPaint();
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void On3DDialog();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnCalibrate_Onestep();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
#ifndef _DEBUG  // debug version in 3DView.cpp
inline C3DDoc* C3DView::GetDocument()
   { return (C3DDoc*)m_pDocument; }
#endif

#endif 



/////////////////////////////////////////////////////////////////////////////
