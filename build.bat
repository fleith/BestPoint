@echo off
setlocal

call "C:\Program Files\Microsoft Visual Studio\2022\Community\VC\Auxiliary\Build\vcvars64.bat" > nul 2>&1

if errorlevel 1 (
    echo ERROR: Could not find Visual Studio 2022. Is it installed?
    exit /b 1
)

cd /d "%~dp0"

echo Building BestPoint...

cl.exe /std:c++14 /EHsc /W2 /nologo ^
    /Isrc /Iapp /Iinterface /Icli ^
    src\chromosome.cpp ^
    src\point.cpp ^
    src\population.cpp ^
    src\fitness.cpp ^
    src\math_utils.cpp ^
    src\selection.cpp ^
    src\crossover.cpp ^
    src\mutation.cpp ^
    src\ga_utils.cpp ^
    app\app.cpp ^
    interface\ui_cli.cpp ^
    cli\main.cpp ^
    /Fe:BestPoint.exe

if errorlevel 1 (
    echo Build FAILED.
    exit /b 1
)

echo Build OK - BestPoint.exe ready.
endlocal
