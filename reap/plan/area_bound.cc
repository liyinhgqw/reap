/* Copyright 2020 The REAP Authors. All Rights Reserved. */

#include "reap/plan/area_bound.h"

#include <utility>

namespace reap {

AreaBound::AreaBound(const Polygon &polygon, double angle)
  : polygon_(polygon), angle_(angle) {
}

AreaBound::~AreaBound() {}

AreaBound AreaBound::Rotate() const {
  Transformation rotate(CGAL::ROTATION, sin(angle_), cos(angle_));
  Polygon pol;
  for (std::size_t i = 0; i < polygon_.size(); ++i) {
    pol.push_back(rotate(polygon_[i]));
  }
  return AreaBound(pol);
}

}  // namespace reap
