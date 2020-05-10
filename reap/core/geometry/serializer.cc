/* Copyright 2020 The REAP Authors. All Rights Reserved. */

#include "reap/core/geometry/serializer.h"

#include "reap/core/geometry/point.h"
#include "reap/core/geometry/line.h"
#include "reap/core/geometry/polygon.h"

namespace reap {

template<>
Status ShapeSerializer::Serialize(const Point &shape, GPoint *message) {
  message->add_pos(shape.x());
  message->add_pos(shape.y());
  message->add_pos(shape.z());
  return Status::OK();
}

template<>
Status ShapeSerializer::Serialize(const Line &shape, GLine *message) {
  auto start_point = message->mutable_start_point();
  start_point->add_pos(shape.start_point().x());
  start_point->add_pos(shape.start_point().y());
  start_point->add_pos(shape.start_point().z());

  auto end_point = message->mutable_end_point();
  end_point->add_pos(shape.end_point().x());
  end_point->add_pos(shape.end_point().y());
  end_point->add_pos(shape.end_point().z());

  return Status::OK();
}

template<>
Status ShapeSerializer::Serialize(const Polygon &shape, GPolygon *message) {
  for (auto &v : shape.points()) {
    auto point = message->add_point();
    point->add_pos(v.x());
    point->add_pos(v.y());
    point->add_pos(v.z());
  }
  return Status::OK();
}

#define SERIALIZE(Shape, GShape)                                   \
  if (dynamic_cast<const Shape*>(&shape)) {                        \
    Serialize<Shape, GShape>(*dynamic_cast<const Shape*>(&shape),  \
      dynamic_cast<GShape*>(message));                             \
  }

template<>
Status ShapeSerializer::Serialize(const Shape &shape,
    google::protobuf::Message *message) {
  SERIALIZE(Point, GPoint);
  SERIALIZE(Line, GLine);
  SERIALIZE(Polygon, GPolygon);
  return Status::OK();
}

#undef SERIALIZE

}  // namespace reap

#define OUTPUT(Shape, GShape)                                         \
  if (dynamic_cast<const reap::Shape*>(&shape)) {                     \
    reap::GShape gshape;                                              \
    serializer.Serialize<reap::Shape, reap::GShape>(                  \
      *dynamic_cast<const reap::Shape*>(&shape),                      \
      &gshape);                                                       \
    out << #Shape << " (" << std::endl;                               \
    out << gshape.DebugString();                                      \
    out << ")" << std::endl;                                          \
  }

std::ostream& operator << (std::ostream& out, const reap::Shape &shape) {
  reap::ShapeSerializer serializer;
  OUTPUT(Point, GPoint);
  OUTPUT(Line, GLine);
  OUTPUT(Polygon, GPolygon);
  return out;
}

#undef OUTPUT
