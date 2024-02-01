/*
** Created by Christian Howard on 10/12/22.
*/
#include "facet.h"

#include "absl/status/status.h"
#include "meshing/mesh_abstractions/chamber.h"

namespace tp_sdg {
namespace meshing {
namespace abstractions {

void Facet::SetTwin(tp_sdg::meshing::abstractions::FacetHandle twin) {
  ABSL_ASSERT(twin.IsNotNull());
  ABSL_ASSERT(twin->GetDimension() == GetDimension());
  twin_ = twin;
}

FacetHandle Facet::GetTwin() const {
  ABSL_ASSERT(cofacet_.IsNotNull());
  return twin_;
}

void Facet::SetCofacet(tp_sdg::meshing::abstractions::ChamberHandle cofacet) {
  ABSL_ASSERT(cofacet.IsNotNull());
  ABSL_ASSERT(cofacet->GetDimension() == GetDimension()+1);
  cofacet_ = cofacet;
}

ChamberHandle Facet::GetCofacet() const {
  ABSL_ASSERT(cofacet_.IsNotNull());
  return cofacet_;
}

void Facet::SetInterstitial(tp_sdg::meshing::abstractions::ChamberHandle interstitial) {
  ABSL_ASSERT(interstitial.IsNotNull());
  ABSL_ASSERT(interstitial->GetDimension() == GetDimension());
  interstitial_ = interstitial;
}

ChamberHandle Facet::GetInterstitial() const {
  ABSL_ASSERT(interstitial_.IsNotNull());
  return interstitial_;
}

}
}
}