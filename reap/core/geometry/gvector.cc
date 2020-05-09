/* Copyright 2020 The REAP Authors. All Rights Reserved. */

#include "reap/core/geometry/gvector.h"

namespace reap {

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

}  // namespace reap
