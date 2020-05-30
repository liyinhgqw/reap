/* Copyright 2020 The REAP Authors. All Rights Reserved. */

#ifndef REAP_PLAN_PLAN_CONFIG_H_
#define REAP_PLAN_PLAN_CONFIG_H_

namespace reap {

struct PlanConfig {
  int num_of_floors;
  double floor_height;
  double building_width;
  double spacing_ratio;
  double first_row_offset;
  int num_of_columns;  // just a hint
};

}  // namespace reap

#endif  // REAP_PLAN_PLAN_CONFIG_H_
