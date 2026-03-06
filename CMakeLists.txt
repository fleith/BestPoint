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
