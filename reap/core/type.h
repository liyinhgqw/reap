/* Copyright 2020 The REAP Authors. All Rights Reserved. */

#ifndef REAP_CORE_TYPE_H_
#define REAP_CORE_TYPE_H_

#include "CGAL/Exact_predicates_inexact_constructions_kernel.h"
#include "CGAL/Polygon_2.h"
#include "CGAL/Point_2.h"
#include "CGAL/Line_2.h"
#include "CGAL/Segment_2.h"

namespace reap {

using Kernel = CGAL::Exact_predicates_inexact_constructions_kernel;
using Polygon = CGAL::Polygon_2<Kernel>;
using Point = CGAL::Point_2<Kernel>;
using Line = CGAL::Line_2<Kernel>;
using Segment = CGAL::Segment_2<Kernel>;

}  // namespace reap

#endif  // REAP_CORE_TYPE_H_
