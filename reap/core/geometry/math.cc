/* Copyright 2020 The REAP Authors. All Rights Reserved. */

#include "reap/core/geometry/math.h"

namespace reap {

bool IsSegmentInsidePolygon(const Segment &segment, const Polygon &polygon) {
  if (polygon.bounded_side(segment.source()) != CGAL::ON_BOUNDED_SIDE
    || polygon.bounded_side(segment.target()) != CGAL::ON_BOUNDED_SIDE) {
    return false;
  }

  for (auto it_edge = polygon.edges_begin(); it_edge != polygon.edges_end(); it_edge++) {
    auto edge = *it_edge;
    auto intersect = CGAL::intersection(edge, segment);
    if (intersect) {
      return false;
    }
  }

  return true;
}

}  // namespace reap