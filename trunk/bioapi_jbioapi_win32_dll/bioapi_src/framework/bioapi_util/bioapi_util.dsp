# Microsoft Developer Studio Project File - Name="bioapi_util" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=bioapi_util - Win32 MemDebug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "bioapi_util.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "bioapi_util.mak" CFG="bioapi_util - Win32 MemDebug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "bioapi_util - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "bioapi_util - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE "bioapi_util - Win32 MemDebug" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "bioapi_util - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /YX /FD /c
# ADD CPP /nologo /MT /W4 /GX /O2 /I "." /I "..\..\include" /I "..\mds_util" /I "..\..\imports\cdsa\v2_0\inc" /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /FD /c
# SUBTRACT CPP /YX
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo
# Begin Custom Build
TargetPath=.\Release\bioapi_util.lib
TargetName=bioapi_util
InputPath=.\Release\bioapi_util.lib
SOURCE="$(InputPath)"

"..\..\build\release\lib\$(TargetName).lib" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	echo on 
	copy $(TargetPath) ..\..\build\release\lib 
	echo off 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "bioapi_util - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /YX /FD /GZ /c
# ADD CPP /nologo /MTd /W4 /Gm /GX /ZI /Od /I "." /I "..\..\include" /I "..\mds_util" /I "..\..\imports\cdsa\v2_0\inc" /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /FD /GZ /c
# SUBTRACT CPP /YX
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo
# Begin Custom Build
TargetPath=.\Debug\bioapi_util.lib
TargetName=bioapi_util
InputPath=.\Debug\bioapi_util.lib
SOURCE="$(InputPath)"

"..\..\build\debug\lib\$(TargetName).lib" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	echo on 
	copy $(TargetPath) ..\..\build\debug\lib 
	echo off 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "bioapi_util - Win32 MemDebug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "MemDebug"
# PROP BASE Intermediate_Dir "MemDebug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "MemDebug"
# PROP Intermediate_Dir "MemDebug"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MTd /W4 /Gm /GX /ZI /Od /I "." /I "..\..\include" /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /FD /GZ /c
# SUBTRACT BASE CPP /YX
# ADD CPP /nologo /MTd /W4 /Gm /GX /ZI /Od /I "." /I "..\..\include" /I "..\mds_util" /I "..\..\imports\cdsa\v2_0\inc" /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /D "BioAPI_MEMTRACK_ON" /FD /GZ /c
# SUBTRACT CPP /YX
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo
# Begin Custom Build
TargetPath=.\MemDebug\bioapi_util.lib
TargetName=bioapi_util
InputPath=.\MemDebug\bioapi_util.lib
SOURCE="$(InputPath)"

"..\..\build\memdebug\lib\$(TargetName).lib" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	echo on 
	copy $(TargetPath) ..\..\build\memdebug\lib 
	echo off 
	
# End Custom Build

!ENDIF 

# Begin Target

# Name "bioapi_util - Win32 Release"
# Name "bioapi_util - Win32 Debug"
# Name "bioapi_util - Win32 MemDebug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\bsp_install.c
# End Source File
# Begin Source File

SOURCE=.\bsp_schema.c
# End Source File
# Begin Source File

SOURCE=.\convert.c
# End Source File
# Begin Source File

SOURCE=.\device_schema.c
# End Source File
# Begin Source File

SOURCE=.\memfuncs.c
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=..\..\include\bioapi_util.h
# End Source File
# Begin Source File

SOURCE=..\..\include\bsp_schema.h
# End Source File
# Begin Source File

SOURCE=..\..\include\device_schema.h
# End Source File
# End Group
# End Target
# End Project
