cmake_minimum_required(VERSION 3.22)
project(tentpitch_sdg VERSION 0.1
        DESCRIPTION "Modern C++ Spacetime Discontinuous Galerkin Tentpitching code"
        LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

option(PACKAGE_TESTS "Build the tests" ON)
if(PACKAGE_TESTS)
    enable_testing()
    include(GoogleTest)
    add_subdirectory(tests)
endif()

# include libraries that we need
include_directories(external/abseil-cpp/)
include_directories(external)
include_directories(external/googletest/googletest/include)
include_directories(external/googletest/googlemock/include)
include_directories(src/)

# add the subdirectories with stuff to be built
add_subdirectory(src)
add_subdirectory(external/abseil-cpp)
add_subdirectory(external/status_macros)
add_subdirectory(external/googletest)