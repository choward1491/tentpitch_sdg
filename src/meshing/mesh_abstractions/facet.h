/*
** Created by Christian Howard on 10/12/22.
*/
#ifndef TENTPITCH_SDG_SRC_MESHING_MESH_ABSTRACTIONS_FACET_H_
#define TENTPITCH_SDG_SRC_MESHING_MESH_ABSTRACTIONS_FACET_H_

#include <array>

#include "absl/status/status.h"
#include "absl/status/statusor.h"

#include "meshing/mesh_abstractions/chamber.fwd.h"
#include "meshing/mesh_abstractions/constants.h"
#include "meshing/mesh_abstractions/facet.fwd.h"
#include "meshing/mesh_abstractions/oriented_cell.h"
#include "meshing/mesh_abstractions/vertex.fwd.h"

namespace tp_sdg {
namespace meshing {
namespace abstractions {

class Facet : public OrientedCell {
 public:
  Facet() = default;
  ~Facet() = default;

  void SetTwin(FacetHandle twin);
  [[nodiscard]] FacetHandle GetTwin() const;
  void SetCofacet(ChamberHandle cofacet);
  [[nodiscard]] ChamberHandle GetCofacet() const;
  void SetInterstitial(ChamberHandle interstitial);
  [[nodiscard]] ChamberHandle GetInterstitial() const;

 private:

  FacetHandle twin_;
  ChamberHandle cofacet_;
  ChamberHandle interstitial_;
};

}
}
}

#endif //TENTPITCH_SDG_SRC_MESHING_MESH_ABSTRACTIONS_FACET_H_
