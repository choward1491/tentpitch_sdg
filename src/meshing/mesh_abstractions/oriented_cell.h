/*
** Created by Christian Howard on 10/12/22.
*/
#ifndef TENTPITCH_SDG_SRC_MESHING_MESH_ABSTRACTIONS_ORIENTED_CELL_H_
#define TENTPITCH_SDG_SRC_MESHING_MESH_ABSTRACTIONS_ORIENTED_CELL_H_

#include <array>

#include "absl/status/status.h"
#include "absl/status/statusor.h"

#include "meshing/mesh_abstractions/constants.h"
#include "meshing/mesh_abstractions/vertex.fwd.h"
#include "shared/utility/raw_ptr.h"

namespace tp_sdg::meshing::abstractions {

class OrientedCell {
 public:
  OrientedCell();
  ~OrientedCell() = default;

  absl::Status SetDimension(int dimension);
  int GetDimension() const;
  absl::Status SetVertices(std::initializer_list<VertexHandle> list);
  absl::Status SetVertex(int idx, VertexHandle vh);
  absl::StatusOr<VertexHandle> GetVertex(int idx) const;

 private:
  int dimension_;
  std::array<VertexHandle, kMaxChamberVertices> vertices_;
};

};


#endif //TENTPITCH_SDG_SRC_MESHING_MESH_ABSTRACTIONS_ORIENTED_CELL_H_
