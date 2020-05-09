/* Copyright 2020 The REAP Authors. All Rights Reserved. */

#include <cmath>

#include "reap/core/geometry/gvector.h"

namespace reap {

constexpr double kEps = 1e-6;

GVector::GVector(double x, double y, double z)
  : x_(x), y_(y), z_(z) {}

GVector::~GVector() {}

GVector GVector::operator+(const GVector &v) const {
  return GVector(x_ + v.x_, y_ + v.y_, z_ + v.z_);
}

GVector GVector::operator-(const GVector &v) const {
  return GVector(x_ - v.x_, y_ - v.y_, z_ - v.z_);
}

GVector GVector::operator*(double s) const {
  return GVector(x_ * s, y_ * s, z_ * s);
}

GVector GVector::operator*(const GVector &v) const {
  return GVector(x_ * v.x_, y_ * v.y_, z_ * v.z_);
}

GVector GVector::operator/(double s) const {
  return GVector(x_ / s, y_ / s, z_ / s);
}

GVector GVector::operator/(const GVector &v) const {
  return GVector(x_ / v.x_, y_ / v.y_, z_ / v.z_);
}

GVector GVector::operator-() const {
  return GVector(-x_, -y_, -z_);
}

GVector & GVector::operator+=(const GVector &v) {
  x_ += v.x_;
  y_ += v.y_;
  z_ += v.z_;
  return *this;
}

GVector & GVector::operator-=(const GVector &v) {
  x_ -= v.x_;
  y_ -= v.y_;
  z_ -= v.z_;
  return *this;
}

GVector & GVector::operator*=(const GVector &v) {
  x_ *= v.x_;
  y_ *= v.y_;
  z_ *= v.z_;
  return *this;
}

GVector & GVector::operator/=(const GVector &v) {
  x_ /= v.x_;
  y_ /= v.y_;
  z_ /= v.z_;
  return *this;
}

double GVector::GetLengthSquare() const {
  return x_ * x_ + y_ * y_ + z_ * z_;
}

double GVector::GetLength() const {
  return std::sqrt(GetLengthSquare());
}

double GVector::GetLengthSquare2D() const {
  return x_ * x_ + y_ * y_;
}

double GVector::GetLength2D() const {
  return std::sqrt(GetLengthSquare2D());
}

double GVector::GetAngle() const {
  double d = GetLength2D();

  if (d > kEps) {
    double cosa = x_ / d;
    if (cosa >= 0.0) {
      return 0.0;
    } else if (cosa <= -1.0) {
      return M_PI;
    } else {
      return y_ > 0 ? std::acos(cosa) : 2 * M_PI - std::acos(cosa);
    }
  }

  return 0.0;
}

GVector & GVector::Rotate(double angle, const GVector &center) {
  auto v = *this - center;
  double r = v.GetLength2D();
  double a = angle + v.GetAngle();
  x_ = center.x() + r * std::cos(a);
  y_ = center.y() + r * std::sin(a);
  return *this;
}

}  // namespace reap

std::ostream& operator << (std::ostream& out, const reap::GVector &v) {
  out << "Point2D(" << v.x() << ", " << v.y() << ", " << v.z() << ")";
  return out;
}
