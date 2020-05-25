/* Copyright 2020 The REAP Authors. All Rights Reserved. */

#include "reap/core/geometry/geometry.h"

namespace reap {

bool IsHorizontal(const Segment &s,
                  double max_angle,
                  double min_len) {
  auto delta = s.max() - s.min();
  return delta.x() >= min_len
      && std::abs(delta.y()) < delta.x() * std::tan(max_angle);
}

void FilterHorizontalSegments(const std::vector<Segment> &segments,
                              std::vector<Segment> *output,
                              double max_angle,
                              double min_len) {
  for (auto &s : segments) {
    if (IsHorizontal(s, max_angle, min_len)) {
      double y = std::min(s[0].y(), s[1].y());
      output->emplace_back(Point(s.min().x(), y), Point(s.max().x(), y));
    }
  }
}

void CalculateBounds(const std::vector<Point> &points,
                     double *min_x, double *max_x,
                     double *min_y, double *max_y) {
  double minx = std::numeric_limits<double>::max();
  double maxx = std::numeric_limits<double>::lowest();
  double miny = std::numeric_limits<double>::max();
  double maxy = std::numeric_limits<double>::lowest();

  for (auto &p : points) {
    minx = std::min(minx, p.x());
    maxx = std::max(maxx, p.x());
    miny = std::min(miny, p.y());
    maxy = std::max(maxy, p.y());
  }

  *min_x = minx;
  *max_x = maxx;
  *min_y = miny;
  *max_y = maxy;
}

}  // namespace reap
