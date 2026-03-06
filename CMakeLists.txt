cmake_minimum_required(VERSION 3.15)
project(BestPoint CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SRCS
    Classes/Cromossomo.cpp
    Classes/Ponto.cpp
    Classes/Populacao.cpp
    Classes/Fitness.cpp
    Classes/Calculo.cpp
    Classes/Selecao.cpp
    Classes/Crossover.cpp
    Classes/Mutacao.cpp
    Util/AGUtil.cpp
    App/AppAG.cpp
    Interface/GerenteInterfaceCLI.cpp
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
