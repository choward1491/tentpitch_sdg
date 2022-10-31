/*
** Created by Christian Howard on 10/9/22.
*/
#include "meshing/mesh_abstractions/vertex.h"

#include <array>
#include <limits>

#include "absl/strings/substitute.h"
#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "status_macros/test_status_macros.h"

#include "meshing/mesh_abstractions/vertex.h"

namespace tp_sdg::meshing::abstractions {
namespace {

class VertexTest : public ::testing::Test {
 public:
  VertexTest() = default;
  ~VertexTest() = default;
};

using VertexConstructionTests = VertexTest;
TEST_F(VertexConstructionTests, InvalidInitializedDimension) {
  EXPECT_DEATH(
      {
        Vertex vertex;
        int dim = vertex.GetSpatialDimension();
      }, "Assertion failed");
}
TEST_F(VertexConstructionTests, InvalidSetDimension) {
  EXPECT_DEATH(
      {
        Vertex vertex;
        vertex.SetSpatialDimension(0);
        int dim = vertex.GetSpatialDimension();
        exit(0);
      }, "Assertion failed");
}
TEST_F(VertexConstructionTests, InvalidLargeSetDimension) {
  EXPECT_DEATH(
      {
        Vertex vertex;
        vertex.SetSpatialDimension(5);
        int dim = vertex.GetSpatialDimension();
        exit(0);
      }, "Assertion failed");
}
TEST_F(VertexConstructionTests, SucceedSetDimension) {
  EXPECT_EXIT(
      {
        for (int i = 1; i < 3; ++i) {
          Vertex vertex;
          vertex.SetSpatialDimension(i);
        }
        exit(0);
      }, ::testing::ExitedWithCode(0), "");
}
TEST_F(VertexConstructionTests, FailSetCoordinateBadIndex) {
  EXPECT_DEATH(
      {
        Vertex v;
        v.SetSpatialDimension(1);
        v.SetCoordinate(2, 1.0);
        exit(0);
      }, "Assertion failed");
}
TEST_F(VertexConstructionTests, FailSetCoordinateNanValue) {
  EXPECT_DEATH(
      {
        Vertex v;
        v.SetSpatialDimension(1);
        v.SetCoordinate(0, std::numeric_limits<shared::constants::PrecisionType>::quiet_NaN());
        exit(0);
      }, "Assertion failed");
}
TEST_F(VertexConstructionTests, FailSetCoordinateInfValue) {
  EXPECT_DEATH(
      {
        Vertex v;
        v.SetSpatialDimension(1);
        v.SetCoordinate(0, std::numeric_limits<shared::constants::PrecisionType>::infinity());
        exit(0);
      }, "Assertion failed");
}
TEST_F(VertexConstructionTests, SucceedSetCoordinate) {
  EXPECT_EXIT(
      {
        Vertex v;
        v.SetSpatialDimension(1);
        v.SetCoordinate(0, 1.0);
        v.SetCoordinate(1, 1.0);
        exit(0);
      }, ::testing::ExitedWithCode(0), "");
}
TEST_F(VertexConstructionTests, FailSetCoordinatesNaNInputList) {
  EXPECT_DEATH(
      {
        Vertex v;
        v.SetCoordinates({1.0, 2.0, std::numeric_limits<shared::constants::PrecisionType>::quiet_NaN(), 1.0});
        exit(0);
      }, "Assertion failed");
}
TEST_F(VertexConstructionTests, FailSetCoordinatesInfInputList) {
  EXPECT_DEATH(
      {
        Vertex v;
        v.SetCoordinates({1.0, 2.0, std::numeric_limits<shared::constants::PrecisionType>::infinity(), 1.0});
        exit(0);
      }, "Assertion failed");
}
TEST_F(VertexConstructionTests, SucceedSetCoordinatesInputList) {
  EXPECT_EXIT(
      {
        Vertex v;
        v.SetCoordinates({1.0, 2.0, 3.0, 1.0});
        exit(0);
      }, ::testing::ExitedWithCode(0), "");
}
TEST_F(VertexConstructionTests, FailSetCoordinatesNaNInputArray) {
  using numeric_array_t = std::array<shared::constants::PrecisionType, 4>;
  EXPECT_DEATH(
      {
        Vertex v;
        numeric_array_t coordinates;
        coordinates[0] = 1.0;
        coordinates[1] = 2.0;
        coordinates[2] = std::numeric_limits<shared::constants::PrecisionType>::quiet_NaN();
        coordinates[3] = 1.0;
        v.SetCoordinates<3>(coordinates);
        exit(0);
      }, "Assertion failed");
}
TEST_F(VertexConstructionTests, FailSetCoordinatesInfInputArray) {
  using numeric_array_t = std::array<shared::constants::PrecisionType, 4>;
  EXPECT_DEATH(
      {
        Vertex v;
        numeric_array_t coordinates;
        coordinates[0] = 1.0;
        coordinates[1] = 2.0;
        coordinates[2] = std::numeric_limits<shared::constants::PrecisionType>::infinity();
        coordinates[3] = 1.0;
        v.SetCoordinates<3>(coordinates);
        exit(0);
      }, "Assertion failed");
}
TEST_F(VertexConstructionTests, SucceedSetCoordinatesInputArray) {
  using numeric_array_t = std::array<shared::constants::PrecisionType, 4>;
  EXPECT_EXIT(
      {
        Vertex v;
        numeric_array_t coordinates;
        coordinates[0] = 1.0;
        coordinates[1] = 2.0;
        coordinates[2] = 3.0;
        coordinates[3] = 1.0;
        v.SetCoordinates<3>(coordinates);
        exit(0);
      }, ::testing::ExitedWithCode(0), "");
}

} // namespace
} // namespace