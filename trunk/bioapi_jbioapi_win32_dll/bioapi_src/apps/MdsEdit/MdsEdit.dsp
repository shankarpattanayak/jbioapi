# Microsoft Developer Studio Project File - Name="MdsEdit" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=MdsEdit - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "MdsEdit.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "MdsEdit.mak" CFG="MdsEdit - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "MdsEdit - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE "MdsEdit - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "MdsEdit - Win32 MemDebug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 1
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "MdsEdit - Win32 Debug"

# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD CPP /nologo /MDd /W4 /GX /ZI /Od /I "..\install" /I "..\framework\mds_util" /I "..\imports\cdsa\v2_0\appsrc\inc" /I "..\imports\cdsa\v2_0\inc" /I "..\include" /I "..\..\include" /I "..\..\framework\mds_util" /I "..\..\imports\cdsa\v2_0\inc" /I "..\CMDS" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FD /GZ /c
# SUBTRACT CPP /Fr /YX /Yc /Yu
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /machine:IX86
# ADD LINK32 bioapi_mds300.lib CMDS.lib version.lib /nologo /subsystem:windows /debug /machine:I386 /nodefaultlib:"msvcrt" /out:"Debug/MdsEdit300.exe" /pdbtype:sept /libpath:"..\..\build\debug\lib"
# SUBTRACT LINK32 /pdb:none
# Begin Custom Build
TargetPath=.\Debug\MdsEdit300.exe
TargetName=MdsEdit300
InputPath=.\Debug\MdsEdit300.exe
SOURCE="$(InputPath)"

"..\..\build\debug\bin\$(TargetName).exe" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	echo on 
	copy $(TargetPath) ..\..\build\debug\bin 
	echo off 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "MdsEdit - Win32 Release"

# PROP Use_MFC 6
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD CPP /nologo /MD /W4 /GX /O2 /I "..\install" /I "..\framework\mds_util" /I "..\imports\cdsa\v2_0\appsrc\inc" /I "..\imports\cdsa\v2_0\inc" /I "..\include" /I "..\..\include" /I "..\..\framework\mds_util" /I "..\..\imports\cdsa\v2_0\inc" /I "..\CMDS" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FD /c
# SUBTRACT CPP /Fr /YX /Yc /Yu
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /machine:IX86
# ADD LINK32 bioapi_mds300.lib CMDS.lib version.lib /nologo /subsystem:windows /machine:I386 /out:"Release/MdsEdit300.exe" /libpath:"..\..\build\release\lib"
# SUBTRACT LINK32 /pdb:none
# Begin Custom Build
TargetPath=.\Release\MdsEdit300.exe
TargetName=MdsEdit300
InputPath=.\Release\MdsEdit300.exe
SOURCE="$(InputPath)"

"..\..\build\release\bin\$(TargetName).exe" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	echo on 
	copy $(TargetPath) ..\..\build\release\bin 
	echo off 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "MdsEdit - Win32 MemDebug"

# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "MemDebug"
# PROP Intermediate_Dir "MemDebug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD CPP /nologo /MDd /W4 /GX /ZI /Od /I "..\..\include" /I "..\..\framework\mds_util" /I "..\..\imports\cdsa\v2_0\inc" /I "..\CMDS" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /D "BioAPI_MEMTRACK_ON" /FD /GZ /c
# SUBTRACT CPP /Fr /YX /Yc /Yu
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /machine:IX86
# ADD LINK32 bioapi_mds300.lib CMDS.lib version.lib /nologo /subsystem:windows /debug /machine:I386 /nodefaultlib:"msvcrt" /out:"MemDebug/MdsEdit300.exe" /pdbtype:sept /libpath:"..\..\build\memdebug\lib"
# SUBTRACT LINK32 /pdb:none
# Begin Custom Build
TargetPath=.\MemDebug\MdsEdit300.exe
TargetName=MdsEdit300
InputPath=.\MemDebug\MdsEdit300.exe
SOURCE="$(InputPath)"

"..\..\build\memdebug\bin\$(TargetName).exe" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	echo on 
	copy $(TargetPath) ..\..\build\memdebug\bin 
	echo off 
	
# End Custom Build

!ENDIF 

# Begin Target

# Name "MdsEdit - Win32 Debug"
# Name "MdsEdit - Win32 Release"
# Name "MdsEdit - Win32 MemDebug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\FindDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\MainFrm.cpp
# End Source File
# Begin Source File

SOURCE=.\MdsEdit.cpp
# End Source File
# Begin Source File

SOURCE=.\MdsEdit.rc

!IF  "$(CFG)" == "MdsEdit - Win32 Debug"

!ELSEIF  "$(CFG)" == "MdsEdit - Win32 Release"

!ELSEIF  "$(CFG)" == "MdsEdit - Win32 MemDebug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\MdsEditDoc.cpp
# End Source File
# Begin Source File

SOURCE=.\MdsEditListView.cpp
# End Source File
# Begin Source File

SOURCE=.\MdsEditView.cpp
# End Source File
# Begin Source File

SOURCE=.\ModifyMultiUint32Dlg.cpp
# End Source File
# Begin Source File

SOURCE=.\ModifyStringDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\ModifyUint32Dlg.cpp
# End Source File
# Begin Source File

SOURCE=.\OptionsDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# SUBTRACT CPP /YX /Yc
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\FindDlg.h
# End Source File
# Begin Source File

SOURCE=.\MainFrm.h
# End Source File
# Begin Source File

SOURCE=.\MdsEdit.h
# End Source File
# Begin Source File

SOURCE=.\MdsEditDoc.h
# End Source File
# Begin Source File

SOURCE=.\MdsEditListView.h
# End Source File
# Begin Source File

SOURCE=.\MdsEditView.h
# End Source File
# Begin Source File

SOURCE=.\ModifyMultiUint32Dlg.h
# End Source File
# Begin Source File

SOURCE=.\ModifyStringDlg.h
# End Source File
# Begin Source File

SOURCE=.\ModifyUint32Dlg.h
# End Source File
# Begin Source File

SOURCE=.\OptionsDlg.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\attribut.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bitmap_ablb.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bitmap_amu32.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bitmap_astr.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bitmap_au32.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Foldrs01.ico
# End Source File
# Begin Source File

SOURCE=.\res\mds_imag.bmp
# End Source File
# Begin Source File

SOURCE=.\res\MdsEdit.rc2
# End Source File
# Begin Source File

SOURCE=.\res\MdsEditDoc.ico
# End Source File
# Begin Source File

SOURCE=.\res\Toolbar.bmp
# End Source File
# End Group
# End Target
# End Project
# Section MdsEdit : {72ADFD6C-2C39-11D0-9903-00A0C91BC942}
# 	1:31:CG_IDR_POPUP_MDS_EDIT_LIST_VIEW:102
# End Section
