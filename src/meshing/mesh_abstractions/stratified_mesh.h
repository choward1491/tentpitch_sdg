/*
** Created by Christian Howard on 10/12/22.
*/
#ifndef TENTPITCH_SDG_SRC_MESHING_MESH_ABSTRACTIONS_STRATIFIED_MESH_H_
#define TENTPITCH_SDG_SRC_MESHING_MESH_ABSTRACTIONS_STRATIFIED_MESH_H_

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

#include "shared/constants.h"
#include "shared/utility/raw_ptr.h"

namespace tp_sdg::meshing::abstractions {

class StratifiedMesh {
 public:
  struct Input {
    int top_dimension;
    shared::util::RawPtr<ChamberPoolGenerator> chamber_pool_generator;
    shared::util::RawPtr<FacetPoolGenerator> facet_pool_generator;
    std::unique_ptr<VertexPoolInterface> vertex_pool;
  };
  [[nodiscard]] static absl::StatusOr<std::unique_ptr<StratifiedMesh>> Create(Input& input);
  StratifiedMesh() = delete;
  StratifiedMesh(StratifiedMesh&) = delete;
  StratifiedMesh& operator=(const StratifiedMesh&) = delete;
  ~StratifiedMesh() = default;

  [[nodiscard]] int GetTopDimension() const;

  [[nodiscard]] VertexHandle AddVertex() const;
  [[nodiscard]] absl::StatusOr<VertexHandle> GetVertex(tp_sdg::shared::constants::IdType id);
  [[nodiscard]] absl::Status RemoveVertex(tp_sdg::shared::constants::IdType id);
  [[nodiscard]] size_t GetNumberOfVertices() const;

  [[nodiscard]] OMeshHandle GetOrientedMesh(int dim);
  [[nodiscard]] const OMeshHandle GetOrientedMesh(int dim) const;

 protected:
  static absl::Status VerifyInputAndBuildMeshes(Input &input,
                                         std::array<std::unique_ptr<OrientedMesh>, 5>& oriented_meshes);
  explicit StratifiedMesh(Input&, std::array<std::unique_ptr<OrientedMesh>, 5>&);

 private:
  int top_dimension_;
  std::unique_ptr<VertexPoolInterface> vertex_pool_;
  std::array<std::unique_ptr<OrientedMesh>, 5> oriented_meshes_;

};

}

#endif //TENTPITCH_SDG_SRC_MESHING_MESH_ABSTRACTIONS_STRATIFIED_MESH_H_
