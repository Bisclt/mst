#include <CGAL/Constrained_Delaunay_triangulation_2.h>
#include <CGAL/Constrained_triangulation_2.h>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Polygon_2.h>
#include <CGAL/Triangulation_face_base_with_info_2.h>
#include <CGAL/Triangulation_vertex_base_with_id_2.h>

#include <cassert>
#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/opencv.hpp>

#include "CGAL/exceptions.h"
typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef CGAL::Triangulation_vertex_base_with_id_2<K> Vb;
typedef CGAL::Constrained_triangulation_face_base_2<K> Fb;
typedef CGAL::Triangulation_data_structure_2<Vb, Fb> TDS;
typedef CGAL::Exact_predicates_tag Itag;
typedef CGAL::Constrained_Delaunay_triangulation_2<K, TDS, Itag> CDT;
typedef CDT::Face_iterator Face_iterator;
typedef CDT::Vertex_handle Vertex_handle;

CDT cdt;

struct Point {
  double x, y;
} point[10000];

void draw_single_line(cv::Mat img, cv::Point2d start, cv::Point2d end) {
  // width of line
  int thickness = 1;

  // type of line
  int lineType = cv::LineTypes::LINE_8;

  // draw a white line between start and end
  cv::line(img, start, end, cv::Scalar(255, 255, 255), thickness, lineType);
}

void draw() {
  cv::Mat image = cv::Mat::zeros(1000, 1000, CV_8UC3);
  for (auto e_iter = cdt.finite_edges_begin(); e_iter != cdt.finite_edges_end();
       e_iter++) {
    CDT::Vertex_handle f_v1 = e_iter->first->vertex(cdt.cw(e_iter->second));
    CDT::Vertex_handle f_v2 = e_iter->first->vertex(cdt.ccw(e_iter->second));
    double id1x = f_v1->point().x(), id1y = f_v1->point().y();
    double id2x = f_v2->point().x(), id2y = f_v2->point().y();
    // draw a single line between p1 and p2
    draw_single_line(image, cv::Point(id1x, id1y), cv::Point(id2x, id2y));
  }

  // output the result graph in a new window
  cv::imshow("Constrained Triangulation", image);

  cv::waitKey(0);
}

using namespace std;

int main(int argc, char** argv) {
  fstream fin("data.in");
  int n;
  fin >> n;
  for (int i = 0; i < n; i++) {
    fin >> point[i].x >> point[i].y;
    cdt.insert(CDT::Point(point[i].x, point[i].y));
  }
  draw();
  return 0;
}