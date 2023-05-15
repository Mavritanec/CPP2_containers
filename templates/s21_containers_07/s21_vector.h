#ifndef SRC_S21_VECTOR_H_
#define SRC_S21_VECTOR_H_

#include <initializer_list>
#include <iostream>
#include <limits>

namespace s21 {

template <typename T>
class vector {
 public:
  //* ===  Vector Member type  ===
  class VectorIterator;
  class ConstVectorIterator;
  using size_type = size_t;
  using reference = T &;
  using const_reference = const T &;
  using value_type = T;
  using iterator = T *;
  using const_iterator = const T *;

  //* ===  Vector Member functions  ===
  vector();
  explicit vector(size_type n);
  vector(size_type n, T value);
  explicit vector(std::initializer_list<value_type> const &items);
  vector(const vector &v);
  vector(vector &&v);
  ~vector();
  vector &operator=(vector &&other);
  vector &operator=(const vector &other);

  //* ===  Vector Element access  ===
  reference at(size_type position);
  reference operator[](size_type position) { return arr_[position]; }
  const_reference operator[](size_type position) const {
    return arr_[position];
  }
  const_reference front() { return *(begin()); }
  const_reference back() { return *(--end()); }
  VectorIterator data() { return begin(); }

  //* === Vector Iterators ===
  VectorIterator begin() { return VectorIterator(arr_); }
  VectorIterator end() { return VectorIterator(arr_ + size_); }

  const VectorIterator cbegin() { return this->begin(); }
  const VectorIterator cend() { return this->end(); }

  //* ===  Vector Capacity  ===
  bool empty() { return (this->size_ == 0); }
  size_type size() const;
  size_type max_size() const;
  void reserve(size_type size);
  size_type capacity() const { return this->capacity_; }
  void shrink_to_fit();

  //* ===  Vector Modifiers  ===
  void clear() { this->size_ = 0; }
  VectorIterator insert(VectorIterator position, const_reference value);
  void erase(VectorIterator position);
  void push_back(value_type value);
  void pop_back() { --size_; }
  void swap(vector &other);

  //* === Bonus ===
  template <typename... Args>
  VectorIterator emplace(VectorIterator pos, Args &&...args);
  template <typename... Args>
  void emplace_back(Args &&...args);

  //* ===  Second foo  ===
  void copy(const vector &other);

 private:
  value_type *arr_ = nullptr;
  size_type size_ = 0;
  size_type capacity_ = 0;

  void resize(size_type new_size);

 public:
  class VectorIterator {
   public:
    VectorIterator();
    explicit VectorIterator(T *arr_ptr);
    VectorIterator(const VectorIterator &other);
    ~VectorIterator() {}
    VectorIterator &operator=(const VectorIterator &other);
    VectorIterator &operator++();
    VectorIterator &operator--();
    VectorIterator &operator+=(int n);
    VectorIterator &operator-=(int n);
    VectorIterator operator+(int n);
    VectorIterator operator-(int n);
    bool operator==(const VectorIterator &other);
    bool operator!=(const VectorIterator &other);
    bool operator>(const VectorIterator &other);
    bool operator<(const VectorIterator &other);
    bool operator>=(const VectorIterator &other);
    bool operator<=(const VectorIterator &other);
    reference operator*() { return *ptr_; }
    const_reference operator*() const { return *ptr_; }
    reference operator[](size_type n) { return *(ptr_ + n); }

   private:
    T *ptr_;
  };

  class ConstVectorIterator : public VectorIterator {
   public:
    ConstVectorIterator() : VectorIterator() {}
    const_reference operator*() { return this->operator*; }
    const_reference operator[](size_type n) { return this->operator[]; }
  };
};

}  // namespace s21

#include "s21_vector.tpp"

#endif  // SRC_S21_VECTOR_H_
