/* Copyright 2020 The REAP Authors. All Rights Reserved. */

#ifndef REAP_CORE_GEOMETRY_MATH_H_
#define REAP_CORE_GEOMETRY_MATH_H_

#include "reap/core/type.h"

namespace reap {

bool IsSegmentInsidePolygon(const Segment &segment, const Polygon &polygon);

}  // namespace reap

#endif  // REAP_CORE_GEOMETRY_MATH_H_
