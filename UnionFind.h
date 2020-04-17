#ifndef _UNION_FIND_H_
#define _UNION_FIND_H_

#include <vector>

class UnionFind {
 private:
  int num_{};
  std::vector<int> parent_;

 public:
  UnionFind() = default;  // Default size is 0.
  UnionFind(int num);     // Designate the size of the union-find set.
  void set(int num);      // Designate the size of the union-find set.
  ~UnionFind() = default;
  void union_between(int idx1, int idx2);
  int find(int idx);
  bool unioned(int idx1, int idx2) const;
  int size() const { return num_; }
};

#endif