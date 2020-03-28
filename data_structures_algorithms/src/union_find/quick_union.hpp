#include <vector>

namespace dsa::union_find {

/// Quick Union Idea: All connected elements have the same root. Tree structure
/// where element values are leading towards root.
///
/// @tparam T is type of elements.
template<typename T>
class QuickUnionUnionFind {
public:
  /// Initialize container of elements of size n {0, 1, 2, ...}.
  /// Each element is a standalone connected component.
  explicit QuickUnionUnionFind(T n) : id_(n), count_{n} {
    std::iota(std::begin(id_), std::end(id_), 0);
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

  /// Join p and q by setting one of them as others root.
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
