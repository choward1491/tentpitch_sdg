/*
** Created by Christian Howard on 10/12/22.
*/
#include "chamber.h"

#include "meshing/mesh_abstractions/facet.h"
#include "absl/status/status.h"
#include "shared/utility/status_macro.h"

namespace tp_sdg {
namespace meshing {
namespace abstractions {

void Chamber::SetFacet(int idx, tp_sdg::meshing::abstractions::FacetHandle facet) {
  ABSL_ASSERT(idx >= 0 && idx <= this->GetDimension());
  ABSL_ASSERT(facet.IsNotNull());
  ABSL_ASSERT(facet->GetDimension() == (GetDimension()-1) );
  facets_[idx] = facet;
}

FacetHandle Chamber::GetFacet(int idx) const {
  ABSL_ASSERT(idx >= 0 && idx <= this->GetDimension());
  return facets_[idx];
}

void Chamber::SetCointerstitial(tp_sdg::meshing::abstractions::FacetHandle cointerstitial) {
  ABSL_ASSERT(cointerstitial.IsNotNull());
  ABSL_ASSERT(cointerstitial->GetDimension() == this->GetDimension());
  cointerstitial_ = cointerstitial;
}

FacetHandle Chamber::GetCointerstitial() const {
  return cointerstitial_;
}

}
}
}