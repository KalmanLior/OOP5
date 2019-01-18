cmake_minimum_required(VERSION 3.7)
project(cpp-advanced)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_VERBOSE_MAKEFILE on)
set(GCC "-std=c++11 -Wall -Werror -pedantic-errors")

# choose compiler - should be the same as the one on csl2
SET(CMAKE_CXX_COMPILER g++)

add_definitions(${GCC})

add_executable(Part1Test
        Part1Test.cpp
        )

add_executable(Part2Test
        Part2Test.cpp
        )

