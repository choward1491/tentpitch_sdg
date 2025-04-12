/*
** Created by Christian Howard on 2/1/24.
*/
#ifndef TENTPITCH_SDG_SRC_MESHING_MESH_ABSTRACTIONS_FACET_POOL_INTERFACE_H_
#define TENTPITCH_SDG_SRC_MESHING_MESH_ABSTRACTIONS_FACET_POOL_INTERFACE_H_

#include "absl/status/status.h"
#include "absl/status/statusor.h"

#include "meshing/mesh_abstractions/facet.fwd.h"
#include "meshing/mesh_abstractions/facet.h"

#include "shared/constants.h"

namespace tp_sdg::meshing::abstractions {
using IdType = ::tp_sdg::shared::constants::IdType;

class FacetPoolInterface {
 public:
  virtual ~FacetPoolInterface() = default;
  void SetDimensionForFacets(int d) { facet_dim_ = d; }
  int GetDimensionForFacets() const { return facet_dim_; }
  // Create new facet that is not in the wild with a distinct ID and its dimension set.
  [[nodiscard]] virtual FacetHandle GetNewFacet() = 0;
  [[nodiscard]] virtual absl::Status RemoveFacetWithId(::tp_sdg::shared::constants::IdType id) = 0;
  [[nodiscard]] virtual absl::StatusOr<FacetHandle> GetFacet(::tp_sdg::shared::constants::IdType id) const = 0;
  [[nodiscard]] virtual std::size_t NumFacets() const = 0;
 private:
  int facet_dim_;
};

}

#endif //TENTPITCH_SDG_SRC_MESHING_MESH_ABSTRACTIONS_FACET_POOL_INTERFACE_H_
