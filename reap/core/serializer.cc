/* Copyright 2020 The REAP Authors. All Rights Reserved. */

#include "reap/core/serializer.h"

namespace reap {

Status ShapeSerializer::Serialize(const Point &point, GPoint *message) {
  message->add_pos(point.x());
  message->add_pos(point.y());
  return Status::OK();
}

Status ShapeSerializer::Serialize(const Segment &segment, GLine *message) {
  auto start_point = message->mutable_start_point();
  auto end_point = message->mutable_end_point();
  start_point->add_pos(segment.min().x());
  start_point->add_pos(segment.min().y());
  end_point->add_pos(segment.max().x());
  end_point->add_pos(segment.max().y());
  return Status::OK();
}

Status ShapeSerializer::Serialize(const Polygon &polygon, GPolygon *message) {
  for (std::size_t i = 0; i < polygon.size(); ++i) {
    auto p = message->add_point();
    Serialize(polygon[i], p);
  }
  return Status::OK();
}

}  // namespace reap