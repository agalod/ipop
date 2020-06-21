// IPOPCalc.h: Schnittstelle für die Klasse CIPOPCalc.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_IPOPCALC_H__46EA1A3F_3C94_4027_A84E_D785ABF0A993__INCLUDED_)
#define AFX_IPOPCALC_H__46EA1A3F_3C94_4027_A84E_D785ABF0A993__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "IPOP.h"

class CIPOPCalc : CIPOP
{
public:
	void Calc_CallibratePlane();
	CIPOPCalc();
	virtual ~CIPOPCalc();

};

#endif // !defined(AFX_IPOPCALC_H__46EA1A3F_3C94_4027_A84E_D785ABF0A993__INCLUDED_)
