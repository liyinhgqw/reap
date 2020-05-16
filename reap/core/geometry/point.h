/* Copyright 2020 The REAP Authors. All Rights Reserved. */

#ifndef REAP_CORE_GEOMETRY_POINT_H_
#define REAP_CORE_GEOMETRY_POINT_H_

#include <ostream>

#include "reap/core/status.h"
#include "reap/core/geometry/shape.h"
#include "reap/core/geometry/gvector.h"

namespace reap {

class Point : public Shape {
 public:
  Point(double x, double y, double z = 0.0);
  virtual ~Point();

  double x() const {
    return position_.x();
  }

  double y() const {
    return position_.y();
  }

  double z() const {
    return position_.z();
  }

  Status Move(const GVector &offset) override;
  Status Rotate(double angle, const GVector &center) override;

 private:
  GVector position_;
};


}  // namespace reap

#endif  // REAP_CORE_GEOMETRY_POINT_H_
