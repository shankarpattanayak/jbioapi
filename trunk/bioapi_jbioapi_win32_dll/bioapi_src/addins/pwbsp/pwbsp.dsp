# Microsoft Developer Studio Project File - Name="pwbsp" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=pwbsp - Win32 MemDebug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "pwbsp.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "pwbsp.mak" CFG="pwbsp - Win32 MemDebug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "pwbsp - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "pwbsp - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "pwbsp - Win32 MemDebug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "pwbsp - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "PWBSP_EXPORTS" /YX /FD /c
# ADD CPP /nologo /MT /W4 /GX /O2 /I "." /I "..\..\include" /I "..\maf" /I "..\..\imports\cdsa\v2_0\inc" /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "PWBSP_EXPORTS" /FD /c
# SUBTRACT CPP /YX
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /machine:I386
# ADD LINK32 util.lib winmm.lib mds_util.lib mds_util_api.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib bioapi_mds300.lib port.lib bioapi_util.lib /nologo /dll /machine:I386 /libpath:"..\..\build\release\lib" /libpath:"..\..\imports\cdsa\v2_0\release\lib"
# Begin Custom Build
TargetPath=.\Release\pwbsp.dll
TargetName=pwbsp
InputPath=.\Release\pwbsp.dll
SOURCE="$(InputPath)"

"..\..\build\release\dll\$(TargetName).dll" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	echo on 
	copy $(TargetPath) ..\..\build\release\dll 
	echo off 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "pwbsp - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "PWBSP_EXPORTS" /YX /FD /GZ /c
# ADD CPP /nologo /MTd /W4 /Gm /GX /ZI /Od /I "." /I "..\..\include" /I "..\maf" /I "..\..\imports\cdsa\v2_0\inc" /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "PWBSP_EXPORTS" /FR /FD /GZ /c
# SUBTRACT CPP /YX
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /debug /machine:I386 /pdbtype:sept
# ADD LINK32 util.lib winmm.lib mds_util.lib mds_util_api.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib bioapi_mds300.lib port.lib bioapi_util.lib /nologo /dll /debug /machine:I386 /pdbtype:sept /libpath:"..\..\build\debug\lib" /libpath:"..\..\imports\cdsa\v2_0\debug\lib"
# Begin Custom Build
TargetPath=.\Debug\pwbsp.dll
TargetName=pwbsp
InputPath=.\Debug\pwbsp.dll
SOURCE="$(InputPath)"

"..\..\build\debug\dll\$(TargetName).dll" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	echo on 
	copy $(TargetPath) ..\..\build\debug\dll 
	echo off 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "pwbsp - Win32 MemDebug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "pwbsp___Win32_MemDebug"
# PROP BASE Intermediate_Dir "pwbsp___Win32_MemDebug"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "MemDebug"
# PROP Intermediate_Dir "MemDebug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MTd /W4 /Gm /GX /ZI /Od /I ".\\" /I "..\..\include" /I "..\..\include\port" /I "..\maf" /I "..\maf\util" /I "..\..\imports\cdsa\v2_0\inc" /I "..\..\framework\mds_util" /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "PWBSP_EXPORTS" /FR /FD /GZ /c
# SUBTRACT BASE CPP /YX
# ADD CPP /nologo /MTd /W4 /Gm /GX /ZI /Od /I "." /I "..\..\include" /I "..\maf" /I "..\..\imports\cdsa\v2_0\inc" /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "PWBSP_EXPORTS" /D "BioAPI_MEMTRACK_ON" /FR /FD /GZ /c
# SUBTRACT CPP /YX
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /debug /machine:I386 /pdbtype:sept
# ADD LINK32 util.lib winmm.lib mds_util.lib mds_util_api.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib bioapi_mds300.lib port.lib bioapi_util.lib /nologo /dll /debug /machine:I386 /pdbtype:sept /libpath:"..\..\build\memdebug\lib" /libpath:"..\..\imports\cdsa\v2_0\memdebug\lib"
# Begin Custom Build
TargetPath=.\MemDebug\pwbsp.dll
TargetName=pwbsp
InputPath=.\MemDebug\pwbsp.dll
SOURCE="$(InputPath)"

"..\..\build\memdebug\dll\$(TargetName).dll" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	echo on 
	copy $(TargetPath) ..\..\build\memdebug\dll 
	echo off 
	
# End Custom Build

!ENDIF 

# Begin Target

# Name "pwbsp - Win32 Release"
# Name "pwbsp - Win32 Debug"
# Name "pwbsp - Win32 MemDebug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
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
# Begin Source File

SOURCE=.\pwbsp.def
# End Source File
# Begin Source File

SOURCE=.\pwbspi.c
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\maf_config.h
# End Source File
# Begin Source File

SOURCE=.\precomp.h
# End Source File
# Begin Source File

SOURCE=.\resource.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\PwDlg.rc
# End Source File
# End Group
# End Target
# End Project
