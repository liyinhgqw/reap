/* Copyright 2020 The REAP Authors. All Rights Reserved. */

#include <iostream>

#include "reap/core/geometry/point_2d.h"
#include "reap/core/geometry/gvector.h"

int main() {
  reap::Point2D point(1.0, 2.0);
  point.Move(reap::GVector(3.0, 4.0));
  std::cout << point << std::endl;

  return 0;
}

