#ifndef SRC_ITERATORS_VECTOR_ITERATOR_H_
#define SRC_ITERATORS_VECTOR_ITERATOR_H_

#include <cstddef>
#include <iterator>

namespace s21 {
template <class T>
class VectorIterator {
public:
    using iterator_category = std::random_access_iterator_tag;
    using difference_type = std::ptrdiff_t;
    using value_type = T;
    using reference = value_type &;
    using pointer = value_type *;

private:
    pointer p_data_;

public:
    VectorIterator() : p_data_(nullptr) {}  // базовый конструктор
    VectorIterator(const VectorIterator &other) noexcept { *this = other; }  // конструктор копирования
    VectorIterator(pointer data) : p_data_(data) {}  // параметризированный конструктор
    ~VectorIterator() {}

    VectorIterator &operator=(const VectorIterator &other) {
        p_data_ = other.p_data_;
        return *this;
    }

    pointer base() const { return p_data_; };
    reference operator*() noexcept { return *p_data_; }
    pointer operator->() noexcept { return p_data_; }
    VectorIterator &operator+(const int val) {
        p_data_ = p_data_ + val;
        return *this;
    }
    VectorIterator &operator-(const int val) {
        p_data_ = p_data_ - val;
        return *this;
    }

    VectorIterator operator++() {
        p_data_++;
        return *this;
    }
    VectorIterator operator--(const int n) {
        p_data_--;
        return *this;
    }
    VectorIterator operator+=(const int n) {
        p_data_ = p_data_ + n;
        return *this;
    }

    bool operator==(const VectorIterator &other) const { return p_data_ == other.p_data_; }
    bool operator!=(const VectorIterator &other) const { return p_data_ != other.p_data_; }

    VectorIterator &operator=(VectorIterator &&other) {
        p_data_ = other.p_data_;
        return *this;
    }  // ???
};

template <class T>
class ConstVectorIterator {
public:
    using iterator_category = std::random_access_iterator_tag;
    using difference_type = std::ptrdiff_t;
    using value_type = const T;
    using reference = const T &;
    using pointer = const T *;

private:
    T *p_data_;

public:
    ConstVectorIterator() : p_data_(nullptr) {}  // базовый конструктор
    ConstVectorIterator(const ConstVectorIterator &other) { *this = other; }  // конструктор копирования
    ConstVectorIterator(T *data) : p_data_(data) {}  // параметризированный конструктор
    ~ConstVectorIterator() {}

    pointer base() const { return p_data_; }
    reference operator*() const { return *p_data_; }
    pointer operator->() const { return p_data_; }
    ConstVectorIterator operator++() {
        p_data_++;
        return *this;
    }
    ConstVectorIterator operator--() {
        p_data_--;
        return *this;
    }
    ConstVectorIterator &operator=(const ConstVectorIterator &other) {
        p_data_ = other.p_data_;
        return *this;
    }
    ConstVectorIterator &operator=(ConstVectorIterator &&other) {
        p_data_ = other.p_data_;
        return *this;
    }
    bool operator==(const ConstVectorIterator &other) const { return p_data_ == other.p_data_; }
    bool operator!=(const ConstVectorIterator &other) const { return p_data_ == other.p_data_; }
};

}  // namespace s21

#endif  // SRC_ITERATORS_VECTOR_ITERATOR_H_
