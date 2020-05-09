/* Copyright 2020 The REAP Authors. All Rights Reserved. */

#ifndef REAP_CORE_GEOMETRY_POINT_2D_H_
#define REAP_CORE_GEOMETRY_POINT_2D_H_

#include <ostream>

#include "reap/core/util//status.h"
#include "reap/core/geometry/shape.h"
#include "reap/core/geometry/gvector.h"

namespace reap {

class Point2D : public Shape {
 public:
  Point2D(double x, double y);
  virtual ~Point2D();

  double x() const {
    return position_.x();
  }

  double y() const {
    return position_.y();
  }

  virtual Status Move(const GVector &offset) override;
  virtual Status Rotate(double angle, const GVector &center) override;

 private:
  GVector position_;
};


}  // namespace reap

std::ostream &operator << (std::ostream &out, const reap::Point2D &p);

#endif  // REAP_CORE_GEOMETRY_POINT_2D_H_
