/* Copyright 2020 The REAP Authors. All Rights Reserved. */

#ifndef REAP_PLAN_ARRANGEMENT_H_
#define REAP_PLAN_ARRANGEMENT_H_

#include <vector>

#include "reap/core/type.h"
#include "reap/plan/plan_config.h"

namespace reap {

struct Row {
  std::vector<Segment> segments;
};

class RowArrangement {
 public:
  RowArrangement() {}
  RowArrangement(const PlanConfig &plan_config)
      : plan_config_(plan_config) {}

  double GetTotalVolume() const {
    double len = 0;
    for (auto &row : rows_) {
      for (auto &s : row.segments) {
        len += sqrt(s.squared_length());
      }
    }
    return len * plan_config_.num_of_floors * plan_config_.floor_height;
  }

  bool operator<(const RowArrangement &other) const {
    return GetTotalVolume() > other.GetTotalVolume();
  }

  const PlanConfig &config() const {
    return plan_config_;
  }

  const std::vector<Row> &rows() const {
    return rows_;
  }

  std::vector<Row> &rows() {
    return rows_;
  }

 private:
  PlanConfig plan_config_;
  std::vector<Row> rows_;
};

class ColumnArrangement {
 public:
  ColumnArrangement() {}

  const std::vector<RowArrangement> &arrangement() const {
    return arrangement_;
  }

  std::vector<RowArrangement> &arrangement() {
    return arrangement_;
  }

  void AddColumn(const RowArrangement &arrangement) {
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
  // row arrangement for each column
  std::vector<RowArrangement> arrangement_;
};

}  // namespace reap

#endif  // REAP_PLAN_ARRANGEMENT_H_
