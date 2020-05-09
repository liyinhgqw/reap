/* Copyright 2020 The REAP Authors. All Rights Reserved. */

#ifndef REAP_CORE_GEOMETRY_POLYGON_H_
#define REAP_CORE_GEOMETRY_POLYGON_H_

#include <vector>

#include "reap/core/util//status.h"
#include "reap/core/geometry/shape.h"
#include "reap/core/geometry/gvector.h"

namespace reap {

class Polygon : public Shape {
 public:
  Polygon(std::vector<GVector> &points);
  virtual ~Polygon();

  std::vector<GVector> points() const {
    return points_;
  }

  virtual Status Move(const GVector &offset) override;
  virtual Status Rotate(double angle, const GVector &center) override;

 private:
  std::vector<GVector> points_;
};

}  // namespace reap

#endif  // REAP_CORE_GEOMETRY_POLYGON_H_
