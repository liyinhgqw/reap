/* Copyright 2020 The REAP Authors. All Rights Reserved. */

#include "reap/plan/outline_mesh_plan.h"

namespace reap {

namespace {

constexpr double kEps = 1e-6;

double GetLeftXOfSegmentOrPoint(const CGAL::cpp11::result_of<Intersect(Segment, Line)>::type &shape) {
  if (const Segment *s = boost::get<Segment>(&*shape)) {
    return s->min().x();
  } else {
    const Point *p = boost::get<Point>(&*shape);
    return p->x();
  }
}

void InsertSegment(const Segment &s, Row *row) {
  if (!row->segments.empty()) {
    auto last = row->segments.back();
    if (last.max().x() >= s.min().x()) {
      // can merge segments
      row->segments.pop_back();
      row->segments.emplace_back(last.min(), s.max());
    } else {
      row->segments.push_back(s);
    }
  } else {
    row->segments.push_back(s);
  }
}

void CalRow(const Polygon &polygon, double y, double min_x, double max_x, Row *row) {
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
    if (const Segment *s = boost::get<Segment>(&*intersect)) {
      InsertSegment(*s, row);
    } else {
      const Point *p = boost::get<Point>(&*intersect);
      if (last_point) {
        Point mid_point((p->x() + last_point->x()) / 2.0, (p->y() + last_point->y()) / 2.0);
        if (polygon.bounded_side(mid_point) == CGAL::ON_BOUNDED_SIDE) {
          double left = std::max(min_x, last_point->x());
          double right = std::min(max_x, p->x());
          if (right - left > kEps) {
            InsertSegment(Segment(Point(left, y), Point(right, y)), row);
          }
        }
      }
      last_point = p;
    }
  }
}

void IntersectRow(const Row &r1, const Row &r2, Row *r) {
  // assume segments have already been sorted by x-axis
  if (r1.segments.empty() || r2.segments.empty()) return;
  double y = r1.segments[0][0].y();
  std::size_t s1 = r1.segments.size();
  std::size_t s2 = r2.segments.size();
  std::size_t p1 = 0, p2 = 0;
  while (p1 < s1 && p2 < s2) {
    double left1 = std::min(r1.segments[p1][0].x(), r1.segments[p1][1].x());
    double right1 = std::max(r1.segments[p1][0].x(), r1.segments[p1][1].x());
    double left2 = std::min(r2.segments[p2][0].x(), r2.segments[p2][1].x());
    double right2 = std::max(r2.segments[p2][0].x(), r2.segments[p2][1].x());
    double left = std::max(left1, left2);
    double right = std::min(right1, right2);
    if (left < right) {
      r->segments.emplace_back(Point(left, y), Point(right, y));
    }
    if (right1 < right2) {
      ++p1;
    } else {
      ++p2;
    }
  }
}

}  // namespace

void OutlineMeshPlan::Plan(OutlinePlanResult *plan_result) {
  ColumnArrangement arrangement;
  ArrangeColumn(&arrangement);
  for (auto &row_arrangement: arrangement.arrangement()) {
    for (auto &row : row_arrangement.rows()) {
      plan_result->segments.insert(plan_result->segments.end(), row.segments.begin(), row.segments.end());
    }
  }
}

void OutlineMeshPlan::ArrangeRow(double min_x, double max_x, RowArrangement *arrangement) {
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
    Row row_up, row_down, row;
    CalRow(polygon, y, min_x, max_x, &row_up);
    CalRow(polygon, y - row_config.building_width, min_x, max_x, &row_down);
    IntersectRow(row_up, row_down, &row);

    arrangement->rows().push_back(row);
  }
}

void OutlineMeshPlan::ArrangeAndSelectRow(double min_x, double max_x, RowArrangement *arrangement) {
  std::vector<RowArrangement> row_arrangements;

  // params: num_of_floors, first_row_offset
  for (int num_of_floors = 1; num_of_floors <= 18; ++num_of_floors) {
    double dist = config_.spacing_ratio * (config_.building_width + num_of_floors * config_.floor_height);
    for (double first_row_offset = 0.0; first_row_offset < dist; first_row_offset += 1.0) {
      PlanConfig plan_config(config_);
      plan_config.num_of_floors = num_of_floors;
      plan_config.first_row_offset = first_row_offset;
      RowArrangement row_arrangement(plan_config);
      ArrangeRow(min_x, max_x, &row_arrangement);
      row_arrangements.push_back(row_arrangement);
    }
  }

  // find the best row assignment
  std::sort(row_arrangements.begin(), row_arrangements.end());
  *arrangement = row_arrangements[0];
}

void OutlineMeshPlan::ArrangeColumn(ColumnArrangement *columns) {
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

  // make every column to be of len >= avg_len
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
    RowArrangement arrangement;
    ArrangeAndSelectRow(s.first, s.second, &arrangement);
    columns->AddColumn(arrangement);
  }
}

}  // namespace reap