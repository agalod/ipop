// stdafx.h : Include-Datei f�r Standard-System-Include-Dateien,
//  oder projektspezifische Include-Dateien, die h�ufig benutzt, aber
//      in unregelm��igen Abst�nden ge�ndert werden.
//

#if !defined(AFX_STDAFX_H__6FF144B2_E2AB_4BED_98EC_E6528DA72F61__INCLUDED_)
#define AFX_STDAFX_H__6FF144B2_E2AB_4BED_98EC_E6528DA72F61__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define VC_EXTRALEAN		// Selten verwendete Teile der Windows-Header nicht einbinden

#include <afxadv.h>			// f�r CRecentFileList
#include <afxtempl.h>		// f�r CList, CArray, ...
#include <afxwin.h>         // MFC-Kern- und -Standardkomponenten
#include <afxext.h>         // MFC-Erweiterungen
#include <afxdisp.h>        // MFC Automatisierungsklassen
#include <afxdtctl.h>		// MFC-Unterst�tzung f�r allgemeine Steuerelemente von Internet Explorer 4
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>			// MFC-Unterst�tzung f�r g�ngige Windows-Steuerelemente
#endif // _AFX_NO_AFXCMN_SUPPORT


#include <gl\gl.h>	//OpenGL
#include <gl\glu.h>	//OpenGL

#include <cmath> 
#include <list>
#include <vector>
#include <math.h>
#include <stdlib.h>
#include "iostream.h"

#include "D3DUTILS.h"
#include "matlab.h"

#include "ltiImage.h"
#include "ltiLoadImageList.h"
#include "ltiExternViewer.h"
#include "ltiThresholding.h"
#include "ltiCannyEdges.h"
#include "ltiOrientedHLTransform.h"


#include "DIB.h"
#include "IPOP.h"
#include "ImageServer.h"

using namespace d3d;
using namespace std; 





//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ f�gt unmittelbar vor der vorhergehenden Zeile zus�tzliche Deklarationen ein.

#endif // !defined(AFX_STDAFX_H__6FF144B2_E2AB_4BED_98EC_E6528DA72F61__INCLUDED_)
