#include <iostream>

#include "MST.h"

int main() {
  MST mst{};

  // graph.generate_points_and_constraints_from_file("data.in");

  // randomly generate 100 points in a square of size 1000
  mst.random_generate_points();

  mst.random_generate_constraints();

  // generate a triangulation based on the points and constraints
  mst.do_constrained_delaunay_triangulation();

  // generate a mst based on the cdt
  mst.generate_mst_from_cdt();

  // draw the result of delaunay triangulaion in a new window
  mst.draw();
  return 0;
}