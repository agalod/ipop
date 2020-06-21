// CCFile.h: Schnittstelle für die Klasse CIni_IPOP.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CCFILE_H__CBD1ECB3_F2DD_431C_8266_5DD594BC9B3A__INCLUDED_)
#define AFX_CCFILE_H__CBD1ECB3_F2DD_431C_8266_5DD594BC9B3A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


enum CharType
{
	SPACE,
		CHARACTER,
		NUMBER,
		OTHER
};


class CIni_IPOP  
{
public:
	void Read_CellSize();
	void Read_ImageSize();
	void Read_Distortion();
	void Read_CameraMatrix();
	void Read_PrincipalPoint();
	void Read_DistortionMatlab();
	void Read_FocalLen();
	CIni_IPOP(CString Verz, CString Datei);
	virtual ~CIni_IPOP();
	
	CharType CharacterType(char zeichen);
	void INI_LesenFileDialog();
	void INI_SchreibenFileDialog();
	void INI_Lesen();
	void INI_Schreiben();
	
	CStringArray	m_StringArray;
	CStdioFile		m_File;

	D3DEULER *m_Euler_Etalon, *m_Euler_Machine, 
		*m_Euler_Workpiece;
	
};

#endif // !defined(AFX_CCFILE_H__CBD1ECB3_F2DD_431C_8266_5DD594BC9B3A__INCLUDED_)
