/* Copyright 2020 The REAP Authors. All Rights Reserved. */

#include "reap/plan/graph_util.h"

namespace reap {

void AreaBoundToGraph(const AreaBound &area_bound, Graph *graph) {
  ShapeSerializer serializer;
  auto polygon = graph->add_polygon();
  serializer.Serialize(area_bound.polygon(), polygon);
}

void OutlinePlanToGraph(const OutlinePlanResult &outline_plan_result, Graph *graph) {
  ShapeSerializer serializer;
  for (auto &building_outline : outline_plan_result.building_outline) {
    auto line = graph->add_line();
    serializer.Serialize(building_outline.segment, line);
  }
}


}  // namespace reap
