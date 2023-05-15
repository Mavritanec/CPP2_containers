#ifndef SRC_LIST_STACK_QUEUE_S21_QUEUE_H
#define SRC_LIST_STACK_QUEUE_S21_QUEUE_H
#include "../list/s21_list.h"

namespace s21 {
template <class T, class Container = s21::list<T> >
class queue {
 public:
  using pointer = typename Container::pointer;
  using const_pointer = typename Container::const_pointer;
  using value_type = typename Container::value_type;
  using reference = typename Container::reference;
  using const_reference = typename Container::const_reference;
  using size_type = typename Container::size_type;

 protected:
  Container c;

 public:
  queue() : c() {}
  queue(std::initializer_list<value_type> const &items) : c(items) {}
  queue(const queue &s) : c(s.c) {}
  queue(queue &&s) : c(std::move(s.c)) {}
  ~queue() {}
  queue &operator=(queue &&s) {
    this->c = std::move(s.c);
    return *this;
  }

  const_reference front() { return c.front(); }

  const_reference back() { return c.back(); }

  bool empty() { return c.empty(); }
  size_type size() { return c.size(); }
  void push(const_reference value) { this->c.push_back(value); }
  void pop() { this->c.pop_front(); }
  void swap(queue &other) { this->c.swap(other.c); }
  void output_s() { this->c.output_list(); }
  template <typename... Args>
  void emplace_back(Args &&...args) {
    this->c.emplace_back(std::forward<Args>(args)...);
  }
};

}  //  namespace s21

#endif  // SRC_LIST_STACK_QUEUE_S21_QUEUE_H
