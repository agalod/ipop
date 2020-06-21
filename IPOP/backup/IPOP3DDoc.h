// IPOP3DDoc.h: Schnittstelle für die Klasse CIPOP3DDoc.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_IPOP3DDOC_H__EF0026AD_23C8_4772_BF1F_320A2BFF02DC__INCLUDED_)
#define AFX_IPOP3DDOC_H__EF0026AD_23C8_4772_BF1F_320A2BFF02DC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "3DDoc.h"

class CIPOP3DDoc : public C3DDoc  
{
public:
	void SetProjectionRays();
	void SetSensingArea();
	void SetObjectpointlist(const CArray <CPoint,CPoint&> &aList);
	void SetImagepointlist(CArray<CPoint,CPoint&> *aList);
	void SetCameraStruct( D3DCAMERA cam);
	CIPOP3DDoc();
	virtual ~CIPOP3DDoc();
	D3DCAMERA m_Camera;
	CArray<CPoint,CPoint&> m_Imagepointlist;
	CArray<D3DVECTOR, D3DVECTOR&> m_Objectpointlist;

};

#endif // !defined(AFX_IPOP3DDOC_H__EF0026AD_23C8_4772_BF1F_320A2BFF02DC__INCLUDED_)
