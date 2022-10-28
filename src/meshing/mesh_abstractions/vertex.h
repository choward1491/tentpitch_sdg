/*
** Created by Christian Howard on 10/12/22.
*/
#ifndef TENTPITCH_SDG_SRC_MESHING_MESH_ABSTRACTIONS_VERTEX_H_
#define TENTPITCH_SDG_SRC_MESHING_MESH_ABSTRACTIONS_VERTEX_H_

#include <array>
#include <set>

#include "absl/status/status.h"
#include "absl/status/statusor.h"

#include "meshing/mesh_abstractions/constants.h"
#include "shared/constants.h"
#include "chamber.fwd.h"

namespace tp_sdg::meshing::abstractions {

class Vertex {
 public:
  Vertex();
  ~Vertex() = default;

  absl::Status SetSpatialDimension(int spatial_dim);
  int GetSpatialDimension() const;

  absl::Status SetCoordinate(int idx, shared::constants::PrecisionType coordinate_value);
  absl::StatusOr<shared::constants::PrecisionType> GetCoordinate(int idx) const;
  absl::Status SetTime(shared::constants::PrecisionType time_value);
  shared::constants::PrecisionType GetTime() const;

  absl::Status AddIncidentChamber(ChamberHandle ch);
  absl::Status RemoveIncidentChamber(ChamberHandle ch);

 private:
  int spatial_dim_;
  std::array<shared::constants::PrecisionType, kMaxVertexSpatialDimensions + 1> coordinates_;
  std::array<std::set<ChamberHandle>, kMaxChamberDim+1> incidence_lists_;
};

}

#endif //TENTPITCH_SDG_SRC_MESHING_MESH_ABSTRACTIONS_VERTEX_H_
