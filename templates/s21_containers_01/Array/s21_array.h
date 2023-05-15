#ifndef ARRAY_S21_ARRAY_H_
#define ARRAY_S21_ARRAY_H_

#include <cstddef>
#include <initializer_list>
#include <iostream>

namespace s21 {
template <class T, size_t N>
class Array {
 public:
  using value_type = T;            // Тип элемента
  using reference = value_type &;  // Тип ссылки на элемент
  using const_reference =
      const value_type &;  // Тип постоянной ссылки на элемент
  using iterator =
      value_type *;  // Тип итератора для управляемой последовательности
  using const_iterator = const value_type
      *;  // Тип постоянного итератора для управляемой последовательности
  using size_type =
      size_t;  // Тип беззнакового расстояния между двумя элементами

  Array() : size_(N) {}  // Создает объект массива

  Array(std::initializer_list<value_type> const &items) : Array() {
    if (size_ < items.size())
      throw std::out_of_range("invalid amount of items");
    for (size_t i = 0; i < N; i++) {
      data_[i] = 0;
    }
    size_type i = 0;
    for (auto it = items.begin(); it != items.end(); it++, i++) {
      data_[i] = *it;
    }
  }

  Array(const Array &a) : Array() { std::copy(a.cbegin(), a.cend(), data_); }

  Array(Array &&a) : Array() { std::move(a.cbegin(), a.cend(), data_); }

  ~Array() {}  // Деструктор

  void operator=(
      Array &a) {  // Заменяет управляемую последовательность this копией a
    std::copy(a.cbegin(), a.cend(), data_);
  }

  void operator=(Array &&a) { std::move(a.cbegin(), a.cend(), data_); }

  reference at(
      size_type position) {  // Обращается к элементу в указанной позиции
    if (position >= size_) throw std::out_of_range("segfault");
    return data_[position];
  }

  const_reference front() const {
    return data_[0];
  }  // Обращается к первому элементу

  const_reference back() const {
    return data_[size_ - 1];
  }  // Обращается к последнему элементу

  iterator data() noexcept { return begin(); }

  reference operator[](size_type position) {
    return data_[position];
  }  // Обращается к элементу в указанной позиции

  const_reference operator[](size_type position) const {
    return data_[position];
  }

  iterator begin() noexcept {
    return data_;
  }  // Задает начало управляемой последовательности

  const_iterator cbegin() const noexcept {
    return data_;
  }  // Возвращает итератор const, направленный на первый элемент в диапазоне

  iterator end() noexcept {
    return &data_[size_];
  }  // Задает конец управляемой последовательности

  const_iterator cend() const noexcept {
    return &data_[size_];
  }  // Возвращает итератор const, который обращается к месту,
     // следующему сразу за последним элементом в диапазоне.

  bool empty() const noexcept { return N == 0; }  // Проверяет наличие элементов

  size_type size() const noexcept {
    return size_;
  }  // Подсчитывает количество элементов

  size_type max_size() const noexcept { return size_; }  // аналогично size

  void swap(Array &other) {  // Выполняет обмен содержимым между этим и другим
                             // массивом
    std::swap_ranges(this->begin(), this->end(), other.begin());
  }

  void fill(const_reference value) {  // Заменяет каждый элемент массива на
                                      // указанное значение
    size_type i = 0;
    for (auto it = this->begin(); it != this->end(); it++, i++) {
      data_[i] = value;
    }
  }

 private:
  size_type size_;
  value_type data_[N];
};
}  // namespace s21

#endif  // ARRAY_S21_ARRAY_H_