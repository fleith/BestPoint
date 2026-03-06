@echo off
setlocal

call "C:\Program Files\Microsoft Visual Studio\2022\Community\VC\Auxiliary\Build\vcvars64.bat" > nul 2>&1

if errorlevel 1 (
    echo ERROR: Could not find Visual Studio 2022. Is it installed?
    exit /b 1
)

cd /d "%~dp0"

echo Building tests...

cl.exe /std:c++14 /EHsc /W2 /nologo ^
    /Isrc /Itests ^
    src\chromosome.cpp ^
    src\point.cpp ^
    src\population.cpp ^
    src\fitness.cpp ^
    src\math_utils.cpp ^
    src\selection.cpp ^
    src\crossover.cpp ^
    src\mutation.cpp ^
    src\ga_utils.cpp ^
    tests\test_chromosome.cpp ^
    tests\test_point.cpp ^
    tests\test_mathutils.cpp ^
    tests\test_population.cpp ^
    tests\test_fitness.cpp ^
    tests\test_selection.cpp ^
    tests\test_crossover.cpp ^
    tests\test_mutation.cpp ^
    tests\test_gautils.cpp ^
    tests\tests_main.cpp ^
    /Fe:run_tests.exe

if errorlevel 1 (
    echo Build FAILED.
    exit /b 1
)

echo Build OK - running tests...
echo.
"%~dp0run_tests.exe"
