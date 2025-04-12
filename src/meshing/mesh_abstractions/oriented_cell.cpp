/*
** Created by Christian Howard on 10/12/22.
*/
#include "meshing/mesh_abstractions/oriented_cell.h"

using ::tp_sdg::shared::constants::kInvalidId;

namespace tp_sdg::meshing::abstractions {

OrientedCell::OrientedCell() : dimension_(-1) {

}
OrientedCell::~OrientedCell() {
  Reset();
}

void OrientedCell::SetDimension(int dimension) {
  ABSL_ASSERT(dimension <= kMaxChamberDim && dimension >= 0);
  dimension_ = dimension;
}
int OrientedCell::GetDimension() const {
  ABSL_ASSERT(dimension_ > -1);
  return dimension_;
}
void OrientedCell::SetVertices(std::initializer_list<VertexHandle> list) {
  int count = 0;
  for (auto vh : list) {
    ABSL_ASSERT(count <= kMaxChamberVertices);
    ABSL_ASSERT(vh.IsNotNull());
    vertices_[count++] = vh;
  }
  dimension_ = count - 1;
}
void OrientedCell::SetVertex(int idx, VertexHandle vh) {
  ABSL_ASSERT(dimension_ > -1);
  ABSL_ASSERT(idx >= 0 && idx <= dimension_);
  ABSL_ASSERT(vh.IsNotNull());
  vertices_[idx] = vh;
}
VertexHandle OrientedCell::GetVertex(int idx) const {
  ABSL_ASSERT(dimension_ > -1);
  ABSL_ASSERT(idx >= 0 && idx <= dimension_);
  return vertices_[idx];
}
void OrientedCell::Reset() {
  id_ = kInvalidId;
  dimension_ = -1;
  vertices_.fill(VertexHandle(nullptr));
}
void OrientedCell::SetId(::tp_sdg::shared::constants::IdType id) {
  ABSL_ASSERT(id != kInvalidId);
  id_ = id;
}
::tp_sdg::shared::constants::IdType OrientedCell::GetId() const {
  return id_;
}

}