#ifndef STACK_S21_STACK_H_
#define STACK_S21_STACK_H_

#include "../Vector/s21_vector.h"

namespace s21 {
template <class T, class Container = s21::Vector<T>>
class Stack {
 public:
  using value_type = T;            // Тип элемента
  using reference = value_type &;  // Тип ссылки на элемент
  using const_reference =
      const value_type &;  // Тип постоянной ссылки на элемент
  using size_type =
      size_t;  // Тип беззнакового расстояния между двумя элементами
  typedef Container container_type;

 protected:
  container_type cont;

 public:
  Stack() : cont() {}

  Stack(std::initializer_list<value_type> const &items) : cont(items) {}

  Stack(const Stack &q) : cont(q.cont) {}

  Stack(Stack &&q) noexcept : cont(std::move(q.cont)) {}

  ~Stack() = default;

  Stack &operator=(Stack &&q) noexcept {
    this->cont = std::move(q.cont);
    return *this;
  }

  bool empty() { return this->cont.empty(); }

  void pop() { this->cont.pop_back(); }

  void push(const_reference value) { this->cont.push_back(value); }

  size_type size() const { return this->cont.size(); }

  const_reference top() { return this->cont.back(); }

  void swap(Stack &other) { this->cont.swap(other.cont); }
};
}  // namespace s21

#endif  // STACK_S21_STACK_H_
