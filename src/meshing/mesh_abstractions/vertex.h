/*
** Created by Christian Howard on 10/12/22.
*/
#ifndef TENTPITCH_SDG_SRC_MESHING_MESH_ABSTRACTIONS_VERTEX_H_
#define TENTPITCH_SDG_SRC_MESHING_MESH_ABSTRACTIONS_VERTEX_H_

#include <array>
#include <cstring>
#include <set>

#include "absl/status/status.h"
#include "absl/status/statusor.h"

#include "meshing/mesh_abstractions/chamber.fwd.h"
#include "meshing/mesh_abstractions/constants.h"
#include "meshing/utility/mesh_entity_id_pack.h"
#include "shared/constants.h"

namespace tp_sdg::meshing::abstractions {

class Vertex {
 public:
  Vertex();
  ~Vertex() = default;

  // methods revolving around the IDs for the vertex
  tp_sdg::shared::constants::IdType &front_id();
  tp_sdg::shared::constants::IdType &footprint_id();
  tp_sdg::shared::constants::IdType &patch_id();

  // methods for setting coordinates and dimension
  void SetSpatialDimension(int vertex_dimension);
  void SetCoordinate(int idx, shared::constants::PrecisionType coordinate_value);
  void SetCoordinates(std::initializer_list<shared::constants::PrecisionType> coordinates);
  void SetTime(shared::constants::PrecisionType time_value);

  template<int d>
  void SetCoordinates(const std::array<shared::constants::PrecisionType, d + 1> &spacetime_coords);

  [[nodiscard]] int GetSpatialDimension() const;
  [[nodiscard]] shared::constants::PrecisionType GetCoordinate(int idx) const;
  [[nodiscard]] shared::constants::PrecisionType GetTime() const;

  // methods for impacting connectivity of the vertex
  absl::Status AddIncidentChamber(ChamberHandle ch);
  absl::Status RemoveIncidentChamber(ChamberHandle ch);
  [[nodiscard]] absl::StatusOr<const std::set<ChamberHandle>*> GetIncidenceList(int dim_of_chambers) const;

  // clean up methods
  void reset();

 private:
  int spatial_dim_;
  tp_sdg::meshing::utility::MeshEntityIdPack id_pack_;
  std::array<shared::constants::PrecisionType, kMaxVertexSpatialDimensions + 1> coordinates_;
  std::array<std::set<ChamberHandle>, kMaxChamberDim + 1> incidence_lists_;
};

}

#include "meshing/mesh_abstractions/vertex.inc.h"

#endif //TENTPITCH_SDG_SRC_MESHING_MESH_ABSTRACTIONS_VERTEX_H_
