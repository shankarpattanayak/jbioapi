@echo off
rem #-----------------------------------------------------------------------
rem # File: INSTALL_NT4.BAT
rem #-----------------------------------------------------------------------
rem #

rem Installs the core, framework, dummy addin, and password BSP on Windows NT4.

set DIR=release
if not "%1"=="" set DIR=%1

echo on
%DIR%\install\mds_install -s %DIR%\dll
%DIR%\install\mod_install -if -s %DIR%\dll\bioapi100 -d c:\winnt\system32\
%DIR%\install\mod_install -if -s %DIR%\dll\bioapi_dummy100 -d c:\winnt\system32\
%DIR%\install\mod_install -if -s %DIR%\dll\pwbsp -d c:\winnt\system32\
