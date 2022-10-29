/*
** Created by Christian Howard on 10/28/22.
*/
#ifndef TENTPITCH_SDG_SRC_MESHING_UTILITY_MESH_ENTITY_ID_PACK_H_
#define TENTPITCH_SDG_SRC_MESHING_UTILITY_MESH_ENTITY_ID_PACK_H_

#include "shared/constants.h"

namespace tp_sdg::meshing::utility {
struct MeshEntityIdPack {
  ::tp_sdg::shared::constants::IdType front_id = ::tp_sdg::shared::constants::kInvalidId;
  ::tp_sdg::shared::constants::IdType footprint_id = ::tp_sdg::shared::constants::kInvalidId;
  ::tp_sdg::shared::constants::IdType patch_id = ::tp_sdg::shared::constants::kInvalidId;
};
}

#endif //TENTPITCH_SDG_SRC_MESHING_UTILITY_MESH_ENTITY_ID_PACK_H_
