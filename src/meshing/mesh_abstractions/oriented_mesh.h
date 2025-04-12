/*
** Created by Christian Howard on 10/27/22.
*/
#ifndef TENTPITCH_SDG_SRC_MESHING_MESH_ABSTRACTIONS_ORIENTED_MESH_H_
#define TENTPITCH_SDG_SRC_MESHING_MESH_ABSTRACTIONS_ORIENTED_MESH_H_

#include <memory>

#include "absl/status/status.h"
#include "absl/status/statusor.h"
#include "absl/memory/memory.h"

#include "meshing/mesh_abstractions/chamber.fwd.h"
#include "meshing/mesh_abstractions/chamber_pool_interface.h"
#include "meshing/mesh_abstractions/constants.h"
#include "meshing/mesh_abstractions/facet.fwd.h"
#include "meshing/mesh_abstractions/facet_pool_interface.h"
#include "meshing/utility/mesh_entity_id_pack.h"
#include "shared/constants.h"

namespace tp_sdg::meshing::abstractions {

class OrientedMesh {
 public:
  struct Input {
    int dimension;
    int vertex_dimension;
    std::unique_ptr<FacetPoolInterface> facet_pool;
    std::unique_ptr<ChamberPoolInterface> chamber_pool;
  };
  [[nodiscard]] static absl::StatusOr<std::unique_ptr<OrientedMesh>> Create(Input& input);

  // ctors/dtors
  OrientedMesh() = delete;
  OrientedMesh(const OrientedMesh &omesh) = delete;
  OrientedMesh(OrientedMesh &omesh) = delete;
  ~OrientedMesh() = default;

  // remove operator= capacity
  OrientedMesh &operator=(const OrientedMesh &omesh) = delete;

  // the dimension is the subspace of smallest dimension that a non-degenerate chamber from this mesh lives in.
  // e.g. a non-degenerate tetrahedron exists in a dimension 3 subspace
  // e.g. a non-degenerate triangle exists in a dimension 2 subspace
  void SetDimension(int d);
  int GetDimension() const;

  // the vertex dimension is the dimension that the coordinates of vertices are in
  // e.g. a triangle lives in a dimension 2 subspace, but the coordinates of the triangle could be in R^3,
  //      making the vertex dimension 3 and the dimension of the mesh 2 (aka the mesh is a 2-manifold embedded in R^3)
  void SetVertexDimension(int vd);
  int GetVertexDimension() const;

  // Adds a new chamber, without building up any of its facets. It just assigns some key properties, such as its unique
  // ID, the dimension of the chamber, its vertex dimension. All connectivity info is null
  [[nodiscard]] ChamberHandle AddChamber();

  // Deletes a chamber with ID `id` if it exists, but without deleting any of its corresponding facets or other
  // connectivity information. This needs to be used mindfully.
  // If chamber does not exist, returns error. *An error should not occur*
  [[nodiscard]] absl::Status DeleteChamberWithId(::tp_sdg::shared::constants::IdType id);

  // Adds a new chamber, constructed with new facets, all based on the passed in vertices.
  [[nodiscard]] absl::StatusOr<ChamberHandle> AddChamberWithFacetsBasedOnVertices(std::initializer_list<VertexHandle> vertices);
  [[nodiscard]] absl::StatusOr<ChamberHandle> AddChamberWithFacetsBasedOnVertices(VertexHandle *vertices, int num_vertices);

  // Deletes a chamber, along with all its corresponding facets, given they all exist and live within this mesh.
  // If a chamber or its facets do not exist, returns error. *An error should not occur*
  [[nodiscard]] absl::Status DeleteChamberWithIdAlongWithFacets(::tp_sdg::shared::constants::IdType id);

  // Grabs a chamber based on its unique ID
  [[nodiscard]] absl::StatusOr<ChamberHandle> GetChamber(::tp_sdg::shared::constants::IdType id) const;

  std::size_t NumChambers() const;

  // Adds a facet without any added connectivity information to vertices or cofacets.
  [[nodiscard]] FacetHandle AddFacet();

  // Grabs a facet baed on its unique ID.
  [[nodiscard]] absl::StatusOr<FacetHandle> GetFacet(::tp_sdg::shared::constants::IdType id) const;

  // Deletes a facet based on its unique ID. If it cannot be found, then an error returns. *This should not happen*
  [[nodiscard]] absl::Status DeleteFacetWithId(::tp_sdg::shared::constants::IdType id);

  std::size_t NumFacets() const;

 private:
  OrientedMesh(Input& input);
  [[nodiscard]] absl::StatusOr<ChamberHandle> BuildChamberWithFacetsUsingTemporaryStructures();
  static void FindAndSetupTwin(FacetHandle fh);

  int dimension_;
  int vertex_dimension_;
  std::unique_ptr<FacetPoolInterface> facet_pool_;
  std::unique_ptr<ChamberPoolInterface> chamber_pool_;
  std::vector<VertexHandle> tmp_chamber_vertices_;
  std::array<std::vector<VertexHandle>, 5> tmp_all_facet_vertices_;

};

}

#endif //TENTPITCH_SDG_SRC_MESHING_MESH_ABSTRACTIONS_ORIENTED_MESH_H_
