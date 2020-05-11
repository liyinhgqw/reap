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
                      {292445.044, 518199.625},
                      {292525.210, 518174.922},
                      {292536.248, 518192.449},
                      {292563.960, 518183.910},
                      {292660.138, 518336.639},
                      {292626.798, 518406.245},
                      {292513.509, 518419.395},
                      {292495.159, 518410.624},
                      {292415.096, 518283.430},
                      {292484.376, 518262.082},
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

