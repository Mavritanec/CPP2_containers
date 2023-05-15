namespace s21 {

template <class value_type, class allocator_type>
Vector<value_type, allocator_type>::Vector() {
  this->bring_to_zero();
}

template <class value_type, class allocator_type>
Vector<value_type, allocator_type>::Vector(size_type n) {
  if (n > this->max_size()) {
    throw std::length_error("cannot create s21::vector larger than max_size()");
  }
  this->m_size_ = n;
  this->m_capacity_ = n;
  this->arr_ = n ? this->get_memory(n) : nullptr;
}

template <class value_type, class allocator_type>
typename Vector<value_type, allocator_type>::pointer
Vector<value_type, allocator_type>::get_memory(size_type size) {
  pointer temp;
  temp = this->alloc_.allocate(size);
  if (!temp) {
    throw std::bad_alloc();
  }
  for (size_type i = 0; i < size; i++) {
    alloc_.construct(temp, value_type());
  }
  return temp;
}

template <class value_type, class allocator_type>
Vector<value_type, allocator_type>::Vector(
    std::initializer_list<value_type> const &items) {
  this->bring_to_zero();
  this->arr_ = get_memory(items.size());
  size_type i = 0;
  for (auto it = items.begin(); it != items.end(); it++) {
    this->arr_[i] = *it;
    i++;
  }
  this->m_size_ = items.size();
  this->m_capacity_ = items.size();
}

template <class value_type, class allocator_type>
Vector<value_type, allocator_type>::Vector(const Vector &v) {
  this->bring_to_zero();
  *this = v;
}

template <class value_type, class allocator_type>
Vector<value_type, allocator_type>::Vector(Vector &&v) {
  this->bring_to_zero();
  if (this->arr_ != v.arr_) {
    *this = std::move(v);
    v.arr_ = nullptr;
    v.m_size_ = 0;
    v.m_capacity_ = 0;
  }
}

template <class value_type, class allocator_type>
Vector<value_type, allocator_type>
    &Vector<value_type, allocator_type>::operator=(const Vector &v) {
  if (this->arr_ != v.arr_) {
    if (this->arr_ != nullptr) {
      delete[] this->arr_;
    }
    if (this->m_capacity_ < v.m_size_) {
      this->m_capacity_ = v.m_capacity_;
    }

    this->m_size_ = v.m_size_;
    this->arr_ = this->get_memory(this->m_capacity_);
    for (size_type i = 0; i < this->m_size_; ++i) this->arr_[i] = v.arr_[i];
  }
  return *this;
}

template <class value_type, class allocator_type>
Vector<value_type, allocator_type>
    &Vector<value_type, allocator_type>::operator=(Vector &&v) {
  if (this != &v) {
    this->clear_all();
    this->arr_ = v.arr_;
    this->m_capacity_ = v.m_capacity_;
    this->m_size_ = v.m_size_;
    //        *this = std::move(v);
    v.m_size_ = 0;
    v.m_capacity_ = 0;
    v.arr_ = nullptr;
  }
  return *this;
}

template <class value_type, class allocator_type>
void Vector<value_type, allocator_type>::swap(Vector &other) {
  if (this->arr_ != other.arr_) {
    std::swap(this->m_size_, other.m_size_);
    std::swap(this->m_capacity_, other.m_capacity_);
    std::swap(this->arr_, other.arr_);
  }
}

template <typename value_type, class allocator_type>
void Vector<value_type, allocator_type>::clear_all() {
  if (this->arr_ != nullptr) {
    delete[] this->arr_;
  }
  this->arr_ = nullptr;
  this->m_size_ = this->m_capacity_ = 0;
}

template <class value_type, class allocator_type>
void Vector<value_type, allocator_type>::output_vector() {
  if (this->empty()) {
    throw std::length_error("Your vector is empty!");
  }
  std::cout << "This is your vector!!" << std::endl;
  for (int i = 0; i < this->size(); i++) {
    std::cout << this->arr_[i];
  }
  std::cout << std::endl;
}

template <class value_type, class allocator_type>
void Vector<value_type, allocator_type>::bring_to_zero() {
  this->arr_ = nullptr;
  this->m_size_ = 0;
  this->m_capacity_ = 0;
}

template <class value_type, class allocator_type>
void Vector<value_type, allocator_type>::pop_back() {
  if (this->empty()) throw std::runtime_error("Vector is empty!!");
  this->arr_[this->m_size_--];
}

template <class value_type, class allocator_type>
void Vector<value_type, allocator_type>::push_back(value_type v) {
  if (this->m_size_ >= this->m_capacity_) {
    reserve_more_capacity(this->m_size_ * 2, false);
  }
  this->arr_[this->m_size_++] = v;
}

template <class value_type, class allocator_type>
void Vector<value_type, allocator_type>::reserve_more_capacity(size_type size,
                                                               bool flag) {
  if (flag) {
    this->m_size_ = size;
  }
  value_type *buff = this->get_memory(size);

  for (size_t i = 0; i < this->m_size_; ++i) buff[i] = std::move(this->arr_[i]);

  delete[] this->arr_;
  this->arr_ = buff;
  this->m_capacity_ = size;
}

template <class value_type, class allocator_type>
void Vector<value_type, allocator_type>::reserve(size_type size) {
  if (size < 0) {
    throw std::length_error("Error size");
  }
  if (size <= this->m_capacity_) {
    return;
  }
  reserve_more_capacity(size, false);
}

template <class value_type, class allocator_type>
typename Vector<value_type, allocator_type>::size_type
Vector<value_type, allocator_type>::capacity() {
  return this->m_capacity_;
}

template <class value_type, class allocator_type>
void Vector<value_type, allocator_type>::shrink_to_fit() {
  reserve_more_capacity(this->m_size_, true);
}

// >>>>>>>> Modifiers <<<<<<<<

template <class value_type, class allocator_type>
void Vector<value_type, allocator_type>::clear() {
  if (this->arr_ != nullptr) {
    delete[] this->arr_;
  }
  this->arr_ = nullptr;
  this->m_size_ = 0;
}

template <class value_type, class allocator_type>
typename Vector<value_type, allocator_type>::iterator
Vector<value_type, allocator_type>::insert(iterator pos,
                                           const_reference value) {
  size_type position = &(*pos) - this->arr_;
  if (this->m_size_ + 1 >= this->m_capacity_) {
    this->reserve_more_capacity(this->m_capacity_ * 2, false);
  }
  value_type buff = this->arr_[position];
  this->m_size_++;
  this->arr_[position] = value;
  for (size_type i = position + 1; i < this->m_size_; ++i) {
    value_type buff_2 = this->arr_[i];
    this->arr_[i] = buff;
    buff = buff_2;
  }
  return this->arr_ + position;
}

template <class value_type, class allocator_type>
void Vector<value_type, allocator_type>::erase(iterator pos) {
  value_type *buff = new value_type[this->m_size_ - 1];
  for (size_type i = 0, t = 0; i < this->m_size_; i++)
    if ((this->begin() + i) != pos) buff[t++] = this->arr_[i];
  delete[] this->arr_;
  this->arr_ = buff;
  this->m_size_--;
}

template <typename value_type, class allocator_type>
template <typename... Args>
typename Vector<value_type, allocator_type>::iterator
Vector<value_type, allocator_type>::emplace(const_iterator pos,
                                            Args &&...args) {
  iterator it(pos);
  it = this->insert(it, value_type(std::forward<Args>(args)...));
  return it;
}

template <typename value_type, class allocator_type>
template <typename... Args>
void Vector<value_type, allocator_type>::emplace_back(Args &&...args) {
  this->push_back(value_type(std::forward<Args>(args)...));
}

}  // namespace s21
