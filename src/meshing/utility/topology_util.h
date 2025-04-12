/*
** Created by Christian Howard on 4/12/25.
*/
#ifndef TENTPITCH_SDG_SRC_MESHING_UTILITY_TOPOLOGY_UTIL_H_
#define TENTPITCH_SDG_SRC_MESHING_UTILITY_TOPOLOGY_UTIL_H_

#include <array>
#include <vector>

#include "absl/status/status.h"

#include "vertex.fwd.h"

namespace tp_sdg::util::topology {
using tp_sdg::meshing::abstractions::VertexHandle;

template<int d>
std::array< std::array<VertexHandle, d-1>, d> GetAllFacetVerticesFromChamberVertices(const std::array<VertexHandle, d>& chamber_verts) {
  std::array< std::array<VertexHandle, d-1>, d> facet_list;

  // Build the ith facet.
  for(int i = 0; i < d; ++i){
    int idx = 0;

    // The ith facet will not have the ith vertex, but will have all the others.
    for(int j = 0; j < d; ++j){
      if( j == i ) continue;
      facet_list[i][idx++] = chamber_verts[j];
    }

    // If i is odd, flip any two vertices (this keeps the sign of things correct from an algebraic topology view).
    if(i % 2 == 1) std::swap(facet_list[i][0], facet_list[i][1]);
  }
  return facet_list;
}

void GetAllFacetVerticesFromChamberVertices(const std::vector<VertexHandle>& chamber_verts, std::array< std::vector<VertexHandle>, 5>& facet_vertices) {
  ABSL_ASSERT(chamber_verts.size() >= 1 && chamber_verts.size() <= 5);
  const int d = chamber_verts.size();
  for(int i = 0; i < d; ++i){
    std::vector<VertexHandle>& fi = facet_vertices[i];
    fi.resize(d-1);
    int idx = 0;

    // The ith facet will not have the ith vertex, but will have all the others.
    for(int j = 0; j < d; ++j){
      if( j == i ) continue;
      fi[idx++] = chamber_verts[j];
    }

    // If i is odd, flip any two vertices (this keeps the sign of things correct from an algebraic topology view).
    if(i % 2 == 1) std::swap(fi[0], fi[1]);
  }
}


}

#endif //TENTPITCH_SDG_SRC_MESHING_UTILITY_TOPOLOGY_UTIL_H_
