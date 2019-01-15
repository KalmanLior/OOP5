project(OOP5_part2)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_VERBOSE_MAKEFILE on)

set(INCLUDE_FILES
        OOP5EventException.h)

set(SOURCE_FILES
        Part2Examples.cpp
        )

# SET(CMAKE_CXX_FLAGS "-std=c++11 -g ")

add_executable(part2 ${SOURCE_FILES})

# target_compile_definitions(RankedTriangulationEnumeration PUBLIC ${LIBMONGOCXX_DEFINITIONS} ${LIBBSONCXX_DEFINITIONS})