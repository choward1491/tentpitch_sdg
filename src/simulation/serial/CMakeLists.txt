add_library(serial)
target_sources(serial
               PUBLIC serial_simulation.h
               PRIVATE serial_simulation.cpp
               )