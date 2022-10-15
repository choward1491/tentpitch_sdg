add_library(meshing INTERFACE)

add_subdirectory(mesh_abstractions)
add_subdirectory(tent_pitching)
add_subdirectory(utility)

target_link_libraries(meshing INTERFACE
                      mesh_abstractions
                      )