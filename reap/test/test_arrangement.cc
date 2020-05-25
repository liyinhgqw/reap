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

  double floor_height = 3.0;
  double building_width = 15.0;
  double spacing_ratio = 1.6;

  std::vector<Arrangement> arrangements;

  for (int num_of_floors = 1; num_of_floors <= 18; ++num_of_floors) {
    double dist = spacing_ratio * (building_width + num_of_floors * floor_height);
    for (double first_row_offset = 0.0; first_row_offset < dist; first_row_offset += 1.0) {
      PlanConfig plan_config {
          .num_of_floors = num_of_floors,
          .floor_height = floor_height,
          .building_width = building_width,
          .spacing_ratio = spacing_ratio,
          .first_row_offset = first_row_offset,
      };
      Plan plan(plan_config, area_bound);
      Arrangement arrangement(plan_config);
      plan.arrange(&arrangement);
      arrangements.push_back(arrangement);
    }
  }

  std::sort(arrangements.begin(), arrangements.end());

  Arrangement &best_arrangement = arrangements[0];
  std::cout << best_arrangement.plan_config().num_of_floors << " " << best_arrangement.plan_config().first_row_offset << std::endl;
  ArrangementToGraph(best_arrangement, &graph);


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

