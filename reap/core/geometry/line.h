/* Copyright 2020 The REAP Authors. All Rights Reserved. */

#ifndef REAP_CORE_GEOMETRY_LINE_H_
#define REAP_CORE_GEOMETRY_LINE_H_

#include <ostream>

#include "reap/core/status.h"
#include "reap/core/geometry/shape.h"
#include "reap/core/geometry/gvector.h"

namespace reap {

class Line : public Shape {
 public:
  Line(const GVector &start, const GVector &end);
  virtual ~Line();

  GVector start_point() const {
    return start_point_;
  }

  GVector end_point() const {
    return end_point_;
  }

  Status Move(const GVector &offset) override;
  Status Rotate(double angle, const GVector &center) override;

 private:
  GVector start_point_;
  GVector end_point_;
};

}  // namespace reap

#endif  // REAP_CORE_GEOMETRY_LINE_H_
