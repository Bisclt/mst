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
using dis_edge_pair = std::pair<double, SimpleEdge>;

struct cmp_dis_edge_pair {
  bool operator()(dis_edge_pair a, dis_edge_pair b) {
    if (a.first != b.first)
      return a.first < b.first;
    else
      return a.second.idx1() < b.second.idx2();
  }
};

class Graph {
 private:
  // std::vector<SimpleEdge> edges_;

  // a container of all the points in the graph
  std::vector<SimplePoint> points_;

  // the number of all the points in the graph
  int num_of_points_{};

  // check if two points have already been connected, used for prim algorithm,
  // and check if a given constraint is legal
  UnionFind uf_;

  // a container of given constraints of a graph
  std::vector<std::pair<int, int>> constraints_;

  // a containter of all edges (include both given constraints and edges of the
  // triangulation generated)
  std::priority_queue<dis_edge_pair, std::vector<dis_edge_pair>,
                      cmp_dis_edge_pair>
      edges_;

  // connect point idx1 and idx2, idx1 and idx2 should not be equal
  void make_edge(int idx1, int idx2);

  // make constraints between two points, idx1 and idx2 should not be equal
  void make_constraint(int idx1, int idx2);

  // calculate the distance between two
  // points, with their indexes already known
  double distance_between(int idx1, int idx2) const;

  // draw a line between two points using opencv
  void draw_single_line(cv::Mat img, cv::Point2d start, cv::Point2d end,
                        std::string color);

 public:
  Graph() {}
  ~Graph() {}

  // initialize the graph from information in the file <file_name>, which must
  // be in the same directory as main.cpp
  void generate_points_and_constraints_from_file(const std::string& file_name);

  // Randomly generate num points in a square of size, to keep
  // points not too close, size must be not smaller than 100;
  // num must not be large than 10000.
  void random_generate_points(int num = 100, double size = 1000.0);

  // Randomly generate num constraints, the number of constraints
  // should not be more than square root of the number of points.
  void random_generate_constraints(int num = 1);

  void do_constrained_delaunay_triangulation();

  // // A test function, output the edges in ascii format to terminal
  // void output_edge();

  // Draw Points and Edges using opencv
  void draw();
};

#endif