/*
** Created by Christian Howard on 10/30/22.
*/
#ifndef TENTPITCH_SDG_SRC_MESHING_MESH_ABSTRACTIONS_ORIENTED_CELL_INC_H_
#define TENTPITCH_SDG_SRC_MESHING_MESH_ABSTRACTIONS_ORIENTED_CELL_INC_H_

#include "oriented_cell.h"

namespace tp_sdg::meshing::abstractions {

template<int d>
absl::Status OrientedCell::SetVertices(const std::array<VertexHandle, d + 1> &vertices) {
  static_assert(d >= 0 && d <= kMaxChamberDim);
  for(int i = 0; i <= d; ++i){
    if (vertices[i].IsNull()) { return absl::InvalidArgumentError("Vertex handle is null"); }
    vertices_[i] = vertices[i];
  }
  dimension_ = d;
  return absl::OkStatus();
}

}

#endif //TENTPITCH_SDG_SRC_MESHING_MESH_ABSTRACTIONS_ORIENTED_CELL_INC_H_
