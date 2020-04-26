#include "UnionFind.h"

#include <cassert>
#include <iostream>
#include <vector>

UnionFind::UnionFind(int num) : num_(num) {
  for (int i = 0; i < num; ++i) {
    parent_.emplace_back(i);
  }
}

void UnionFind::union_between(int idx1, int idx2) {
  assert(idx1 < size() && idx2 < size());
  parent_[find(idx1)] = find(idx2);
}

int UnionFind::find(int idx) {
  assert(idx < size());
  return (parent_[idx] == idx ? idx : parent_[idx] = find(parent_[idx]));
}

bool UnionFind::unioned(int idx1, int idx2) {
  assert(idx1 < size() && idx2 < size());
  return find(idx1) == find(idx2);
}

void UnionFind::set(int num) {
  num_ = num;
  parent_.clear();
  for (int i = 0; i < num; ++i) {
    parent_.emplace_back(i);
  }
}

void UnionFind::clean() {
  for (int i = 0; i < size(); ++i) {
    parent_[i] = i;
  }
}