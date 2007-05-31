# Microsoft Developer Studio Generated NMAKE File, Based on h_layer.dsp
!IF "$(CFG)" == ""
CFG=h_layer - Win32 MemDebug
!MESSAGE No configuration specified. Defaulting to h_layer - Win32 MemDebug.
!ENDIF 

!IF "$(CFG)" != "h_layer - Win32 Release" && "$(CFG)" != "h_layer - Win32 Debug" && "$(CFG)" != "h_layer - Win32 MemDebug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "h_layer.mak" CFG="h_layer - Win32 MemDebug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "h_layer - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "h_layer - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "h_layer - Win32 MemDebug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "h_layer - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\jbioapi.dll" "..\..\build\release\dll\jbioapi.dll" "..\..\build\release\lib\jbioapi.lib"

!ELSE 

ALL : "bioapi_util - Win32 Release" "bioapi_install - Win32 Release" "mds_util_api - Win32 Release" "mds_util - Win32 Release" "$(OUTDIR)\jbioapi.dll" "..\..\build\release\dll\jbioapi.dll" "..\..\build\release\lib\jbioapi.lib"

!ENDIF 

!IF "$(RECURSE)" == "1" 
CLEAN :"mds_util - Win32 ReleaseCLEAN" "mds_util_api - Win32 ReleaseCLEAN" "bioapi_install - Win32 ReleaseCLEAN" "bioapi_util - Win32 ReleaseCLEAN" 
!ELSE 
CLEAN :
!ENDIF 
	-@erase "$(INTDIR)\extra.obj"
	-@erase "$(INTDIR)\jbioapi_wrap.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\jbioapi.dll"
	-@erase "$(OUTDIR)\jbioapi.exp"
	-@erase "$(OUTDIR)\jbioapi.lib"
	-@erase "..\..\build\release\dll\jbioapi.dll"
	-@erase "..\..\build\release\lib\jbioapi.lib"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MT /W4 /GX /O2 /I "." /I "..\..\include" /I "..\mds_util" /I "..\..\imports\cdsa\v2_0\inc" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "H_LAYER_EXPORTS" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /win32 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\h_layer.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=bioapi100.lib mds_util.lib mds_util_api.lib install.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib bioapi_mds300.lib port.lib bioapi_util.lib /nologo /dll /incremental:no /pdb:"$(OUTDIR)\jbioapi.pdb" /machine:I386 /out:"$(OUTDIR)\jbioapi.dll" /implib:"$(OUTDIR)\jbioapi.lib" /libpath:"..\..\build\release\lib" /libpath:"..\..\imports\cdsa\v2_0\release\lib" 
LINK32_OBJS= \
	"$(INTDIR)\extra.obj" \
	"$(INTDIR)\jbioapi_wrap.obj" \
	"..\..\build\release\lib\mds_util.lib" \
	"..\..\build\release\lib\mds_util_api.lib" \
	"..\..\build\release\lib\install.lib" \
	"..\..\build\release\lib\bioapi_util.lib"

"$(OUTDIR)\jbioapi.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

TargetDir=.\Release
TargetPath=.\Release\jbioapi.dll
TargetName=jbioapi
InputPath=.\Release\jbioapi.dll
SOURCE="$(InputPath)"

"..\..\build\release\dll\jbioapi.dll"	"..\..\build\release\lib\jbioapi.lib" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	echo on 
	copy $(TargetPath) ..\..\build\release\dll 
	copy $(TargetDir)\$(TargetName).lib ..\..\build\release\lib 
	echo off
<< 
	

!ELSEIF  "$(CFG)" == "h_layer - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\bioapi100.dll" "$(OUTDIR)\h_layer.bsc" "..\..\build\debug\dll\bioapi100.dll" "..\..\build\debug\lib\bioapi100.lib"

!ELSE 

ALL : "bioapi_util - Win32 Debug" "bioapi_install - Win32 Debug" "mds_util_api - Win32 Debug" "mds_util - Win32 Debug" "$(OUTDIR)\bioapi100.dll" "$(OUTDIR)\h_layer.bsc" "..\..\build\debug\dll\bioapi100.dll" "..\..\build\debug\lib\bioapi100.lib"

!ENDIF 

!IF "$(RECURSE)" == "1" 
CLEAN :"mds_util - Win32 DebugCLEAN" "mds_util_api - Win32 DebugCLEAN" "bioapi_install - Win32 DebugCLEAN" "bioapi_util - Win32 DebugCLEAN" 
!ELSE 
CLEAN :
!ENDIF 
	-@erase "$(INTDIR)\extra.obj"
	-@erase "$(INTDIR)\extra.sbr"
	-@erase "$(INTDIR)\jbioapi_wrap.obj"
	-@erase "$(INTDIR)\jbioapi_wrap.sbr"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\bioapi100.dll"
	-@erase "$(OUTDIR)\bioapi100.exp"
	-@erase "$(OUTDIR)\bioapi100.ilk"
	-@erase "$(OUTDIR)\bioapi100.lib"
	-@erase "$(OUTDIR)\bioapi100.pdb"
	-@erase "$(OUTDIR)\h_layer.bsc"
	-@erase "..\..\build\debug\dll\bioapi100.dll"
	-@erase "..\..\build\debug\lib\bioapi100.lib"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MTd /W4 /Gm /GX /ZI /Od /I "." /I "..\..\include" /I "..\mds_util" /I "..\..\imports\cdsa\v2_0\inc" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "H_LAYER_EXPORTS" /FR"$(INTDIR)\\" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 
MTL_PROJ=/nologo /D "_DEBUG" /mktyplib203 /win32 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\h_layer.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\extra.sbr" \
	"$(INTDIR)\jbioapi_wrap.sbr"

"$(OUTDIR)\h_layer.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
LINK32_FLAGS=install.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib bioapi_mds300.lib port.lib bioapi_util.lib /nologo /dll /incremental:yes /pdb:"$(OUTDIR)\bioapi100.pdb" /debug /machine:I386 /out:"$(OUTDIR)\bioapi100.dll" /implib:"$(OUTDIR)\bioapi100.lib" /pdbtype:sept /libpath:"..\..\build\debug\lib" /libpath:"..\..\imports\cdsa\v2_0\debug\lib" 
LINK32_OBJS= \
	"$(INTDIR)\extra.obj" \
	"$(INTDIR)\jbioapi_wrap.obj" \
	"..\..\build\debug\lib\mds_util.lib" \
	"..\..\build\debug\lib\mds_util_api.lib" \
	"..\..\build\debug\lib\install.lib" \
	"..\..\build\debug\lib\bioapi_util.lib"

"$(OUTDIR)\bioapi100.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

TargetDir=.\Debug
TargetPath=.\Debug\bioapi100.dll
TargetName=bioapi100
InputPath=.\Debug\bioapi100.dll
SOURCE="$(InputPath)"

"..\..\build\debug\dll\bioapi100.dll"	"..\..\build\debug\lib\bioapi100.lib" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	echo on 
	copy $(TargetPath) ..\..\build\debug\dll 
	copy $(TargetDir)\$(TargetName).lib ..\..\build\debug\lib 
	echo off
<< 
	

!ELSEIF  "$(CFG)" == "h_layer - Win32 MemDebug"

OUTDIR=.\MemDebug
INTDIR=.\MemDebug
# Begin Custom Macros
OutDir=.\MemDebug
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\jbioapi.dll" "$(OUTDIR)\h_layer.bsc" "..\..\build\memdebug\dll\jbioapi.dll" "..\..\build\memdebug\lib\jbioapi.lib"

!ELSE 

ALL : "bioapi_util - Win32 MemDebug" "bioapi_install - Win32 MemDebug" "mds_util_api - Win32 MemDebug" "mds_util - Win32 MemDebug" "$(OUTDIR)\jbioapi.dll" "$(OUTDIR)\h_layer.bsc" "..\..\build\memdebug\dll\jbioapi.dll" "..\..\build\memdebug\lib\jbioapi.lib"

!ENDIF 

!IF "$(RECURSE)" == "1" 
CLEAN :"mds_util - Win32 MemDebugCLEAN" "mds_util_api - Win32 MemDebugCLEAN" "bioapi_install - Win32 MemDebugCLEAN" "bioapi_util - Win32 MemDebugCLEAN" 
!ELSE 
CLEAN :
!ENDIF 
	-@erase "$(INTDIR)\extra.obj"
	-@erase "$(INTDIR)\extra.sbr"
	-@erase "$(INTDIR)\jbioapi_wrap.obj"
	-@erase "$(INTDIR)\jbioapi_wrap.sbr"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\h_layer.bsc"
	-@erase "$(OUTDIR)\jbioapi.dll"
	-@erase "$(OUTDIR)\jbioapi.exp"
	-@erase "$(OUTDIR)\jbioapi.ilk"
	-@erase "$(OUTDIR)\jbioapi.lib"
	-@erase "$(OUTDIR)\jbioapi.pdb"
	-@erase "..\..\build\memdebug\dll\jbioapi.dll"
	-@erase "..\..\build\memdebug\lib\jbioapi.lib"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MTd /W4 /Gm /GX /ZI /Od /I "." /I "..\..\include" /I "..\mds_util" /I "..\..\imports\cdsa\v2_0\inc" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "H_LAYER_EXPORTS" /D "BioAPI_MEMTRACK_ON" /FR"$(INTDIR)\\" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 
MTL_PROJ=/nologo /D "_DEBUG" /mktyplib203 /win32 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\h_layer.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\extra.sbr" \
	"$(INTDIR)\jbioapi_wrap.sbr"

"$(OUTDIR)\h_layer.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
LINK32_FLAGS=bioapi100.lib msjava.lib mds_util.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib bioapi_mds300.lib port.lib bioapi_util.lib /nologo /dll /incremental:yes /pdb:"$(OUTDIR)\jbioapi.pdb" /debug /machine:I386 /out:"$(OUTDIR)\jbioapi.dll" /implib:"$(OUTDIR)\jbioapi.lib" /pdbtype:sept /libpath:"..\..\build\memdebug\lib" /libpath:"..\..\imports\cdsa\v2_0\memdebug\lib" 
LINK32_OBJS= \
	"$(INTDIR)\extra.obj" \
	"$(INTDIR)\jbioapi_wrap.obj" \
	"..\..\build\memdebug\lib\mds_util.lib" \
	"..\..\build\memdebug\lib\mds_util_api.lib" \
	"..\..\build\memdebug\lib\install.lib" \
	"..\..\build\memdebug\lib\bioapi_util.lib"

"$(OUTDIR)\jbioapi.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

TargetDir=.\MemDebug
TargetPath=.\MemDebug\jbioapi.dll
TargetName=jbioapi
InputPath=.\MemDebug\jbioapi.dll
SOURCE="$(InputPath)"

"..\..\build\memdebug\dll\jbioapi.dll"	"..\..\build\memdebug\lib\jbioapi.lib" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	echo on 
	copy $(TargetPath) ..\..\build\memdebug\dll 
	copy $(TargetDir)\$(TargetName).lib ..\..\build\memdebug\lib 
	echo off
<< 
	

!ENDIF 

.c{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.c{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<


!IF "$(NO_EXTERNAL_DEPS)" != "1"
!IF EXISTS("h_layer.dep")
!INCLUDE "h_layer.dep"
!ELSE 
!MESSAGE Warning: cannot find "h_layer.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "h_layer - Win32 Release" || "$(CFG)" == "h_layer - Win32 Debug" || "$(CFG)" == "h_layer - Win32 MemDebug"
SOURCE=.\extra.c

!IF  "$(CFG)" == "h_layer - Win32 Release"


"$(INTDIR)\extra.obj" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "h_layer - Win32 Debug"


"$(INTDIR)\extra.obj"	"$(INTDIR)\extra.sbr" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "h_layer - Win32 MemDebug"


"$(INTDIR)\extra.obj"	"$(INTDIR)\extra.sbr" : $(SOURCE) "$(INTDIR)"


!ENDIF 

SOURCE=.\jbioapi_wrap.c

!IF  "$(CFG)" == "h_layer - Win32 Release"


"$(INTDIR)\jbioapi_wrap.obj" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "h_layer - Win32 Debug"


"$(INTDIR)\jbioapi_wrap.obj"	"$(INTDIR)\jbioapi_wrap.sbr" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "h_layer - Win32 MemDebug"


"$(INTDIR)\jbioapi_wrap.obj"	"$(INTDIR)\jbioapi_wrap.sbr" : $(SOURCE) "$(INTDIR)"


!ENDIF 

!IF  "$(CFG)" == "h_layer - Win32 Release"

"mds_util - Win32 Release" : 
   cd "\eotero\bioapi_src\framework\mds_util"
   $(MAKE) /$(MAKEFLAGS) /F .\mds_util.mak CFG="mds_util - Win32 Release" 
   cd "..\h_layer"

"mds_util - Win32 ReleaseCLEAN" : 
   cd "\eotero\bioapi_src\framework\mds_util"
   $(MAKE) /$(MAKEFLAGS) /F .\mds_util.mak CFG="mds_util - Win32 Release" RECURSE=1 CLEAN 
   cd "..\h_layer"

!ELSEIF  "$(CFG)" == "h_layer - Win32 Debug"

"mds_util - Win32 Debug" : 
   cd "\eotero\bioapi_src\framework\mds_util"
   $(MAKE) /$(MAKEFLAGS) /F .\mds_util.mak CFG="mds_util - Win32 Debug" 
   cd "..\h_layer"

"mds_util - Win32 DebugCLEAN" : 
   cd "\eotero\bioapi_src\framework\mds_util"
   $(MAKE) /$(MAKEFLAGS) /F .\mds_util.mak CFG="mds_util - Win32 Debug" RECURSE=1 CLEAN 
   cd "..\h_layer"

!ELSEIF  "$(CFG)" == "h_layer - Win32 MemDebug"

"mds_util - Win32 MemDebug" : 
   cd "\eotero\bioapi_src\framework\mds_util"
   $(MAKE) /$(MAKEFLAGS) /F .\mds_util.mak CFG="mds_util - Win32 MemDebug" 
   cd "..\h_layer"

"mds_util - Win32 MemDebugCLEAN" : 
   cd "\eotero\bioapi_src\framework\mds_util"
   $(MAKE) /$(MAKEFLAGS) /F .\mds_util.mak CFG="mds_util - Win32 MemDebug" RECURSE=1 CLEAN 
   cd "..\h_layer"

!ENDIF 

!IF  "$(CFG)" == "h_layer - Win32 Release"

"mds_util_api - Win32 Release" : 
   cd "\eotero\bioapi_src\framework\mds_util_api"
   $(MAKE) /$(MAKEFLAGS) /F .\mds_util_api.mak CFG="mds_util_api - Win32 Release" 
   cd "..\h_layer"

"mds_util_api - Win32 ReleaseCLEAN" : 
   cd "\eotero\bioapi_src\framework\mds_util_api"
   $(MAKE) /$(MAKEFLAGS) /F .\mds_util_api.mak CFG="mds_util_api - Win32 Release" RECURSE=1 CLEAN 
   cd "..\h_layer"

!ELSEIF  "$(CFG)" == "h_layer - Win32 Debug"

"mds_util_api - Win32 Debug" : 
   cd "\eotero\bioapi_src\framework\mds_util_api"
   $(MAKE) /$(MAKEFLAGS) /F .\mds_util_api.mak CFG="mds_util_api - Win32 Debug" 
   cd "..\h_layer"

"mds_util_api - Win32 DebugCLEAN" : 
   cd "\eotero\bioapi_src\framework\mds_util_api"
   $(MAKE) /$(MAKEFLAGS) /F .\mds_util_api.mak CFG="mds_util_api - Win32 Debug" RECURSE=1 CLEAN 
   cd "..\h_layer"

!ELSEIF  "$(CFG)" == "h_layer - Win32 MemDebug"

"mds_util_api - Win32 MemDebug" : 
   cd "\eotero\bioapi_src\framework\mds_util_api"
   $(MAKE) /$(MAKEFLAGS) /F .\mds_util_api.mak CFG="mds_util_api - Win32 MemDebug" 
   cd "..\h_layer"

"mds_util_api - Win32 MemDebugCLEAN" : 
   cd "\eotero\bioapi_src\framework\mds_util_api"
   $(MAKE) /$(MAKEFLAGS) /F .\mds_util_api.mak CFG="mds_util_api - Win32 MemDebug" RECURSE=1 CLEAN 
   cd "..\h_layer"

!ENDIF 

!IF  "$(CFG)" == "h_layer - Win32 Release"

"bioapi_install - Win32 Release" : 
   cd ".\install"
   $(MAKE) /$(MAKEFLAGS) /F .\install.mak CFG="bioapi_install - Win32 Release" 
   cd ".."

"bioapi_install - Win32 ReleaseCLEAN" : 
   cd ".\install"
   $(MAKE) /$(MAKEFLAGS) /F .\install.mak CFG="bioapi_install - Win32 Release" RECURSE=1 CLEAN 
   cd ".."

!ELSEIF  "$(CFG)" == "h_layer - Win32 Debug"

"bioapi_install - Win32 Debug" : 
   cd ".\install"
   $(MAKE) /$(MAKEFLAGS) /F .\install.mak CFG="bioapi_install - Win32 Debug" 
   cd ".."

"bioapi_install - Win32 DebugCLEAN" : 
   cd ".\install"
   $(MAKE) /$(MAKEFLAGS) /F .\install.mak CFG="bioapi_install - Win32 Debug" RECURSE=1 CLEAN 
   cd ".."

!ELSEIF  "$(CFG)" == "h_layer - Win32 MemDebug"

"bioapi_install - Win32 MemDebug" : 
   cd ".\install"
   $(MAKE) /$(MAKEFLAGS) /F .\install.mak CFG="bioapi_install - Win32 MemDebug" 
   cd ".."

"bioapi_install - Win32 MemDebugCLEAN" : 
   cd ".\install"
   $(MAKE) /$(MAKEFLAGS) /F .\install.mak CFG="bioapi_install - Win32 MemDebug" RECURSE=1 CLEAN 
   cd ".."

!ENDIF 

!IF  "$(CFG)" == "h_layer - Win32 Release"

"bioapi_util - Win32 Release" : 
   cd "\eotero\bioapi_src\framework\bioapi_util"
   $(MAKE) /$(MAKEFLAGS) /F .\bioapi_util.mak CFG="bioapi_util - Win32 Release" 
   cd "..\h_layer"

"bioapi_util - Win32 ReleaseCLEAN" : 
   cd "\eotero\bioapi_src\framework\bioapi_util"
   $(MAKE) /$(MAKEFLAGS) /F .\bioapi_util.mak CFG="bioapi_util - Win32 Release" RECURSE=1 CLEAN 
   cd "..\h_layer"

!ELSEIF  "$(CFG)" == "h_layer - Win32 Debug"

"bioapi_util - Win32 Debug" : 
   cd "\eotero\bioapi_src\framework\bioapi_util"
   $(MAKE) /$(MAKEFLAGS) /F .\bioapi_util.mak CFG="bioapi_util - Win32 Debug" 
   cd "..\h_layer"

"bioapi_util - Win32 DebugCLEAN" : 
   cd "\eotero\bioapi_src\framework\bioapi_util"
   $(MAKE) /$(MAKEFLAGS) /F .\bioapi_util.mak CFG="bioapi_util - Win32 Debug" RECURSE=1 CLEAN 
   cd "..\h_layer"

!ELSEIF  "$(CFG)" == "h_layer - Win32 MemDebug"

"bioapi_util - Win32 MemDebug" : 
   cd "\eotero\bioapi_src\framework\bioapi_util"
   $(MAKE) /$(MAKEFLAGS) /F .\bioapi_util.mak CFG="bioapi_util - Win32 MemDebug" 
   cd "..\h_layer"

"bioapi_util - Win32 MemDebugCLEAN" : 
   cd "\eotero\bioapi_src\framework\bioapi_util"
   $(MAKE) /$(MAKEFLAGS) /F .\bioapi_util.mak CFG="bioapi_util - Win32 MemDebug" RECURSE=1 CLEAN 
   cd "..\h_layer"

!ENDIF 


!ENDIF 

