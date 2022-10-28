add_library(external INTERFACE)

add_subdirectory(abseil-cpp)
target_link_libraries(external INTERFACE absl)