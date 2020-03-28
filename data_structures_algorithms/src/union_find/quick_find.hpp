#include <vector>

namespace dsa::union_find {

/// @tparam T is type of elements.
template<typename T>
class QuickFindUnionFind {
public:
  explicit QuickFindUnionFind(T n) : id_(n), count_{n} {
    std::iota(std::begin(id_), std::end(id_), 0);
  }
  auto Connected(T p, T q) const { return this->Find(p) == this->Find(q); }
  auto Count() const { return this->count_; }
  auto Find(T p) const { return id_[p]; }
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
