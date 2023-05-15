#ifndef SRC_VEC_ARRAY_SEQUENCE_VECTOR_H_
#define SRC_VEC_ARRAY_SEQUENCE_VECTOR_H_
#include "../sequence/s21_sequence.h"

namespace s21 {
template <class T, class Alloc = std::allocator<T> >
class Vector : public abstract<T> {
 public:
  using pointer = typename abstract<T>::pointer;
  using value_type = typename abstract<T>::value_type;
  using reference = typename abstract<T>::reference;
  using const_reference = typename abstract<T>::const_reference;
  using size_type = typename abstract<T>::size_type;
  using const_iterator = typename abstract<T>::ConstIterator;
  using iterator = typename abstract<T>::Iterator;
  using allocator_type = Alloc;
  Vector();
  explicit Vector(size_type n);
  Vector(std::initializer_list<value_type> const &items);
  Vector(const Vector &v);
  Vector(Vector &&v);
  ~Vector() { clear_all(); }
  Vector &operator=(const Vector &v);
  Vector &operator=(Vector &&v);

 private:
  void reserve_more_capacity(size_type size, bool shrink);
  size_t m_capacity_;
  allocator_type alloc_;

 public:
  size_type capacity();
  void push_back(value_type v);
  void pop_back();
  void swap(Vector &other);
  void reserve(size_type size);
  void shrink_to_fit();
  void clear();
  iterator insert(iterator pos, const_reference value);
  void erase(iterator pos);
  template <typename... Args>
  iterator emplace(const_iterator pos, Args &&...args);
  template <typename... Args>
  void emplace_back(Args &&...args);

 private:
  void clear_all();
  void output_vector();
  void bring_to_zero();
  pointer get_memory(size_type size);
};

}  // namespace s21

#include "s21_vector.tpp"

#endif  //  SRC_VECTOR_H_
