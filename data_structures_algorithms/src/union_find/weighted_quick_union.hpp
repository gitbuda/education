#include <vector>

namespace dsa::union_find {

/// Weighted Quick Union Idea: Make smaller root point to larger one.
///
/// @tparam T is type of elements.
template<typename T>
class WeightedQuickUnionUnionFind {
public:
  /// Initialize container of elements of size n {0, 1, 2, ...}.
  /// Each element is a standalone connected component.
  explicit WeightedQuickUnionUnionFind(T n) : id_(n), size_(n), count_{n} {
    std::iota(std::begin(id_), std::end(id_), 0);
    std::fill(std::begin(size_), std::end(size_), 1);
  }

  /// Are p and q connected.
  auto Connected(T p, T q) const { return this->Find(p) == this->Find(q); }

  /// Number of connected components.
  auto Count() const { return this->count_; }

  /// Find root element by search array for an element where element index
  /// is equal as element value. Returned value is component id.
  auto Find(T p) const {
    // Follow links to find a root.
    while (p != id_[p]) p = id_[p];
    return p;
  }

  /// Join p and q by making smaller root point to larger one.
  auto Union(T p, T q) {
    auto pRoot = this->Find(p);
    auto qRoot = this->Find(q);
    if (pRoot == qRoot) return;
    if (size_[pRoot] < size_[qRoot]) {
      id_[pRoot] = qRoot;
      size_[qRoot] += size_[pRoot];
    } else {
      id_[qRoot] = pRoot;
      size_[pRoot] += size_[qRoot];
    }
    count_--;
  }

private:
  std::vector<T> id_; // Access to component id (site indexed).
  std::vector<T> size_; // Size of component for roots (site indexed).
  T count_; // Number of components.
};

} // namespace dsa::union_find
