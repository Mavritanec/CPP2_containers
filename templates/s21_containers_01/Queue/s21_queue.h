#ifndef QUEUE_S21_QUEUE_H_
#define QUEUE_S21_QUEUE_H_

#include <cstddef>
#include <initializer_list>
#include <iostream>
#include <list>

#include "../List/s21_list.h"

namespace s21 {
template <class T, class Container = s21::List<T>>
class Queue {
 public:
  using value_type = T;  // Тип элемента
  using container_type = s21::List<T>;
  using reference = value_type &;  // Тип ссылки на элемент
  using const_reference =
      const value_type &;  // Тип постоянной ссылки на элемент
  using size_type =
      size_t;  // Тип беззнакового расстояния между двумя элементами

 protected:
  container_type cont;

 public:
  Queue() : cont() {}

  Queue(std::initializer_list<value_type> const &items) : cont(items) {}

  Queue(const Queue &q) : cont(q.cont) {}

  Queue(Queue &&q) noexcept : cont(std::move(q.cont)) {}

  ~Queue() = default;

  Queue &operator=(Queue &&q) noexcept {
    this->cont = std::move(q.cont);
    return *this;
  }

  bool empty() { return this->cont.empty(); }

  size_type size() { return this->cont.size(); }

  void push(const_reference value) { this->cont.push_back(value); }

  void pop() { this->cont.pop_front(); }

  //  reference front() { return this->cont.front(); }

  const_reference front() { return this->cont.front(); }

  //  reference back() { return this->cont.back(); }

  const_reference back() { return this->cont.back(); }

  void swap(Queue &other) { this->cont.Swap(other.cont); }

  template <class... Args>
  void emplace_back(Args &&...args) {
    return this->push(value_type(std::forward<Args>(args)...));
  }
};
}  // namespace s21

#endif  // QUEUE_S21_QUEUE_H_