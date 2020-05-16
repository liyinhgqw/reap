/* Copyright 2020 The REAP Authors. All Rights Reserved. */

#include "reap/plan/area_bound.h"

#include <utility>

namespace reap {

AreaBound::AreaBound(const Polygon &polygon, double angle)
  : polygon_(polygon), angle_(angle) {
}

AreaBound::~AreaBound() {}

}  // namespace reap
