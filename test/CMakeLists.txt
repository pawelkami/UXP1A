cmake_minimum_required(VERSION 2.8)
project(Test)
set(CMAKE_BUILD_TYPE Debug)

find_package (Boost COMPONENTS system filesystem unit_test_framework REQUIRED)
include_directories (..
                    ${Boost_INCLUDE_DIRS}
                    )

file(GLOB_RECURSE HDRSERVER ${CMAKE_SOURCE_DIR}/src/server/*.h)
file(GLOB_RECURSE SRCSERVER ${CMAKE_SOURCE_DIR}/src/server/*.cpp)

add_definitions (-DBOOST_TEST_DYN_LINK)

add_executable (Test LindaLangTests.cpp ${HDRSERVER} ${SRCSERVER})


target_link_libraries (Test
        lindalang
        ${Boost_FILESYSTEM_LIBRARY}
        ${Boost_SYSTEM_LIBRARY}
        ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY}
        )
