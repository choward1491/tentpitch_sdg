add_library(external INTERFACE)
#target_include_directories(external PRIVATE ${CMAKE_CURRENT_LIST_DIR})
#target_sources(external PRIVATE dummy.cpp)

add_subdirectory(abseil-cpp)
target_link_libraries(external INTERFACE absl)