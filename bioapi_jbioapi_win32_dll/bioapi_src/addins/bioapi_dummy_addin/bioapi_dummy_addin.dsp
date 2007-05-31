# Microsoft Developer Studio Project File - Name="bioapi_dummy_addin" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=bioapi_dummy_addin - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "bioapi_dummy_addin.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "bioapi_dummy_addin.mak" CFG="bioapi_dummy_addin - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "bioapi_dummy_addin - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "bioapi_dummy_addin - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "bioapi_dummy_addin - Win32 MemDebug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 1
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "bioapi_dummy_addin - Win32 Debug"

# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD CPP /nologo /MTd /W4 /Gm /GX /ZI /Od /I "." /I "..\..\include" /I "..\maf" /I "..\..\imports\cdsa\v2_0\inc" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "BIOAPI_DUMMY_ADDIN_EXPORTS" /FD /GZ /c
# SUBTRACT CPP /YX
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /machine:IX86
# ADD LINK32 mds_util.lib util.lib winmm.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib bioapi_mds300.lib port.lib bioapi_util.lib /nologo /dll /debug /machine:I386 /out:"Debug/bioapi_dummy100.dll" /pdbtype:sept /libpath:"..\..\build\debug\lib" /libpath:"..\..\imports\cdsa\v2_0\debug\lib"
# SUBTRACT LINK32 /pdb:none
# Begin Custom Build
TargetDir=.\Debug
TargetPath=.\Debug\bioapi_dummy100.dll
TargetName=bioapi_dummy100
InputPath=.\Debug\bioapi_dummy100.dll
SOURCE="$(InputPath)"

BuildCmds= \
	echo on \
	copy $(TargetPath) ..\..\build\debug\dll \
	copy $(TargetDir)\$(TargetName).lib ..\..\build\debug\lib \
	echo off \
	

"..\..\build\debug\dll\$(TargetName).dll" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"..\..\build\debug\lib\$(TargetName).lib" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "bioapi_dummy_addin - Win32 Release"

# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD CPP /nologo /MT /W4 /GX /O2 /I "." /I "..\..\include" /I "..\maf" /I "..\..\imports\cdsa\v2_0\inc" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "BIOAPI_DUMMY_ADDIN_EXPORTS" /FD /c
# SUBTRACT CPP /YX
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /machine:IX86
# ADD LINK32 mds_util.lib util.lib winmm.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib bioapi_mds300.lib port.lib bioapi_util.lib /nologo /dll /machine:I386 /out:"Release/bioapi_dummy100.dll" /libpath:"..\..\build\release\lib" /libpath:"..\..\imports\cdsa\v2_0\release\lib"
# SUBTRACT LINK32 /pdb:none
# Begin Custom Build
TargetDir=.\Release
TargetPath=.\Release\bioapi_dummy100.dll
TargetName=bioapi_dummy100
InputPath=.\Release\bioapi_dummy100.dll
SOURCE="$(InputPath)"

BuildCmds= \
	echo on \
	copy $(TargetPath) ..\..\build\release\dll \
	copy $(TargetDir)\$(TargetName).lib ..\..\build\release\lib \
	echo off \
	

"..\..\build\release\dll\$(TargetName).dll" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"..\..\build\release\lib\$(TargetName).lib" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "bioapi_dummy_addin - Win32 MemDebug"

# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "MemDebug"
# PROP Intermediate_Dir "MemDebug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD CPP /nologo /MTd /W4 /Gm /GX /ZI /Od /I "." /I "..\..\include" /I "..\maf" /I "..\..\imports\cdsa\v2_0\inc" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "BIOAPI_DUMMY_ADDIN_EXPORTS" /D "BioAPI_MEMTRACK_ON" /FD /GZ /c
# SUBTRACT CPP /YX
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /machine:IX86
# ADD LINK32 mds_util.lib util.lib winmm.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib bioapi_mds300.lib port.lib bioapi_util.lib /nologo /dll /debug /machine:I386 /out:"MemDebug/bioapi_dummy100.dll" /pdbtype:sept /libpath:"..\..\build\memdebug\lib" /libpath:"..\..\imports\cdsa\v2_0\memdebug\lib" /FIXED:no
# SUBTRACT LINK32 /pdb:none
# Begin Custom Build
TargetDir=.\MemDebug
TargetPath=.\MemDebug\bioapi_dummy100.dll
TargetName=bioapi_dummy100
InputPath=.\MemDebug\bioapi_dummy100.dll
SOURCE="$(InputPath)"

BuildCmds= \
	echo on \
	copy $(TargetPath) ..\..\build\memdebug\dll \
	copy $(TargetDir)\$(TargetName).lib ..\..\build\memdebug\lib \
	echo off \
	

"..\..\build\memdebug\dll\$(TargetName).dll" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"..\..\build\memdebug\lib\$(TargetName).lib" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ENDIF 

# Begin Target

# Name "bioapi_dummy_addin - Win32 Debug"
# Name "bioapi_dummy_addin - Win32 Release"
# Name "bioapi_dummy_addin - Win32 MemDebug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\bioapi_dummy_addin.def
# End Source File
# Begin Source File

SOURCE=.\bioapi_dummy_addini.c
# End Source File
# Begin Source File

SOURCE=.\install.c
# End Source File
# Begin Source File

SOURCE=..\maf\maf_collectn.c
# End Source File
# Begin Source File

SOURCE=..\maf\maf_dllmain.c
# End Source File
# Begin Source File

SOURCE=.\mod_manage.c
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\bioapi_dummy_addini_err.h
# End Source File
# Begin Source File

SOURCE=.\maf_config.h
# End Source File
# Begin Source File

SOURCE=.\precomp.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# End Group
# End Target
# End Project
