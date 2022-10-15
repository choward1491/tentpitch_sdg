add_library(numerics INTERFACE)

add_subdirectory(physics_models)
add_subdirectory(quadrature)

target_link_libraries(numerics INTERFACE physics_models quadrature)