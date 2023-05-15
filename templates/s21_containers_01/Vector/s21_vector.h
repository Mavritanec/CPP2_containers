#ifndef S21_VECTOR_H_
#define S21_VECTOR_H_

#include <initializer_list>
#include <stdexcept>

using std::out_of_range;

namespace s21 {
template <typename T>
class Vector {
 public:
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using iterator = T *;
  using const_iterator = const T *;
  using size_type = size_t;

 private:
  size_type size_;
  size_type capacity_;
  iterator arr_;

 public:
  // functions (constructors and operator overload)
  Vector() : size_(0), capacity_(0), arr_(nullptr) {}

  Vector(size_type n) : size_(n), capacity_(n), arr_(nullptr) {
    arr_ = new value_type[size_];
    for (size_t i = 0; i < size_; i++) {
      arr_[i] = value_type();
    }
  }

  Vector(std::initializer_list<value_type> const &items)
      : Vector(items.size()) {
    std::copy(items.begin(), items.end(), arr_);
  }

  Vector(const Vector &other) : Vector(other.size_) {
    std::copy(other.arr_, other.arr_ + other.size_, arr_);
  }

  Vector(Vector &&other)
      : size_(other.size_), capacity_(other.capacity_), arr_(other.arr_) {
    other.arr_ = nullptr;
    other.size_ = 0;
    other.capacity_ = 0;
  }

  ~Vector() {
    if (arr_) {
      delete[] arr_;
    }
    size_ = 0;
    capacity_ = 0;
    arr_ = nullptr;
  }

  Vector &operator=(Vector &&other) {
    ~Vector();
    arr_ = other.arr_;
    size_ = other.size_;
    capacity_ = other.capacity_;
    other.arr_ = nullptr;
    other.size_ = 0;
    other.capacity_ = 0;
    return *this;
  }

  // element access
  reference at(size_type pos) {
    if (pos >= size_) {
      throw out_of_range("Index is out of range");
    }
    return arr_[pos];
  }

  reference operator[](size_type pos) { return arr_[pos]; }

  const_reference front() { return arr_[0]; }

  const_reference back() { return arr_[size_ - 1]; }

  iterator data() noexcept { return arr_; }

  // iterators
  iterator begin() noexcept { return arr_; }
  const_iterator cbegin() const noexcept { return arr_; }
  iterator end() noexcept { return arr_ + size_; }
  const_iterator cend() const noexcept { return arr_ + size_; }

  // vector capacity
  bool empty() const noexcept { return size_ == 0; }

  size_type size() const noexcept { return size_; }

  size_type max_size() const noexcept {
    std::allocator<value_type> Alloc;
    return Alloc.max_size();
  }

  void reserve(size_type new_capacity) {
    if (new_capacity > max_size()) {
      std::length_error("error: new_cap > max_size()");
    }
    if (new_capacity > capacity_) {
      value_type *buff = new value_type[new_capacity];
      for (size_t i = 0; i < size_; ++i) buff[i] = std::move(arr_[i]);
      delete[] arr_;
      arr_ = buff;
      capacity_ = new_capacity;
    }
  }

  size_type capacity() const noexcept { return capacity_; }

  void shrink_to_fit() noexcept {
    if (capacity_ != size_) {
      reserve(size_);
    }
  }

  void clear() noexcept { size_ = 0; }

  iterator insert(iterator pos, const_reference value) {
    if (pos < begin() || pos > end()) {
      throw std::out_of_range("Out of range");
    }

    auto dif = pos - begin();

    size_++;
    for (int i = size_ - 1; i > pos - begin(); i--) {
      arr_[i] = arr_[i - 1];
    }
    arr_[pos - begin()] = value;

    if (size_ - 1 == capacity_) {
      reserve(size_ == 0 ? 1 : capacity_ * 2);
    }

    return begin() + dif;
  }

  void erase(iterator pos) {
    if (pos < begin() || pos > end()) {
      throw std::out_of_range("Out of range");
    }
    for (size_type i = pos - begin(); i < size_ - 1; i++) {
      arr_[i] = arr_[i + 1];
    }
    size_--;
  }

  void push_back(const_reference value) {
    if (size_ == capacity_) {
      reserve(size_ == 0 ? 1 : capacity_ * 2);
    }
    size_++;
    if (size_ == 1) {
      arr_[0] = value;
    } else {
      arr_[size_ - 1] = value;
    }
  }

  void pop_back() noexcept { size_--; }

  void swap(Vector &other) {
    std::swap(capacity_, other.capacity_);
    std::swap(size_, other.size_);
    std::swap(arr_, other.arr_);
  }

  // iterator's operators
  reference operator*() const noexcept { return *arr_; }

  reference operator++() noexcept { return *(arr_ + 1); }

  reference operator--() noexcept { return *(arr_ - 1); }

  bool operator==(iterator other_iter) noexcept { return arr_ == other_iter; }

  bool operator!=(iterator other_iter) noexcept { return arr_ != other_iter; }

  template <typename... Args>
  iterator emplace(iterator pos, Args &&...args) {
    value_type end2 = arr_[size_ - 1];
    value_type end3;
    int dif_emp = pos - begin();
    int shift = 0;
    for (auto &i : {args...}) {
      insert(begin() + dif_emp + shift, i);
      shift++;
      end3 = i;
    }
    arr_[size_ - 1] = (begin() + dif_emp + shift != end()) ? end2 : end3;

    return begin() + dif_emp + shift - 1;
  }
};
}  // namespace s21

#endif  // S21_VECTOR_H_
