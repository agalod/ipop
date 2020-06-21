// CCFile.h: Schnittstelle für die Klasse CIni_Camera.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CCFILE_H__CBD1ECB3_F2DD_431C_8266_5DD594BC9B3A__INCLUDED_)
#define AFX_CCFILE_H__CBD1ECB3_F2DD_431C_8266_5DD594BC9B3A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


enum CharReturn
{
	SPACE,
		CHARACTER,
		NUMBER,
		OTHER
};


class CIni_Camera  
{
public:
	void Set_FocLen(float aFocLen);
	int Get_PixNumY();
	int Get_PixNumX();
	float Get_CellSizeY();
	float Get_CellSizeX();
	float Get_FocLen();
	void Set_CellSize(float x, float y);
	void Read_CellSize();
	void Set_DistortionVec(float* aDistortionVec);
	void Set_CameraMat(float* aCameraMat);
	void Set_ImageSize(int x, int y);
	void Read_ImageSize();
	void Read_Distortion();
	void Read_CameraMatrix();
	CIni_Camera(CString Verz, CString Datei);
	virtual ~CIni_Camera();
	
	CharReturn CheckChar(char zeichen);
	void INI_LesenFileDialog();
	void INI_SchreibenFileDialog();
	bool INI_Lesen();
	bool INI_Schreiben();
	void Read_PrincipalPoint();
	void Read_DistortionMatlab();
	void Read_FocalLen();
	
	CStringArray	m_StringArray;
	CStdioFile		m_File;
	
	CString m_CurrLine;
	CString m_cstrPrincPtName;
	CString m_cstrFocLenName;
	CString m_cstrDistNameMatlab;
	CString m_cstrDistName;
	CString m_cstrCameraMat;
	CString m_cstrImageSize;
	CString m_cstrCellSize;
	CString m_cstr_Datei;
	
	char m_chrArray[500];
	
	int    m_Int_ImageSize[2];
	float m_Int_PrincPt[2];
	float m_Int_FocLen[2];
	float m_Int_Dist[5];
	float m_Int_CameraMat[9];
	float m_Int_CellSize[2];

	int m_iPos;
	
	
};

#endif // !defined(AFX_CCFILE_H__CBD1ECB3_F2DD_431C_8266_5DD594BC9B3A__INCLUDED_)
