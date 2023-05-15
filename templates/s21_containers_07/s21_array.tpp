namespace s21 {

// Array Member functions //

template <typename value_type, size_t N>
array<value_type, N>::array() : size_(N) {}

template <typename value_type, size_t N>
array<value_type, N>::array(std::initializer_list<value_type> const &items) {
  int count = 0;
  for (auto it = items.begin(); it != items.end(); ++it) {
    arr_[count] = *it;
    ++count;
  }
}

template <typename value_type, size_t N>
array<value_type, N>::array(const array &other) {
  copy(other);
}

template <typename value_type, size_t N>
array<value_type, N>::array(array &&other) {
  copy(other);
}

template <typename value_type, size_t N>
array<value_type, N> &array<value_type, N>::operator=(array &&other) {
  if (size_ != other.size_) {
    throw std::out_of_range("container size is not equal");
  }
  copy(other);
  return *this;
}

template <typename value_type, size_t N>
array<value_type, N> &array<value_type, N>::operator=(const array &other) {
  copy(other);
  return *this;
}

// Array Element access //

template <typename value_type, size_t N>
typename array<value_type, N>::reference array<value_type, N>::at(
    size_type pos) {
  if (pos > size_) {
    throw std::out_of_range("Position is out of range");
  }
  return arr_[pos];
}

template <typename value_type, size_t N>
typename array<value_type, N>::reference array<value_type, N>::operator[](
    size_type pos) {
  return at(pos);
}

template <typename value_type, size_t N>
typename array<value_type, N>::const_reference array<value_type, N>::front() {
  if (empty()) {
    throw std::out_of_range("Container is empty");
  }
  return arr_[0];
}

template <typename value_type, size_t N>
typename array<value_type, N>::const_reference array<value_type, N>::back() {
  if (empty()) {
    throw std::out_of_range("Container is empty");
  }
  return arr_[size_ - 1];
}

template <typename value_type, size_t N>
typename array<value_type, N>::iterator array<value_type, N>::data() {
  if (empty()) {
    throw std::out_of_range("Container is empty");
  }
  return arr_;
}

// Array Iterators //

template <typename value_type, size_t N>
typename array<value_type, N>::iterator array<value_type, N>::begin() {
  return arr_;
}

template <typename value_type, size_t N>
typename array<value_type, N>::iterator array<value_type, N>::end() {
  return arr_ + size_;
}

// Array Capacity //

template <typename value_type, size_t N>
bool array<value_type, N>::empty() {
  return size_ == 0;
}

template <typename value_type, size_t N>
typename array<value_type, N>::size_type array<value_type, N>::size() {
  return size_;
}

template <typename value_type, size_t N>
typename array<value_type, N>::size_type array<value_type, N>::max_size() {
  return size_;
}

// Array Modifiers //

template <typename value_type, size_t N>
void array<value_type, N>::swap(array &other) {
  for (size_t i = 0; i < size_; ++i) {
    value_type tmp;
    tmp = arr_[i];
    arr_[i] = other.arr_[i];
    other.arr_[i] = tmp;
  }
}

template <typename value_type, size_t N>
void array<value_type, N>::fill(const_reference value) {
  if (empty()) {
    throw std::out_of_range("Container is empty");
  }
  for (size_t i = 0; i < size_; ++i) {
    arr_[i] = value;
  }
}

// Support function //

template <typename value_type, size_t N>
void array<value_type, N>::copy(const array &other) {
  for (size_t i = 0; i != size_; ++i) {
    arr_[i] = other.arr_[i];
  }
}

template <typename value_type, size_t N>
void array<value_type, N>::print_array() {
  std::cout << "array -> ";
  for (size_t i = 0; i != size_; ++i) {
    std::cout << arr_[i] << " ";
  }
  std::cout << std::endl;
}
}  // namespace s21