/*
** Created by Christian Howard on 10/28/22.
*/
#ifndef TENTPITCH_SDG_SRC_MESHING_MESH_ABSTRACTIONS_VERTEX_INC_H_
#define TENTPITCH_SDG_SRC_MESHING_MESH_ABSTRACTIONS_VERTEX_INC_H_

#include "meshing/mesh_abstractions/vertex.h"
namespace tp_sdg::meshing::abstractions {
template<int d>
absl::Status Vertex::SetCoordinates(const std::array<shared::constants::PrecisionType, d + 1> &spacetime_coords) {
  if constexpr (d > kMaxVertexSpatialDimensions) {
    return absl::InvalidArgumentError("Input list of spacetime coordinates had too large a dimension");
  }
  if constexpr (d < 1) {
    return absl::InvalidArgumentError("Input list of spacetime coordinates has too small a dimension");
  }
  spatial_dim_ = d;
  coordinates_.fill(0.0);
  std::memcpy(coordinates_.data(), spacetime_coords.data(), (d + 1) * sizeof(shared::constants::PrecisionType));
}
}

#endif //TENTPITCH_SDG_SRC_MESHING_MESH_ABSTRACTIONS_VERTEX_INC_H_
