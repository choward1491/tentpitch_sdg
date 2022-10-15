cmake_minimum_required(VERSION 3.22)
project(tentpitch_sdg VERSION 0.1
        DESCRIPTION "Modern C++ Spacetime Discontinuous Galerkin Tentpitching code"
        LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# add google test
include(FetchContent)
FetchContent_Declare(
        googletest
        # Specify the commit you depend on and update it regularly.
        URL https://github.com/google/googletest/archive/5376968f6948923e2411081fd9372e71a59d8e77.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# include libraries that we need
include_directories(external/abseil-cpp/)

# add the subdirectories with stuff to be built
add_subdirectory(src)
add_subdirectory(external)
add_subdirectory(tests)