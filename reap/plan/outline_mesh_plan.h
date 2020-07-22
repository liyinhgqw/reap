/* Copyright 2020 The REAP Authors. All Rights Reserved. */

#ifndef REAP_PLAN_OUTLINE_MESH_PLAN_H_
#define REAP_PLAN_OUTLINE_MESH_PLAN_H_

#include "reap/plan/outline_plan.h"
#include "reap/plan/arrangement.h"

namespace reap {

class OutlineMeshPlan : public OutlinePlan {
 public:
  OutlineMeshPlan(const PlanConfig &config,
                  const AreaBound &area_bound)
      : OutlinePlan(config, area_bound) {}
  ~OutlineMeshPlan() = default;

  void Plan(OutlinePlanResult *plan_result);

 private:
  void ArrangeRow(double min_x, double max_x, RowArrangement *arrangement);
  void ArrangeAndSelectRow(double min_x, double max_x, RowArrangement *arrangement);
  void ArrangeColumn(ColumnArrangement *columns);
};

}  // namespace reap

#endif  // REAP_PLAN_OUTLINE_MESH_PLAN_H_
