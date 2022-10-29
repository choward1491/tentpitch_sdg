/*
** Created by Christian Howard on 10/12/22.
*/
#ifndef TENTPITCH_SDG_SRC_MESHING_MESH_ABSTRACTIONS_CHAMBER_H_
#define TENTPITCH_SDG_SRC_MESHING_MESH_ABSTRACTIONS_CHAMBER_H_

#include <array>

#include "absl/status/status.h"
#include "absl/status/statusor.h"

#include "meshing/mesh_abstractions/facet.fwd.h"
#include "meshing/mesh_abstractions/oriented_cell.h"

namespace tp_sdg::meshing::abstractions {

class Chamber : public OrientedCell {
 public:
  Chamber() = default;
  ~Chamber() = default;

  absl::Status SetFacet(int idx, FacetHandle facet);
  absl::StatusOr<FacetHandle> GetFacet(int idx) const;
  absl::Status SetCointerstitial(FacetHandle cointerstitial);
  FacetHandle GetCointerstitial() const;

 private:
  std::array<FacetHandle, kMaxChamberDim + 1> facets_;
  FacetHandle cointerstitial_;
};

}

#endif //TENTPITCH_SDG_SRC_MESHING_MESH_ABSTRACTIONS_CHAMBER_H_
