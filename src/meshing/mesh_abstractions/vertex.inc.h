/*
** Created by Christian Howard on 10/28/22.
*/
#ifndef TENTPITCH_SDG_SRC_MESHING_MESH_ABSTRACTIONS_VERTEX_INC_H_
#define TENTPITCH_SDG_SRC_MESHING_MESH_ABSTRACTIONS_VERTEX_INC_H_

#include "meshing/mesh_abstractions/vertex.h"
namespace tp_sdg::meshing::abstractions {
template<int d>
void Vertex::SetCoordinates(const std::array<shared::constants::PrecisionType, d + 1> &spacetime_coords) {
  static_assert(d <= kMaxVertexSpatialDimensions && d >= 1, "Invalid spacetime coordinate list");
  SetSpatialDimension(d);
  coordinates_.fill(0.0);
  for(int i = 0; i <= d; ++i){
    SetCoordinate(i, spacetime_coords[i]);
  }
}
}

#endif //TENTPITCH_SDG_SRC_MESHING_MESH_ABSTRACTIONS_VERTEX_INC_H_
