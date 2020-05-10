/* Copyright 2020 The REAP Authors. All Rights Reserved. */

#ifndef REAP_PLAN_AREA_BOUND_H_
#define REAP_PLAN_AREA_BOUND_H_

#include "reap/core/geometry/polygon.h"

namespace reap {

class AreaBound {
 public:
  explicit AreaBound(const Polygon &polygon, double angle = 0.0);
  explicit AreaBound(Polygon &&polygon, double angle = 0.0);
  virtual ~AreaBound();

  Polygon polygon() const {
    return polygon_;
  }

  double angle() const {
    return angle_;
  }

  void SetAngle(double angle) {
    angle_ = angle;
  }

 private:
  Polygon polygon_;
  double angle_;
};

}  // namespace reap

#endif  // REAP_PLAN_AREA_BOUND_H_
