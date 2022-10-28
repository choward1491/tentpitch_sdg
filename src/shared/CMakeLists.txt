add_library(shared INTERFACE constants.h)

add_subdirectory(utility)

set_target_properties(shared PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(shared INTERFACE utility)