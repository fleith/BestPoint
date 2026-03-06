cmake_minimum_required(VERSION 3.15)
project(BestPoint CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SRCS
    Classes/Chromosome.cpp
    Classes/Point.cpp
    Classes/Population.cpp
    Classes/Fitness.cpp
    Classes/MathUtils.cpp
    Classes/Selection.cpp
    Classes/Crossover.cpp
    Classes/Mutation.cpp
    Util/GAUtils.cpp
    App/App.cpp
    Interface/UICli.cpp
    CLI/main.cpp
)

add_executable(BestPoint ${SRCS})

target_include_directories(BestPoint PRIVATE
    Classes
    Util
    App
    Interface
    CLI
)
