// CCamera.cpp: Implementierung der Klasse CCamera.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "stdafx.h"
#include "Camera.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Konstruktion/Destruktion
//////////////////////////////////////////////////////////////////////

CCamera::CCamera(CString Verz, CString Datei)
{
	m_cstr_Datei  = Verz + "\\" + Datei;
	m_cstrPrincPtName = "Principal point:";
	m_cstrFocLenName = "Focal length:";
	m_cstrDistNameMatlab = "m_Int_Dist coefficients:";
	m_cstrDistName = "Verzerrung";
	m_cstrCameraMat = "Kameramatrix";
	m_cstrImageSize = "Bildgröße";
	m_cstrCellSize = "Pixelgröße";
	
	m_Int_FocLen[0] = 0;
	m_Int_FocLen[1] = 0;
	
	m_Int_PrincPt[0] = 0;
	m_Int_PrincPt[1] = 0;
	
	m_Int_Dist[0] = 0;
	m_Int_Dist[1] = 0;
	m_Int_Dist[2] = 0;
	m_Int_Dist[3] = 0;
	m_Int_Dist[4] = 0;

	m_Int_ImageSize[0] = 0;
	m_Int_ImageSize[1] = 0;

	m_Int_CellSize[0] = 8.6;
	m_Int_CellSize[1] = 8.2;

	for(int i=0;i<9;i++)
		m_Int_CameraMat[i] = 0;
	
}

CCamera::~CCamera()
{
	if( !INI_Schreiben() )
		AfxMessageBox("Camera.ini konnte nicht neu geschrieben werden!");

}
CharReturn CCamera::CheckChar( char zeichen )
{
	CharReturn ret;
	if( zeichen==' ' ) // Leerzeichen
	{	ret = SPACE; return ret;}
	else if( zeichen==char(13) ) // CR
	{ ret = CHARACTER;return ret;}
	else if( ( zeichen>='0' && zeichen<='9' ) 
		|| zeichen=='-' || zeichen=='+' || zeichen=='.' ) // Zahl
	{	 ret = NUMBER;return ret;}
	else // Sonstige Zeichen
	{ret = OTHER;return ret;}
}

void CCamera::INI_LesenFileDialog()
{
	m_File.Abort();
	CString Fullpath, m_CurrLine, search_str; 
	CFileException error; char wert[1000]; bool stop = 0; 
	int i = 0, m_iPos = 0; CharReturn chartype;
	
	
	//static char BASED_CODE szFilter[] = "Matlab Calibration Files (*.m)|*.m|Alle Dateien (*.*)|*.*||";
	static char BASED_CODE szFilter[] = "Text Files (*.txt)|*.txt|Alle Dateien (*.*)|*.*||";
	CFileDialog Dlg( 1, (LPCTSTR) &"txt", NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, szFilter );
	char ch_string[200];
	GetCurrentDirectory(100,ch_string);
	Dlg.m_ofn.lpstrInitialDir = ch_string;
	if(Dlg.DoModal()==IDOK) Fullpath = Dlg.GetPathName();
	
	//if(!m_File.Open( "c:\\pictures\\Calib_Results.m", CFile::modeRead, &error))
	if(!m_File.Open( Fullpath, CFile::modeRead, &error))
	{
		char text[100];
		afxDump << "File could not be opened " << error.m_cause << "\n";
		sprintf( text,"%s konnte nicht geöffnet werden!", Fullpath );
		AfxMessageBox( text );
		return;
	}
	DWORD dateilaenge = m_File.GetLength();
	
	do{
		// Zeile aus Ini-Datei lesen und auf gesuchten Text untersuchen
		m_File.ReadString(m_CurrLine); m_StringArray.Add(m_CurrLine);
		//if(m_iPos = m_CurrLine.Find(m_cstrFocLenName) && m_CurrLine.Find(m_cstrFocLenName) != -1)
		if(m_CurrLine.Find(m_cstrFocLenName) != -1){
			m_iPos = m_CurrLine.Find(m_cstrFocLenName);
			Read_FocalLen();
		}
		if(m_iPos = m_CurrLine.Find(m_cstrPrincPtName) && m_CurrLine.Find(m_cstrPrincPtName) != -1)
			Read_PrincipalPoint();
		if(m_CurrLine.Find(m_cstrDistName) != -1){
			m_iPos = m_CurrLine.Find(m_cstrDistName);
			Read_Distortion();}
		//if(m_iPos = m_CurrLine.Find(m_cstrCameraMat) && m_CurrLine.Find(m_cstrCameraMat) != -1)
		if(m_CurrLine.Find(m_cstrCameraMat) != -1){
			m_iPos = m_CurrLine.Find(m_cstrCameraMat);
			Read_CameraMatrix();
		}
		if(m_iPos = m_CurrLine.Find(m_cstrDistNameMatlab) && m_CurrLine.Find(m_cstrDistNameMatlab) != -1)
			Read_DistortionMatlab();
		if(m_CurrLine.Find(m_cstrImageSize) != -1){
			m_iPos = m_CurrLine.Find(m_cstrImageSize);
			Read_ImageSize();
		}
		if(m_CurrLine.Find(m_cstrCellSize) != -1){
			m_iPos = m_CurrLine.Find(m_cstrCellSize);
			Read_CellSize();
		}
		
	}while(m_File.GetPosition() != dateilaenge);
	
	m_File.Close();
	//Setm_Int_CameraMat();
}


bool CCamera::INI_Lesen()
{
	m_File.Abort();
	CString Fullpath, m_CurrLine, search_str; 
	CFileException error; char wert[1000]; bool stop = 0; 
	int i = 0, m_iPos = 0; CharReturn chartype;
	
	if(!m_File.Open( m_cstr_Datei, CFile::modeRead, &error))
	{
		char text[100];
		afxDump << "File could not be opened " << error.m_cause << "\n";
		sprintf( text,"%s konnte nicht geöffnet werden!", Fullpath );
		AfxMessageBox( text );
		return 0;
	}
	DWORD dateilaenge = m_File.GetLength();
	
	do{
		// Zeile aus Ini-Datei lesen und auf gesuchten Text untersuchen
		m_File.ReadString(m_CurrLine); m_StringArray.Add(m_CurrLine);
		//if(m_iPos = m_CurrLine.Find(m_cstrFocLenName) && m_CurrLine.Find(m_cstrFocLenName) != -1)
		if(m_CurrLine.Find(m_cstrFocLenName) != -1){
			m_iPos = m_CurrLine.Find(m_cstrFocLenName);
			Read_FocalLen();
		}
		if(m_iPos = m_CurrLine.Find(m_cstrPrincPtName) && m_CurrLine.Find(m_cstrPrincPtName) != -1)
			Read_PrincipalPoint();
		if(m_CurrLine.Find(m_cstrDistName) != -1){
			m_iPos = m_CurrLine.Find(m_cstrDistName);
			Read_Distortion();}
		//if(m_iPos = m_CurrLine.Find(m_cstrCameraMat) && m_CurrLine.Find(m_cstrCameraMat) != -1)
		if(m_CurrLine.Find(m_cstrCameraMat) != -1){
			m_iPos = m_CurrLine.Find(m_cstrCameraMat);
			Read_CameraMatrix();
		}
		if(m_iPos = m_CurrLine.Find(m_cstrDistNameMatlab) && m_CurrLine.Find(m_cstrDistNameMatlab) != -1)
			Read_DistortionMatlab();
		if(m_CurrLine.Find(m_cstrImageSize) != -1){
			m_iPos = m_CurrLine.Find(m_cstrImageSize);
			Read_ImageSize();
		}
		if(m_CurrLine.Find(m_cstrCellSize) != -1){
			m_iPos = m_CurrLine.Find(m_cstrCellSize);
			Read_CellSize();
		}
		
	}while(m_File.GetPosition() != dateilaenge);
	
	m_File.Close();
	m_Int_FocLen[0] = m_Int_CameraMat[0] * m_Int_CellSize[0] / 1000;
	m_Int_FocLen[1] = m_Int_CameraMat[3] * m_Int_CellSize[1] / 1000;
	m_Int_PrincPt[0] = m_Int_CameraMat[2];
	m_Int_PrincPt[1] = m_Int_CameraMat[5];
	return 1;
	//Setm_Int_CameraMat();
}


void CCamera::Read_PrincipalPoint(){
	
	m_File.ReadString(m_CurrLine); 
	if(m_CurrLine.GetLength()==0) return;
	m_StringArray.Add(m_CurrLine);
	CharReturn chartype;
	int end = m_CurrLine.Find("];"), second = m_CurrLine.Find(" ; "), i=0;
	m_iPos = 0; //m_iPos is set to beg. of data (" = [ ")
	
	do{
		if(m_iPos == second){
			m_Int_PrincPt[0] = atof(m_chrArray); i = 0; m_iPos += 3;
		}
		chartype = CheckChar(m_CurrLine[m_iPos]);
		// Read current number if it is one
		if( chartype == NUMBER ){
			m_chrArray[i] = m_CurrLine[m_iPos]; i++;
		}
		
		else if( chartype == SPACE || m_CurrLine[m_iPos] == ';' )
			m_iPos++;
		
		m_iPos++;
		if( m_iPos>500 ) // Position für Textstring zu groß
			return;
		
	}while(m_iPos != end-1);
	
	m_Int_PrincPt[1] = atof(m_chrArray);
	
}

void CCamera::Read_DistortionMatlab(){
	
	m_File.ReadString(m_CurrLine);  m_StringArray.Add(m_CurrLine);
	CharReturn chartype;
	int end = m_CurrLine.Find("];"), second = m_CurrLine.Find(" ; "), 
		third = m_CurrLine.Find(" ; ", second+1), fourth = m_CurrLine.Find(" ; ",third+1),
		fifth = m_CurrLine.Find(" ; ",fourth+1), i=0;
	m_iPos = (2 + 5); //m_iPos is set to beg. of data (" = [ ")
	
	do{
		if(m_iPos == second){m_Int_Dist[0] = atof(m_chrArray); i = 0; m_iPos += 3;}
		if(m_iPos == third) {m_Int_Dist[1] = atof(m_chrArray); i = 0; m_iPos += 3;}
		if(m_iPos == fourth){m_Int_Dist[2] = atof(m_chrArray); i = 0; m_iPos += 3;}
		if(m_iPos == fifth){m_Int_Dist[3] = atof(m_chrArray); i = 0; m_iPos += 3;}
		
		chartype = CheckChar(m_CurrLine[m_iPos]);
		// Read current number if it is one
		if( chartype == NUMBER ){
			m_chrArray[i] = m_CurrLine[m_iPos]; i++;
		}
		
		else if( chartype == SPACE || m_CurrLine[m_iPos] == ';' )
			m_iPos++;
		
		m_iPos++;
		if( m_iPos>500 ) // Position für Textstring zu groß
			return;
		
	}while(m_iPos != end-1);
	
	m_Int_Dist[4] = atof(m_chrArray);
}



void CCamera::Read_FocalLen(){
	
	m_File.ReadString(m_CurrLine); 
	if(m_CurrLine.GetLength()==0) return;
	m_StringArray.Add(m_CurrLine);
	CharReturn chartype;
	int end = m_CurrLine.Find("];"), second = m_CurrLine.Find(" ; "), i=0;
	m_iPos = (2 + 5); //m_iPos is set to beg. of data (" = [ ")
	
	do{
		if(m_iPos == second){
			m_Int_FocLen[0] = atof(m_chrArray); i = 0; m_iPos += 3;
		}
		chartype = CheckChar(m_CurrLine[m_iPos]);
		// Read current number if it is one
		if( chartype == NUMBER ){
			m_chrArray[i] = m_CurrLine[m_iPos]; i++;
		}
		
		else if( chartype == SPACE || m_CurrLine[m_iPos] == ';' )
			m_iPos++;
		
		m_iPos++;
		if( m_iPos>500 ) // Position für Textstring zu groß
			return;
		
	}while(m_iPos != end-1);
	
	m_Int_FocLen[1] = atof(m_chrArray);
}


void CCamera::Read_CameraMatrix()
{
	CharReturn chartype;
	int end = m_CurrLine.GetLength(), second = m_CurrLine.Find(";"), 
		third = m_CurrLine.Find(";", second+1), i=0, j=0;
	m_iPos = 0; //m_iPos is set to beg. of data (" = [ ")
	
	for(j=0;j<3;j++){
		m_File.ReadString(m_CurrLine); m_StringArray.Add(m_CurrLine);
		end = m_CurrLine.GetLength(); if(end==0) return;
		second = m_CurrLine.Find(" "); 
			third = m_CurrLine.Find(" ", second+1); i=0;
		m_iPos = 0; //m_iPos is set to beg. of data (" = [ ")
		do{
			if(m_iPos == second){
			//; Setze den letzten Wert und setze i=0 für den nächsten Wert
				m_chrArray[i] = '\0';
				m_Int_CameraMat[0+j*3] = atof(m_chrArray); i = 0; m_iPos ++; }
			if(m_iPos == third){
			//; Setze den letzten Wert und setze i=0 für den nächsten Wert
				m_chrArray[i] = '\0';
				m_Int_CameraMat[1+j*3] = atof(m_chrArray); i = 0; m_iPos ++;}
			
			// Read current number if it is one
			chartype = CheckChar(m_CurrLine[m_iPos]);
			if( chartype == NUMBER ){
				m_chrArray[i] = m_CurrLine[m_iPos]; i++;
			}
			m_iPos++;
			if( m_iPos>500 ) // Position für Textstring zu groß
				return;
		}while(m_iPos != end);
		m_chrArray[i] = '\0';
		m_Int_CameraMat[2+j*3] = atof(m_chrArray);
	}

}

void CCamera::Read_Distortion()
{
	m_File.ReadString(m_CurrLine); 
	if(m_CurrLine.GetLength()==0) return;
	m_StringArray.Add(m_CurrLine);
	CharReturn chartype;
	int end = m_CurrLine.GetLength(), second = m_CurrLine.Find(";"), 
		third = m_CurrLine.Find(";", second+1), fourth = m_CurrLine.Find(";",third+1), i=0, j=0;
	m_iPos = 0; //m_iPos is set to beg. of data (" = [ ")
	
	do{
		if(m_iPos == second){
		//; Setze den letzten Wert und setze i=0 für den nächsten Wert
			m_chrArray[i] = '\0';
			m_Int_Dist[0] = atof(m_chrArray)/1000; i = 0; m_iPos++;}
		if(m_iPos == third){
		//; Setze den letzten Wert und setze i=0 für den nächsten Wert
			m_chrArray[i] = '\0';
			m_Int_Dist[1] = atof(m_chrArray)/1000; i = 0; m_iPos++;}
		if(m_iPos == fourth){
		//; Setze den letzten Wert und setze i=0 für den nächsten Wert
			m_chrArray[i] = '\0';
			m_Int_Dist[2] = atof(m_chrArray)/1000; i = 0; m_iPos++;}
		// Read current number if it is one
		chartype = CheckChar(m_CurrLine[m_iPos]);
		if( chartype == NUMBER ){
			m_chrArray[i] = m_CurrLine[m_iPos]; i++;
		}
		m_iPos++;
		if( m_iPos>500 ) // Position für Textstring zu groß
			return;
	}while(m_iPos != end);
	m_chrArray[i] = '\0';
	m_Int_Dist[3] = atof(m_chrArray)/1000;

}

void CCamera::Read_ImageSize()
{
	m_File.ReadString(m_CurrLine); 
	if(m_CurrLine.GetLength()==0) return;
	m_StringArray.Add(m_CurrLine);
	CharReturn chartype;
	int end = m_CurrLine.GetLength(), second = m_CurrLine.Find(";"), i=0, j=0;
	m_iPos = 0; //m_iPos is set to beg. of data (" = [ ")
	
	do{
		if(m_iPos == second){
		//; Setze den letzten Wert und setze i=0 für den nächsten Wert
			m_chrArray[i] = '\0';
			m_Int_ImageSize[0] = atof(m_chrArray); i = 0; m_iPos++;}
		// Read current number if it is one
		chartype = CheckChar(m_CurrLine[m_iPos]);
		if( chartype == NUMBER ){
			m_chrArray[i] = m_CurrLine[m_iPos]; i++;
		}
		m_iPos++;
		if( m_iPos>500 ) // Position für Textstring zu groß
			return;
	}while(m_iPos != end);
	m_chrArray[i] = '\0';
	m_Int_ImageSize[1] = atof(m_chrArray);

}
void CCamera::INI_SchreibenFileDialog()
{
	CFileException error; CString str;
	static char BASED_CODE szFilter[] = "Text Files (*.txt)|*.txt||";
	CFileDialog dlg(0,"txt",0, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, szFilter );
	dlg.m_ofn.lpstrInitialDir = "C:\\pictures";
	if(dlg.DoModal()==IDCANCEL) return;
	if( !m_File.Open(dlg.GetPathName(), CFile::modeCreate | CFile::modeWrite, &error)){ //"D:\\Projekte\\SFB368_TP_8_2\\KAZ\\DATEN\\NC_Prog.txt", CFile::modeCreate | CFile::modeWrite, &error) )
		AfxMessageBox( "Datei konnte nicht erstellt werden!" );	return;
	}
    m_StringArray.RemoveAll();	
	str.Format("Pixelgröße (aus dem Datenblatt des Kameraherstellers):"); m_StringArray.Add(str);
	str.Format("%d %d", m_Int_CellSize[0], m_Int_CellSize[1]);
	m_StringArray.Add(str);
	str.Format("Bildgröße:");	m_StringArray.Add(str);
	str.Format("%d %d", m_Int_ImageSize[0], m_Int_ImageSize[1]);
	m_StringArray.Add(str);	m_StringArray.Add(str);
	str.Format("Kameramatrix:");	m_StringArray.Add(str);
	str.Format("%f %f %f",m_Int_CameraMat[0],m_Int_CameraMat[1],m_Int_CameraMat[2]);
	m_StringArray.Add(str);
	str.Format("%f %f %f", m_Int_CameraMat[3],m_Int_CameraMat[4],m_Int_CameraMat[5]);
	m_StringArray.Add(str);
	str.Format("%f %f %f",m_Int_CameraMat[6],m_Int_CameraMat[7],m_Int_CameraMat[8]);
	m_StringArray.Add(str);	m_StringArray.Add(str);
	str.Format("Verzerrung:");	m_StringArray.Add(str);
	str.Format("%f %f %f %f",m_Int_Dist[0],m_Int_Dist[1],m_Int_Dist[2],
		m_Int_Dist[3]);

	for( int i = 0; i<m_StringArray.GetSize(); i++ ){
		m_File.WriteString(m_StringArray.GetAt(i));
		m_File.WriteString("\n");
	}
	m_File.Close();

}
bool CCamera::INI_Schreiben()
{
	CFileException error; CString str;
	if( !m_File.Open(m_cstr_Datei, CFile::modeCreate | CFile::modeWrite, &error)){ //"D:\\Projekte\\SFB368_TP_8_2\\KAZ\\DATEN\\NC_Prog.txt", CFile::modeCreate | CFile::modeWrite, &error) )
		AfxMessageBox( "Datei konnte nicht erstellt werden!" );	return 0;
	}
    m_StringArray.RemoveAll();	
	str.Format("Pixelgröße (aus dem Datenblatt des Kameraherstellers):"); m_StringArray.Add(str);
	str.Format("%.1f %.1f", m_Int_CellSize[0], m_Int_CellSize[1]);
	m_StringArray.Add(str); str.Empty(); m_StringArray.Add(str); 
	str.Format("Bildgröße:");	m_StringArray.Add(str);
	str.Format("%d %d", m_Int_ImageSize[0], m_Int_ImageSize[1]);
	m_StringArray.Add(str); str.Empty(); m_StringArray.Add(str);
	str.Format("Kameramatrix:");	m_StringArray.Add(str);
	str.Format("%f %f %f",m_Int_CameraMat[0],m_Int_CameraMat[1],m_Int_CameraMat[2]);
	m_StringArray.Add(str);
	str.Format("%f %f %f", m_Int_CameraMat[3],m_Int_CameraMat[4],m_Int_CameraMat[5]);
	m_StringArray.Add(str);
	str.Format("%f %f %f",m_Int_CameraMat[6],m_Int_CameraMat[7],m_Int_CameraMat[8]);
	m_StringArray.Add(str); str.Empty(); m_StringArray.Add(str);
	str.Format("Verzerrung:");	m_StringArray.Add(str);
	str.Format("%f %f %f %f",m_Int_Dist[0],m_Int_Dist[1],m_Int_Dist[2],
		m_Int_Dist[3]);
	m_StringArray.Add(str);

	for( int i = 0; i<m_StringArray.GetSize(); i++ ){
		m_File.WriteString(m_StringArray.GetAt(i));
		m_File.WriteString("\n");
	}
	m_File.Close();

	return 1;
}

void CCamera::Set_ImageSize(int x, int y)
{
	m_Int_ImageSize[0] = x;
	m_Int_ImageSize[1] = y;
}



void CCamera::Set_CameraMat(double* aCameraMat)
{
	for(int i=0;i<9;i++)
			m_Int_CameraMat[i] = aCameraMat[i];
}



void CCamera::Set_DistortionVec(double* aDistortionVec)
{
	m_Int_Dist[0] = aDistortionVec[0];
	m_Int_Dist[1] = aDistortionVec[1];
	m_Int_Dist[2] = aDistortionVec[2];
	m_Int_Dist[3] = aDistortionVec[3];
}

void CCamera::Read_CellSize()
{
	m_File.ReadString(m_CurrLine); m_StringArray.Add(m_CurrLine);
	CharReturn chartype;
	int end = m_CurrLine.GetLength(), second = m_CurrLine.Find(" "), i=0, j=0;
	m_iPos = 0; //m_iPos is set to beg. of data (" = [ ")
	
	do{
		if(m_iPos == second){
		//; Setze den letzten Wert und setze i=0 für den nächsten Wert
			m_chrArray[i] = '\0';
			m_Int_CellSize[0] = atof(m_chrArray); i = 0; m_iPos++;}
		// Read current number if it is one
		chartype = CheckChar(m_CurrLine[m_iPos]);
		if( chartype == NUMBER ){
			m_chrArray[i] = m_CurrLine[m_iPos]; i++;
		}
		m_iPos++;
		if( m_iPos>500 ) // Position für Textstring zu groß
			return;
	}while(m_iPos != end);
	m_chrArray[i] = '\0';
	m_Int_CellSize[1] = atof(m_chrArray);

}

void CCamera::Set_CellSize(double x, double y)
{
	m_Int_CellSize[0] = x;
	m_Int_CellSize[1] = y;
}

double CCamera::Get_FocLen()
{
	return m_Int_FocLen[0];
}

double CCamera::Get_CellSizeX()
{
	return m_Int_CellSize[0];
}

double CCamera::Get_CellSizeY()
{
	return m_Int_CellSize[1];

}

int CCamera::Get_PixNumX()
{
	return m_Int_ImageSize[0];
}

int CCamera::Get_PixNumY()
{
	return m_Int_ImageSize[1];

}

void CCamera::Set_FocLen(double aFocLen)
{
	m_Int_FocLen[0] = aFocLen;
}
