/*
** Created by Christian Howard on 10/28/22.
*/
#ifndef TENTPITCH_SDG_SRC_MESHING_UTILITY_MESH_ENTITY_ID_PACK_H_
#define TENTPITCH_SDG_SRC_MESHING_UTILITY_MESH_ENTITY_ID_PACK_H_

#include <array>

#include "shared/constants.h"

namespace tp_sdg::meshing::utility {
class MeshEntityIdPack {
 public:
  enum class MeshIdType : int { Front = 0, Footprint, Patch };
  MeshEntityIdPack();
  ~MeshEntityIdPack() = default;
  void SetIdTypeTo(MeshIdType type);
  void SetId(::tp_sdg::shared::constants::IdType);
  void SetSpecificId(MeshIdType type, ::tp_sdg::shared::constants::IdType);
  ::tp_sdg::shared::constants::IdType GetId() const;
  ::tp_sdg::shared::constants::IdType GetSpecificId(MeshIdType type) const;
  void SetAllIdsTo(::tp_sdg::shared::constants::IdType id);
  void SetAllIdsInvalid();

 private:
  MeshIdType main_id_type;
  std::array<::tp_sdg::shared::constants::IdType, 3> ids;

};
}

#endif //TENTPITCH_SDG_SRC_MESHING_UTILITY_MESH_ENTITY_ID_PACK_H_
