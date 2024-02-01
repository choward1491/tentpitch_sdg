/*
** Created by Christian Howard on 10/9/22.
*/
#include "meshing/mesh_abstractions/facet.h"
#include "meshing/mesh_abstractions/chamber.h"

#include "gtest/gtest.h"

namespace tp_sdg::meshing::abstractions {
namespace {

 class FacetTest : public ::testing::Test {
  public:
   FacetTest() = default;
   ~FacetTest() override = default;
 };

 using FacetConstructionTests = FacetTest;
 TEST_F(FacetConstructionTests, FailSetNullTwin){
  EXPECT_DEATH(
      {
        Facet facet;
        facet.SetTwin(FacetHandle(nullptr));
      }, "Assertion failed");
 }

TEST_F(FacetConstructionTests, FailSetInvalidTwin){
  EXPECT_DEATH(
      {
        Facet facet;
        facet.SetDimension(2);
        Facet twin;
        twin.SetDimension(1);
        facet.SetTwin(FacetHandle(&twin));
      }, "Assertion failed");
}

TEST_F(FacetConstructionTests, PassSetValidTwin){
  EXPECT_EXIT(
      {
        Facet facet;
        facet.SetDimension(2);
        Facet twin;
        twin.SetDimension(2);
        facet.SetTwin(FacetHandle(&twin));
        exit(0);
      }, ::testing::ExitedWithCode(0), "");
}

TEST_F(FacetConstructionTests, FailSetNullCofacet){
  EXPECT_DEATH(
      {
        Facet facet;
        facet.SetCofacet(ChamberHandle(nullptr));
      }, "Assertion failed");
}
TEST_F(FacetConstructionTests, FailSetInvalidCofacet){
  EXPECT_DEATH(
      {
        Facet facet;
        facet.SetDimension(2);
        Chamber chamber;
        chamber.SetDimension(2);
        facet.SetCofacet(ChamberHandle(&chamber));
      }, "Assertion failed");
}

TEST_F(FacetConstructionTests, FailGetNullCofacet){
  EXPECT_DEATH(
      {
        Facet facet;
        facet.SetDimension(2);
        ChamberHandle cofacet = facet.GetCofacet();
      }, "Assertion failed");
}

TEST_F(FacetConstructionTests, PassSetValidCofacet){
  Facet facet;
  facet.SetDimension(2);
  Chamber chamber;
  chamber.SetDimension(3);
  facet.SetCofacet(ChamberHandle(&chamber));
  EXPECT_EQ(ChamberHandle(&chamber), facet.GetCofacet());
}

TEST_F(FacetConstructionTests, FailSetNullInterstitial){
  EXPECT_DEATH(
      {
        Facet facet;
        facet.SetInterstitial(ChamberHandle(nullptr));
      }, "Assertion failed");
}

TEST_F(FacetConstructionTests, FailSetInvalidInterstitial){
  EXPECT_DEATH(
      {
        Facet facet;
        facet.SetDimension(2);
        Chamber chamber;
        chamber.SetDimension(3);
        facet.SetInterstitial(ChamberHandle(&chamber));
      }, "Assertion failed");
}

TEST_F(FacetConstructionTests, FailGetNullInterstitial){
  EXPECT_DEATH(
      {
        Facet facet;
        facet.SetDimension(2);
        ChamberHandle chandle = facet.GetInterstitial();
      }, "Assertion failed");
}

TEST_F(FacetConstructionTests, PassSetInterstitial){
  Facet facet;
  facet.SetDimension(2);
  Chamber chamber;
  chamber.SetDimension(2);
  facet.SetInterstitial(ChamberHandle(&chamber));
  EXPECT_EQ(ChamberHandle(&chamber), facet.GetInterstitial());
}

}
}