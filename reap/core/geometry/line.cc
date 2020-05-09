/* Copyright 2020 The REAP Authors. All Rights Reserved. */

#include "line.h"

namespace reap {

Line::Line(const GVector &start, const GVector &end)
  : start_point_(start), end_point_(end) {
}

Line::~Line() {
}

Status Line::Move(const GVector &offset) {
  start_point_ += offset;
  end_point_ += offset;
  return Status::OK();
}

Status Line::Rotate(double angle, const GVector &center) {
  start_point_.Rotate(angle, center);
  end_point_.Rotate(angle, center);
  return Status::OK();
}



}  // namespace reap