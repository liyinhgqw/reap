/* Copyright 2020 The REAP Authors. All Rights Reserved. */

#include <google/protobuf/text_format.h>
#include <google/protobuf/message.h>

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "reap/plan/area_bound.h"
#include "reap/plan/graph_util.h"

using namespace reap;  // NOLINT(build/namespaces)
using namespace std;  // NOLINT(build/namespaces)

int main() {
  std::vector<Point> points {
                      {518199.625, 292445.044},
                      {518174.922, 292525.210},
                      {518192.449, 292536.248},
                      {518183.910, 292563.960},
                      {518336.639, 292660.138},
                      {518406.245, 292626.798},
                      {518419.395, 292513.509},
                      {518410.624, 292495.159},
                      {518283.430, 292415.096},
                      {518262.082, 292484.376},
  };
  Polygon polygon(points.begin(), points.end());
  AreaBound area_bound(std::move(polygon), 0.0);

  Graph graph;
  AreaBoundToGraph(area_bound, &graph);

  fstream output("area_bound.pb", ios::out | ios::trunc | ios::binary);
  if (!graph.SerializeToOstream(&output)) {
    cerr << "Failed to write graph." << endl;
    return -1;
  }

  return 0;
}

