/* Copyright 2020 The REAP Authors. All Rights Reserved. */

#include "reap/plan/graph_util.h"

namespace reap {

Status AreaBoundToGraph(const AreaBound &area_bound, Graph *graph) {
  ShapeSerializer serializer;
  auto polygon = graph->add_polygon();
  return serializer.Serialize(area_bound.polygon(), polygon);
}

Status RowArrangementToGraph(const RowArrangement &row_arrangement, Graph *graph) {
  ShapeSerializer serializer;
  for (auto row : row_arrangement.rows()) {
    for (auto &segment: row.segments) {
      auto line = graph->add_line();
      serializer.Serialize(segment, line);
    }
  }
  return Status::OK();
}

Status ColumnArrangementToGraph(const ColumnArrangement &arrangement, Graph *graph) {
  ShapeSerializer serializer;
  for (auto & column: arrangement.arrangement()) {
    RowArrangementToGraph(column, graph);
  }
  return Status::OK();
}


}  // namespace reap
