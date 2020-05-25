/* Copyright 2020 The REAP Authors. All Rights Reserved. */

#ifndef REAP_PLAN_PLAN_H_
#define REAP_PLAN_PLAN_H_

#include "reap/plan/area_bound.h"
#include "reap/plan/arrangement.h"
#include "reap/plan/plan_config.h"

namespace reap {

class Plan {
 public:
  Plan(const PlanConfig &config,
       const AreaBound &area_bound)
      : config_(config),
        area_bound_(area_bound) {}
  virtual ~Plan() {}

  void arrange(Arrangement *arrangement);

 private:
  PlanConfig config_;
  AreaBound area_bound_;
};

}  // namespace reap

#endif  // REAP_PLAN_PLAN_H_
