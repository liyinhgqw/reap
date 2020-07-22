/* Copyright 2020 The REAP Authors. All Rights Reserved. */

#ifndef REAP_PLAN_PLAN_H_
#define REAP_PLAN_PLAN_H_

#include <vector>

#include "reap/plan/plan_config.h"
#include "reap/plan/area_bound.h"

namespace reap {

struct BuildingOutline {
  Segment segment;
};

struct OutlinePlanResult {
  std::vector<BuildingOutline> building_outline;
};

class OutlinePlan {
 public:
  OutlinePlan(const PlanConfig &config,
              const AreaBound &area_bound)
      : config_(config),
        area_bound_(area_bound) {}
  virtual ~OutlinePlan() = default;

  virtual void Plan(OutlinePlanResult *plan_result) = 0;

 protected:
  PlanConfig config_;
  AreaBound area_bound_;
};

}  // namespace reap

#endif  // REAP_PLAN_PLAN_H_
