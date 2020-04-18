#ifndef _EDGE_H_
#define _EDGE_H_

#include "Point.h"

class SimpleEdge {
  // Class SimpleEdge, contains two indexes idx1_ and idx2_, as a helper class
  // of class Graph, indicates a singel edge between two points with index idx1_
  // and idx2_

 private:
  int idx1_, idx2_;

 public:
  // a SimpleEdge is always initialized with two indexes
  SimpleEdge() = delete;
  SimpleEdge(int idx1, int idx2) : idx1_(idx1), idx2_(idx2) {}
  ~SimpleEdge() = default;

  // return the stored indexes
  int idx1() const { return idx1_; }
  int idx2() const { return idx2_; }
};

#endif
