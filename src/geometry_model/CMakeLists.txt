# set library for the meshing and geometry model abstractions
add_library(geometry_model)
target_include_directories(geometry_model PRIVATE ${CMAKE_CURRENT_LIST_DIR}/)
target_sources(geometry_model PUBLIC geometry_model.h geometry_model.cpp)

# testing related executables
add_executable(geom_lib_tests)
target_include_directories(geom_lib_tests PRIVATE ${CMAKE_CURRENT_LIST_DIR}/)
target_sources(geom_lib_tests PRIVATE geometry_model_test.cpp)
target_link_libraries(geom_lib_tests gtest_main geometry_model)
add_test(NAME GeomLibTests COMMAND geom_lib_tests)