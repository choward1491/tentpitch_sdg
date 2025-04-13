/*
** Created by Christian Howard on 10/12/22.
*/
#include "stratified_mesh.h"

#include <utility>

#include "absl/status/status.h"
#include "absl/status/statusor.h"
#include "absl/memory/memory.h"

#include "oriented_mesh.h"
#include "status_macros/status_macros.h"

namespace tp_sdg::meshing::abstractions {
absl::StatusOr<std::unique_ptr<StratifiedMesh>> StratifiedMesh::Create(Input &input) {
  if(input.top_dimension < 1 || input.top_dimension > 4) {
    return absl::InvalidArgumentError("Top bound must be in set {1, 2, 3, 4}.");
  }
  if(input.chamber_pool_generator.IsNull()) return absl::InvalidArgumentError("Chamber pool generator is null.");
  if(input.facet_pool_generator.IsNull()) return absl::InvalidArgumentError("Facet pool generator is null.");
  if(not input.vertex_pool) return absl::InvalidArgumentError("Vertex pool is null.");

  // Try to build up the oriented meshes and return an error if something goes wrong.
  std::array<std::unique_ptr<OrientedMesh>, 5> oriented_meshes;
  for(int i = 1; i <= 4; ++i){
    int vertex_dim = i <= input.top_dimension ? input.top_dimension : i;
    OrientedMesh::Input input2{.dimension = i,
        .vertex_dimension = vertex_dim,
        .facet_pool = input.facet_pool_generator->Create(),
        .chamber_pool = input.chamber_pool_generator->Create()};
    ASSIGN_OR_RETURN(oriented_meshes[i], OrientedMesh::Create(input2));
  }
  return absl::WrapUnique(new StratifiedMesh(input, oriented_meshes));
}

VertexHandle StratifiedMesh::AddVertex() const {
  return vertex_pool_->GetNewVertex();
}
absl::StatusOr<VertexHandle> StratifiedMesh::GetVertex(tp_sdg::shared::constants::IdType id){
  return vertex_pool_->GetVertex(id);
}
absl::Status StratifiedMesh::RemoveVertex(tp_sdg::shared::constants::IdType id){
  // Assumes any chambers or facets that use this vertex are getting removed.
  return vertex_pool_->RemoveVertexWithId(id);
}
size_t StratifiedMesh::GetNumberOfVertices() const {
  return vertex_pool_->NumVertices();
}

OMeshHandle StratifiedMesh::GetOrientedMesh(int dim) {
  ABSL_ASSERT(dim >= 1 && dim <= 4);
  return OMeshHandle(oriented_meshes_[dim].get());
}
const OMeshHandle StratifiedMesh::GetOrientedMesh(int dim) const {
  ABSL_ASSERT(dim >= 1 && dim <= 4);
  return OMeshHandle(oriented_meshes_[dim].get());
}

StratifiedMesh::StratifiedMesh(Input& strat_input, std::array<std::unique_ptr<OrientedMesh>, 5>& oriented_meshes): oriented_meshes_({nullptr, nullptr, nullptr, nullptr, nullptr}) {
  top_dimension_ = strat_input.top_dimension;
  vertex_pool_ = std::move(strat_input.vertex_pool);
  for(int i = 1; i <= 4; ++i){
    oriented_meshes_[i] = std::move(oriented_meshes[i]);
  }
}

}