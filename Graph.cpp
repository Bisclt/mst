#include "Graph.h"

#include <cassert>
#include <ctime>  //time(nullptr)
#include <fstream>
#include <iostream>  //cout
#include <string>
#include <vector>

#include "Edge.h"
#include "Point.h"

/*======================CGAL header files======================*/

#include <CGAL/Constrained_triangulation_2.h>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Triangulation_face_base_with_info_2.h>
#include <CGAL/Triangulation_vertex_base_with_id_2.h>

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef CGAL::Triangulation_vertex_base_with_id_2<K> Vb;
typedef CGAL::Constrained_triangulation_face_base_2<K> Fb;
typedef CGAL::Triangulation_data_structure_2<Vb, Fb> TDS;
typedef CGAL::Exact_predicates_tag Itag;
typedef CGAL::Constrained_triangulation_2<K, TDS, Itag> CDT;
typedef CDT::Point Point;
typedef CDT::Face_iterator Face_iterator;
typedef CDT::Vertex_handle Vertex_handle;

/*=============================================================*/

void Graph::generate_points_and_constraints_from_file(
    const std::string& file_name) {
  std::ifstream fin;
  fin.open(file_name);

  // Deal with new points.
  int num_of_points;
  fin >> num_of_points;
  assert(num_of_points <= 10000);
  num_of_points_ = num_of_points;
  uf_.set(num_of_points_);
  for (int i = 0; i < num_of_points; ++i) {
    double x, y;
    fin >> x >> y;
    points_.emplace_back(x, y);
  }

  // Deal with constraints.
  int num_of_constraints;
  fin >> num_of_constraints;
  for (int i = 0; i < num_of_constraints; ++i) {
    int idx1, idx2;
    fin >> idx1 >> idx2;
    assert(!uf_.unioned(idx1, idx2));
    make_constraint(idx1, idx2);
    make_edge(idx1, idx2);
  }
  fin.close();
}

void Graph::random_generate_points(int num, double size) {
  assert(num <= 10000 && size >= 100.0);
  num_of_points_ = num;
  uf_.set(num_of_points_);
  points_.clear();
  srand(time(nullptr));
  for (int i = 0; i < num; ++i) {
    double ld1 = rand() / double(RAND_MAX);
    double ld2 = rand() / double(RAND_MAX);
    points_.emplace_back(ld1 * size, ld2 * size);
  }
}

void Graph::random_generate_constraints(int num) {
  int size = points_.size();
  assert(num * num <= size);
  srand(time(nullptr));
  for (int i = 0; i < num; ++i) {
    int idx1, idx2;
    do {
      idx1 = rand() % size;
      idx2 = rand() % size;
    } while (uf_.unioned(idx1, idx2));
    make_constraint(idx1, idx2);
    make_edge(idx1, idx2);
  }
}

void Graph::make_constraint(int idx1, int idx2) {
  uf_.union_between(idx1, idx2);
  constraints_.emplace_back(idx1, idx2);
}

void Graph::make_edge(int idx1, int idx2) {
  uf_.union_between(idx1, idx2);
  edges_.emplace(distance_between(idx1, idx2), SimpleEdge(idx1, idx2));
  // edges_.emplace_back(SimpleEdge(idx1, idx2));
}

double Graph::distance_between(int idx1, int idx2) const {
  return (points_[idx1].x() - points_[idx2].x()) *
             (points_[idx1].x() - points_[idx2].x()) +
         (points_[idx1].y() - points_[idx2].y()) *
             (points_[idx1].y() - points_[idx2].y());
}

void Graph::do_constrained_delaunay_triangulation() {
  CDT cdt;

  // int nop = num_of_points_;
  // std::cout << "There are " << nop << " points.\n";
  for (int i = 0; i < num_of_points_; ++i) {
    double x = points_[i].x();
    double y = points_[i].y();
    cdt.insert(Point(x, y));
  }

  // int noc = constraints_.size();
  // std::cout << "There are " << noc << " constraints.\n";
  for (int i = 0; i < constraints_.size(); ++i) {
    double x1 = points_[constraints_[i].first].x();
    double y1 = points_[constraints_[i].first].y();
    double x2 = points_[constraints_[i].second].x();
    double y2 = points_[constraints_[i].second].y();
    cdt.insert_constraint(Point(x1, y1), Point(x2, y2));
  }

  // Initialize the indexes of points.
  int idx = 0;
  for (CDT::Vertex_iterator v = cdt.vertices_begin(); v != cdt.vertices_end();
       ++v) {
    Vertex_handle vv = v->handle();
    vv->id() = idx;
    idx++;
  }

  // CGAL does the triangulation.
  for (auto e_iter = cdt.finite_edges_begin(); e_iter != cdt.finite_edges_end();
       e_iter++) {
    CDT::Vertex_handle f_v1 = e_iter->first->vertex(cdt.cw(e_iter->second));
    CDT::Vertex_handle f_v2 = e_iter->first->vertex(cdt.ccw(e_iter->second));

    Point p1 = f_v1->point();
    Point p2 = f_v2->point();

    int i1 = e_iter->first->vertex(cdt.cw(e_iter->second))->id();
    int i2 = e_iter->first->vertex(cdt.ccw(e_iter->second))->id();

    // std::cout << i1 << " " << i2 << std::endl;

    // std::cout << "(" << p1.x() << "," << p1.y() << ")"
    //           << " ";
    // std::cout << "(" << p2.x() << "," << p2.y() << ")" << std::endl;

    make_edge(i1, i2);
  }
}

void Graph::output_edge() {
  while (!edges_.empty()) {
    SimplePoint p1 = points_[edges_.top().second.idx1()];
    SimplePoint p2 = points_[edges_.top().second.idx2()];
    std::cout << "(" << p1.x() << ", " << p1.y() << ") --- (" << p2.x() << ", "
              << p2.y() << ")\n";
    edges_.pop();
  }
}

void Graph::draw() {
  cv::Mat image = cv::Mat::zeros(width, width, CV_8UC3);
  while (!edges_.empty()) {
    SimplePoint p1 = points_[edges_.top().second.idx1()];
    SimplePoint p2 = points_[edges_.top().second.idx2()];
    double x1 = p1.x(), y1 = p1.y(), x2 = p2.x(), y2 = p2.y();
    std::cout << "(" << x1 << ", " << y1 << ") --- (" << x2 << ", " << y2
              << ")\n";

    // draw a single line between p1 and p2
    draw_single_line(image, cv::Point(x1, y1), cv::Point(x2, y2));
    edges_.pop();
  }

  // output the result graph in a new window
  cv::imshow("Constrained Triangulation", image);

  cv::waitKey(0);
}

void Graph::draw_single_line(cv::Mat img, cv::Point2d start, cv::Point2d end) {
  // width of line
  int thickness = 1;

  // type of line
  int lineType = cv::LineTypes::LINE_8;

  // draw a white line between start and end
  cv::line(img, start, end, cv::Scalar(255, 255, 255), thickness, lineType);
}