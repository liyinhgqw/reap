/* Copyright 2020 The REAP Authors. All Rights Reserved. */

#include "reap/plan/plan.h"

namespace reap {

namespace {

double GetLeftXOfSegmentOrPoint(const CGAL::cpp11::result_of<Intersect(Segment, Line)>::type& shape) {
  if (const Segment* s = boost::get<Segment>(&*shape)) {
    return s->min().x();
  } else {
    const Point* p = boost::get<Point>(&*shape);
    return p->x();
  }
}

void InsertSegment(RowArrangement &row_arrangement, const Segment &s) {
  if (!row_arrangement.segments.empty()) {
    auto last = row_arrangement.segments.back();
    if (last.max().x() >= s.min().x()) {
      // can merge segments
      row_arrangement.segments.pop_back();
      row_arrangement.segments.emplace_back(last.min(), s.max());
    } else {
      row_arrangement.segments.push_back(s);
    }
  } else {
    row_arrangement.segments.push_back(s);
  }
}

}  // namespace

void Plan::arrange(Arrangement *arrangement) {
  // rotate area to align with main direction
  auto normalized_area_bound = area_bound_.Rotate();
  auto polygon = normalized_area_bound.polygon();

  // calculate bound
  auto max_y = polygon.top_vertex()->y();
  auto min_y = polygon.bottom_vertex()->y();
//  auto max_x = polygon.right_vertex()->x();
//  auto min_x = polygon.left_vertex()->x();

  double building_height = config_.floor_height * config_.num_of_floors;
  double building_dist = config_.spacing_ratio * building_height + config_.building_width;
  double first_row_offset = config_.first_row_offset;

  for (double y = max_y - first_row_offset; y > min_y + config_.building_width; y -= building_dist) {
    RowArrangement row_arrangement;

    auto y_line = Line(0, 1, -y);  // y = y0;
    std::vector<CGAL::cpp11::result_of<Intersect(Segment, Line)>::type> intersects;
    // calculate the intersections of y_line and the polygon, could be set of points and segments
    for (auto it_edge = polygon.edges_begin(); it_edge != polygon.edges_end(); it_edge++) {
      auto edge = *it_edge;
      auto intersect = CGAL::intersection(edge, y_line);
      if (intersect) {
        intersects.push_back(intersect);
      }
    }
    // sort the intersections according to the left most vertex
    std::sort(intersects.begin(), intersects.end(), [&](auto &lhs, auto &rhs) {
      return GetLeftXOfSegmentOrPoint(lhs) < GetLeftXOfSegmentOrPoint(rhs);
    });
    const Point *last_point = nullptr;

    // arrange for a row
    for (auto &intersect: intersects) {
      if (const Segment* s = boost::get<Segment>(&*intersect)) {
        InsertSegment(row_arrangement, *s);
      } else {
        const Point* p = boost::get<Point>(&*intersect);
        if (last_point) {
          Point mid_point((p->x() + last_point->x()) / 2.0, (p->y() + last_point->y()) / 2.0);
          if (polygon.bounded_side(mid_point) == CGAL::ON_BOUNDED_SIDE) {
            InsertSegment(row_arrangement, Segment(*last_point, *p));
          }
        }
        last_point = p;
      }
    }

    arrangement->row_arrangement().push_back(row_arrangement);
  }
}

}  // namespace reap