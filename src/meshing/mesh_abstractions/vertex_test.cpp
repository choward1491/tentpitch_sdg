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

#include "meshing/mesh_abstractions/chamber.h"
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
TEST_F(VertexConstructionTests, FailSetTimeNanValue) {
  EXPECT_DEATH(
      {
        Vertex v;
        v.SetSpatialDimension(1);
        v.SetTime(std::numeric_limits<shared::constants::PrecisionType>::quiet_NaN());
        exit(0);
      }, "Assertion failed");
}
TEST_F(VertexConstructionTests, FailSetTimeInfValue) {
  EXPECT_DEATH(
      {
        Vertex v;
        v.SetSpatialDimension(1);
        v.SetTime(std::numeric_limits<shared::constants::PrecisionType>::infinity());
        exit(0);
      }, "Assertion failed");
}
TEST_F(VertexConstructionTests, SucceedSetTime) {
  EXPECT_EXIT(
      {
        Vertex v;
        v.SetSpatialDimension(1);
        v.SetTime(1.0);
        exit(0);
      }, ::testing::ExitedWithCode(0), "");
}
TEST_F(VertexConstructionTests, SucceedGetTime) {
  constexpr shared::constants::PrecisionType time_value = 1.234;
  Vertex v;
  v.SetSpatialDimension(1);
  EXPECT_EQ(v.GetSpatialDimension(), 1);
  v.SetTime(time_value);
  EXPECT_EQ(time_value, v.GetTime());
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
TEST_F(VertexConstructionTests, SucceedGetCoordinates) {
  std::array<shared::constants::PrecisionType, 4> expected_coordinates{1.23, -1.23, 3.14, 17.0};
  Vertex v;
  v.SetSpatialDimension(3);
  v.SetCoordinates<3>(expected_coordinates);
  EXPECT_EQ(v.GetSpatialDimension(), 3);
  for (int i = 0; i <= 3; ++i) {
    EXPECT_EQ(expected_coordinates[i], v.GetCoordinate(i)) << absl::Substitute("Coordinate mismatch at position $0", i);
  }
}

using VertexAddIncidentListsTests = VertexTest;
TEST_F(VertexAddIncidentListsTests, FailAddChamberInvalidSpatialDim) {
  EXPECT_DEATH(
      {
        Vertex v;
        ChamberHandle ch;
        v.AddIncidentChamber(ch);
        exit(0);
      }, "Assertion failed");
}
TEST_F(VertexAddIncidentListsTests, FailAddChamberNullHandle) {
  EXPECT_DEATH(
      {
        Vertex v;
        v.SetSpatialDimension(3);
        ChamberHandle ch;
        v.AddIncidentChamber(ch);
        exit(0);
      }, "Assertion failed");
}

using VertexRemoveIncidentListsTests = VertexTest;
TEST_F(VertexRemoveIncidentListsTests, FailRemoveChamberInvalidSpatialDim) {
  EXPECT_DEATH(
      {
        Vertex v;
        ChamberHandle ch;
        v.RemoveIncidentChamber(ch);
        exit(0);
      }, "Assertion failed");
}
TEST_F(VertexRemoveIncidentListsTests, FailRemoveChamberNullHandle) {
  EXPECT_DEATH(
      {
        Vertex v;
        v.SetSpatialDimension(3);
        ChamberHandle ch;
        v.RemoveIncidentChamber(ch);
        exit(0);
      }, "Assertion failed");
}

using VertexIncidentListsAccessTests = VertexTest;
TEST_F(VertexIncidentListsAccessTests, BadChamberSetAccess) {
  EXPECT_DEATH(
      {
        Vertex v;
        v.SetSpatialDimension(3);
        const std::set<ChamberHandle>& set = v.GetIncidenceList(5);
        exit(0);
      }, "Assertion failed");
}
TEST_F(VertexIncidentListsAccessTests, GoodChamberSetAccessAndAddedChamber) {
  Vertex v;
  v.SetSpatialDimension(3);
  Chamber c;
  ChamberHandle ch(&c);
  ch->SetDimension(4);
  v.AddIncidentChamber(ch);
  std::set<ChamberHandle> expect_set{ch};
  ASSERT_EXIT(
      {
        const std::set<ChamberHandle>& set = v.GetIncidenceList(4);
        exit(0);
      }, ::testing::ExitedWithCode(0), "");

  const std::set<ChamberHandle>& inc_set = v.GetIncidenceList(4);
  EXPECT_EQ(inc_set, expect_set);
}
TEST_F(VertexIncidentListsAccessTests, GoodChamberSetAccessAndRemovedChamber) {
  Vertex v;
  v.SetSpatialDimension(3);
  Chamber c1, c2;
  ChamberHandle ch1(&c1), ch2(&c2);
  ch1->SetDimension(4);
  ch2->SetDimension(4);
  v.AddIncidentChamber(ch1);
  v.AddIncidentChamber(ch2);

  // check sets after adding two chambers
  ASSERT_EXIT(
      {
        const std::set<ChamberHandle>& set = v.GetIncidenceList(4);
        exit(0);
      }, ::testing::ExitedWithCode(0), "");

  {
    std::set<ChamberHandle> expect_set{ch1, ch2};
    const std::set<ChamberHandle>& inc_set = v.GetIncidenceList(4);
    EXPECT_EQ(inc_set, expect_set);
  }

  // check after deleting chamber 1
  v.RemoveIncidentChamber(ch1);
  ASSERT_EXIT(
      {
        const std::set<ChamberHandle>& set = v.GetIncidenceList(4);
        exit(0);
      }, ::testing::ExitedWithCode(0), "");

  {
    std::set<ChamberHandle> expect_set{ch2};
    const std::set<ChamberHandle>& inc_set = v.GetIncidenceList(4);
    EXPECT_EQ(inc_set, expect_set);
  }

  // check after deleting chamber 2
  v.RemoveIncidentChamber(ch2);
  ASSERT_EXIT(
      {
        const std::set<ChamberHandle>& set = v.GetIncidenceList(4);
        exit(0);
      }, ::testing::ExitedWithCode(0), "");

  {
    std::set<ChamberHandle> expect_set;
    const std::set<ChamberHandle>& inc_set = v.GetIncidenceList(4);
    EXPECT_EQ(inc_set, expect_set);
  }

  // check after adding back chamber 1
  v.AddIncidentChamber(ch1);
  ASSERT_EXIT(
      {
        const std::set<ChamberHandle>& set = v.GetIncidenceList(4);
        exit(0);
      }, ::testing::ExitedWithCode(0), "");

  {
    std::set<ChamberHandle> expect_set{ch1};
    const std::set<ChamberHandle>& inc_set = v.GetIncidenceList(4);
    EXPECT_EQ(inc_set, expect_set);
  }
}

using VertexResetTests = VertexTest;
TEST_F(VertexResetTests, SuccessfulVertexReset) {

  // setup the vertex
  Vertex v;
  v.front_id() = 0;
  v.footprint_id() = 17;
  v.patch_id() = 7;
  v.SetSpatialDimension(3);
  Chamber c1, c2;
  ChamberHandle ch1(&c1), ch2(&c2);
  ch1->SetDimension(4);
  ch2->SetDimension(4);
  v.AddIncidentChamber(ch1);
  v.AddIncidentChamber(ch2);

  // perform reset
  v.reset();

  // check that things are set properly
  EXPECT_DEATH(
      {
        int dim = v.GetSpatialDimension();
        exit(0);
      }, "Assertion failed");

  v.SetSpatialDimension(4);
  std::set<ChamberHandle> empty_set;
  for(int i = 0; i <= 4; ++i){
    ASSERT_EXIT(
        {
          const std::set<ChamberHandle>& set = v.GetIncidenceList(i);
          exit(0);
        }, ::testing::ExitedWithCode(0), "") << absl::Substitute("Failure to get incidence list at index $0", i);
    EXPECT_EQ(empty_set, v.GetIncidenceList(i)) << absl::Substitute("Incident chamber set at dimension $0 does not match expected result", i);
    EXPECT_EQ(v.GetCoordinate(i), shared::constants::PrecisionType(0.0) ) << absl::Substitute("Coordinate at dimension $0 does not match expected result", i);
  }

  EXPECT_EQ(v.front_id(), shared::constants::kInvalidId);
  EXPECT_EQ(v.footprint_id(), shared::constants::kInvalidId);
  EXPECT_EQ(v.patch_id(), shared::constants::kInvalidId);

}

} // namespace
} // namespace