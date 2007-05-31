# Microsoft Developer Studio Project File - Name="mds" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=mds - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "mds.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "mds.mak" CFG="mds - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "mds - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "mds - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "mds - Win32 MemDebug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 1
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "mds - Win32 Debug"

# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD CPP /nologo /MTd /W4 /Gm /GX /ZI /Od /I "..\..\..\..\imports\intel\integrity\r1_2_1\inc" /I "..\..\..\include" /I "..\..\..\imports\cdsa\v2_0\inc" /I "..\dal-dl" /I "..\dlutil" /I "..\flatfile" /I "..\..\maf" /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "STRONG_TYPES" /D "MODULE_DIRECTORY_SERVICES" /FR /FD /c
# SUBTRACT CPP /YX
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /o "NUL" /win32
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /machine:IX86
# ADD LINK32 winmm.lib kernel32.lib user32.lib advapi32.lib port.lib bioapi_util.lib /nologo /subsystem:windows /dll /profile /debug /machine:I386 /out:"Debug/bioapi_mds300.dll" /libpath:"..\..\..\build\debug\lib" /libpath:"..\..\..\imports\cdsa\v2_0\debug\lib"
# Begin Custom Build
TargetDir=.\Debug
TargetPath=.\Debug\bioapi_mds300.dll
TargetName=bioapi_mds300
InputPath=.\Debug\bioapi_mds300.dll
SOURCE="$(InputPath)"

BuildCmds= \
	echo on \
	copy $(TargetPath) ..\..\..\build\debug\dll \
	copy $(TargetDir)\$(TargetName).lib ..\..\..\build\debug\lib \
	echo off \
	

"..\..\..\build\debug\dll\$(TargetName).dll" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"..\..\..\build\debug\lib\$(TargetName).lib" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "mds - Win32 Release"

# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD CPP /nologo /MT /W4 /GX /O2 /I "..\..\..\..\imports\intel\integrity\r1_2_1\inc" /I "..\..\..\include" /I "..\..\..\imports\cdsa\v2_0\inc" /I "..\dal-dl" /I "..\dlutil" /I "..\flatfile" /I "..\..\maf" /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "STRONG_TYPES" /D "MODULE_DIRECTORY_SERVICES" /FD /c
# SUBTRACT CPP /YX
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /o "NUL" /win32
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /machine:IX86
# ADD LINK32 winmm.lib kernel32.lib user32.lib advapi32.lib port.lib bioapi_util.lib /nologo /subsystem:windows /dll /machine:I386 /out:"Release/bioapi_mds300.dll" /libpath:"..\..\..\build\release\lib" /libpath:"..\..\..\imports\cdsa\v2_0\release\lib"
# SUBTRACT LINK32 /pdb:none
# Begin Custom Build
TargetDir=.\Release
TargetPath=.\Release\bioapi_mds300.dll
TargetName=bioapi_mds300
InputPath=.\Release\bioapi_mds300.dll
SOURCE="$(InputPath)"

BuildCmds= \
	echo on \
	copy $(TargetPath) ..\..\..\build\release\dll \
	copy $(TargetDir)\$(TargetName).lib ..\..\..\build\release\lib \
	echo off \
	

"..\..\..\build\release\dll\$(TargetName).dll" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"..\..\..\build\release\lib\$(TargetName).lib" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "mds - Win32 MemDebug"

# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "MemDebug"
# PROP Intermediate_Dir "MemDebug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD CPP /nologo /MTd /W4 /Gm /GX /ZI /Od /I "..\..\..\include" /I "..\..\..\imports\cdsa\v2_0\inc" /I "..\dal-dl" /I "..\dlutil" /I "..\flatfile" /I "..\..\maf" /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "STRONG_TYPES" /D "MODULE_DIRECTORY_SERVICES" /D "BioAPI_MEMTRACK_ON" /FR /FD /c
# SUBTRACT CPP /YX
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /o "NUL" /win32
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /machine:IX86
# ADD LINK32 winmm.lib kernel32.lib user32.lib advapi32.lib port.lib bioapi_util.lib /nologo /subsystem:windows /dll /debug /machine:I386 /out:"MemDebug/bioapi_mds300.dll" /libpath:"..\..\..\build\memdebug\lib" /libpath:"..\..\..\imports\cdsa\v2_0\memdebug\lib" /FIXED:no
# SUBTRACT LINK32 /pdb:none
# Begin Custom Build
TargetDir=.\MemDebug
TargetPath=.\MemDebug\bioapi_mds300.dll
TargetName=bioapi_mds300
InputPath=.\MemDebug\bioapi_mds300.dll
SOURCE="$(InputPath)"

BuildCmds= \
	echo on \
	copy $(TargetPath) ..\..\..\build\memdebug\dll \
	copy $(TargetDir)\$(TargetName).lib ..\..\..\build\memdebug\lib \
	echo off \
	

"..\..\..\build\memdebug\dll\$(TargetName).dll" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"..\..\..\build\memdebug\lib\$(TargetName).lib" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ENDIF 

# Begin Target

# Name "mds - Win32 Debug"
# Name "mds - Win32 Release"
# Name "mds - Win32 MemDebug"
# Begin Group "Flat File Source Files"

# PROP Default_Filter ""
# Begin Group "Flat File Header Files"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\flatfile\ff_common.h
# End Source File
# Begin Source File

SOURCE=..\flatfile\ff_data.h
# End Source File
# Begin Source File

SOURCE=..\flatfile\ff_freelist.h
# End Source File
# Begin Source File

SOURCE=..\flatfile\ff_index.h
# End Source File
# Begin Source File

SOURCE=..\flatfile\ff_port.h
# End Source File
# Begin Source File

SOURCE=..\flatfile\ff_util.h
# End Source File
# End Group
# Begin Group "DAL Source"

# PROP Default_Filter ""
# Begin Group "DAL Header Files"

# PROP Default_Filter ""
# Begin Source File

SOURCE="..\dal-dl\dal_classes.h"
# End Source File
# Begin Source File

SOURCE="..\dal-dl\dal_common.h"
# End Source File
# Begin Source File

SOURCE="..\dal-dl\dal_dlbe.h"
# End Source File
# Begin Source File

SOURCE="..\dal-dl\dal_internal.h"
# End Source File
# Begin Source File

SOURCE="..\dal-dl\dal_schema.h"
# End Source File
# Begin Source File

SOURCE="..\dal-dl\dal_src.h"
# End Source File
# Begin Source File

SOURCE="..\dal-dl\dal_translation.h"
# End Source File
# Begin Source File

SOURCE="..\dal-dl\dal_typearray.h"
# End Source File
# Begin Source File

SOURCE=..\flatfile\flatfile.h
# End Source File
# Begin Source File

SOURCE=..\..\maf\maf_callouts.h
# End Source File
# Begin Source File

SOURCE=..\..\maf\maf_collectn.h
# End Source File
# Begin Source File

SOURCE=..\..\maf\maf_util.h
# End Source File
# End Group
# Begin Source File

SOURCE="..\dal-dl\dal_database.cpp"
# End Source File
# Begin Source File

SOURCE="..\dal-dl\dal_database_list.cpp"
# End Source File
# Begin Source File

SOURCE="..\dal-dl\dal_internal.cpp"
# End Source File
# Begin Source File

SOURCE="..\dal-dl\dal_preparefield.cpp"
# End Source File
# Begin Source File

SOURCE="..\dal-dl\dal_recordtable.cpp"
# End Source File
# Begin Source File

SOURCE="..\dal-dl\dal_relation.cpp"
# End Source File
# Begin Source File

SOURCE="..\dal-dl\dal_src.cpp"
# End Source File
# Begin Source File

SOURCE="..\dal-dl\dal_translation.cpp"
# End Source File
# End Group
# Begin Source File

SOURCE=..\flatfile\ff_data.c
# End Source File
# Begin Source File

SOURCE=..\flatfile\ff_freelist.c
# End Source File
# Begin Source File

SOURCE=..\flatfile\ff_func.cpp
# End Source File
# Begin Source File

SOURCE=..\flatfile\ff_index.c
# End Source File
# Begin Source File

SOURCE=..\flatfile\ff_port.c
# End Source File
# Begin Source File

SOURCE=..\flatfile\ff_table.cpp
# End Source File
# Begin Source File

SOURCE=..\flatfile\ff_util.c
# End Source File
# End Group
# Begin Group "Directory Service Files"

# PROP Default_Filter ".c .cpp .h"
# Begin Source File

SOURCE=.\defines.h
# End Source File
# Begin Source File

SOURCE=..\..\maf\maf_collectn.c
# End Source File
# Begin Source File

SOURCE=.\mds.cpp
# End Source File
# Begin Source File

SOURCE=.\mds.def
# End Source File
# Begin Source File

SOURCE=.\mds_create.cpp
# End Source File
# Begin Source File

SOURCE=.\mds_emulate.cpp
# End Source File
# Begin Source File

SOURCE=.\mds_internal.h
# End Source File
# End Group
# Begin Group "DLUTIL Files"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\dlutil\dl_file.c
# End Source File
# Begin Source File

SOURCE=..\dlutil\dl_fileread.c
# End Source File
# Begin Source File

SOURCE=..\dlutil\dl_filewrite.c
# End Source File
# Begin Source File

SOURCE=..\dlutil\dl_isbad.c
# End Source File
# Begin Source File

SOURCE=..\dlutil\dl_memutil.c
# End Source File
# Begin Source File

SOURCE=..\dlutil\dl_portreg.c
# End Source File
# Begin Source File

SOURCE=..\dlutil\dl_reg.c
# End Source File
# End Group
# End Target
# End Project
