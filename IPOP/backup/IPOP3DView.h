// IPOP3DView.h: Schnittstelle für die Klasse CIPOP3DView.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_IPOP3DVIEW_H__36193A07_745A_4E02_85AF_0DCA730D2C87__INCLUDED_)
#define AFX_IPOP3DVIEW_H__36193A07_745A_4E02_85AF_0DCA730D2C87__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "3DView.h"

class CIPOP3DView : public C3DView  
{
public:
	void OnDestroy();
	CIPOP3DView();
	virtual ~CIPOP3DView();

};

#endif // !defined(AFX_IPOP3DVIEW_H__36193A07_745A_4E02_85AF_0DCA730D2C87__INCLUDED_)
