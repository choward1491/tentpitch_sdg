# set library for the meshing and geometry model abstractions
add_library(meshing_utility INTERFACE)
set_target_properties(meshing_utility PROPERTIES LINKER_LANGUAGE CXX)
target_sources(meshing_utility
               INTERFACE mesh_entity_id_pack.h)