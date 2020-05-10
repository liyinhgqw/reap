/* Copyright 2020 The REAP Authors. All Rights Reserved. */

#include "reap/core/geometry/point.h"

namespace reap {

Point::Point(double x, double y, double z): position_(x, y, z) {}

Point::~Point() {}

Status Point::Move(const GVector &offset) {
  position_ += offset;
  return Status::OK();
}

Status Point::Rotate(double angle, const GVector &center) {
  position_.Rotate(angle, center);
  return Status::OK();
}

}  // namespace reap
