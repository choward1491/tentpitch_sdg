
cc_library(
    name = "mesh_abstractions",
    hdrs = [
      "chamber.h",
      "facet.h",
      "footprint.h",
      "oriented_cell.h",
      "oriented_mesh.h",
      "patch.h",
      "stratified_mesh.h",
      "vertex.h"
    ],
    srcs = [
      "chamber.cpp",
      "facet.cpp",
      "footprint.cpp",
      "oriented_cell.cpp",
      "oriented_mesh.cpp",
      "patch.cpp",
      "stratified_mesh.cpp",
      "vertex.cpp"
    ]
)

cc_test(
    name = "mesh_abstractions_test",
    srcs = [
        "chamber_test.cpp",
        "facet_test.cpp",
        "footprint_test.cpp",
        "oriented_cell_test.cpp",
        "oriented_mesh_test.cpp",
        "stratified_mesh_test.cpp",
        "patch_test.cpp",
        "vertex_test.cpp"
    ],
    deps = [
        ":mesh_abstractions"
    ]
)