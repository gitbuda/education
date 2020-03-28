#include <vector>

namespace dsa::union_find {

/// @tparam T is type of elements.
// TODO: Add a concept that T has to be unusigned becase it's used to
// access vector elements.
template<typename T>
class QuickUnionUnionFind {
public:
  explicit QuickUnionUnionFind(T n) : id_(n), count_{n} {
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

} // namespace dsa::union_find
