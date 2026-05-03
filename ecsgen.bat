@echo off

:: Check if project name was provided
if "%~1"=="" (
    echo No project name
    exit /b
)

:: Check if filename was provided
if "%~2"=="" (
    echo Usage: newcpp filename
    exit /b
)

set PROJECT=%~1
set NAME=%~2

set TEMPLATE_DIR=engine\templates
set OUTPUT_DIR=projects\%PROJECT%\src

:: Ensure output directory exists
if not exist "%OUTPUT_DIR%" mkdir "%OUTPUT_DIR%"

:: Generate header
powershell.exe -NoProfile -Command "(Get-Content 'engine\templates\ecstemplate.h') -replace '{{NAME}}', '%NAME%' | Set-Content '%OUTPUT_DIR%\%NAME%.h'"

:: Generate source
powershell.exe -NoProfile -Command "(Get-Content 'engine\templates\ecstemplate.cpp') -replace '{{NAME}}', '%NAME%' | Set-Content '%OUTPUT_DIR%\%NAME%.cpp'"

echo Created %NAME%.h and %NAME%.cpp