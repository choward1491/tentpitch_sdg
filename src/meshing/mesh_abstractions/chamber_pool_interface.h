/*
** Created by Christian Howard on 2/1/24.
*/
#ifndef TENTPITCH_SDG_SRC_MESHING_MESH_ABSTRACTIONS_CHAMBER_POOL_INTERFACE_H_
#define TENTPITCH_SDG_SRC_MESHING_MESH_ABSTRACTIONS_CHAMBER_POOL_INTERFACE_H_

#include "absl/status/status.h"
#include "absl/status/statusor.h"

#include "meshing/mesh_abstractions/chamber.fwd.h"
#include "meshing/mesh_abstractions/chamber.h"

#include "shared/constants.h"

namespace tp_sdg::meshing::abstractions {
using ::tp_sdg::shared::constants::IdType;

class ChamberPoolInterface {
 public:
  virtual ~ChamberPoolInterface() = default;
  void SetDimensionForChambers(int d) { chamber_dim_ = d; }
  int GetDimensionForChambers() const { return chamber_dim_; }

  // Create new chamber that is not in the wild with a distinct ID and its dimension set.
  [[nodiscard]] virtual ChamberHandle GetNewChamber() = 0;
  [[nodiscard]] virtual absl::Status RemoveChamberWithId(::tp_sdg::shared::constants::IdType id) = 0;
  [[nodiscard]] virtual absl::StatusOr<ChamberHandle> GetChamber(::tp_sdg::shared::constants::IdType id) const = 0;
  [[nodiscard]] virtual std::size_t NumChambers() const = 0;

 private:
  int chamber_dim_;
};

}

#endif //TENTPITCH_SDG_SRC_MESHING_MESH_ABSTRACTIONS_CHAMBER_POOL_INTERFACE_H_
