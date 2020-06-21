// MtqCamCalibDoc.h : Schnittstelle der Klasse CImageServer
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MTQCAMCALIBDOC_H__099F2DAA_69C0_11D7_8BDF_0000F4C3D5FS__INCLUDED_)
#define AFX_MTQCAMCALIBDOC_H__099F2DAA_69C0_11D7_8BDF_0000F4C3D5FS__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <vector>
using namespace std;

#define HAVE_IPL
#include "cv.h"
#include "highgui.h"

#include "ltiImage.h"
#include "ltiALLFunctor.h" 

#include "DIB.h"


typedef CList <CImage*,CImage*&> CListImage;



class CImageServer
{
public:
	IplImage* CList_GetCurrentImageAsIPL();
	void CList_GetAtImageAsLTI(const int &index);
	CImageServer();
	~CImageServer();
		
	CStringArray	m_CListNames;
	CListImage		m_CListImage;
	//CDIB			m_WindowsDIB;
	//CImage*			m_CImg; 
	POSITION			m_pos;
	int m_ImageIndex;
		// Implementierung
	void		CList_GetCurrentImage_GreyIPL();
	void		CList_SaveCurrentImage();
	CString		CList_GetCurrentImageName();
	void		CList_AppendImage(lti::channel aImg, CString ImgName);
	void		CList_AppendImage(IplImage aImg, CString ImgName);
	lti::channel CList_GetCurrentImageAsLTI();
	lti::channel CList_GetCurrentImageAsLTI(const int &relindex);
	int 	Image_Width() { return (CList_GetCurrentImage())->Width(); }
	int 	Image_Height() { return CList_GetCurrentImage()->Height(); }
	
	
	void			CList_DeleteCurrImage();
	void			CList_BrowseBackward();
	void			CList_BrowseForward();
	void			CList_SaveAsBmps() ;
	void			CList_SetAtPos( POSITION position, CImage* aImage) 	{ m_CListImage.SetAt( position, aImage); }
	void			CList_AppendImage(  CImage*, CString ImgName );
	void			CList_AppendImageCopy(  CImage*, CString ImgName );
	void			CList_RemoveAll() { m_CListImage.RemoveAll(); }
	int				CList_GetIndex();
	int				CList_GetCount();
	CImage*		CList_GetCurrentImage() { return m_CListImage.GetAt(m_pos);}

	//void Image_ConvertToCxImage(CImage aIplImg, CxImage& aCxImg);
	//	ImageVec::iterator m_iterator; // Iterator Left ( wandert von links nach rechts )
	//ImageVec			m_VecImage; 
	
	// Überladungen
	// Vom Klassenassistenten generierte Überladungen virtueller Funktionen
	//{{AFX_VIRTUAL(CImageServer)
public:
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL
	
#ifdef _DEBUG
#endif
	
protected:
	void FreeCListImage(CListImage &aCListImage);
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // !defined(AFX_MTQCAMCALIBDOC_H__099F2DAA_69C0_11D7_8BDF_0000F4C3D5FS__INCLUDED_)
