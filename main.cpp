#include <iostream>

#include "MST.h"
#include "timer.h"

int main() {
  srand(time(nullptr));
  Timer timer{};

  std::cout << "Using brute force...\n";

  timer.start();
  for (int i = 0; i < 10; ++i) {
    MST mst{};

    // randomly generate 1000 points in a square of size 2000
    mst.random_generate_points();

    mst.random_generate_constraints();

    mst.generate_mst_brute_force();

    std::cout << "The total length is " << mst.total_length() << ".\n";

    // draw the result of delaunay triangulaion in a new window
    // mst.draw();
  }
  timer.stop();
  std::cout << "Brute force: " << timer.time() << "s\n";
  timer.reset();

  std::cout << "\nBased on constrained delaunay triangulation...\n";
  timer.start();
  for (int i = 0; i < 10; ++i) {
    MST mst{};

    // randomly generate 1000 points in a square of size 2000
    mst.random_generate_points();

    mst.random_generate_constraints();

    // generate a triangulation based on the points and constraints
    mst.do_constrained_delaunay_triangulation();

    // generate a mst based on the cdt
    mst.generate_mst_from_edges();

    std::cout << "The total length is " << mst.total_length() << ".\n";

    // draw the result of delaunay triangulaion in a new window
    // mst.draw();
  }
  timer.stop();
  std::cout << "CDT based: " << timer.time() << "s\n";

  return 0;
}