add_library(physics_models)
target_sources(physics_models
               PUBLIC physics_modeler.h
               PRIVATE physics_modeler.cpp)