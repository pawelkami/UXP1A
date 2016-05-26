cmake_minimum_required(VERSION 2.8)
project(lindalang)
set(CMAKE_BUILD_TYPE Release)

include_directories(.)

add_library(lindalang STATIC
        Linda.cpp Tuple.cpp Tuple.h TuplePattern.cpp TuplePattern.h)


set(SOURCES
        src/Linda.cpp
        )


set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -std=c++11")

target_link_libraries(lindalang ${PROJECT_LINK_LIBS})



