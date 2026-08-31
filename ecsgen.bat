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

set /a CMP_ID=%RANDOM% * 32768 / 32768 + 10000
set FILE_NAME="%NAME%Component"

:: Ensure output directory exists
if not exist "%OUTPUT_DIR%" (echo Target folder "src\" does not exist & exit /b)

if exist "%OUTPUT_DIR%\%FILE_NAME%.h" (echo File already exists: src\%FILE_NAME%.h & exit /b)
if exist "%OUTPUT_DIR%\%FILE_NAME%.cpp" (echo File already exists: src\%FILE_NAME%.cpp & exit /b)

:: Generate header
powershell.exe -NoProfile -Command "(Get-Content 'engine\templates\ecstemplate.h') -replace '{{NAME}}', '%NAME%' ` -replace '{{CMP_ID}}', '%CMP_ID%' | Set-Content '%OUTPUT_DIR%\%FILE_NAME%.h'"

:: Generate source
powershell.exe -NoProfile -Command "(Get-Content 'engine\templates\ecstemplate.cpp') -replace '{{NAME}}', '%NAME%' | Set-Content '%OUTPUT_DIR%\%FILE_NAME%.cpp'"

echo Created %FILE_NAME%.h and %FILE_NAME%.cpp