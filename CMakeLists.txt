cmake_minimum_required(VERSION 3.16)
project(reap)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(reap
        LICENSE
        README.md
        WORKSPACE reap/core/geometry/point_2d.cc reap/core/geometry/point_2d.h reap/core/geometry/gvector.cc reap/core/geometry/gvector.h reap/core/main.cc)
