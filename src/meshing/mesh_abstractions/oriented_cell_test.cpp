/*
** Created by Christian Howard on 10/9/22.
*/
#include "meshing/mesh_abstractions/oriented_cell.h"

#include <array>

#include "absl/strings/substitute.h"
#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "status_macros/test_status_macros.h"

#include "meshing/mesh_abstractions/vertex.h"

namespace tp_sdg::meshing::abstractions {
namespace {

class OrientedCellTest : public ::testing::Test {
 public:
  OrientedCellTest() = default;
  ~OrientedCellTest() = default;
};

using CellConstructionTests = OrientedCellTest;
TEST_F(CellConstructionTests, InvalidInitializedDimension) {
  EXPECT_DEATH(
      {
        OrientedCell cell;
        int dim = cell.GetDimension();
      }, "Assertion failed");
}
}
TEST_F(CellConstructionTests, InvalidNegativeSetDimension) {
  EXPECT_DEATH(
      {
        OrientedCell cell;
        cell.SetDimension(-1);
        int dim = cell.GetDimension();
        exit(0);
      }, "Assertion failed");
}
TEST_F(CellConstructionTests, InvalidLargeSetDimension) {
  EXPECT_DEATH(
      {
        OrientedCell cell;
        cell.SetDimension(5);
        int dim = cell.GetDimension();
        exit(0);
      }, "Assertion failed");
}
TEST_F(CellConstructionTests, SucceedSetDimension) {
  EXPECT_EXIT(
      {
        for (int i = 0; i < 5; ++i) {
          OrientedCell cell;
          cell.SetDimension(i);
        }
        exit(0);
      }, ::testing::ExitedWithCode(0), "");
}
TEST_F(CellConstructionTests, FailSetVertex) {
  EXPECT_DEATH(
      {
        Vertex v;
        VertexHandle vh(&v);
        OrientedCell cell;
        cell.SetDimension(0);
        auto status = cell.SetVertex(1, vh);
        if (!status.ok()) { exit(1); }
        exit(0);
      }, "Assertion failed");
}
TEST_F(CellConstructionTests, SucceedSetVertex) {
  EXPECT_EXIT(
      {
        Vertex v;
        VertexHandle vh(&v);
        OrientedCell cell;
        cell.SetDimension(0);
        auto status = cell.SetVertex(0, vh);
        if (!status.ok()) { exit(1); }
        exit(0);
      }, ::testing::ExitedWithCode(0), "");
}
TEST_F(CellConstructionTests, FailGetVertex) {
  EXPECT_DEATH(
      {
        Vertex v;
        VertexHandle vh(&v);
        OrientedCell cell;
        cell.SetDimension(0);
        auto status = cell.SetVertex(0, vh);
        if (!status.ok()) { exit(1); }
        VertexHandle vh_new = cell.GetVertex(1);
        exit(0);
      }, "Assertion failed");
}
TEST_F(CellConstructionTests, SucceedGetVertex) {
  EXPECT_EXIT(
      {
        Vertex v;
        VertexHandle vh(&v);
        OrientedCell cell;
        cell.SetDimension(0);
        auto status = cell.SetVertex(0, vh);
        if (!status.ok()) { exit(1); }
        VertexHandle vh_new = cell.GetVertex(0);
        exit(0);
      }, ::testing::ExitedWithCode(0), "");
}
TEST_F(CellConstructionTests, SucceedSetVerticesIndividual) {
  constexpr int kDimension = 3;
  std::array<Vertex, kDimension + 1> vertices;
  std::array<VertexHandle, kDimension + 1> vertex_handles;
  for (int i = 0; i <= kDimension; ++i) {
    vertex_handles[i] = VertexHandle(&vertices[i]);
  }

  // build the exact cell we will compare against
  OrientedCell cell;
  cell.SetDimension(kDimension);
  for (int i = 0; i <= kDimension; ++i) {
    EXPECT_OK(cell.SetVertex(i, vertex_handles[i]));
  }

  // compare the vertices
  EXPECT_EQ(kDimension, cell.GetDimension());
  for (int i = 0; i <= kDimension; ++i) {
    EXPECT_EQ(cell.GetVertex(i), vertex_handles[i]) << absl::Substitute("Difference for vertex($0)", i);
  }
}
TEST_F(CellConstructionTests, SucceedSetVerticesInitListCollection) {
  constexpr int kDimension = 3;
  std::array<Vertex, kDimension + 1> vertices;
  std::array<VertexHandle, kDimension + 1> vertex_handles;
  for (int i = 0; i <= kDimension; ++i) {
    vertex_handles[i] = VertexHandle(&vertices[i]);
  }

  // build the exact cell we will compare against
  OrientedCell exact_cell;
  exact_cell.SetDimension(kDimension);
  for (int i = 0; i <= kDimension; ++i) {
    EXPECT_OK(exact_cell.SetVertex(i, vertex_handles[i]));
  }

  // build a new cell using the SetVertices method
  OrientedCell new_cell;
  EXPECT_OK(new_cell.SetVertices({vertex_handles[0], vertex_handles[1], vertex_handles[2], vertex_handles[3]}));

  // compare the vertices
  EXPECT_EQ(new_cell.GetDimension(), exact_cell.GetDimension());
  for (int i = 0; i <= 3; ++i) {
    EXPECT_EQ(exact_cell.GetVertex(i), new_cell.GetVertex(i)) << absl::Substitute("Difference for vertex($0)", i);
  }
}
TEST_F(CellConstructionTests, SucceedSetVerticesArrayCollection) {
  constexpr int kDimension = 3;
  std::array<Vertex, kDimension + 1> vertices;
  std::array<VertexHandle, kDimension + 1> vertex_handles;
  for (int i = 0; i <= kDimension; ++i) {
    vertex_handles[i] = VertexHandle(&vertices[i]);
  }

  // build the exact cell we will compare against
  OrientedCell exact_cell;
  exact_cell.SetDimension(kDimension);
  for (int i = 0; i <= kDimension; ++i) {
    EXPECT_OK(exact_cell.SetVertex(i, vertex_handles[i]));
  }

  // build a new cell using the SetVertices method
  OrientedCell new_cell;
  EXPECT_OK(new_cell.SetVertices<kDimension>(vertex_handles));

  // compare the vertices
  EXPECT_EQ(new_cell.GetDimension(), exact_cell.GetDimension());
  for (int i = 0; i <= 3; ++i) {
    EXPECT_EQ(exact_cell.GetVertex(i), new_cell.GetVertex(i)) << absl::Substitute("Difference for vertex($0)", i);
  }
}

TEST_F(CellConstructionTests, FailSetVerticesIndividual) {
  constexpr int kDimension = 3;
  std::array<Vertex, kDimension + 1> vertices;
  std::array<VertexHandle, kDimension + 1> vertex_handles;
  for (int i = 0; i <= kDimension; ++i) {
    vertex_handles[i] = VertexHandle(&vertices[i]);
  }
  constexpr int bad_idx = 2;
  vertex_handles[bad_idx] = nullptr;

  // build the exact cell we will compare against
  OrientedCell cell;
  cell.SetDimension(kDimension);
  for (int i = 0; i <= kDimension; ++i) {
    if (i == bad_idx) {
      absl::Status status = cell.SetVertex(i, vertex_handles[i]);
      EXPECT_FALSE(status.ok());
      EXPECT_EQ(status.code(), absl::StatusCode::kInvalidArgument);
      EXPECT_THAT(status.message(), ::testing::HasSubstr("Vertex handle is null"));
    } else {
      EXPECT_OK(cell.SetVertex(i, vertex_handles[i]));
    }
  }

  // compare the vertices
  EXPECT_EQ(kDimension, cell.GetDimension());
  for (int i = 0; i <= kDimension; ++i) {
    EXPECT_EQ(cell.GetVertex(i), vertex_handles[i]) << absl::Substitute("Difference for vertex($0)", i);
  }
}
TEST_F(CellConstructionTests, FailSetVerticesInitListCollection) {
  constexpr int kDimension = 3;
  std::array<Vertex, kDimension + 1> vertices;
  std::array<VertexHandle, kDimension + 1> vertex_handles;
  for (int i = 0; i <= kDimension; ++i) {
    vertex_handles[i] = VertexHandle(&vertices[i]);
  }
  constexpr int bad_idx = 2;
  vertex_handles[bad_idx] = nullptr;

  // build a new cell using the SetVertices method
  OrientedCell cell;
  absl::Status status = cell.SetVertices({vertex_handles[0], vertex_handles[1], vertex_handles[2], vertex_handles[3]});
  EXPECT_FALSE(status.ok());
  EXPECT_EQ(status.code(), absl::StatusCode::kInvalidArgument);
  EXPECT_THAT(status.message(), ::testing::HasSubstr("Vertex handle is null"));

}
TEST_F(CellConstructionTests, FailSetVerticesArrayCollection) {
  constexpr int kDimension = 3;
  std::array<Vertex, kDimension + 1> vertices;
  std::array<VertexHandle, kDimension + 1> vertex_handles;
  for (int i = 0; i <= kDimension; ++i) {
    vertex_handles[i] = VertexHandle(&vertices[i]);
  }
  constexpr int bad_idx = 2;
  vertex_handles[bad_idx] = nullptr;

  // build a new cell using the SetVertices method
  OrientedCell cell;
  absl::Status status = cell.SetVertices<kDimension>(vertex_handles);
  EXPECT_FALSE(status.ok());
  EXPECT_EQ(status.code(), absl::StatusCode::kInvalidArgument);
  EXPECT_THAT(status.message(), ::testing::HasSubstr("Vertex handle is null"));
}

}