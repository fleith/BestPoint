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
    /Isrc /IApp /IInterface /ICLI ^
    src\Chromosome.cpp ^
    src\Point.cpp ^
    src\Population.cpp ^
    src\Fitness.cpp ^
    src\MathUtils.cpp ^
    src\Selection.cpp ^
    src\Crossover.cpp ^
    src\Mutation.cpp ^
    src\GAUtils.cpp ^
    App\App.cpp ^
    Interface\UICli.cpp ^
    CLI\main.cpp ^
    /Fe:BestPoint.exe

if errorlevel 1 (
    echo Build FAILED.
    exit /b 1
)

echo Build OK - BestPoint.exe ready.
endlocal
