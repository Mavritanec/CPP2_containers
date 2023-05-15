#ifndef S21_ARRAY_H_
#define S21_ARRAY_H_

#include <iostream>

namespace s21 {
template <typename T, size_t N>
class array {
 public:
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using iterator = T *;
  using const_iterator = const T *;
  using size_type = size_t;

  // Array Member functions //

  // default constructor, creates empty array
  array();
  // initializer list constructor, creates array initizialized using
  // std::initializer_list<T>
  explicit array(std::initializer_list<value_type> const &items);
  // copy constructor
  array(const array &other);
  // move constructor
  array(array &&other);
  // destructor
  ~array() {}
  // assignment operator overload for moving object
  array &operator=(array &&other);
  // assignment operator overload for copy object
  array &operator=(const array &other);

  // Array Element access //

  // access specified element with bounds checking
  reference at(size_type pos);
  // access specified element
  reference operator[](size_type pos);
  // access the first element
  const_reference front();
  // access the last element
  const_reference back();
  // direct access to the underlying array
  iterator data();

  // Array Iterators //

  // returns an iterator to the beginning
  iterator begin();
  // returns an iterator to the end
  iterator end();

  // Array Capacity //

  // checks whether the container is empty
  bool empty();
  // returns the number of elements
  size_type size();
  // returns the maximum possible number of elements
  size_type max_size();

  // Array Modifiers //

  // swaps the contents
  void swap(array &other);
  // assigns the given value value to all elements in the container
  void fill(const_reference value);

  // Support function //

  void copy(const array &other);

  void print_array();

 private:
  value_type arr_[N]{};
  size_type size_ = N;
};
}  // namespace s21
#include "s21_array.tpp"

#endif  // S21_ARRAY_H_
