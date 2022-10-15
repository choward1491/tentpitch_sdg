# set library for the meshing and geometry model abstractions
add_library(mesh_abstractions)
target_include_directories(mesh_abstractions PRIVATE ${CMAKE_CURRENT_LIST_DIR}/)
target_sources(mesh_abstractions
               PUBLIC chamber.cpp chamber.h facet.cpp facet.h footprint.cpp footprint.h oriented_cell.cpp oriented_cell.h patch.cpp patch.h stratified_mesh.cpp stratified_mesh.h vertex.cpp vertex.h)

# testing related executables
add_executable(mesh_abstraction_tests)
target_include_directories(mesh_abstraction_tests PRIVATE ${CMAKE_CURRENT_LIST_DIR}/)
target_sources(mesh_abstraction_tests PRIVATE chamber_test.cpp facet_test.cpp footprint_test.cpp oriented_cell_test.cpp oriented_mesh_test.cpp patch_test.cpp stratified_mesh_test.cpp vertex_test.cpp)
target_link_libraries(mesh_abstraction_tests gtest_main mesh_abstractions geometry_model)
add_test(NAME MeshAbstractionTests COMMAND mesh_abstraction_tests)