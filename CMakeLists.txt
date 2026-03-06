cmake_minimum_required(VERSION 3.15)
project(BestPoint CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SRCS
    src/Chromosome.cpp
    src/Point.cpp
    src/Population.cpp
    src/Fitness.cpp
    src/MathUtils.cpp
    src/Selection.cpp
    src/Crossover.cpp
    src/Mutation.cpp
    src/GAUtils.cpp
    App/App.cpp
    Interface/UICli.cpp
    CLI/main.cpp
)

add_executable(BestPoint ${SRCS})

target_include_directories(BestPoint PRIVATE
    src
    App
    Interface
    CLI
)
