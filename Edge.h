#ifndef _EDGE_H_
#define _EDGE_H_

#include "Point.h"

class SimpleEdge {
 private:
  int idx1_, idx2_;

 public:
  SimpleEdge() = delete;
  SimpleEdge(int idx1, int idx2) : idx1_(idx1), idx2_(idx2) {}
  ~SimpleEdge() = default;
  bool operator<(SimpleEdge& rhs) {
    if (idx1_ != rhs.idx1_)
      return idx1_ < rhs.idx1_;
    else
      return idx2_ < rhs.idx2_;
  }
  int idx1() const { return idx1_; }
  int idx2() const { return idx2_; }
};

#endif
