========================================================================
       STATISCHE BIBLIOTHEK : GCV
========================================================================


Diese GCV-Bibliothek hat der Anwendungs-Assistent für Sie erstellt.  

Diese Datei enthält eine Zusammenfassung dessen, was Sie in jeder der Dateien
finden, die Ihre GCV-Anwendung bilden.

/////////////////////////////////////////////////////////////////////////////

StdAfx.h, StdAfx.cpp
    Diese Dateien werden zum Erstellen einer vorkompilierten Header-Datei (PCH) namens
    GCV.pch und einer vorkompilierten Typdatei namens StdAfx.obj verwendet.

/////////////////////////////////////////////////////////////////////////////
Die Schalter für den Compiler und Linker wurden verändert, um MFC zu unterstützen. Die
Verwendung des MFC-Klassen-Assistenten für dieses Projekt erfordert von Ihnen das  
Hinzufügen verschiedener Dateien zum Projekt, einschließlich "resource.h", "GCV.rc" 
und einer "GCV.h", die resource.h einbezieht. Wenn Sie einer statischen Bibliothek 
eine rc-Datei hinzufügen, können vielleicht dadurch Probleme auftreten, daß eine 
Beschränkung auf nur eine rc-Datei in einer DLL oder EXE besteht. Dieses Problem kann 
umgangen werden, indem Sie die .rc-Datei der Bibliothek in die .rc-Datei des übergeordneten
Projekts einbeziehen.

/////////////////////////////////////////////////////////////////////////////
Weitere Hinweise:

Der Anwendungs-Assistent verwendet "ZU ERLEDIGEN:", um Bereiche des Quellcodes zu
kennzeichnen, die Sie hinzufügen oder anpassen sollten.


/////////////////////////////////////////////////////////////////////////////
