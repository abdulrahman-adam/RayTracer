@echo off
rem Runs a command inside the Visual Studio developer environment, so that
rem cmake, ninja and the MSVC compiler are found from a normal terminal.
rem Used by the Makefile on Windows (see ADR 0006). Usage: vsenv.cmd <command...>

rem Already in a Developer PowerShell / Command Prompt: run the command as is.
where cl >nul 2>nul && goto run

set "VSINSTALLER=%ProgramFiles(x86)%\Microsoft Visual Studio\Installer"
if not exist "%VSINSTALLER%\vswhere.exe" goto novs
set "PATH=%VSINSTALLER%;%PATH%"

set "VSINSTALL="
for /f "usebackq delims=" %%i in (`vswhere.exe -latest -prerelease -products * -requires Microsoft.VisualStudio.Component.VC.Tools.x86.x64 -property installationPath`) do set "VSINSTALL=%%i"
if not defined VSINSTALL goto novs

call "%VSINSTALL%\Common7\Tools\VsDevCmd.bat" -arch=x64 -host_arch=x64 -no_logo >nul
if errorlevel 1 exit /b 1

:run
%*
exit /b %errorlevel%

:novs
echo Visual Studio with "Desktop development with C++" was not found. 1>&2
echo Install it, or run this command from a Developer PowerShell for VS. 1>&2
exit /b 1
