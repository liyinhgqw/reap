/* Copyright 2020 The REAP Authors. All Rights Reserved. */

#ifndef REAP_CORE_GEOMETRY_GEOMETRY_H_
#define REAP_CORE_GEOMETRY_GEOMETRY_H_

#include <cmath>
#include <vector>

#include "reap/core/type.h"

namespace reap {

constexpr double kMaxHorizontalAngle = 10 * M_PI / 180.0;
constexpr double kMinHorizontalLength = 15;

bool IsHorizontal(const Segment &s,
                  double max_angle = kMaxHorizontalAngle,
                  double min_len = kMinHorizontalLength);

void FilterHorizontalSegments(const std::vector<Segment> &segments,
                              std::vector<Segment> *output,
                              double max_angle = kMaxHorizontalAngle,
                              double min_len = kMinHorizontalLength);

void CalculateBounds(const std::vector<Point> &points,
                     double *min_x, double *max_x,
                     double *min_y, double *max_y);

}  // namespace reap

#endif  // REAP_CORE_GEOMETRY_GEOMETRY_H_
