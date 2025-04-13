/*
** Created by Christian Howard on 2/1/24.
*/
#ifndef TENTPITCH_SDG_SRC_MESHING_MESH_ABSTRACTIONS_VERTEX_POOL_INTERFACE_H_
#define TENTPITCH_SDG_SRC_MESHING_MESH_ABSTRACTIONS_VERTEX_POOL_INTERFACE_H_

#include "absl/status/status.h"
#include "absl/status/statusor.h"

#include "meshing/mesh_abstractions/vertex.fwd.h"
#include "meshing/mesh_abstractions/vertex.h"

#include "shared/constants.h"

namespace tp_sdg::meshing::abstractions {
using ::tp_sdg::shared::constants::IdType;

class VertexPoolInterface {
 public:
  virtual ~VertexPoolInterface() = default;
  void SetDimensionForFacets(int d) { vertex_dim_ = d; }
  int GetDimensionForFacets() const { return vertex_dim_; }
  [[nodiscard]] virtual VertexHandle GetNewVertex() = 0;
  [[nodiscard]] virtual absl::Status RemoveVertexWithId(::tp_sdg::shared::constants::IdType id) = 0;
  [[nodiscard]] virtual absl::StatusOr<VertexHandle> GetVertex(::tp_sdg::shared::constants::IdType id) const = 0;
  [[nodiscard]] virtual std::size_t NumVertices() const = 0;
 private:
  int vertex_dim_;
};

}

#endif //TENTPITCH_SDG_SRC_MESHING_MESH_ABSTRACTIONS_VERTEX_POOL_INTERFACE_H_
