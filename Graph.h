#ifndef _GRAPH_H_
#define _GRAPH_H_

#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
const int width = 1000;
#include <queue>
#include <string>
#include <vector>

#include "Edge.h"
#include "Point.h"
#include "UnionFind.h"
using pde = std::pair<double, SimpleEdge>;

struct cmpr {
  bool operator()(pde a, pde b) {
    if (a.first != b.first)
      return a.first < b.first;
    else
      return a.second.idx1() < b.second.idx2();
  }
};

class Graph {
 private:
  // std::vector<SimpleEdge> edges_;
  std::vector<SimplePoint> points_;
  int num_of_points_{};
  UnionFind uf_;  // used for prim algorithm
  std::vector<std::pair<int, int>> constraints_;
  std::priority_queue<pde, std::vector<pde>, cmpr> edges_;

  void make_edge(int idx1, int idx2);
  void make_constraint(int idx1,
                       int idx2);  // Make constraints between two points, idx1
                                   // and idx2 should not be equal.

  double distance_between(
      int idx1,
      int idx2) const;  // calculate the distance between two
                        // points, with their indexes already known
  void draw_single_line(
      cv::Mat img, cv::Point2d start,
      cv::Point2d end);  // draw line between two points using opencv

 public:
  Graph() {}
  ~Graph() {}
  void generate_points_and_constraints_from_file(const std::string& file_name);

  void random_generate_points(
      int num = 100,
      double size =
          100.0);  // Randomly generate num points in a square of size, to keep
                   // points not too close, size must be not smaller than 100;
                   // num must not be large than 10000.

  void random_generate_constraints(
      int num =
          1);  // Randomly generate num constraints, the number of constraints
               // should not be more than square root of the number of points.

  void do_constrained_delaunay_triangulation();

  void output_edge();  // A test function.

  void draw();  // Draw Points and Edges using opencv
};

#endif