#include "MST.h"

#include <iostream>

void MST::generate_mst_from_cdt() {
  uf_.clean();

  for (int i = 0; i < constraints_.size(); ++i) {
    make_mst_edge(constraints_[i].first, constraints_[i].second);
  }
  while (!edges_.empty()) {
    double len = edges_.top().first;
    int idx1 = edges_.top().second.idx1();
    int idx2 = edges_.top().second.idx2();
    edges_.pop();
    if (unioned(idx1, idx2)) continue;
    make_mst_edge(idx1, idx2);
  }
}

void MST::make_mst_edge(int idx1, int idx2) {
  mst_edges_.emplace_back(idx1, idx2);
  uf_.union_between(idx1, idx2);
}

void MST::draw() {
  cv::Mat image = cv::Mat::zeros(width, width, CV_8UC3);
  for (auto& e : mst_edges_) {
    SimplePoint p1 = points_[e.idx1()];
    SimplePoint p2 = points_[e.idx2()];
    double x1 = p1.x(), y1 = p1.y(), x2 = p2.x(), y2 = p2.y();

    // draw a single white line between p1 and p2
    draw_single_line(image, cv::Point(x1, y1), cv::Point(x2, y2), "white");
  }

  for (int i = 0; i < constraints_.size(); ++i) {
    SimplePoint p1 = points_[constraints_[i].first];
    SimplePoint p2 = points_[constraints_[i].second];
    double x1 = p1.x(), y1 = p1.y(), x2 = p2.x(), y2 = p2.y();

    // draw a single blue line between two constrained points
    draw_single_line(image, cv::Point(x1, y1), cv::Point(x2, y2), "blue");
  }

  // output the result graph in a new window
  cv::imshow("Constrained Triangulation", image);

  cv::waitKey(0);
}