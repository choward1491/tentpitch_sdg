/*
** Created by Christian Howard on 10/9/22.
*/

#include "meshing/mesh_abstractions/chamber.h"
#include "meshing/mesh_abstractions/facet.h"
#include "shared/utility/raw_ptr.h"

#include "gtest/gtest.h"
#include "gmock/gmock.h"


namespace tp_sdg::meshing::abstractions {
namespace {
using ::testing::ContainerEq;

class ChamberTest : public ::testing::Test {
 public:
  ChamberTest() = default;
  ~ChamberTest() override = default;
};

using ChamberConstructionTests = ChamberTest;
TEST_F(ChamberConstructionTests, FailNegativeIndex){
  EXPECT_DEATH(
      {
        Chamber chamber;
        chamber.SetDimension(3);
        Facet f;

        chamber.SetFacet(-1, FacetHandle(&f));
      }, "Assertion failed");
}

TEST_F(ChamberConstructionTests, FailTooLargeIndex){
  EXPECT_DEATH(
      {
        Chamber chamber;
        chamber.SetDimension(3);
        Facet f;

        chamber.SetFacet(4, FacetHandle(&f));
      }, "Assertion failed");
}

TEST_F(ChamberConstructionTests, FailFacetWrongRelativeDimension){
  EXPECT_DEATH(
      {
        Chamber chamber;
        chamber.SetDimension(3);
        Facet f;
        f.SetDimension(1);

        chamber.SetFacet(0, FacetHandle(&f));
      }, "Assertion failed");
}

TEST_F(ChamberConstructionTests, FailNullPtr){
  EXPECT_DEATH(
      {
        Chamber chamber;
        chamber.SetDimension(3);

        chamber.SetFacet(0, FacetHandle(nullptr));
      }, "Assertion failed");
}

TEST_F(ChamberConstructionTests, PassSetValidFacet){
  EXPECT_EXIT(
      {
        Chamber chamber;
        chamber.SetDimension(3);
        Facet f;
        f.SetDimension(2);
        chamber.SetFacet(0, FacetHandle(&f));
        exit(0);
      },  ::testing::ExitedWithCode(0), "");
}

TEST_F(ChamberConstructionTests, FailSetNullCointerstitial){
  EXPECT_DEATH(
      {
        Chamber chamber;
        chamber.SetDimension(3);

        Facet facet;
        facet.SetDimension(2);

        chamber.SetCointerstitial(FacetHandle(&facet));
      }, "Assertion failed");
}

TEST_F(ChamberConstructionTests, PassSetValidCointerstitial){
  EXPECT_EXIT(
      {
        Chamber chamber;
        chamber.SetDimension(3);

        Facet facet;
        facet.SetDimension(3);

        chamber.SetCointerstitial(FacetHandle(&facet));
        exit(0);
      }, ::testing::ExitedWithCode(0), "");
}

using ChamberGetterTests = ChamberTest;
TEST_F(ChamberGetterTests, FailNegativeIndex){
  EXPECT_DEATH(
      {
        Chamber chamber;
        chamber.SetDimension(3);
        FacetHandle fhandle = chamber.GetFacet(-1);
      }, "Assertion failed");
}

TEST_F(ChamberGetterTests, FailTooLargeIndex){
  EXPECT_DEATH(
      {
        Chamber chamber;
        chamber.SetDimension(3);
        FacetHandle fhandle = chamber.GetFacet(4);
      }, "Assertion failed");
}

TEST_F(ChamberGetterTests, SuccessReadAllFacets){
  Chamber chamber;
  chamber.SetDimension(3);

  std::array<Facet, 4> facets;
  std::array<FacetHandle, 4> facet_ptrs;
  std::array<FacetHandle, 4> chambers_facets_ptrs;
  for(int i = 0; i < 4; ++i){
    facets[i].SetDimension(2);
    facet_ptrs[i] = &facets[i];
    chamber.SetFacet(i, facet_ptrs[i]);
    chambers_facets_ptrs[i] = chamber.GetFacet(i);
  }
  EXPECT_THAT(facet_ptrs, ContainerEq(chambers_facets_ptrs));
}

}
}