# Microsoft Developer Studio Project File - Name="mds_util_api" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=mds_util_api - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "mds_util_api.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "mds_util_api.mak" CFG="mds_util_api - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "mds_util_api - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE "mds_util_api - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "mds_util_api - Win32 MemDebug" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 1
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "mds_util_api - Win32 Debug"

# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Target_Dir ""
# ADD CPP /nologo /MTd /W4 /GX /ZI /Od /I "." /I "..\..\include" /I "..\..\imports\cdsa\v2_0\inc" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /Fr /FD /c
# SUBTRACT CPP /YX
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD LIB32 /nologo
# Begin Custom Build
TargetPath=.\Debug\mds_util_api.lib
TargetName=mds_util_api
InputPath=.\Debug\mds_util_api.lib
SOURCE="$(InputPath)"

"..\..\build\debug\lib\$(TargetName).lib" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	echo on 
	copy $(TargetPath) ..\..\build\debug\lib 
	echo off 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "mds_util_api - Win32 Release"

# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
# ADD CPP /nologo /MT /W4 /GX /O2 /I "." /I "..\..\include" /I "..\..\imports\cdsa\v2_0\inc" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /FD /c
# SUBTRACT CPP /Fr /YX
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD LIB32 /nologo
# Begin Custom Build
TargetPath=.\Release\mds_util_api.lib
TargetName=mds_util_api
InputPath=.\Release\mds_util_api.lib
SOURCE="$(InputPath)"

"..\..\build\release\lib\$(TargetName).lib" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	echo on 
	copy $(TargetPath) ..\..\build\release\lib 
	echo off 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "mds_util_api - Win32 MemDebug"

# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "MemDebug"
# PROP Intermediate_Dir "MemDebug"
# PROP Target_Dir ""
# ADD CPP /nologo /MTd /W4 /GX /ZI /Od /I "." /I "..\..\include" /I "..\..\imports\cdsa\v2_0\inc" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "BioAPI_MEMTRACK_ON" /Fr /FD /c
# SUBTRACT CPP /YX
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD LIB32 /nologo
# Begin Custom Build
TargetPath=.\MemDebug\mds_util_api.lib
TargetName=mds_util_api
InputPath=.\MemDebug\mds_util_api.lib
SOURCE="$(InputPath)"

"..\..\build\memdebug\lib\$(TargetName).lib" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	echo on 
	copy $(TargetPath) ..\..\build\memdebug\lib 
	echo off 
	
# End Custom Build

!ENDIF 

# Begin Target

# Name "mds_util_api - Win32 Debug"
# Name "mds_util_api - Win32 Release"
# Name "mds_util_api - Win32 MemDebug"
# Begin Group "Source Files"

# PROP Default_Filter "c"
# Begin Source File

SOURCE=.\mds_app_util.c
# End Source File
# Begin Source File

SOURCE=.\mds_util_attr.c
# End Source File
# Begin Source File

SOURCE=.\mds_util_query.c
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h"
# Begin Source File

SOURCE=.\mds_app_util.h
# End Source File
# Begin Source File

SOURCE=..\..\imports\cdsa\v2_0\inc\intel\mds_util_api.h
# End Source File
# Begin Source File

SOURCE=..\..\imports\cdsa\v2_0\inc\intel\mds_util_helper.h
# End Source File
# Begin Source File

SOURCE=.\mds_util_intrn.h
# End Source File
# Begin Source File

SOURCE=..\..\imports\cdsa\v2_0\inc\intel\mds_util_type.h
# End Source File
# End Group
# End Target
# End Project
