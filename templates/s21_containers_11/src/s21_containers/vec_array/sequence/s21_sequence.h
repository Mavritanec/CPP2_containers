#ifndef SRC_VEC_ARRAY_SEQUENCE_S21_ABSTRACT_H_
#define SRC_VEC_ARRAY_SEQUENCE_S21_ABSTRACT_H_
#include <cmath>
#include <iostream>
#include <stdexcept>
#include <cstring>

namespace s21 {
template <class T>
class abstract {
 protected:
  abstract() {}
  T *arr_;
  size_t m_size_;

 public:
  using pointer = T *;
  using const_pointer = const T *;
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using size_type = size_t;
  class ConstIterator {
   public:
    ConstIterator();
    ConstIterator(pointer pt);
    ConstIterator(const ConstIterator &other) : data_(other.data_) {}
    ~ConstIterator() {}
    ConstIterator& operator=(const ConstIterator& other) {
        this->data_ = other.data_;
        return *this;
    }
    ConstIterator &operator++();
    ConstIterator operator++(int);
    ConstIterator &operator--();
    ConstIterator operator--(int);
    operator const_pointer() { return this->data_; }
    const_reference operator*();
    ConstIterator operator+(const size_t value);
    bool operator!=(const ConstIterator &other) const;
    bool operator==(const ConstIterator &other) const;

   protected:
    pointer data_;
  };
  class Iterator : public ConstIterator {
   public:
    Iterator();
    Iterator(pointer pt);
    Iterator(const Iterator &other) : ConstIterator(other) {}
    Iterator(const ConstIterator &other) : ConstIterator(other) {}
    ~Iterator() {}
    reference operator*();
    Iterator& operator=(const Iterator& other) {
        this->data_ = other.data_;
        return *this;
    }
    Iterator &operator=(const value_type& val);
    operator pointer() { return this->data_; }
    Iterator operator+(const size_t value);
    Iterator operator-(const size_t value);
    Iterator operator-(const Iterator &value);
  };
  using iterator = Iterator;
  using const_iterator = ConstIterator;

  reference at(size_type pos);
  reference operator[](size_type pos);
  virtual const_reference front();
  virtual const_reference back();
  iterator data();

  virtual iterator begin();
  virtual iterator end();

  virtual bool empty() const noexcept;
  virtual size_type size() const noexcept;
  virtual size_type max_size() const noexcept;
};

}  // namespace s21

#include "s21_sequence.tpp"
#endif  // SRC_VEC_ARRAY_SEQUENCE_S21_ABSTRACT_H_
