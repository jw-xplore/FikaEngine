@echo off

:: Check if project name was provided
if "%~1"=="" (
    echo No project name
    exit /b
)

set PROJECT=%~1
set TEMPLATE_DIR=engine\templates\projectTemplate
set SRC=src
set ASSETS=assets

set OUTPUT_DIR=projects\%PROJECT%

:: Check name collision
if exist "%OUTPUT_DIR%" (echo Project '%PROJECT%' already exists & exit /b)

:: Create directories
mkdir %OUTPUT_DIR%
mkdir %OUTPUT_DIR%\%SRC%
mkdir %OUTPUT_DIR%\%ASSETS%

:: Generate cmake
powershell.exe -NoProfile -Command "(Get-Content '%TEMPLATE_DIR%\CMakeLists.txt') -replace '{{NAME}}', '%PROJECT%' | Set-Content '%OUTPUT_DIR%\CMakeLists.txt'"

copy %TEMPLATE_DIR%\%SRC%\main.cpp %OUTPUT_DIR%\%SRC%
echo Project '%PROJECT%' created. Rebuilding solution.

:: Rebuild
build.bat