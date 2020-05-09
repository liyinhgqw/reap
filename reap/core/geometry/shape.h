/* Copyright 2020 The REAP Authors. All Rights Reserved. */

#ifndef REAP_CORE_GEOMETRY_SHAPE_H_
#define REAP_CORE_GEOMETRY_SHAPE_H_

#include "reap/core/util/status.h"
#include "reap/core/geometry/gvector.h"

namespace reap {

class Shape {
 public:
  Shape() {}
  virtual ~Shape() {}
  virtual Status Move(const GVector &offset) = 0;
  virtual Status Rotate(double angle, const GVector &center) = 0;
};

}  // namespace reap

#endif  // REAP_CORE_GEOMETRY_SHAPE_H_
