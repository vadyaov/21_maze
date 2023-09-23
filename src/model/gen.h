#ifndef DISJOINT_H_
#define DISJOINT_H_

#include <vector>

namespace maze {
  class DisjointSet {
    public:
      explicit DisjointSet(int size) : parent(size), rank(size, 0) {
        for (int i = 0; i < size; ++i)
          parent[i] = i; // every ceil in its own set
      }

    private:
      std::vector<int> parent;
      std::vector<int> rank;
  };
} // namespace maze

#endif // DISJOINT_H_
