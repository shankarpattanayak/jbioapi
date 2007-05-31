# Microsoft Developer Studio Project File - Name="mds_install" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Console Application" 0x0103

CFG=mds_install - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "mds_install.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "mds_install.mak" CFG="mds_install - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "mds_install - Win32 Debug" (based on "Win32 (x86) Console Application")
!MESSAGE "mds_install - Win32 Release" (based on "Win32 (x86) Console Application")
!MESSAGE "mds_install - Win32 MemDebug" (based on "Win32 (x86) Console Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 1
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "mds_install - Win32 Debug"

# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD CPP /nologo /MTd /W4 /Gm /GX /ZI /Od /I "..\..\..\..\include" /I "..\..\..\..\imports\cdsa\v2_0\inc" /I "..\..\dlutil" /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /FR /FD /c
# SUBTRACT CPP /YX
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /machine:IX86
# ADD LINK32 port.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib winmm.lib bioapi_util.lib /nologo /subsystem:console /debug /machine:I386 /pdbtype:sept /libpath:"..\..\..\..\build\debug\lib" /libpath:"..\..\..\..\imports\cdsa\v2_0\debug\lib"
# SUBTRACT LINK32 /pdb:none
# Begin Custom Build
TargetPath=.\Debug\mds_install.exe
TargetName=mds_install
InputPath=.\Debug\mds_install.exe
SOURCE="$(InputPath)"

"..\..\..\..\build\debug\install\$(TargetName).exe" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	echo on 
	copy $(TargetPath) ..\..\..\..\build\debug\install 
	echo off 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "mds_install - Win32 Release"

# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD CPP /nologo /MT /W4 /GX /O2 /I "..\..\..\..\include" /I "..\..\..\..\imports\cdsa\v2_0\inc" /I "..\..\dlutil" /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /FD /c
# SUBTRACT CPP /YX
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /machine:IX86
# ADD LINK32 port.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib winmm.lib bioapi_util.lib /nologo /subsystem:console /machine:I386 /libpath:"..\..\..\..\build\release\lib" /libpath:"..\..\..\..\imports\cdsa\v2_0\release\lib"
# SUBTRACT LINK32 /pdb:none
# Begin Custom Build
TargetPath=.\Release\mds_install.exe
TargetName=mds_install
InputPath=.\Release\mds_install.exe
SOURCE="$(InputPath)"

"..\..\..\..\build\release\install\$(TargetName).exe" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	echo on 
	copy $(TargetPath) ..\..\..\..\build\release\install 
	echo off 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "mds_install - Win32 MemDebug"

# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "MemDebug"
# PROP Intermediate_Dir "MemDebug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD CPP /nologo /MTd /W4 /Gm /GX /ZI /Od /I "..\..\..\..\include" /I "..\..\..\..\imports\cdsa\v2_0\inc" /I "..\..\dlutil" /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /D "BioAPI_MEMTRACK_ON" /FR /FD /c
# SUBTRACT CPP /YX
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /machine:IX86
# ADD LINK32 port.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib winmm.lib bioapi_util.lib /nologo /subsystem:console /debug /machine:I386 /pdbtype:sept /libpath:"..\..\..\..\build\memdebug\lib" /libpath:"..\..\..\..\imports\cdsa\v2_0\memdebug\lib"
# SUBTRACT LINK32 /pdb:none
# Begin Custom Build
TargetPath=.\MemDebug\mds_install.exe
TargetName=mds_install
InputPath=.\MemDebug\mds_install.exe
SOURCE="$(InputPath)"

"..\..\..\..\build\memdebug\install\$(TargetName).exe" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	echo on 
	copy $(TargetPath) ..\..\..\..\build\memdebug\install 
	echo off 
	
# End Custom Build

!ENDIF 

# Begin Target

# Name "mds_install - Win32 Debug"
# Name "mds_install - Win32 Release"
# Name "mds_install - Win32 MemDebug"
# Begin Source File

SOURCE=..\..\dlutil\dl_portreg.c
# End Source File
# Begin Source File

SOURCE=.\ins_mds.c
# End Source File
# Begin Source File

SOURCE=.\ins_mds.h
# End Source File
# Begin Source File

SOURCE=.\mds_install.c
# End Source File
# End Target
# End Project
