/* Copyright 2020 The REAP Authors. All Rights Reserved. */

#ifndef REAP_PLAN_GRAPH_UTIL_H_
#define REAP_PLAN_GRAPH_UTIL_H_

#include "reap/proto/geometry.pb.h"
#include "reap/core/serializer.h"
#include "reap/plan/area_bound.h"
#include "reap/plan/plan.h"

namespace reap {

Status AreaBoundToGraph(const AreaBound &area_bound, Graph *graph);

Status ArrangementToGraph(const Arrangement &area_bound, Graph *graph);

Status ColumnArrangementToGraph(const ColumnArrangement &area_bound, Graph *graph);


}  // namespace reap

#endif  // REAP_PLAN_GRAPH_UTIL_H_
