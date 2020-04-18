#include <iostream>

#include "Graph.h"

int main() {
  Graph graph{};

  // graph.generate_points_and_constraints_from_file("data.in");

  // randomly generate 100 points in a square of size 1000
  graph.random_generate_points();

  // graph.random_generate_constraints();

  // generate a triangulation based on the points and constraints
  graph.do_constrained_delaunay_triangulation();

  // draw the result in a new window
  graph.draw();
  return 0;
}