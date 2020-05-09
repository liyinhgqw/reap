/* Copyright 2020 The REAP Authors. All Rights Reserved. */

#ifndef REAP_CORE_GEOMETRY_GVECTOR_H_
#define REAP_CORE_GEOMETRY_GVECTOR_H_

#include <ostream>

namespace reap {

class GVector {
 public:
  GVector(double x, double y, double z = 0.0);
  virtual ~GVector();

  double x() const { return x_; }
  double y() const { return y_; }
  double z() const { return z_; }

  GVector operator+(const GVector &v) const;
  GVector operator-(const GVector &v) const;
  GVector operator*(double s) const;
  GVector operator*(const GVector &v) const;
  GVector operator/(double s) const;
  GVector operator/(const GVector &v) const;
  GVector& operator+=(const GVector &v);
  GVector& operator-=(const GVector &v);
  GVector& operator*=(const GVector &v);
  GVector& operator/=(const GVector &v);
  GVector operator-() const;

  double GetLength() const;
  double GetLengthSquare() const;
  double GetLength2D() const;
  double GetLengthSquare2D() const;
  double GetAngle() const;
  GVector &Rotate(double angle, const GVector &center);

 protected:
  double x_;
  double y_;
  double z_;
};

}  // namespace reap

std::ostream& operator << (std::ostream& out, const reap::GVector &v);

#endif  // REAP_CORE_GEOMETRY_GVECTOR_H_
