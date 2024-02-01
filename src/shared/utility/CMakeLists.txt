add_library(utility status_macro.cpp status_macro.h)
set_target_properties(utility PROPERTIES LINKER_LANGUAGE CXX)
target_include_directories(utility PRIVATE ${CMAKE_CURRENT_LIST_DIR}/)
target_sources(utility
               PUBLIC raw_ptr.h
               PRIVATE raw_ptr.cpp)