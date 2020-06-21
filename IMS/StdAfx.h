// stdafx.h : Include-Datei für Standard-System-Include-Dateien,
//  oder projektspezifische Include-Dateien, die häufig benutzt, aber
//      in unregelmäßigen Abständen geändert werden.
//

#if !defined(AFX_STDAFX_H__81558722_CBE4_491F_BBE9_3A0F3ABB4CFB__INCLUDED_)
#define AFX_STDAFX_H__81558722_CBE4_491F_BBE9_3A0F3ABB4CFB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define VC_EXTRALEAN		// Selten benutzte Teile der Windows-Header nicht einbinden

#include <afx.h>
#include <afxwin.h>
#include <afxtempl.h>		// für CList, CArray, ...
#include <afxext.h>         // MFC-Erweiterungen

#include <vector>
using namespace std;

#define HAVE_IPL
#include "cv.h"
#include "highgui.h"
#include "ltiImage.h"


// ZU ERLEDIGEN: Verweisen Sie hier auf zusätzliche Header-Dateien, die Ihr Programm benötigt

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt zusätzliche Deklarationen unmittelbar vor der vorherigen Zeile ein.

#endif // !defined(AFX_STDAFX_H__81558722_CBE4_491F_BBE9_3A0F3ABB4CFB__INCLUDED_)
