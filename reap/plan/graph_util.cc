/* Copyright 2020 The REAP Authors. All Rights Reserved. */

#include "reap/plan/graph_util.h"

namespace reap {

Status AreaBoundToGraph(const AreaBound &area_bound, Graph *graph) {
  ShapeSerializer serializer;
  auto polygon = graph->add_polygon();
  return serializer.Serialize(area_bound.polygon(), polygon);
}

Status ArrangementToGraph(const Arrangement &arrangement, Graph *graph) {
  ShapeSerializer serializer;
  for (auto row_arrangement : arrangement.row_arrangement()) {
    for (auto segment: row_arrangement.segments) {
      auto line = graph->add_line();
      serializer.Serialize(segment, line);
    }
  }
  return Status::OK();
}

}  // namespace reap
