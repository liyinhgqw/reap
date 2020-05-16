/* Copyright 2020 The REAP Authors. All Rights Reserved. */

#ifndef REAP_CORE_GEOMETRY_SERIALIZER_H_
#define REAP_CORE_GEOMETRY_SERIALIZER_H_

#include <google/protobuf/message.h>

#include "reap/proto/geometry.pb.h"
#include "status.h"
#include "reap/core/type.h"

namespace reap {

class ShapeSerializer {
 public:
  ShapeSerializer() {}
  virtual ~ShapeSerializer() {}

  Status Serialize(const Polygon &polygon, GPolygon *message);
  Status Serialize(const Point &point, GPoint *message);
};

}  // namespace reap

#endif  // REAP_CORE_GEOMETRY_SERIALIZER_H_
