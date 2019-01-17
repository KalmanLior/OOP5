project(OOP5_part1)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_VERBOSE_MAKEFILE on)

# choose compiler - should be the same as the one on csl2
SET(CMAKE_CXX_COMPILER gcc)

# must be ONLY MatrixOperations.h
set(INCLUDE_FILES
      MatrixOperations.h)

set(SOURCE_FILES
        Part1Examples.cpp
        )

# SET(CMAKE_CXX_FLAGS "-std=c++11 -g ")

add_executable(part1 ${SOURCE_FILES})

# target_compile_definitions(RankedTriangulationEnumeration PUBLIC ${LIBMONGOCXX_DEFINITIONS} ${LIBBSONCXX_DEFINITIONS})