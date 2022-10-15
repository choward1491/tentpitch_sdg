add_library(simulation INTERFACE)

add_subdirectory(serial)
add_subdirectory(threaded)
add_subdirectory(distributed)

target_link_libraries(simulation INTERFACE serial threaded distributed)