/*
** Created by Christian Howard on 4/12/25.
*/
#ifndef TENTPITCH_SDG_SRC_MESHING_MESH_ABSTRACTIONS_CHAMBER_POOL_GENERATOR_H_
#define TENTPITCH_SDG_SRC_MESHING_MESH_ABSTRACTIONS_CHAMBER_POOL_GENERATOR_H_

#include <memory>

#include "absl/status/status.h"
#include "absl/status/statusor.h"

#include "chamber_pool_interface.h"

namespace tp_sdg::meshing::abstractions {
using ::tp_sdg::shared::constants::IdType;

class ChamberPoolGenerator {
 public:
  ChamberPoolGenerator() = default;
  ~ChamberPoolGenerator() = default;
  [[nodiscard]] virtual std::unique_ptr<ChamberPoolInterface> Create() = 0;
};


}

#endif //TENTPITCH_SDG_SRC_MESHING_MESH_ABSTRACTIONS_CHAMBER_POOL_GENERATOR_H_
