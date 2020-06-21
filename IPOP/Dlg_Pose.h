///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
//-----------------------------------------------------------------------------
// Written by cand.ing. Alexander M.Roehnisch @ WZL-RWTH, Aachen, Germany, 2005
//-----------------------------------------------------------------------------
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
#if !defined(AFX_Dlg_Pose_H__79FBB818_1117_4FB6_8545_954C46A29452__INCLUDED_)
#define AFX_Dlg_Pose_H__79FBB818_1117_4FB6_8545_954C46A29452__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Dlg_Pose.h : Header-Datei
//

#include "resource.h"
/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CDlg_Pose 

class CDlg_Pose : public CDialog
{
// Konstruktion
public:
	void SetAsMachineRef();
	void File_Save();
	double File_ReadLine(const CString &line);
	void File_Load();
	void Update();
	void UpdateObjectPoints();
	CDlg_Pose(CWnd* pParent = NULL);   // Standardkonstruktor
	double m_increment;
	CStdioFile		m_File;
	CString m_Ini_Verzeichnis;

// Dialogfelddaten
	//{{AFX_DATA(CDlg_Pose)
	enum { IDD = IDD_DLG_POSE };
		// HINWEIS: Der Klassen-Assistent fügt hier Datenelemente ein
	GCV_EULER3D *m_pCamPos, *m_pMachineRef, *m_pWorkpiece;
	int *m_pNumIterations; double * m_pDistances_Sum;
	//}}AFX_DATA


// Überschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktionsüberschreibungen
	//{{AFX_VIRTUAL(CDlg_Pose)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
	//}}AFX_VIRTUAL

// Implementierung
protected:

	// Generierte Nachrichtenzuordnungsfunktionen
	//{{AFX_MSG(CDlg_Pose)
		// HINWEIS: Der Klassen-Assistent fügt hier Member-Funktionen ein
	afx_msg void On_MachineRef_TransX_Neg();
	afx_msg void On_MachineRef_TransY_Neg();
	afx_msg void On_MachineRef_RotZ_Neg();
	afx_msg void On_MachineRef_RotX_Neg();
	afx_msg void On_MachineRef_TransX_Pos();
	afx_msg void On_MachineRef_TransY_Pos();
	afx_msg void On_MachineRef_RotZ_Pos();
	afx_msg void On_MachineRef_RotX_Pos();

	afx_msg void On_Workpiece_TransX_Neg();
	afx_msg void On_Workpiece_TransY_Neg();
	afx_msg void On_Workpiece_RotZ_Neg();
	afx_msg void On_Workpiece_TransX_Pos();
	afx_msg void On_Workpiece_TransY_Pos();
	afx_msg void On_Workpiece_RotZ_Pos();

	afx_msg void OnChange_TransX();
	afx_msg void OnChange_TransY();
	afx_msg void OnChange_TransZ();
	afx_msg void OnChange_RotX();
	afx_msg void OnChange_RotY();
	afx_msg void OnChange_RotZ();

	afx_msg void On_TransX_Neg();
	afx_msg void On_TransY_Neg();
	afx_msg void On_TransZ_Neg();
	afx_msg void On_RotX_Neg();
	afx_msg void On_RotY_Neg();
	afx_msg void On_RotZ_Neg();
	afx_msg void On_TransX_Pos();
	afx_msg void On_TransY_Pos();
	afx_msg void On_TransZ_Pos();
	afx_msg void On_RotX_Pos();
	afx_msg void On_RotY_Pos();
	afx_msg void On_RotZ_Pos();

	afx_msg void OnChangeMachineRefX();
	afx_msg void OnChangeMachineRefY();
	afx_msg void OnChangeMachineRefRotZ();
	afx_msg void OnChangeMachineRefRotX();
	afx_msg void OnChangeWorkpiece_TransX();
	afx_msg void OnChangeWorkpiece_TransY();
	afx_msg void OnChangeWorkpiece_RotZ();
	afx_msg void OnKillFocus(CWnd* pNewWnd);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // AFX_Dlg_Pose_H__79FBB818_1117_4FB6_8545_954C46A29452__INCLUDED_
