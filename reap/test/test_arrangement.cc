/* Copyright 2020 The REAP Authors. All Rights Reserved. */

#include <google/protobuf/text_format.h>
#include <google/protobuf/message.h>

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

#include "reap/plan/area_bound.h"
#include "reap/plan/arrangement.h"
#include "reap/plan/graph_util.h"
#include "reap/plan/plan.h"

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
  AreaBound area_bound(polygon, -30.0 * M_PI / 180.0);
  auto rotated_area_bound = area_bound.Rotate();

  Graph graph;
  AreaBoundToGraph(rotated_area_bound, &graph);

  PlanConfig plan_config {
      .num_of_floors = 0,
      .floor_height = 3.0,
      .building_width = 15.0,
      .spacing_ratio = 1.6,
      .first_row_offset = 0,
      .num_of_columns = 5,
  };

  Plan plan(plan_config, rotated_area_bound);
  ColumnArrangement col_arrangement;
  plan.ArrangeColumn(&col_arrangement);

  ColumnArrangementToGraph(col_arrangement, &graph);



//  std::string s;
//  google::protobuf::TextFormat::PrintToString(graph, &s);
//  std::cout << s << std::endl;

  fstream output("area_bound.pb", ios::out | ios::trunc | ios::binary);
  if (!graph.SerializeToOstream(&output)) {
    cerr << "Failed to write graph." << endl;
    return -1;
  }

  return 0;
}

