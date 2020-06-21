# Microsoft Developer Studio Project File - Name="IPOP" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** NICHT BEARBEITEN **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=IPOP - Win32 Debug
!MESSAGE Dies ist kein gültiges Makefile. Zum Erstellen dieses Projekts mit NMAKE
!MESSAGE verwenden Sie den Befehl "Makefile exportieren" und führen Sie den Befehl
!MESSAGE 
!MESSAGE NMAKE /f "IPOP.mak".
!MESSAGE 
!MESSAGE Sie können beim Ausführen von NMAKE eine Konfiguration angeben
!MESSAGE durch Definieren des Makros CFG in der Befehlszeile. Zum Beispiel:
!MESSAGE 
!MESSAGE NMAKE /f "IPOP.mak" CFG="IPOP - Win32 Debug"
!MESSAGE 
!MESSAGE Für die Konfiguration stehen zur Auswahl:
!MESSAGE 
!MESSAGE "IPOP - Win32 Release" (basierend auf  "Win32 (x86) Application")
!MESSAGE "IPOP - Win32 Debug" (basierend auf  "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "IPOP - Win32 Release"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x407 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x407 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 /nologo /subsystem:windows /machine:I386

!ELSEIF  "$(CFG)" == "IPOP - Win32 Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /I "..\ltilib" /I "..\ltilib\include" /I "..\GCV" /I "..\DIB" /I "..\IMAGESERVER" /I "..\IMAGEPROC" /I "..\IMG" /I "..\OpenCV" /I "..\HIGHGui" /I "..\dxsdk" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x407 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x407 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 opengl32.lib glu32.lib glaux.lib ..\ltilib\ltilib.lib ..\IMAGESERVER\Debug\ImageServer.lib highgui.lib cv.lib strmbasd.lib winmm.lib vfw32.lib d3dx9.lib ..\IMG\PXC\ilib_32.lib ipl.lib /nologo /subsystem:windows /debug /machine:I386 /nodefaultlib:"LIBCD.lib" /pdbtype:sept /libpath:"..\ltilib"
# SUBTRACT LINK32 /verbose

!ENDIF 

# Begin Target

# Name "IPOP - Win32 Release"
# Name "IPOP - Win32 Debug"
# Begin Group "Quellcodedateien"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\ChildFrm.cpp
# End Source File
# Begin Source File

SOURCE=.\Disp_3D_Doc.cpp
# End Source File
# Begin Source File

SOURCE=.\Disp_3D_View.cpp
# End Source File
# Begin Source File

SOURCE=.\Disp_Live_Doc.cpp
# End Source File
# Begin Source File

SOURCE=.\Disp_Live_View.cpp
# End Source File
# Begin Source File

SOURCE=.\Disp_Pic_Doc.cpp
# End Source File
# Begin Source File

SOURCE=.\Disp_Pic_View.cpp
# End Source File
# Begin Source File

SOURCE=.\Dlg_3D.cpp
# End Source File
# Begin Source File

SOURCE=.\Dlg_Camera.cpp
# End Source File
# Begin Source File

SOURCE=.\Dlg_Etalon.cpp
# End Source File
# Begin Source File

SOURCE=.\Dlg_IPParams.cpp
# End Source File
# Begin Source File

SOURCE=.\Dlg_Pose.cpp
# End Source File
# Begin Source File

SOURCE=.\IPOP.rc
# End Source File
# Begin Source File

SOURCE=.\IPOPApp.cpp
# End Source File
# Begin Source File

SOURCE=.\MainFrm.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# End Group
# Begin Group "Header-Dateien"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\ChildFrm.h
# End Source File
# Begin Source File

SOURCE=.\Disp_3D_Doc.h
# End Source File
# Begin Source File

SOURCE=.\Disp_3D_View.h
# End Source File
# Begin Source File

SOURCE=.\Disp_Live_Doc.h
# End Source File
# Begin Source File

SOURCE=.\Disp_Live_View.h
# End Source File
# Begin Source File

SOURCE=.\Disp_Pic_Doc.h
# End Source File
# Begin Source File

SOURCE=.\Disp_Pic_View.h
# End Source File
# Begin Source File

SOURCE=.\Dlg_3D.h
# End Source File
# Begin Source File

SOURCE=.\Dlg_Camera.h
# End Source File
# Begin Source File

SOURCE=.\Dlg_Etalon.h
# End Source File
# Begin Source File

SOURCE=.\Dlg_IPParams.h
# End Source File
# Begin Source File

SOURCE=.\Dlg_Pose.h
# End Source File
# Begin Source File

SOURCE=.\IPOPApp.h
# End Source File
# Begin Source File

SOURCE=.\MainFrm.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# End Group
# Begin Group "Ressourcendateien"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\IPOP.ico
# End Source File
# Begin Source File

SOURCE=.\res\IPOP.rc2
# End Source File
# Begin Source File

SOURCE=.\res\IPOPDoc.ico
# End Source File
# Begin Source File

SOURCE=.\res\Toolbar.bmp
# End Source File
# End Group
# Begin Source File

SOURCE=.\backup.txt
# End Source File
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# Begin Source File

SOURCE=.\ToDo.txt
# End Source File
# End Target
# End Project
