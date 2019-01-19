cmake_minimum_required(VERSION 3.7)
project(cpp-advanced)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_VERBOSE_MAKEFILE on)
# choose compiler - should be the same as the one on csl2
SET(CMAKE_CXX_COMPILER g++)

set(GCC "-std=c++11 -Wall -Werror -pedantic-errors")

add_definitions(${GCC})

add_executable(part1ExampleTest
        staffExampleTests/Part1Examples.cpp
        )
add_executable(part2ExampleTest
        staffExampleTests/Part2Examples.cpp
        )
add_executable(FacebookPart1Test
        facebookTests/Part1Test.cpp
        )
add_executable(FacebookPart2Test
        facebookTests/Part2Test.cpp
        )
add_executable(oldPart1Test
        old/AviramTest_spring_2018.cpp
        )
add_executable(whatsappPart1Test
        WhatsappTests/PartOneTests/main.cpp
        )
add_executable(whatsappPart2Test
        WhatsappTests/PartTwoTests/main.cpp
        )
add_executable(morePart1Test
        moreTests/part1/main.cpp
        )
add_executable(morePart2Test
        moreTests/part2/main.cpp
        )