// stdafx.h : Include-Datei für Standard-System-Include-Dateien,
//  oder projektspezifische Include-Dateien, die häufig benutzt, aber
//      in unregelmäßigen Abständen geändert werden.
//

#if !defined(AFX_STDAFX_H__6FF144B2_E2AB_4BED_98EC_E6528DA72F61__INCLUDED_)
#define AFX_STDAFX_H__6FF144B2_E2AB_4BED_98EC_E6528DA72F61__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define VC_EXTRALEAN		// Selten verwendete Teile der Windows-Header nicht einbinden
//#define REGISTER_FILTERGRAPH 
//#define D3DVECTOR_DEFINED
//#define D3DMATRIX_DEFINED
//#define DX_SHARED_DEFINES
  

#pragma warning( disable : 4786 )
#pragma warning( disable : 4183 )

#include <afxadv.h>			// für CRecentFileList
#include <afxtempl.h>		// für CList, CArray, ...
#include <afxwin.h>         // MFC-Kern- und -Standardkomponenten
#include <afxext.h>         // MFC-Erweiterungen
#include <afxdisp.h>        // MFC Automatisierungsklassen
#include <afxdtctl.h>		// MFC-Unterstützung für allgemeine Steuerelemente von Internet Explorer 4
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>			// MFC-Unterstützung für gängige Windows-Steuerelemente
#endif // _AFX_NO_AFXCMN_SUPPORT


#include "gcvision.h"
using namespace gcvision;

//#include <dshow.h>
//#include <atlbase.h>
//#include <atlstr.h>
//#include "qedit.h"
//#include "dshowutil.cpp"
//#include <mtype.h>
//#include <reftime.h>
//#include "dshowutil.cpp"
 

#include <gl\gl.h>	//OpenGL
#include <gl\glu.h>	//OpenGL

#include <cmath> 
#include <list>
#include <vector>
#include <math.h>
#include <stdlib.h>
#include "iostream.h"
using namespace std; 

//#include "matlab.h"

#include "ltiImage.h"
#include "ltiLoadImageList.h"
#include "ltiExternViewer.h"
#include "ltiThresholding.h"
#include "ltiCannyEdges.h"
#include "ltiOrientedHLTransform.h"
#include <ltiGHoughTransform.h> 
#include "ltiSVD.h"
#include "ltiMatrix.h" 
#include "ltiVector.h" 
#include "ltiPoint.h"
#include <ltiCannyEdges.h> 
#include "ltiOrientedHLTransform.h"
#include "ltiGeometry.h "
#include <ltiHistograming1D.h>
#include <ltiHistogram.h>
#include <ltiConvolution.h>
#include <ltiErosion.h>
#include <ltiDilation.h>
#include <ltiLinearKernels.h>
#include <ltiRegionGrowing.h>

#define HAVE_IPL
#include "DIB.h"
#include "cv.h"
#include "highgui.h"


//#include <wia.h>




//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // !defined(AFX_STDAFX_H__6FF144B2_E2AB_4BED_98EC_E6528DA72F61__INCLUDED_)
