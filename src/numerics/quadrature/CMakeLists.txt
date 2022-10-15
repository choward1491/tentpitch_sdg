add_library(quadrature)
target_sources(quadrature
               PUBLIC quadrature_builder.h
               PRIVATE quadrature_builder.cpp
               )