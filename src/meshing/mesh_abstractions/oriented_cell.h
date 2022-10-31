/*
** Created by Christian Howard on 10/12/22.
*/
#ifndef TENTPITCH_SDG_SRC_MESHING_MESH_ABSTRACTIONS_ORIENTED_CELL_H_
#define TENTPITCH_SDG_SRC_MESHING_MESH_ABSTRACTIONS_ORIENTED_CELL_H_

#include <array>

#include "absl/status/status.h"

#include "meshing/mesh_abstractions/constants.h"
#include "meshing/mesh_abstractions/vertex.fwd.h"
#include "shared/utility/raw_ptr.h"

namespace tp_sdg::meshing::abstractions {

class OrientedCell {
 public:
  OrientedCell();
  ~OrientedCell() = default;

  void SetDimension(int dimension);
  absl::Status SetVertex(int idx, VertexHandle vh);
  absl::Status SetVertices(std::initializer_list<VertexHandle> list);
  template<int d>
  absl::Status SetVertices(const std::array<VertexHandle, d+1>& vertices);

  [[nodiscard]] int GetDimension() const;
  [[nodiscard]] VertexHandle GetVertex(int idx) const;

  void reset();

 private:
  int dimension_;
  std::array<VertexHandle, kMaxChamberVertices> vertices_;
};

}

#include "meshing/mesh_abstractions/oriented_cell.inc.h"

#endif //TENTPITCH_SDG_SRC_MESHING_MESH_ABSTRACTIONS_ORIENTED_CELL_H_
