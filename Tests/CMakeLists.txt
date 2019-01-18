cmake_minimum_required(VERSION 3.7)
project(cpp-advanced)

set(CMAKE_CXX_STANDARD 11)
set(GCC "-std=c++11 -Wall -Werror -pedantic-errors")

add_definitions(${GCC})

add_executable(Part1Test
        Provided/part1/Part1Test.cpp
        )

add_executable(Part2Test
        Provided/part2/Part2Test.cpp
        )

