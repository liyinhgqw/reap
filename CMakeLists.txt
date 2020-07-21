cmake_minimum_required(VERSION 3.16)
project(reap)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)
include_directories(bazel-out/darwin-opt/bin)
include_directories(bazel-reap/external/cgal)

add_executable(reap
        LICENSE
        README.md
        WORKSPACE
        reap/core/geometry/math.cc
        reap/core/geometry/math.h
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
        reap/core/serializer.cc
        reap/core/serializer.h
        reap/core/status.cc
        reap/core/status.h
        reap/plan/area_bound.cc
        reap/plan/area_bound.h reap/plan/graph_util.cc reap/plan/graph_util.h reap/test/test_cgal.cc reap/core/type.h reap/core/geometry/geometry.h reap/core/geometry/geometry.cc reap/plan/plan.cc reap/plan/plan.h reap/plan/arrangement.h reap/test/test_arrangement.cc reap/plan/plan_config.h reap/core/geometry/math.cc reap/core/geometry/math.h)
