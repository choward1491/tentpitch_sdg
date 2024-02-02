/*
** Created by Christian Howard on 2/1/24.
*/

#include "mesh_entity_id_pack.h"

namespace tp_sdg::meshing::utility {

//enum class MeshIdType: int { Front= 0, Footprint, Patch};
MeshEntityIdPack::MeshEntityIdPack() : ids{shared::constants::kInvalidId, shared::constants::kInvalidId,
                                           shared::constants::kInvalidId} {
  main_id_type = MeshIdType::Front;
}
void MeshEntityIdPack::SetIdTypeTo(MeshIdType type) {
  main_id_type = type;
}
void MeshEntityIdPack::SetId(::tp_sdg::shared::constants::IdType id) {
  SetSpecificId(main_id_type, id);
}
void MeshEntityIdPack::SetSpecificId(MeshIdType type, ::tp_sdg::shared::constants::IdType id) {
  ids[static_cast<int>(type)] = id;
}
::tp_sdg::shared::constants::IdType MeshEntityIdPack::GetId() const {
  return GetSpecificId(main_id_type);
}
::tp_sdg::shared::constants::IdType MeshEntityIdPack::GetSpecificId(MeshIdType type) const {
  return ids[static_cast<int>(type)];
}
void MeshEntityIdPack::SetAllIdsTo(::tp_sdg::shared::constants::IdType id) {
  ids.fill(id);
}
void MeshEntityIdPack::SetAllIdsInvalid() {
  ids.fill(shared::constants::kInvalidId);
}

//std::array<::tp_sdg::shared::constants::IdType, 3> ids;

}