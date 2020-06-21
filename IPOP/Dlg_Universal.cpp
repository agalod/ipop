// Dlg_Universal.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "ipop.h"
#include "Dlg_Universal.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CDlg_Universal 
  

CDlg_Universal::CDlg_Universal(CWnd* pParent /*=NULL*/)
	: CDialog(CDlg_Universal::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlg_Universal)
	m_Text1 = _T("");
	m_Text2 = _T("");
	m_Edit1 = 0.0;
	m_Edit2 = 0.0;
	//}}AFX_DATA_INIT
}


void CDlg_Universal::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlg_Universal)
	DDX_Text(pDX, IDC_DLG_UNI_TEXT1, m_Text1);
	DDX_Text(pDX, IDC_DLG_UNI_TEXT2, m_Text2);
	DDX_Text(pDX, IDC_DLG_UNI_EDIT1, m_Edit1);
	DDX_Text(pDX, IDC_DLG_UNI_EDIT2, m_Edit2);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlg_Universal, CDialog)
	//{{AFX_MSG_MAP(CDlg_Universal)
		// HINWEIS: Der Klassen-Assistent fügt hier Zuordnungsmakros für Nachrichten ein
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten CDlg_Universal 
