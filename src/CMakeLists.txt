add_library(tentpitch_sdg_lib INTERFACE)

add_subdirectory(geometry_model)
add_subdirectory(meshing)
add_subdirectory(numerics)
add_subdirectory(shared)
add_subdirectory(simulation)

target_link_libraries(tentpitch_sdg_lib INTERFACE
                      geometry_model
                      meshing
                      numerics
                      simulation
                      shared)