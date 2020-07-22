/* Copyright 2020 The REAP Authors. All Rights Reserved. */

#ifndef REAP_PLAN_GRAPH_UTIL_H_
#define REAP_PLAN_GRAPH_UTIL_H_

#include "reap/core/serializer.h"
#include "reap/plan/outline_plan.h"

namespace reap {

void AreaBoundToGraph(const AreaBound &area_bound, Graph *graph);

void OutlinePlanToGraph(const OutlinePlanResult &outline_plan_result, Graph *graph);

}  // namespace reap

#endif  // REAP_PLAN_GRAPH_UTIL_H_
