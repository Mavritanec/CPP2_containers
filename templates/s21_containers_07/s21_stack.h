
#ifndef S21_STACK_H_
#define S21_STACK_H_

#include <iostream>

#include "s21_list.h"

using namespace std;

namespace s21 {

template <typename T>
class stack {
  using size_type = size_t;
  using value_type = T;
  using reference = value_type &;
  using const_reference = const value_type &;

 private:
  list<value_type> list_;

 public:
  stack();

  explicit stack(std::initializer_list<value_type> const &items);

  stack(const stack &s);

  stack(stack &&s);

  ~stack();

  stack &operator=(stack &&s);

  const_reference top();

  bool empty();

  size_type size();

  void push(const_reference value);

  void pop();

  void swap(stack &other);

  template <class... Args>
  void emplace_front(Args &&...args);
};
}  // namespace s21
#include "s21_stack.tpp"

#endif  // S21_STACK_H_