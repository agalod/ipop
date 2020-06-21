// Von Klassen-Assistent automatisch erstellte IDispatch-Kapselungsklasse(n).

#include "stdafx.h"
#include "avtformat.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif



/////////////////////////////////////////////////////////////////////////////
// Eigenschaften _IAVTFormatPageEvents 

/////////////////////////////////////////////////////////////////////////////
// Operationen _IAVTFormatPageEvents 


/////////////////////////////////////////////////////////////////////////////
// Eigenschaften IAVTFormatPage 

/////////////////////////////////////////////////////////////////////////////
// Operationen IAVTFormatPage 

void IAVTFormatPage::SetICamera(LPUNKNOWN newValue)
{
	static BYTE parms[] =
		VTS_UNKNOWN;
	InvokeHelper(0x1, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

void IAVTFormatPage::SetIStream(LPUNKNOWN newValue)
{
	static BYTE parms[] =
		VTS_UNKNOWN;
	InvokeHelper(0x2, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

void IAVTFormatPage::Init()
{
	InvokeHelper(0x3, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}
