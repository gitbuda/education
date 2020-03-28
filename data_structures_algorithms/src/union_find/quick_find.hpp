#include <vector>

namespace dsa::union_find {

/// Quick Find Idea: All connected elements have the same value id.
///
/// @tparam T is type of elements.
template<typename T>
class QuickFindUnionFind {
public:
  /// Initialize container of elements of size n {0, 1, 2, ...}.
  /// Each element is a standalone connected component.
  explicit QuickFindUnionFind(T n) : id_(n), count_{n} {
    std::iota(std::begin(id_), std::end(id_), 0);
  }

  /// Are p and q connected.
  auto Connected(T p, T q) const { return this->Find(p) == this->Find(q); }

  /// Number of connected components.
  auto Count() const { return this->count_; }

  /// Find component id by just looking at underlying index.
  auto Find(T p) const { return id_[p]; }

  /// Join p and q by assigning one of underlying component id to all
  /// elements belonging to the other component.
  auto Union(T p, T q) {
    auto pId = this->Find(p);
    auto qId = this->Find(q);
    if (pId == qId) return;
    for (unsigned int i = 0; i < id_.size(); i++) {
      // Find all elements where the group id is pId and set them to qId.
      if (id_[i] == pId) { id_[i] = qId; }
    }
    this->count_--;
  }

private:
  std::vector<T> id_; // Access to component id (site indexed).
  T count_; // Number of components.
};

} // namespace dsa::union_find
