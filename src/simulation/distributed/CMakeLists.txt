add_library(distributed)
target_sources(distributed
               PUBLIC distributed_simulation.h
               PRIVATE distributed_simulation.cpp
               )