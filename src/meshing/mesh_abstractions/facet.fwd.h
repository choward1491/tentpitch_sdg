/*
** Created by Christian Howard on 10/27/22.
*/
#ifndef TENTPITCH_SDG_SRC_MESHING_MESH_ABSTRACTIONS_FACET_FWD_H_
#define TENTPITCH_SDG_SRC_MESHING_MESH_ABSTRACTIONS_FACET_FWD_H_

#include "shared/utility/raw_ptr.h"

namespace tp_sdg::meshing::abstractions {
class Facet;
using FacetHandle = shared::util::RawPtr<Facet>;
const FacetHandle kNullFacetHandle = FacetHandle(nullptr);
}

#endif //TENTPITCH_SDG_SRC_MESHING_MESH_ABSTRACTIONS_FACET_FWD_H_
