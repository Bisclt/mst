#ifndef _UNION_FIND_H_
#define _UNION_FIND_H_

#include <vector>

class UnionFind {
 private:
  int num_{};
  std::vector<int> parent_;

 public:
  // Default size is 0.
  UnionFind() = default;

  // Designate the size of the union-find set.
  UnionFind(int num);

  // Designate the size of the union-find set.
  void set(int num);

  ~UnionFind() = default;

  // union to points with indexes idx1 and idx2
  void union_between(int idx1, int idx2);

  int find(int idx);

  // chech if point idx1 and idx2 are already connected
  bool unioned(int idx1, int idx2);

  // return the number of all points
  int size() const { return num_; }

  // initialize the uf-set
  void clean();
};

#endif