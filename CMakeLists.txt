cmake_minimum_required(VERSION 3.22)
project(tentpitch_sdg VERSION 0.1
        DESCRIPTION "Modern C++ Spacetime Discontinuous Galerkin Tentpitching code"
        LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(tentpitch_sdg tests/misc_testing.cpp)
