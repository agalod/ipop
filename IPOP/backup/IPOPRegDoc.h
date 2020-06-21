// IPOPDoc.h : Schnittstelle der Klasse CIPOPRegDoc
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_IPOPDOC_H__04E950DD_6D0E_4E58_A740_9440B28E0D7E__INCLUDED_)
#define AFX_IPOPDOC_H__04E950DD_6D0E_4E58_A740_9440B28E0D7E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ImageServer.h"


class CIPOPRegDoc : public CDocument
{
protected: // Nur aus Serialisierung erzeugen
	CIPOPRegDoc();
	DECLARE_DYNCREATE(CIPOPRegDoc)

// Attribute
public:

// Operationen
public:

// Überladungen
	// Vom Klassenassistenten generierte Überladungen virtueller Funktionen
	//{{AFX_VIRTUAL(CIPOPRegDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

	D3DVECTORPAIR *m_pRegPointPair;
// Implementierung
public:
	CImageServer* GetImageServer();
	virtual ~CIPOPRegDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	CImageServer m_ImageServer;

// Generierte Message-Map-Funktionen
protected:
	//{{AFX_MSG(CIPOPRegDoc)
		// HINWEIS - An dieser Stelle werden Member-Funktionen vom Klassen-Assistenten eingefügt und entfernt.
		//    Innerhalb dieser generierten Quelltextabschnitte NICHTS VERÄNDERN!
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // !defined(AFX_IPOPDOC_H__04E950DD_6D0E_4E58_A740_9440B28E0D7E__INCLUDED_)
