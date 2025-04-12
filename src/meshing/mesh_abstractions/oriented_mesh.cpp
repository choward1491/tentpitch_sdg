/*
** Created by Christian Howard on 10/27/22.
*/
#include "oriented_mesh.h"

#include <memory>

#include "absl/container/btree_set.h"

#include "chamber.h"
#include "chamber_pool_interface.h"
#include "facet.h"
#include "facet_pool_interface.h"
#include "meshing/utility/topology_util.h"
#include "shared/constants.h"
#include "status_macros/status_macros.h"
#include "vertex.h"

namespace sdg = tp_sdg::meshing::abstractions;

absl::StatusOr<std::unique_ptr<sdg::OrientedMesh>> tp_sdg::meshing::abstractions::OrientedMesh::Create(tp_sdg::meshing::abstractions::OrientedMesh::Input& input) {
  if(input.dimension < 1 || input.dimension > 4)
    return absl::InvalidArgumentError("Dimension of mesh must be between 1 and 4.");
  if(input.dimension < input.vertex_dimension )
    return absl::InvalidArgumentError("Vertex dimension cannot be more than dimension of mesh.");
  if(input.vertex_dimension < 1)
    return absl::InvalidArgumentError("Vertex dimension must be at least 1");
  return absl::WrapUnique(new OrientedMesh(input));
}
void tp_sdg::meshing::abstractions::OrientedMesh::SetDimension(int d) {
  ABSL_ASSERT(d >= 0 && d <= 4);
  dimension_ = d;
}
int tp_sdg::meshing::abstractions::OrientedMesh::GetDimension() const {
  return dimension_;
}
void tp_sdg::meshing::abstractions::OrientedMesh::SetVertexDimension(int vd) {
  ABSL_ASSERT(vd >= 0 && vd <= 4);
  vertex_dimension_ = vd;
}
int tp_sdg::meshing::abstractions::OrientedMesh::GetVertexDimension() const {
  return vertex_dimension_;
}
tp_sdg::meshing::abstractions::ChamberHandle tp_sdg::meshing::abstractions::OrientedMesh::AddChamber() {
  return chamber_pool_->GetNewChamber();
}
absl::Status tp_sdg::meshing::abstractions::OrientedMesh::DeleteChamberWithId(::tp_sdg::shared::constants::IdType id) {
  ASSIGN_OR_RETURN(ChamberHandle c, chamber_pool_->GetChamber(id));
  // Remove connectivity to facets.
  for(int i = 0; i <= c->GetDimension(); ++i){
    FacetHandle fi = c->GetFacet(i);
    c->SetFacet(i, kNullFacetHandle);
    if( fi.IsNotNull() ){
      fi->SetCofacet(kNullChamberHandle);
    }
  }

  // Remove connections to cointerstitials.
  FacetHandle coint = c->GetCointerstitial();
  if( coint.IsNotNull() ){
    c->SetCointerstitial(kNullFacetHandle);
    coint->SetInterstitial(kNullChamberHandle);
  }

  // Remove connections to vertices.
  for(int i = 0; i <= c->GetDimension(); ++i){
    VertexHandle vh = c->GetVertex(i);
    vh->RemoveIncidentChamber(c);
    c->SetVertex(i, kNullVertexHandle);
  }
  // Clear underlying oriented cell data.
  c->Reset();
  return chamber_pool_->RemoveChamberWithId(id);
}
absl::StatusOr<tp_sdg::meshing::abstractions::ChamberHandle> tp_sdg::meshing::abstractions::OrientedMesh::AddChamberWithFacetsBasedOnVertices(
    std::initializer_list<VertexHandle> vertices) {
  const int d = vertices.size();
  ABSL_ASSERT(d == dimension_ + 1);

  // Get the chamber vertices.
  tmp_chamber_vertices_.resize(d);
  int idx = 0;
  for(auto vh: vertices){
    if( vh.IsNull() ){
      return absl::InvalidArgumentError("At least one vertex being passed to build a chamber with its facets is null.");
    }
    tmp_chamber_vertices_[idx++] = vh;
  }

  return BuildChamberWithFacetsUsingTemporaryStructures();
}
absl::StatusOr<tp_sdg::meshing::abstractions::ChamberHandle> tp_sdg::meshing::abstractions::OrientedMesh::AddChamberWithFacetsBasedOnVertices(
    tp_sdg::meshing::abstractions::VertexHandle *vertices,
    int num_vertices) {
  const int d = num_vertices;
  ABSL_ASSERT(d == dimension_ + 1);

  // Get the chamber vertices.
  tmp_chamber_vertices_.resize(d);
  for(int i = 0; i < d; ++i){
    if( vertices[i].IsNull() ){
      return absl::InvalidArgumentError("At least one vertex being passed to build a chamber with its facets is null.");
    }
    tmp_chamber_vertices_[i] = vertices[i];
  }

  return BuildChamberWithFacetsUsingTemporaryStructures();
}
absl::Status tp_sdg::meshing::abstractions::OrientedMesh::DeleteChamberWithIdAlongWithFacets(::tp_sdg::shared::constants::IdType id) {
  ASSIGN_OR_RETURN(sdg::ChamberHandle ch, chamber_pool_->GetChamber(id));
  for(int i = 0; i < ch->GetNumFacets(); ++i){
    sdg::FacetHandle fh = ch->GetFacet(i);
    ch->SetFacet(i, kNullFacetHandle);
    RETURN_IF_ERROR(DeleteFacetWithId(fh->GetId()));
  }
  RETURN_IF_ERROR(DeleteChamberWithId(id));
  return absl::OkStatus();
}
absl::StatusOr<sdg::ChamberHandle> tp_sdg::meshing::abstractions::OrientedMesh::GetChamber(::tp_sdg::shared::constants::IdType id) const {
  return chamber_pool_->GetChamber(id);
}
std::size_t tp_sdg::meshing::abstractions::OrientedMesh::NumChambers() const {
  return chamber_pool_->NumChambers();
}
tp_sdg::meshing::abstractions::FacetHandle tp_sdg::meshing::abstractions::OrientedMesh::AddFacet() {
  return facet_pool_->GetNewFacet();
}
absl::StatusOr<sdg::FacetHandle> tp_sdg::meshing::abstractions::OrientedMesh::GetFacet(::tp_sdg::shared::constants::IdType id) const {
  return facet_pool_->GetFacet(id);
}
absl::Status tp_sdg::meshing::abstractions::OrientedMesh::DeleteFacetWithId(::tp_sdg::shared::constants::IdType id) {
  ASSIGN_OR_RETURN(FacetHandle f, facet_pool_->GetFacet(id));
  // Remove connectivity with twin.
  FacetHandle twin = f->GetTwin();
  if( twin.IsNotNull() ){
    f->SetTwin(kNullFacetHandle);
    twin->SetTwin(kNullFacetHandle);
  }

  // Remove connectivity with interstitial.
  ChamberHandle interstitial = f->GetInterstitial();
  if( interstitial.IsNotNull()){
    f->SetInterstitial(kNullChamberHandle);
    interstitial->SetCointerstitial(kNullChamberHandle);
  }

  // Remove connectivity to cofacet.
  f->SetCofacet(kNullChamberHandle);

  // Clear underlying oriented cell data
  f->Reset();
  return facet_pool_->RemoveFacetWithId(id);
}
std::size_t tp_sdg::meshing::abstractions::OrientedMesh::NumFacets() const {
  return facet_pool_->NumFacets();
}
tp_sdg::meshing::abstractions::OrientedMesh::OrientedMesh(tp_sdg::meshing::abstractions::OrientedMesh::Input& input) {
  SetDimension(input.dimension);
  SetVertexDimension(input.vertex_dimension);
  std::swap(chamber_pool_, input.chamber_pool);
  std::swap(facet_pool_, input.facet_pool);
  chamber_pool_->SetDimensionForChambers(GetDimension());
  facet_pool_->SetDimensionForFacets(GetDimension()-1);
  tmp_chamber_vertices_.reserve(5);
  for(int i = 0; i < 5; ++i){
    tmp_all_facet_vertices_[i].reserve(5);
  }
}

absl::StatusOr<sdg::ChamberHandle> tp_sdg::meshing::abstractions::OrientedMesh::BuildChamberWithFacetsUsingTemporaryStructures() {
  // Build facet vertex lists.
  tp_sdg::util::topology::GetAllFacetVerticesFromChamberVertices(tmp_chamber_vertices_, tmp_all_facet_vertices_);

  // Build the chamber.
  ChamberHandle c = chamber_pool_->GetNewChamber();
  for(int i = 0; i <= dimension_; ++i){
    c->SetVertex(i, tmp_chamber_vertices_[i]);
    tmp_chamber_vertices_[i]->AddIncidentChamber(c);
  }

  // Build all the facets.
  std::array<FacetHandle, 5> facets;
  for(int i = 0; i <= dimension_; ++i){

    // Construct facet with an ID and its dimension set.
    FacetHandle fi = facet_pool_->GetNewFacet();

    // Set vertices for facet.
    for(int j = 0; j < dimension_; ++j){
      fi->SetVertex(j, tmp_all_facet_vertices_[i][j]);
    }

    // Setup connectivity for facet fi.
    fi->SetCofacet(c);
    FindAndSetupTwin(fi);
    c->SetFacet(i, fi);
  }

  return c;
}

void tp_sdg::meshing::abstractions::OrientedMesh::FindAndSetupTwin(FacetHandle fh) {
  if( fh->GetTwin().IsNotNull() ) return;
  const int d = fh->GetDimension()+1;

  // Get the vertices of fh.
  absl::btree_set<VertexHandle> fh_vert_set;
  std::array<VertexHandle, 5> vertices;
  std::array<const std::set<ChamberHandle>*, 5> vertex_incidence_lists{};
  for(int i = 0; i < d; ++i){
    vertices[i] = fh->GetVertex(i);
    fh_vert_set.insert(vertices[i]);
    vertex_incidence_lists[i] = &vertices[i]->GetIncidenceList(d);
  }

  // Try to see if any other facet exists with the same vertices.
  ChamberHandle cofacet = fh->GetCofacet();
  for(ChamberHandle ch: *vertex_incidence_lists[0]) {
    // Skip cofacet.
    if( ch->GetId() == cofacet->GetId()) continue;

    // Check to see if this chamber is in all the other lists.
    // If so, we have a chamber that potentially has the twin facet.
    bool in_all = true;
    for(int i = 1; i < d; ++i){
      if( vertex_incidence_lists[i]->count(ch) == 0 ) in_all = false; break;
    }

    // Look through the facets of ch to see if any are a twin to fh.
    if( in_all ){
      for(int i = 0; i <= d; ++i){
        FacetHandle fi = ch->GetFacet(i);

        // Check if all vertices of fi are in the vertex set for fh.
        bool all_verts_in_set = true;
        for(int j = 0; j < d; ++j){
          VertexHandle vj = fi->GetVertex(j);
          if( not fh_vert_set.contains(vj) ) all_verts_in_set = false; break;
        }

        // If all vertices are the same as fi, they must be twins.
        fi->SetTwin(fh);
        fh->SetTwin(fi);

        // Complete, so return.
        return;
      }
    }
  }
}