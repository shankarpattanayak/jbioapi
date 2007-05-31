@echo off
rem #-----------------------------------------------------------------------
rem # File: UNINSTALL_W98.BAT
rem #-----------------------------------------------------------------------
rem #

rem Uninstalls the core, framework, dummy addin, and password BSP on Windows98.

set DIR=release
if not "%1"=="" set DIR=%1

echo on
%DIR%\install\mod_install -u -s c:\windows\system\bioapi100
%DIR%\install\mod_install -u -s c:\windows\system\bioapi_dummy100
%DIR%\install\mod_install -u -s c:\windows\system\pwbsp
%DIR%\install\mds_install -u
del c:\windows\system\bioapi100.*
del c:\windows\system\bioapi_dummy100.*
del c:\windows\system\pwbsp.*
