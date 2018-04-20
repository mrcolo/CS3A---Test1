cmake_minimum_required(VERSION 3.9)
project(wilkinsonTEST1)

set(CMAKE_CXX_STANDARD 11)

add_executable(wilkinsonTEST1
        fraction.cpp
        fraction.h
        fractionfriends.cpp
        main.cpp
        polynomial.cpp
        polynomial.h
        term.cpp
        term.h)
