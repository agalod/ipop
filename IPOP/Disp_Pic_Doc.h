///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
//-----------------------------------------------------------------------------
// Written by cand.ing. Alexander M.Roehnisch @ WZL-RWTH, Aachen, Germany, 2005
//-----------------------------------------------------------------------------
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
// Disp_Pic_Doc.h : Schnittstelle der Klasse CDisp_Pic_Doc
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_IPOPDOC_H__04E950DD_6D0E_4E58_A740_9440B28E0D7D__INCLUDED_)
#define AFX_IPOPDOC_H__04E950DD_6D0E_4E58_A740_9440B28E0D7D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


#include "ImageServer.h"


class CDisp_Pic_Doc : public CImageServer, public CDocument
{
protected: // Nur aus Serialisierung erzeugen
	CDisp_Pic_Doc();
	DECLARE_DYNCREATE(CDisp_Pic_Doc)

// Attribute
public:

// Operationen
public:

// Überladungen
	// Vom Klassenassistenten generierte Überladungen virtueller Funktionen
	//{{AFX_VIRTUAL(CDisp_Pic_Doc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementierung
public:
	void Apply_Erosion();
	void Apply_FloodFill();
	void DeleteCurrentImage();
	void SetTitle();
	void Apply_Preprocess();
	void Apply_Hough();
	void Apply_Binarization();
	void Apply_Edgefilter();
    void Image_DefineGrid();
	virtual ~CDisp_Pic_Doc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	vector< GCV_VECTOR3D > fPts_Img;

	GCV_QUAD2D					m_Etalon_Corners;
	vector < GCV_VECTOR3D >	m_Etalon_Points_Camera;
	vector < GCV_POINT2D >		m_Etalon_Points_Image;	
	int *m_Etalon_Cols, *m_Etalon_Rows, m_Mode;
	GCV_LINE2D m_Workpiece_Points;
	vector <GCV_LINE2D> m_Lines;

protected:
	//CImageServer m_ImageServer;

// Generierte Message-Map-Funktionen
protected:
	//{{AFX_MSG(CDisp_Pic_Doc)
		// HINWEIS - An dieser Stelle werden Member-Funktionen vom Klassen-Assistenten eingefügt und entfernt.
		//    Innerhalb dieser generierten Quelltextabschnitte NICHTS VERÄNDERN!
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // !defined(AFX_IPOPDOC_H__04E950DD_6D0E_4E58_A740_9440B28E0D7D__INCLUDED_)
