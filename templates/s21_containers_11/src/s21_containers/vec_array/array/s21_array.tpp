namespace s21 {
template <class value_type, size_t N>
array<value_type, N>::array() {
  this->bring_to_zero();
}

template <class value_type, size_t N>
array<value_type, N>::array(std::initializer_list<value_type> const &items) {
  this->bring_to_zero();
  if (items.size() > N) {
    throw std::out_of_range("too many initializers");
  }
  int count = 0;
  for (auto element : items) {
    this->new_arr_[count] = element;
    ++count;
  }
}

template <class value_type, size_t N>
array<value_type, N>::array(const array &a) {
  this->bring_to_zero();
  for (size_type i = 0; i < this->m_size_; ++i)
    this->new_arr_[i] = a.new_arr_[i];
}

template <class value_type, size_t N>
array<value_type, N>::array(array &&a) {
  this->bring_to_zero();
  if (this != &a) {
    std::move(a.new_arr_, a.new_arr_ + N, this->new_arr_);
  }
}

template <class value_type, size_t N>
array<value_type, N> &array<value_type, N>::operator=(array &&a) {
  if (this != &a) {
    std::move(a.new_arr_, a.new_arr_ + N, this->new_arr_);
  }
  return *this;
}

template <class value_type, size_t N>
void array<value_type, N>::swap(array &other) {
  std::swap(this->new_arr_, other.new_arr_);
}

template <class value_type, size_t N>
void array<value_type, N>::fill(const_reference value_type) {
  for (size_type i = 0; i < this->m_size_; i++) {
    this->new_arr_[i] = value_type;
  }
}

template <class value_type, size_t N>
void array<value_type, N>::bring_to_zero() {
  this->size_N();
  this->m_size_ = N;
  this->fill(value_type(0));
  this->arr_ = new_arr_;
}
template <class T, size_t N>
void array<T, N>::size_N() {
  if (this->len_N < 0) throw std::invalid_argument("Error size for array!");
}

template <typename T, size_t N>
typename array<T, N>::size_type array<T, N>::max_size() {
  return N;
}

}  // namespace s21
