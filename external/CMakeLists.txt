add_library(external INTERFACE)

add_subdirectory(abseil-cpp)
add_subdirectory(status_macros)
target_link_libraries(external INTERFACE absl status_macros)