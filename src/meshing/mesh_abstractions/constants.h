/*
** Created by Christian Howard on 10/27/22.
*/
#ifndef TENTPITCH_SDG_SRC_MESHING_MESH_ABSTRACTIONS_CONSTANTS_H_
#define TENTPITCH_SDG_SRC_MESHING_MESH_ABSTRACTIONS_CONSTANTS_H_

namespace tp_sdg::meshing::abstractions {
constexpr int kMaxChamberDim = 4;
constexpr int kMaxChamberVertices = kMaxChamberDim + 1;
constexpr int kMaxFacetDim = kMaxChamberDim - 1;
constexpr int kMaxFacetVertices = kMaxFacetDim + 1;
constexpr int kMaxVertexSpatialDimensions = 4;
}

#endif //TENTPITCH_SDG_SRC_MESHING_MESH_ABSTRACTIONS_CONSTANTS_H_
