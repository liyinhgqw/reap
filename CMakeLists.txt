cmake_minimum_required(VERSION 3.16)
project(reap)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)
include_directories(bazel-out/darwin-opt/bin)

add_executable(reap
        LICENSE
        README.md
        WORKSPACE
        reap/core/geometry/point.cc
        reap/core/geometry/point.h
        reap/core/geometry/gvector.cc
        reap/core/geometry/gvector.h
        reap/test/draw_area_bound.cc
        reap/core/geometry/line.cc
        reap/core/geometry/line.h
        reap/core/geometry/polygon.cc
        reap/core/geometry/polygon.h
        reap/core/geometry/shape.cc
        reap/core/geometry/shape.h
        reap/core/geometry/serializer.cc
        reap/core/geometry/serializer.h
        reap/core/util/status.cc
        reap/core/util/status.h
        reap/core/util/error.h
        reap/plan/area_bound.cc
        reap/plan/area_bound.h reap/plan/graph_util.cc reap/plan/graph_util.h)
