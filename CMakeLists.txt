cmake_minimum_required(VERSION 3.20.0)
project(simulator-variables VERSION 1.0.0 LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

#add GTEST for unit tests
include(FetchContent)

FetchContent_Declare(
    GoogleTest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG v1.15.1
)
FetchContent_GetProperties(GoogleTest)
if (NOT GoogleTest_POPULATED)

    FetchContent_Populate(GoogleTest)
    add_subdirectory( ${googletest_SOURCE_DIR} ${googletest_build_DIR})
endif()

add_subdirectory(test)

add_subdirectory(src)
