/* Copyright 2020 The REAP Authors. All Rights Reserved. */

#include <iostream>

#include "reap/core/geometry/point.h"
#include "reap/core/geometry/gvector.h"
#include "reap/core/geometry/serializer.h"

int main() {
  reap::Point point(1.0, 2.0);
  point.Move(reap::GVector(3.0, 4.0));
  std::cout << point << std::endl;

  return 0;
}

