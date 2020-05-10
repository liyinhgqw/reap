/* Copyright 2020 The REAP Authors. All Rights Reserved. */

#include "reap/core/geometry/polygon.h"

namespace reap {

Polygon::Polygon(const std::vector<GVector> &points): points_() {}

Polygon::~Polygon() {}

Status Polygon::Move(const GVector &offset) {
  for (auto &v : points_) {
    v += offset;
  }
  return Status::OK();
}

Status Polygon::Rotate(double angle, const GVector &center) {
  for (auto &v : points_) {
    v.Rotate(angle, center);
  }
  return Status::OK();
}

}  // namespace reap
