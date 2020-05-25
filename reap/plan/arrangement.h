/* Copyright 2020 The REAP Authors. All Rights Reserved. */

#ifndef REAP_PLAN_ARRANGEMENT_H_
#define REAP_PLAN_ARRANGEMENT_H_

#include <vector>

#include "reap/core/type.h"
#include "reap/plan/plan_config.h"

namespace reap {

struct RowArrangement {
  std::vector<Segment> segments;
};

class Arrangement {
 public:
  Arrangement(const PlanConfig &plan_config)
      : plan_config_(plan_config) {}
  Arrangement(const Arrangement &other)
      : plan_config_(other.plan_config_),
      row_arrangement_(other.row_arrangement_) {}

  double GetTotalVolume() const {
    double len = 0;
    for (auto &row : row_arrangement_) {
      for (auto &s : row.segments) {
        len += sqrt(s.squared_length());
      }
    }
    return len * plan_config_.num_of_floors * plan_config_.floor_height;
  }

  bool operator<(const Arrangement &other) const {
    return GetTotalVolume() > other.GetTotalVolume();
  }

  const PlanConfig &plan_config() const {
    return plan_config_;
  }

  const std::vector<RowArrangement> &row_arrangement() const {
    return row_arrangement_;
  }

  std::vector<RowArrangement> &row_arrangement() {
    return row_arrangement_;
  }

 private:
  PlanConfig plan_config_;
  std::vector<RowArrangement> row_arrangement_;
};

}  // namespace reap

#endif  // REAP_PLAN_ARRANGEMENT_H_
