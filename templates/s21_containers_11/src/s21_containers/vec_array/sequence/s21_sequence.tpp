namespace s21 {

//  >>>>>>>>>>>>>> Access <<<<<<<<<<<<<<<<<<<<<<
template <class value_type>
typename abstract<value_type>::reference abstract<value_type>::at(
    size_type pos) {
  if (pos > this->m_size_) throw std::out_of_range("Out of range");
  return this->arr_[pos];
}

template <class value_type>
typename abstract<value_type>::reference abstract<value_type>::operator[](
    size_type pos) {
  return this->arr_[pos];
}

template <class value_type>
typename abstract<value_type>::const_reference abstract<value_type>::front() {
  if (this->empty()) {
    throw std::out_of_range("In origin vector here segmentation fault");
  }
  return this->at(0);
}

template <class value_type>
typename abstract<value_type>::const_reference abstract<value_type>::back() {
  if (this->empty()) {
    throw std::out_of_range("In origin vector here segmentation fault");
  }
  return this->at(this->m_size_ - 1);
}

// >>>>>>>>>>>>> Const Iterator <<<<<<<<<<<<<<<<<<<<<<<<
template <class value_type>
abstract<value_type>::ConstIterator::ConstIterator() {
  this->data_ = nullptr;
}

template <class value_type>
abstract<value_type>::ConstIterator::ConstIterator(pointer pt) {
  this->data_ = pt;
}

template <class value_type>
typename abstract<value_type>::const_reference
abstract<value_type>::ConstIterator::operator*() {
  if (this->data_ == nullptr)
    throw std::invalid_argument("Bad <*> parameters!");
  return *this->data_;
}

template <class value_type>
bool abstract<value_type>::ConstIterator::operator!=(
    const ConstIterator &other) const {
  return this->data_ != other.data_;
}

template <class value_type>
bool abstract<value_type>::ConstIterator::operator==(
    const ConstIterator &other) const {
  return this->data_ == other.data_;
}

template <class value_type>
typename abstract<value_type>::ConstIterator
abstract<value_type>::ConstIterator::operator+(const size_t value) {
  ConstIterator it_const(this->data_ + value);
  return it_const;
}

template <class value_type>
typename abstract<value_type>::ConstIterator &
abstract<value_type>::ConstIterator::operator++() {
  this->data_++;
  return *this;
}

template <class value_type>
typename abstract<value_type>::ConstIterator
abstract<value_type>::ConstIterator::operator++(int) {
  ConstIterator temp(*this);
  this->data_++;
  return temp;
}

template <class value_type>
typename abstract<value_type>::ConstIterator &
abstract<value_type>::ConstIterator::operator--() {
  this->data_--;
  return *this;
}

template <class value_type>
typename abstract<value_type>::ConstIterator
abstract<value_type>::ConstIterator::operator--(int) {
  ConstIterator temp(*this);
  this->data_--;
  return temp;
}

// >>>>>>>>>>>>> Iterator  <<<<<<<<<<<<<<<<<<<<<<<<
template <class value_type>
abstract<value_type>::Iterator::Iterator() : ConstIterator() {}

template <class value_type>  // see this function need some fixed
abstract<value_type>::Iterator::Iterator(pointer pt) : ConstIterator(pt) {}

template <class value_type>
typename abstract<value_type>::reference
abstract<value_type>::Iterator::operator*() {
  if (this->data_ == nullptr)
    throw std::invalid_argument("Bad <*> parameters!");
  return *this->data_;
}

template <class value_type>
typename abstract<value_type>::Iterator &
abstract<value_type>::Iterator::operator=(const value_type& val) {
  *this->data_ = val;
  return *this->data_;
}

template <class value_type>
typename abstract<value_type>::Iterator
abstract<value_type>::Iterator::operator+(const size_t value) {
  Iterator it(this->data_ + value);
  return it;
}

template <class value_type>
typename abstract<value_type>::Iterator
abstract<value_type>::Iterator::operator-(const size_t value) {
  Iterator it(this->data_ - value);
  return it;
}

template <class value_type>
typename abstract<value_type>::Iterator
abstract<value_type>::Iterator::operator-(const Iterator &value) {
  return this->data_ - value;
}
//    VectorIterator operator-(const VectorIterator &value);

template <class value_type>
typename abstract<value_type>::iterator abstract<value_type>::data() {
  return this->begin();
}

//   >>>>>>>>>>>> Iterator begin end <<<<<<<<<<<<<<<<<<<<
template <class value_type>
typename abstract<value_type>::iterator abstract<value_type>::begin() {
  iterator temp(this->arr_);
  return temp;
}

template <class value_type>
typename abstract<value_type>::iterator abstract<value_type>::end() {
  iterator temp(this->arr_ + this->m_size_);
  return temp;
}

//  >>>>>>>>>>> Capacity <<<<<<<<<<<<<<<

template <class value_type>
bool abstract<value_type>::empty() const noexcept {
  return this->m_size_ > 0 ? false : true;
}

template <class value_type>
typename abstract<value_type>::size_type abstract<value_type>::size()
    const noexcept {
  return this->m_size_;
}

template <class value_type>
typename abstract<value_type>::size_type abstract<value_type>::max_size()
    const noexcept {
  char bits = 63;
  if (sizeof(void *) == 4) {
    bits = 31;
  }
  return static_cast<size_type>(pow(2, bits)) / sizeof(value_type) - 1;
}

}  //  namespace s21
