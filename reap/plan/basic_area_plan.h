/* Copyright 2020 The REAP Authors. All Rights Reserved. */

#ifndef REAP_PLAN_BASIC_AREA_PLAN_H_
#define REAP_PLAN_BASIC_AREA_PLAN_H_

#include "reap/plan/area_plan.h"

namespace reap {

class BasicAreaPlan : public AreaPlan {
  BasicAreaPlan(const PlanConfig &config,
                const AreaBound &area_bound,
                const OutlinePlanResult &outline_plan_result)
      : AreaPlan(config, area_bound, outline_plan_result) {}
  ~BasicAreaPlan() = default;

  void Plan(AreaPlanResult *plan_result);
};

}  // namespace reap

#endif  // REAP_PLAN_BASIC_AREA_PLAN_H_
