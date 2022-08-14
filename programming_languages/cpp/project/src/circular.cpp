#include <memory>

struct A {
  std::weak_ptr<A> circle_ref;
};

int main() {
  auto si1 = std::make_shared<A>();
  auto si2 = std::make_shared<A>();
  si1->circle_ref = si2;
  si2->circle_ref = si1;
  return 0;
}
