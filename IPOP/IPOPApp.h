///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
//-----------------------------------------------------------------------------
// Written by cand.ing. Alexander M.Roehnisch @ WZL-RWTH, Aachen, Germany, 2005
//-----------------------------------------------------------------------------
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
// IPOPApp.h : Haupt-Header-Datei für die Anwendung IPOP
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
#if !defined(AFX_IPOP_H__DF5D1CC2_AF63_470F_A847_563C27A893B9__INCLUDED_)
#define AFX_IPOP_H__DF5D1CC2_AF63_470F_A847_563C27A893B9__INCLUDED_
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif
#include "resource.h"
#include "Disp_Pic_Doc.h"	
#include "Disp_Pic_View.h" 
#include "Disp_3D_View.h"	
#include "Disp_3D_Doc.h"
#include "IPOP.h"			
#include "Dlg_Camera.h"
#include "Dlg_Etalon.h"		
#include "Dlg_Pose.h"
#include "Dlg_3D.h"			
#include "Dlg_IPParams.h"
#include "avtformat.h"
#include "Disp_Live_Doc.h"
#include "Disp_Live_View.h"
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
class CIPOPApp : public CWinApp {
public:
	void SnapAndReg();
	void VideoInit();
	void VideoGrabFrame();
	CIPOPApp(); 
	void Calc_Calibrate_OneStep(); void Calc_Calibrate_Init();
	void CreatePicView(); void CreateDisp_Live_View(); void CreateDisp_3D_View();	
	CRecentFileList* GetRecentFileList();
	void LoadBmps(); void LoadBmp(CString str);
	//{{AFX_VIRTUAL(CIPOPApp)
	public: virtual BOOL InitInstance(); virtual int ExitInstance();
	//}}AFX_VIRTUAL
	CDisp_3D_View*		m_Disp_3D_pView;	CDisp_3D_Doc*		m_Disp_3D_pDoc;
	CDisp_Pic_Doc*		m_Disp_pPicDoc;		CDisp_Pic_View*		m_Disp_pPicView;
	CDisp_Live_View *	m_Disp_pLiveView;	CDisp_Live_Doc *	m_Disp_pLiveDoc;
	CMultiDocTemplate	*m_Template_pRegPic, * m_Template_pPic, 
						*m_Template_pLive, *m_Template_p3D;
	CDlg_3D*		m_Dlg_3D;	CDlg_Camera*	m_Dlg_CamParams;
	CDlg_Etalon*	m_Dlg_Etalon;	CDlg_Pose*		m_Dlg_Pose;
	CDlg_IPParams*	m_Dlg_IPParams;
	CString m_Ini_Verzeichnis;
	CIPOP m_IPOP;
	//{{AFX_MSG(CIPOPApp)
	afx_msg void OnAppAbout();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP() };
/////////////////////////////////////////////////////////////////////////////
//{{AFX_INSERT_LOCATION}}
#endif // !defined(AFX_IPOP_H__DF5D1CC2_AF63_470F_A847_563C27A893B9__INCLUDED_)
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
