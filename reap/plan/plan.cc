/* Copyright 2020 The REAP Authors. All Rights Reserved. */

#include "reap/plan/plan.h"

namespace reap {

namespace {

constexpr double kEps = 1e-6;

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

void Plan::ArrangeRow(Arrangement *arrangement, double min_x, double max_x) {
  auto polygon = area_bound_.polygon();

  // calculate bound
  auto max_y = polygon.top_vertex()->y();
  auto min_y = polygon.bottom_vertex()->y();
  max_x = std::min(max_x, polygon.right_vertex()->x());
  min_x = std::max(min_x, polygon.left_vertex()->x());

  auto row_config = arrangement->config();
  double building_height = row_config.floor_height * row_config.num_of_floors;
  double building_dist = row_config.spacing_ratio * building_height + row_config.building_width;
  double first_row_offset = row_config.first_row_offset;

  for (double y = max_y - first_row_offset; y > min_y + row_config.building_width; y -= building_dist) {
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
            double left = std::max(min_x, last_point->x());
            double right = std::min(max_x, p->x());
            if (right - left > kEps) {
              InsertSegment(row_arrangement, Segment(Point(left, y), Point(right, y)));
            }
          }
        }
        last_point = p;
      }
    }

    arrangement->row_arrangement().push_back(row_arrangement);
  }
}

void Plan::SelectRow(Arrangement *arrangement, double min_x, double max_x) {
  std::vector<Arrangement> arrangements;

  for (int num_of_floors = 1; num_of_floors <= 18; ++num_of_floors) {
    double dist = config_.spacing_ratio * (config_.building_width + num_of_floors * config_.floor_height);
    for (double first_row_offset = 0.0; first_row_offset < dist; first_row_offset += 1.0) {
      PlanConfig plan_config {
          .num_of_floors = num_of_floors,
          .floor_height = config_.floor_height,
          .building_width = config_.building_width,
          .spacing_ratio = config_.spacing_ratio,
          .first_row_offset = first_row_offset,
          .num_of_columns = config_.num_of_columns,
      };
      Arrangement arr(plan_config);
      ArrangeRow(&arr, min_x, max_x);
      arrangements.push_back(arr);
    }
  }

  std::sort(arrangements.begin(), arrangements.end());
  *arrangement = arrangements[0];
}

void Plan::ArrangeColumn(ColumnArrangement *columns) {
  auto polygon = area_bound_.polygon();
  std::vector<double> xs;
  for (auto it = polygon.vertices_begin(); it != polygon.vertices_end(); it++) {
    auto point = *it;
    xs.push_back(point.x());
  }
  sort(xs.begin(), xs.end());

  if (xs.size() < 2) return;
  int cols = config_.num_of_columns;
  double total_width = xs.back() - xs[0];
  double avg_col_len = total_width / cols;

  std::vector<std::pair<double, double>> col_segs;
  double last = xs[0];

  for (std::size_t i = 1; i < xs.size(); ++i) {
    double dx = xs[i] - last;
    if (dx >= avg_col_len) {
      col_segs.emplace_back(last, xs[i]);
      last = xs[i];
    } else if (i + 1 == xs.size()) {
      if (col_segs.empty()) {
        col_segs.emplace_back(last, xs[i]);
      } else {
        col_segs.back().second = xs[i];
      }
    }
  }

  for (auto &s : col_segs) {
    Arrangement arrangement;
    SelectRow(&arrangement, s.first, s.second);
    columns->AddColumn(arrangement);
  }
}

}  // namespace reap