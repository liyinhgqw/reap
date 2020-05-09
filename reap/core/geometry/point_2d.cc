/* Copyright 2020 The REAP Authors. All Rights Reserved. */

#include "reap/core/geometry/point_2d.h"

namespace reap {

Point2D::Point2D(double x, double y): position_(x, y) {}

Point2D::~Point2D() {}

Status Point2D::Move(const GVector &offset) {
  position_ += offset;
  return Status::OK();
}

Status Point2D::Rotate(double angle, const GVector &center) {
  position_.Rotate(angle, center);
  return Status::OK();
}

}  // namespace reap

std::ostream& operator << (std::ostream& out, const reap::Point2D &p) {
  out << "Point2D(" << p.x() << ", " << p.y() << ")";
  return out;
}
