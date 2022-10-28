/*
** Created by Christian Howard on 10/12/22.
*/
#ifndef TENTPITCH_SDG_SRC_MESHING_MESH_ABSTRACTIONS_FACET_H_
#define TENTPITCH_SDG_SRC_MESHING_MESH_ABSTRACTIONS_FACET_H_

#include <array>

#include "meshing/mesh_abstractions/chamber.fwd.h"
#include "meshing/mesh_abstractions/constants.h"
#include "meshing/mesh_abstractions/facet.fwd.h"
#include "meshing/mesh_abstractions/oriented_cell.h"
#include "meshing/mesh_abstractions/vertex.fwd.h"

namespace tp_sdg::meshing::abstractions {

class Facet : public OrientedCell {
 public:
  Facet();
  ~Facet() = default;

 private:
  int dim_;
  FacetHandle twin_;
  ChamberHandle cofacet_;
  ChamberHandle cointerstitial_;
};

}

#endif //TENTPITCH_SDG_SRC_MESHING_MESH_ABSTRACTIONS_FACET_H_
