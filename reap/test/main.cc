/* Copyright 2020 The REAP Authors. All Rights Reserved. */

#include <google/protobuf/text_format.h>

#include <iostream>
#include <string>

#include "reap/plan/area_bound.h"
#include "reap/plan/graph_util.h"

using namespace reap;  // NOLINT(build/namespaces)

int main() {
  Polygon polygon({
    GVector(1, 2, 0),
  });
  AreaBound area_bound(std::move(polygon), 0.0);

  Graph graph;
  AreaBoundToGraph(area_bound, &graph);
  std::string out;
  google::protobuf::TextFormat::PrintToString(graph, &out);
  std::cout << out << std::endl;

  return 0;
}

