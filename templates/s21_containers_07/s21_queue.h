
#ifndef S21_QUEUE_H_
#define S21_QUEUE_H_

#include <iostream>

#include "s21_list.h"

using namespace std;

namespace s21 {

template <typename T>
class queue {
  using size_type = size_t;
  using value_type = T;
  using reference = value_type &;
  using const_reference = const value_type &;

 private:
  list<T> list_;

 public:
  queue();

  explicit queue(std::initializer_list<value_type> const &items);

  queue(const queue &q);

  queue(queue &&q);

  ~queue();

  queue &operator=(queue &&q);

  const_reference front();

  const_reference back();

  bool empty();

  size_type size();

  void push(const_reference value);

  void pop();

  void swap(queue &other);

  template <class... Args>
  void emplace_back(Args &&...args);
};
}  // namespace s21
#include "s21_queue.tpp"

#endif  // S21_QUEUE_H_