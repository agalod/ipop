///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
//-----------------------------------------------------------------------------
// Written by cand.ing. Alexander M.Roehnisch @ WZL-RWTH, Aachen, Germany, 2005
//-----------------------------------------------------------------------------
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
#if !defined(AFX_LIVEDOC_H__67CAF089_4406_420B_89EC_B2E246A2C55D__INCLUDED_)
#define AFX_LIVEDOC_H__67CAF089_4406_420B_89EC_B2E246A2C55D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Disp_Live_Doc.h : Header-Datei
//
#include "IMG_VFW.h"
//#include "IMG_DSHOW.h"
#include "IMG_PXC.h"
/////////////////////////////////////////////////////////////////////////////
// Dokument CDisp_Live_Doc 

class CDisp_Live_Doc : public CDocument
{
protected:
	CDisp_Live_Doc();           // Dynamische Erstellung verwendet geschützten Konstruktor
	DECLARE_DYNCREATE(CDisp_Live_Doc)

// Attribute
public:
	IMG_VFW m_Grabber_VFW;
	//IMG_DSHOW m_Grabber_DSHOW;
	IMG_PXC *m_Grabber_PXC;
// Operationen
public:

// Überschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktionsüberschreibungen
	//{{AFX_VIRTUAL(CDisp_Live_Doc)
	public:
	virtual void Serialize(CArchive& ar);   // Überschrieben für Dokument-Ein-/Ausgabe
	virtual void OnCloseDocument();
	protected:
	virtual BOOL OnNewDocument();
	//}}AFX_VIRTUAL

// Implementierung
public:
	IMG *m_Grabber;
	virtual ~CDisp_Live_Doc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generierte Nachrichtenzuordnungsfunktionen
protected:
	//{{AFX_MSG(CDisp_Live_Doc)
		// HINWEIS - Der Klassen-Assistent fügt hier Member-Funktionen ein und entfernt diese.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // AFX_LIVEDOC_H__67CAF089_4406_420B_89EC_B2E246A2C55D__INCLUDED_
