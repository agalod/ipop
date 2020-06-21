// ChildFrm.h : Schnittstelle der Klasse CChildFrame
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_CHILDFRM_H__B8CD8594_20B8_4E72_AFB8_99561DD89108__INCLUDED_)
#define AFX_CHILDFRM_H__B8CD8594_20B8_4E72_AFB8_99561DD89108__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CChildFrame : public CMDIChildWnd
{
	DECLARE_DYNCREATE(CChildFrame)
public:
	CChildFrame();
 
// Attribute
public:

// Operationen
public:

// Überladungen
	// Vom Klassenassistenten generierte Überladungen virtueller Funktionen
	//{{AFX_VIRTUAL(CChildFrame)
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

// Implementierung
public:
	virtual ~CChildFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

// Generierte Message-Map-Funktionen
protected:
	//{{AFX_MSG(CChildFrame)
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // !defined(AFX_CHILDFRM_H__B8CD8594_20B8_4E72_AFB8_99561DD89108__INCLUDED_)
