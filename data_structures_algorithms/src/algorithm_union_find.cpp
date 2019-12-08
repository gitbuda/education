#include <numeric>
#include <vector>

#include "include/using_iostream.hpp"

// NOTE: Work in progress.

// https://stackoverflow.com/questions/39923968/in-c-how-to-initialize-a-vector-with-values-1-2-n-without-a-loop
// https://stackoverflow.com/questions/11965732/set-stdvectorint-to-a-range

template <typename T>
class UnionQuickFind {
 public:
  UnionQuickFind(T n) : id_(n), count_{n} {
    std::iota(std::begin(id_), std::end(id_), 0);
  }
  bool Connected(T p, T q) const { return this->Find(p) == this->Find(q); }
  int Count() const { return this->count_; }
  int Find(T p) const { return id_[p]; }
  void Union(T p, T q) {
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
  std::vector<T> id_;
  T count_;
};

template <typename T>
class QuickUnionFind {
};

int main() {
  Println<0>("Union Find");
  auto uf = UnionQuickFind(10);
  uf.Union(1,3);
  uf.Union(3,4);
  Println<0>(uf.Connected(1,4));
  return 0;
}
