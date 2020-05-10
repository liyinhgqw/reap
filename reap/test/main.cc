/* Copyright 2020 The REAP Authors. All Rights Reserved. */

#include <google/protobuf/text_format.h>
#include <google/protobuf/message.h>

#include <iostream>
#include <fstream>
#include <string>

#include "reap/plan/area_bound.h"
#include "reap/plan/graph_util.h"

using namespace reap;  // NOLINT(build/namespaces)
using namespace std;  // NOLINT(build/namespaces)

int main() {
  Polygon polygon({
    GVector(0, 0, 0),
    GVector(0, 1, 0),
    GVector(1, 1, 0),
    GVector(1, 0, 0),
  });
  AreaBound area_bound(std::move(polygon), 0.0);

  Graph graph;
  AreaBoundToGraph(area_bound, &graph);
  std::string out;
  google::protobuf::TextFormat::PrintToString(graph, &out);
  cout << out << endl;

  fstream output("area_bound.pb", ios::out | ios::trunc | ios::binary);
  if (!graph.SerializeToOstream(&output)) {
    cerr << "Failed to write graph." << endl;
    return -1;
  }

  return 0;
}

