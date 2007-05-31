@echo off
rem #-----------------------------------------------------------------------
rem # File: INSTALL_APPS_W98.BAT
rem #-----------------------------------------------------------------------
rem #

rem Installs the core and framework on Windows98.

set DIR=release
if not "%1"=="" set DIR=%1

echo on
%DIR%\install\mds_install -s %DIR%\dll
%DIR%\install\mod_install -if -s %DIR%\dll\bioapi100 -d c:\windows\system\
