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
  Arrangement() {}
  Arrangement(const PlanConfig &plan_config)
      : plan_config_(plan_config) {}

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

  const PlanConfig &config() const {
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

class ColumnArrangement {
 public:
  ColumnArrangement() {}

  const std::vector<Arrangement> &arrangement() const {
    return arrangement_;
  }

  std::vector<Arrangement> &arrangement() {
    return arrangement_;
  }

  void AddColumn(const Arrangement &arrangement) {
    arrangement_.push_back(arrangement);
  }

  double GetTotalVolume() const {
    double len = 0;
    for (auto &col : arrangement_) {
      len += col.GetTotalVolume();
    }
    return len;
  }

  bool operator<(const ColumnArrangement &other) const {
    return GetTotalVolume() > other.GetTotalVolume();
  }

 private:
  std::vector<Arrangement> arrangement_;
};

}  // namespace reap

#endif  // REAP_PLAN_ARRANGEMENT_H_
