/* Copyright 2020 The REAP Authors. All Rights Reserved. */

#ifndef REAP_CORE_TYPE_H_
#define REAP_CORE_TYPE_H_

#include "CGAL/Exact_predicates_inexact_constructions_kernel.h"
#include "CGAL/Polygon_2.h"
#include "CGAL/Point_2.h"
#include "CGAL/Line_2.h"
#include "CGAL/Segment_2.h"

#include "CGAL/Aff_transformation_2.h"
#include "CGAL/Vector_2.h"
#include "CGAL/Direction_2.h"
#include "CGAL/intersection_2.h"

namespace reap {

using Kernel = CGAL::Exact_predicates_inexact_constructions_kernel;
using Polygon = CGAL::Polygon_2<Kernel>;
using Point = CGAL::Point_2<Kernel>;
using Line = CGAL::Line_2<Kernel>;
using Segment = CGAL::Segment_2<Kernel>;

using Transformation = CGAL::Aff_transformation_2<Kernel>;
using Vector = CGAL::Vector_2<Kernel>;
using Direction = CGAL::Direction_2<Kernel>;
using Intersect = Kernel::Intersect_2;

struct ShapeUnion {
  enum {POINT, SEGMENT} tag;
  union {
    Point p;
    Segment s;
  };
};

}  // namespace reap

#endif  // REAP_CORE_TYPE_H_
