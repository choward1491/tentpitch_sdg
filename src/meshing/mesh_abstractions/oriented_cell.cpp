/*
** Created by Christian Howard on 10/12/22.
*/
#include "meshing/mesh_abstractions/oriented_cell.h"

namespace tp_sdg::meshing::abstractions {

OrientedCell::OrientedCell() : dimension_(-1) {

}
void OrientedCell::SetDimension(int dimension) {
  ABSL_ASSERT(dimension <= kMaxChamberDim && dimension >= 0);
  dimension_ = dimension;
}
int OrientedCell::GetDimension() const {
  ABSL_ASSERT(dimension_ > -1);
  return dimension_;
}
absl::Status OrientedCell::SetVertices(std::initializer_list<VertexHandle> list) {
  int count = 0;
  for (auto vh : list) {
    if (count > kMaxChamberVertices) { return absl::InvalidArgumentError("Initializer list of vertices is too large"); }
    if (vh.IsNull()) { return absl::InvalidArgumentError("Vertex handle is null"); }
    vertices_[count++] = vh;
  }
  dimension_ = count - 1;
  return absl::OkStatus();
}
absl::Status OrientedCell::SetVertex(int idx, VertexHandle vh) {
  ABSL_ASSERT(dimension_ > -1);
  ABSL_ASSERT(idx >= 0 && idx <= dimension_);
  if (vh.IsNull()) { return absl::InvalidArgumentError("Vertex handle is null"); }
  vertices_[idx] = vh;
  return absl::OkStatus();
}
VertexHandle OrientedCell::GetVertex(int idx) const {
  ABSL_ASSERT(dimension_ > -1);
  ABSL_ASSERT(idx >= 0 && idx <= dimension_);
  return vertices_[idx];
}
void OrientedCell::reset() {
  dimension_ = -1;
  vertices_.fill(nullptr);
}
}