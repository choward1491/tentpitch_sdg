add_library(threaded)
target_sources(threaded
               PUBLIC threaded_simulation.h
               PRIVATE threaded_simulation.cpp
               )