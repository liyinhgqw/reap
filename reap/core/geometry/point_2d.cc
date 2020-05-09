/* Copyright 2020 The REAP Authors. All Rights Reserved. */

#include "reap/core/geometry/point_2d.h"

namespace reap {

Point2D::Point2D(double x, double y): position_(x, y) {}

Point2D::~Point2D() {}

void Point2D::Move(double x, double y) {
  position_ += GVector(x, y);
}

}  // namespace reap

std::ostream& operator << (std::ostream& out, const reap::Point2D &p) {
  out << "Point2D(" << p.x() << ", " << p.y() << ")";
  return out;
}
