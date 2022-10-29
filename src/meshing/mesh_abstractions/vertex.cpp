/*
** Created by Christian Howard on 10/12/22.
*/
#include "meshing/mesh_abstractions/vertex.h"
#include "meshing/mesh_abstractions/chamber.h"
#include "status_macros/status_macros.h"

namespace tp_sdg::meshing::abstractions {

Vertex::Vertex() : spatial_dim_(-1) {
  coordinates_.fill(0.0);
}
absl::Status Vertex::SetCoordinate(int idx, shared::constants::PrecisionType coordinate_value) {
  ABSL_ASSERT(spatial_dim_ > 1);
  if (idx < 0 || idx > spatial_dim_) {
    return absl::InvalidArgumentError("Index out of bounds");
  }
  coordinates_[idx] = coordinate_value;
  return absl::OkStatus();
}
absl::StatusOr<shared::constants::PrecisionType> Vertex::GetCoordinate(int idx) const {
  ABSL_ASSERT(spatial_dim_ > 1);
  if (idx < 0 || idx > spatial_dim_) {
    return absl::InvalidArgumentError("Index out of bounds");
  }
  return coordinates_[idx];
}
void Vertex::SetTime(shared::constants::PrecisionType time_value) {
  ABSL_ASSERT(spatial_dim_ > 1);
  coordinates_[spatial_dim_] = time_value;
}
shared::constants::PrecisionType Vertex::GetTime() const {
  ABSL_ASSERT(spatial_dim_ > 1);
  return coordinates_[spatial_dim_];
}
absl::Status Vertex::AddIncidentChamber(ChamberHandle ch) {
  ABSL_ASSERT(spatial_dim_ > 1);
  int dim = ch->GetDimension();
  if (dim > kMaxChamberDim || dim < 0) {
    return absl::InvalidArgumentError("Input chamber has an invalid dimension");
  }
  incidence_lists_[dim].insert(ch);
  return absl::OkStatus();
}
absl::Status Vertex::RemoveIncidentChamber(ChamberHandle ch) {
  ABSL_ASSERT(spatial_dim_ > 1);
  int dim = ch->GetDimension();
  if (dim > kMaxChamberDim || dim < 0) {
    return absl::InvalidArgumentError("Input chamber has an invalid dimension");
  }
  incidence_lists_[dim].erase(ch);
  return absl::OkStatus();
}
tp_sdg::shared::constants::IdType &Vertex::front_id() {
  return id_pack_.front_id;
}
tp_sdg::shared::constants::IdType &Vertex::footprint_id() {
  return id_pack_.footprint_id;
}
tp_sdg::shared::constants::IdType &Vertex::patch_id() {
  return id_pack_.patch_id;
}
void Vertex::reset() {
  spatial_dim_ = -1;
  id_pack_ = tp_sdg::meshing::utility::MeshEntityIdPack();
  coordinates_.fill(0.0);
  for(auto& set: incidence_lists_){ set.clear(); }
}
absl::Status Vertex::SetSpatialDimension(int vertex_dimension) {
  if( vertex_dimension > kMaxVertexSpatialDimensions || vertex_dimension < 1) {
    return absl::InvalidArgumentError("Invalid vertex dimension");
  }
  spatial_dim_ = vertex_dimension;
  return absl::OkStatus();
}
int Vertex::GetSpatialDimension() const {
  return spatial_dim_;
}

}