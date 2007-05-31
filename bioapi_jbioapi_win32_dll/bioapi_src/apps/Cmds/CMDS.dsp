# Microsoft Developer Studio Project File - Name="CMDS" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=CMDS - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE
!MESSAGE NMAKE /f "CMDS.mak".
!MESSAGE
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE
!MESSAGE NMAKE /f "CMDS.mak" CFG="CMDS - Win32 Debug"
!MESSAGE
!MESSAGE Possible choices for configuration are:
!MESSAGE
!MESSAGE "CMDS - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE "CMDS - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "CMDS - Win32 MemDebug" (based on "Win32 (x86) Static Library")
!MESSAGE

# Begin Project
# PROP AllowPerConfigDependencies 1
CPP=cl.exe
RSC=rc.exe

!IF	 "$(CFG)" == "CMDS - Win32 Debug"

# PROP Use_MFC 2
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Target_Dir ""
# ADD CPP /nologo /MDd /W4 /GX /ZI /Od /I "..\install" /I "..\framework\mds_util" /I "..\imports\cdsa\v2_0\appsrc\inc" /I "..\imports\cdsa\v2_0\inc" /I "..\include" /I "..\..\include" /I "..\..\framework\mds_util" /I "..\..\imports\cdsa\v2_0\appsrc\inc" /I "..\..\imports\cdsa\v2_0\inc" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FD /GZ /c
# SUBTRACT CPP /Fr /YX /Yc /Yu
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD LIB32 /nologo
# Begin Custom Build
TargetPath=.\Debug\CMDS.lib
TargetName=CMDS
InputPath=.\Debug\CMDS.lib
SOURCE="$(InputPath)"

"..\..\build\debug\lib\$(TargetName).lib" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	echo on
	copy $(TargetPath) ..\..\build\debug\lib
	echo off

# End Custom Build

!ELSEIF	 "$(CFG)" == "CMDS - Win32 Release"

# PROP Use_MFC 2
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
# ADD CPP /nologo /MD /W4 /GX /O2 /I "..\install" /I "..\framework\mds_util" /I "..\imports\cdsa\v2_0\appsrc\inc" /I "..\imports\cdsa\v2_0\inc" /I "..\include" /I "..\..\include" /I "..\..\framework\mds_util" /I "..\..\imports\cdsa\v2_0\appsrc\inc" /I "..\..\imports\cdsa\v2_0\inc" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FD /c
# SUBTRACT CPP /YX /Yc /Yu
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD LIB32 /nologo
# Begin Custom Build
TargetPath=.\Release\CMDS.lib
TargetName=CMDS
InputPath=.\Release\CMDS.lib
SOURCE="$(InputPath)"

"..\..\build\release\lib\$(TargetName).lib" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	echo on
	copy $(TargetPath) ..\..\build\release\lib
	echo off

# End Custom Build

!ELSEIF	 "$(CFG)" == "CMDS - Win32 MemDebug"

# PROP Use_MFC 2
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "MemDebug"
# PROP Intermediate_Dir "MemDebug"
# PROP Target_Dir ""
# ADD CPP /nologo /MDd /W4 /GX /ZI /Od /I "..\..\include" /I "..\..\framework\mds_util" /I "..\..\imports\cdsa\v2_0\appsrc\inc" /I "..\..\imports\cdsa\v2_0\inc" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /D "BioAPI_MEMTRACK_ON" /FD /GZ /c
# SUBTRACT CPP /Fr /YX /Yc /Yu
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD LIB32 /nologo
# Begin Custom Build
TargetPath=.\MemDebug\CMDS.lib
TargetName=CMDS
InputPath=.\MemDebug\CMDS.lib
SOURCE="$(InputPath)"

"..\..\build\memdebug\lib\$(TargetName).lib" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	echo on
	copy $(TargetPath) ..\..\build\memdebug\lib
	echo off

# End Custom Build

!ENDIF

# Begin Target

# Name "CMDS - Win32 Debug"
# Name "CMDS - Win32 Release"
# Name "CMDS - Win32 MemDebug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\CdsaRec.cpp
# End Source File
# Begin Source File

SOURCE=.\CMDS.cpp
# End Source File
# Begin Source File

SOURCE=.\CMDSUtil.cpp
# End Source File
# Begin Source File

SOURCE=.\Dir.cpp
# End Source File
# Begin Source File

SOURCE=.\Rec.cpp
# End Source File
# Begin Source File

SOURCE=.\RecType.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# SUBTRACT CPP /YX /Yc
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\CdsaRec.h
# End Source File
# Begin Source File

SOURCE=.\CdsaRecType.h
# End Source File
# Begin Source File

SOURCE=.\CMDS.h
# End Source File
# Begin Source File

SOURCE=.\CMDSUtil.h
# End Source File
# Begin Source File

SOURCE=.\Dir.h
# End Source File
# Begin Source File

SOURCE=.\MDSRecType.h
# End Source File
# Begin Source File

SOURCE=.\Rec.h
# End Source File
# Begin Source File

SOURCE=.\RecType.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# End Group
# End Target
# End Project
