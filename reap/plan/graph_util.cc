/* Copyright 2020 The REAP Authors. All Rights Reserved. */

#include "reap/plan/graph_util.h"

namespace reap {

Status AreaBoundToGraph(const AreaBound &area_bound, Graph *graph) {
  ShapeSerializer serializer;
  auto polygon = graph->add_polygon();
  return serializer.Serialize(area_bound.polygon(), polygon);
}

}  // namespace reap
