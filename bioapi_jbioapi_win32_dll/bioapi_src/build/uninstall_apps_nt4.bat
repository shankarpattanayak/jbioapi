@echo off
rem #-----------------------------------------------------------------------
rem # File: UNINSTALL_APPS_NT4.BAT
rem #-----------------------------------------------------------------------
rem #

rem Uninstalls the core and framework on Windows NT4.

set DIR=release
if not "%1"=="" set DIR=%1

echo on
%DIR%\install\mod_install -u -s c:\winnt\system32\bioapi100
%DIR%\install\mds_install -u
del c:\winnt\system32\bioapi100.*
