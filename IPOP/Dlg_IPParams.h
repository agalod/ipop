///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
//-----------------------------------------------------------------------------
// Written by cand.ing. Alexander M.Roehnisch @ WZL-RWTH, Aachen, Germany, 2005
//-----------------------------------------------------------------------------
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
#if !defined(AFX_DLG_IPPARAMS_H__71B71104_3EEC_40C5_AE7A_90771E8159B8__INCLUDED_)
#define AFX_DLG_IPPARAMS_H__71B71104_3EEC_40C5_AE7A_90771E8159B8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Dlg_IPParams.h : Header-Datei
//

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CDlg_IPParams 
#include "resource.h"

class CDlg_IPParams : public CDialog
{
// Konstruktion
public:
	CDlg_IPParams(CWnd* pParent = NULL);   // Standardkonstruktor
	void File_Save();
	double File_ReadLine(const CString &line);
	void File_Load();
	CString m_Ini_Verzeichnis;
	CStdioFile		m_File;
// Dialogfelddaten
	//{{AFX_DATA(CDlg_IPParams)
	enum { IDD = IDD_DLG_IP_PARAMS };
	int		m_BinThreshold;
	BOOL	m_bHoughAccu180;
	BOOL	m_bHoughAccu360;
	BOOL	m_bHoughAccu540;
	BOOL	m_bShowSteps;
	double	m_HoughSensivity;
	//}}AFX_DATA
// Überschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktionsüberschreibungen
	//{{AFX_VIRTUAL(CDlg_IPParams)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
	//}}AFX_VIRTUAL
// Implementierung
protected:
	// Generierte Nachrichtenzuordnungsfunktionen
	//{{AFX_MSG(CDlg_IPParams)
	afx_msg void OnIpparamsHoughaccu180();
	afx_msg void OnIpparamsHoughaccu360();
	afx_msg void OnIpparamsHoughaccu540();
	afx_msg void OnIpparamsShowsteps();
	afx_msg void OnChangeIpparamsBinthresh();
	afx_msg void OnChangeIpparamsHoughsensivity();
	afx_msg void OnIpparamsHoughsensivityPos();
	afx_msg void OnIpparamsHoughsensivityNeg();
	afx_msg void OnIpparamsBinthreshPos();
	afx_msg void OnIpparamsBinthreshNeg();
	afx_msg void OnCancelMode();
	afx_msg void OnClose();
	afx_msg void OnDestroy();
	afx_msg void OnKillFocus(CWnd* pNewWnd);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // AFX_DLG_IPPARAMS_H__71B71104_3EEC_40C5_AE7A_90771E8159B8__INCLUDED_
