/* Copyright 2020 The REAP Authors. All Rights Reserved. */

#ifndef REAP_PLAN_AREA_PLAN_H_
#define REAP_PLAN_AREA_PLAN_H_

#include <vector>

#include "reap/plan/plan_config.h"
#include "reap/plan/area_bound.h"
#include "reap/plan/outline_plan.h"

namespace reap {

struct BuildingUnit {
  Point anchor;
  std::vector<BuildingUnit *> neighbors;
};

struct AreaPlanResult {
  std::vector<BuildingUnit> building_units;
  BuildingOutline *building_outline_ref;
};

class AreaPlan {
 public:
  AreaPlan(const PlanConfig &config,
           const AreaBound &area_bound,
           const OutlinePlanResult &outline_plan_result)
      : config_(config),
        area_bound_(area_bound) {}
  virtual ~AreaPlan() = default;

  virtual void Plan(AreaPlanResult *plan_result) = 0;

 protected:
  PlanConfig config_;
  AreaBound area_bound_;
  OutlinePlanResult outline_plan_result_;
};

}  // namespace reap

#endif  // REAP_PLAN_AREA_PLAN_H_
