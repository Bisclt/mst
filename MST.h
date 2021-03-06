#ifndef _MST_H_
#define _MST_H_

#include <vector>

#include "Graph.h"

class MST : public Graph {
 protected:
  std::vector<SimpleEdge> mst_edges_;
  double total_length_{};

 public:
  // based on the constrained delaunay triangulation, using kruskal algorithm to
  // calculate the desired MST with constraints. ATTENTION: this function will
  // remove everything stored in the edges_ vector
  void generate_mst_from_edges();

  // generate the MST using BRUTE FORCE
  void generate_mst_brute_force();

  // draw the final MST using opencv
  void draw();

  // return the total length of the generated MST
  double total_length() const { return total_length_; }

  // add edge into mst_edges_
  void make_mst_edge(int idx1, int idx2);
};

#endif  //_MST_H_