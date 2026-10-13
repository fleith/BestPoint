cmake_minimum_required(VERSION 3.15)
project(BestPoint CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SRCS
    src/chromosome.cpp
    src/point.cpp
    src/population.cpp
    src/fitness.cpp
    src/math_utils.cpp
    src/selection.cpp
    src/crossover.cpp
    src/mutation.cpp
    src/ga_utils.cpp
    app/app.cpp
    interface/ui_cli.cpp
    cli/main.cpp
)

add_executable(BestPoint ${SRCS})

target_include_directories(BestPoint PRIVATE
    src
    app
    interface
    cli
)


include(CTest)
if(BUILD_TESTING)
    file(GLOB CORE_SOURCES CONFIGURE_DEPENDS src/*.cpp)
    list(REMOVE_ITEM CORE_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp")
    file(GLOB TEST_SOURCES CONFIGURE_DEPENDS tests/*.cpp)
    add_executable(run_tests ${CORE_SOURCES} ${TEST_SOURCES})
    target_include_directories(run_tests PRIVATE src tests)
    add_test(NAME unit COMMAND run_tests)
    find_package(Python3 COMPONENTS Interpreter REQUIRED)
    add_test(NAME cli_regressions COMMAND ${Python3_EXECUTABLE}
        ${CMAKE_CURRENT_SOURCE_DIR}/tests/test_cli.py $<TARGET_FILE:BestPoint>)
    set_tests_properties(unit cli_regressions PROPERTIES TIMEOUT 60)
endif()
