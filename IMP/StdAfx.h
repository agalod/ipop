// stdafx.h : Include-Datei f�r Standard-System-Include-Dateien,
//  oder projektspezifische Include-Dateien, die h�ufig benutzt, aber
//      in unregelm��igen Abst�nden ge�ndert werden.
//

#if !defined(AFX_STDAFX_H__B725BA35_9109_4A64_B8D4_2935E58A7E3C__INCLUDED_)
#define AFX_STDAFX_H__B725BA35_9109_4A64_B8D4_2935E58A7E3C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define VC_EXTRALEAN		// Selten benutzte Teile der Windows-Header nicht einbinden

#include <afx.h>
#include <afxwin.h>

#define HAVE_IPL
//#include "DIB.h"
#include "cv.h"
#include "cvtypes.h"
#include "highgui.h"

#include "gcvision.h"
using namespace gcvision;

#include <cmath> 
#include <list>
#include <vector>
#include <math.h>
#include <stdlib.h>
#include "iostream.h"
using namespace std; 

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

// ZU ERLEDIGEN: Verweisen Sie hier auf zus�tzliche Header-Dateien, die Ihr Programm ben�tigt

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ f�gt zus�tzliche Deklarationen unmittelbar vor der vorherigen Zeile ein.

#endif // !defined(AFX_STDAFX_H__B725BA35_9109_4A64_B8D4_2935E58A7E3C__INCLUDED_)
