// stdafx.h : Include-Datei f�r Standard-System-Include-Dateien,
//  oder projektspezifische Include-Dateien, die h�ufig benutzt, aber
//      in unregelm��igen Abst�nden ge�ndert werden.
//

#if !defined(AFX_STDAFX_H__81558722_CBE4_491F_BBE9_3A0F3ABB4CFB__INCLUDED_)
#define AFX_STDAFX_H__81558722_CBE4_491F_BBE9_3A0F3ABB4CFB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define VC_EXTRALEAN		// Selten benutzte Teile der Windows-Header nicht einbinden

#include <afx.h>
#include <afxwin.h>
#include <afxtempl.h>		// f�r CList, CArray, ...
#include <afxext.h>         // MFC-Erweiterungen

#include <vector>
using namespace std;

#define HAVE_IPL
#include "cv.h"
#include "highgui.h"
#include "ltiImage.h"


// ZU ERLEDIGEN: Verweisen Sie hier auf zus�tzliche Header-Dateien, die Ihr Programm ben�tigt

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ f�gt zus�tzliche Deklarationen unmittelbar vor der vorherigen Zeile ein.

#endif // !defined(AFX_STDAFX_H__81558722_CBE4_491F_BBE9_3A0F3ABB4CFB__INCLUDED_)
