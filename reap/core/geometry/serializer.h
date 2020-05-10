/* Copyright 2020 The REAP Authors. All Rights Reserved. */

#ifndef REAP_CORE_GEOMETRY_SERIALIZER_H_
#define REAP_CORE_GEOMETRY_SERIALIZER_H_

#include <google/protobuf/message.h>

#include "reap/proto/reap.pb.h"
#include "reap/core/util//status.h"
#include "reap/core/geometry/shape.h"
#include "reap/core/geometry/gvector.h"

namespace reap {

class ShapeSerializer {
 public:
  ShapeSerializer() {}
  virtual ~ShapeSerializer() {}

  template<typename S, typename T,
      typename std::enable_if<std::is_base_of<
      google::protobuf::Message, T>::value>::type* = nullptr>
  Status Serialize(const S& shape, T *message);

  template<>
  Status Serialize(const Shape& shape, google::protobuf::Message *message);
};

}  // namespace reap


std::ostream& operator << (std::ostream& out, const reap::Shape &shape);

#endif  // REAP_CORE_GEOMETRY_SERIALIZER_H_
