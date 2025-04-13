/*
** Created by Christian Howard on 10/12/22.
*/
#ifndef TENTPITCH_SDG_SRC_MESHING_MESH_ABSTRACTIONS_FOOTPRINT_H_
#define TENTPITCH_SDG_SRC_MESHING_MESH_ABSTRACTIONS_FOOTPRINT_H_

#include <array>
#include <memory>

#include "absl/status/status.h"
#include "absl/status/statusor.h"

#include "chamber_pool_generator.h"
#include "chamber_pool_interface.h"
#include "facet_pool_generator.h"
#include "facet_pool_interface.h"
#include "vertex.fwd.h"
#include "vertex_pool_interface.h"
#include "oriented_mesh.fwd.h"
#include "stratified_mesh.h"

#include "shared/constants.h"
#include "shared/utility/raw_ptr.h"

namespace tp_sdg::meshing::abstractions {

class Footprint : public StratifiedMesh {
 public:
  struct Input {

  };

 private:
  explicit Footprint(Input &input);
};

}

#endif //TENTPITCH_SDG_SRC_MESHING_MESH_ABSTRACTIONS_FOOTPRINT_H_
