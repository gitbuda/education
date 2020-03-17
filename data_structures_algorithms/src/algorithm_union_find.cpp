#include <numeric>
#include <vector>

#include "include/using_iostream.hpp"

// NOTE: Work in progress.

// https://stackoverflow.com/questions/39923968/in-c-how-to-initialize-a-vector-with-values-1-2-n-without-a-loop
// https://stackoverflow.com/questions/11965732/set-stdvectorint-to-a-range

/// @tparam T is type of elements.
template <typename T>
class QuickFindUnionFind {
 public:
  QuickFindUnionFind(T n) : id_(n), count_{n} {
    std::iota(std::begin(id_), std::end(id_), 0);
  }
  auto Connected(T p, T q) const { return this->Find(p) == this->Find(q); }
  auto Count() const { return this->count_; }
  auto Find(T p) const { return id_[p]; }
  auto Union(T p, T q) {
    auto pId = this->Find(p);
    auto qId = this->Find(q);
    if (pId == qId) return;
    for (int i = 0; i < id_.size(); i++) {
      // Find all elements where the group id is pId and set them to qId.
      if (id_[i] == pId) {
        id_[i] = qId;
      }
    }
    this->count_--;
  }

 private:
  std::vector<T> id_; // Access to component id (site indexed).
  T count_; // Number of components.
};

template <typename T>
class QuickUnionUnionFind {
 public:
  QuickUnionUnionFind(T n) : id_(n), count_{n} {
    std::iota(std::begin(id_), std::end(id_), 0);
  }
  auto Connected(T p, T q) const { return this->Find(p) == this->Find(q); }
  auto Count() const { return this->count_; }
  auto Find(T p) const {
    while (p != id_[p]) p = id_[p];
    return p;
  }
  auto Union(T p, T q) {
    // Give p and q the same root.
    auto pRoot = this->Find(p);
    auto qRoot = this->Find(q);
    if (pRoot == qRoot) return;
    id_[pRoot] = qRoot;
    count_--;
  }

 private:
  std::vector<T> id_; // Access to component id (site indexed).
  T count_; // Number of components.
};

int main() {
  Println<0>("Quick Find Union Find");
  auto qfuf = QuickFindUnionFind(10);
  qfuf.Union(1,3);
  qfuf.Union(3,4);
  Println<0>(qfuf.Connected(1,4));

  Println<0>("Quick Union Union Find");
  auto quuf = QuickUnionUnionFind(10);
  quuf.Union(1,3);
  quuf.Union(3,4);
  Println<0>(quuf.Connected(1,4));

  return 0;
}
