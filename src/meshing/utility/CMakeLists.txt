# set library for the meshing and geometry model abstractions
add_library(meshing_utility)
set_target_properties(meshing_utility PROPERTIES LINKER_LANGUAGE CXX)
target_sources(meshing_utility
               PUBLIC mesh_entity_id_pack.h
               PRIVATE mesh_entity_id_pack.cpp)