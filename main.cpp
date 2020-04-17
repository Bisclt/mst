#include <iostream>

#include "Graph.h"

int main() {
  Graph graph{};
  // graph.generate_points_and_constraints_from_file("data.in");
  graph.random_generate_points(100, 1000);
  // graph.random_generate_constraints();
  graph.do_constrained_delaunay_triangulation();
  graph.draw();
  return 0;
}