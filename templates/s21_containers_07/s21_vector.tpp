namespace s21 {

//* ===  Vector Member functions  ===
// default constructor
template <typename T>
vector<T>::vector() {
  arr_ = new T[0];
  capacity_ = 0;
}

// parameterized constructor
template <typename T>
vector<T>::vector(size_type n) : size_(n), capacity_(n) {
  arr_ = new T[n]();
}

template <typename T>
vector<T>::vector(size_type n, T value) : vector(n) {
  for (size_type i = 0; i < n; ++i) {
    arr_[i] = value;
  }
}

// initializer list constructor
template <typename T>
vector<T>::vector(std::initializer_list<value_type> const &items) : vector() {
  for (auto i = items.begin(); i != items.end(); ++i) {
    this->push_back(*i);
  }
}

// copy constructor
template <typename T>
vector<T>::vector(const vector &v) : vector(v.capacity_) {
  copy(v);
}

// move constructor
template <typename T>
vector<T>::vector(vector &&v) {
  this->arr_ = v.arr_;
  v.arr_ = nullptr;
  this->capacity_ = v.capacity_;
  this->size_ = v.size_;
}

// destructor
template <typename T>
vector<T>::~vector() {
  if (this->arr_ != nullptr) {
    delete[] arr_;
  }
}

// assignment operator overload for moving object
template <typename T>
typename vector<T>::vector &vector<T>::operator=(vector &&other) {
  if (this != &other) {
    this->arr_ = other.arr_;
    this->capacity_ = other.capacity_;
    this->size_ = other.size_;
    other.arr_ = nullptr;
  }
  return *this;
}

template <typename T>
typename vector<T>::vector &vector<T>::operator=(const vector &other) {
  resize(other.capacity_);
  copy(other);
  return *this;
}

//* ===  Vector Element access ===
// access specified element with bounds checking
template <typename T>
T &vector<T>::at(size_type position) {
  if (position >= size_)
    throw std::out_of_range("index is out of vector range");
  return arr_[position];
}

//* ===  Vector Capacity  ===
// returns the number of elements
template <typename T>
typename vector<T>::size_type vector<T>::size() const {
  return this->size_;
}

// returns the maximum possible number of elements
template <typename T>
typename vector<T>::size_type vector<T>::max_size() const {
  std::allocator<vector<T>::value_type> tmp;
  return tmp.max_size();
}

// allocate storage of size elements
template <typename T>
void vector<T>::reserve(size_type size) {
  if (size > this->capacity_) {
    resize(size);
  }
}

// reduces memory usage by freeing unused memory
template <typename T>
void vector<T>::shrink_to_fit() {
  if (this->size_ < this->capacity_) {
    resize(this->size_);
  }
}

//* ===  Vector Modifiers  ===
// inserts elements into concrete pos and returns the iterator that points to
// the new element
template <typename T>
typename vector<T>::VectorIterator vector<T>::insert(VectorIterator position,
                                                     const_reference value) {
  VectorIterator myit = this->begin();
  VectorIterator it_ = position;
  s21::vector<value_type> tmp;
  int count = 0;

  for (auto i = this->begin(); i != position; ++i) {
    tmp.push_back(*i);
    count++;
  }
  tmp.push_back(value);
  count++;
  for (auto i = position; i != end(); ++i) {
    tmp.push_back(*i);
  }
  if (this->arr_ != nullptr) {
    delete[] arr_;
  }
  this->arr_ = tmp.arr_;
  this->size_ = tmp.size_;
  this->capacity_ = tmp.capacity_;
  tmp.arr_ = nullptr;
  auto result_it = this->begin();
  while (count > 0) {
    count--;
    ++result_it;
  }
  return result_it;
}

// erases element at pos
template <typename T>
void vector<T>::erase(VectorIterator position) {
  if (!empty()) {
    VectorIterator it_ = position + 1;
    while (it_ != end()) {
      *position = std::move(*it_);
      ++position;
      ++it_;
    }
    --size_;
  }
}

// adds an element to the end
template <typename T>
void vector<T>::push_back(T value) {
  if (size_ == capacity_) {
    capacity_ < 4 ? resize(capacity_ + 1) : resize(capacity_ * 2);
  }
  arr_[size_] = value;
  ++size_;
}

// swaps the contents
template <typename T>
void vector<T>::swap(vector &other) {
  std::swap(capacity_, other.capacity_);
  std::swap(size_, other.size_);
  std::swap(arr_, other.arr_);
}

template <typename T>
void vector<T>::copy(const vector &other) {
  for (size_type i = 0; i < other.size_; ++i) {
    this->arr_[i] = other.arr_[i];
  }
  this->size_ = other.size_;
  this->capacity_ = other.capacity_;
}

template <typename T>
void vector<T>::resize(size_type new_size) {
  vector tmp(new_size);
  for (size_type i = 0; i < this->size_; ++i) {
    tmp.arr_[i] = this->arr_[i];
  }
  delete[] this->arr_;
  this->arr_ = tmp.arr_;
  this->capacity_ = tmp.capacity_;
  tmp.arr_ = nullptr;
}

//* === Bonus ===
template <typename T>
template <typename... Args>
typename vector<T>::VectorIterator vector<T>::emplace(VectorIterator pos,
                                                      Args &&...args) {
  s21::vector<int> vctr{args...};
  auto tmp = pos;
  VectorIterator value = vctr.begin();
  size_t count = vctr.size();
  for (size_t i = 0; i < count; ++i) {
    tmp = insert(tmp, *value);
    ++value;
  }
  return tmp;
}

template <typename T>
template <typename... Args>
void vector<T>::emplace_back(Args &&...args) {
  emplace(this->cend(), args...);
}

///// class VectorIterator ///////

template <typename T>
vector<T>::VectorIterator::VectorIterator() : ptr_(nullptr) {}

template <typename T>
vector<T>::VectorIterator::VectorIterator(T *arr_ptr) : ptr_(arr_ptr) {}

template <typename T>
vector<T>::VectorIterator::VectorIterator(const VectorIterator &other)
    : ptr_(other.ptr_) {}

template <typename T>
typename vector<T>::VectorIterator &vector<T>::VectorIterator::operator=(
    const VectorIterator &other) {
  ptr_ = other.ptr_;
  return *this;
}

template <typename T>
typename vector<T>::VectorIterator &vector<T>::VectorIterator::operator++() {
  ++ptr_;
  return *this;
}

template <typename T>
typename vector<T>::VectorIterator &vector<T>::VectorIterator::operator--() {
  --ptr_;
  return *this;
}

template <typename T>
typename vector<T>::VectorIterator &vector<T>::VectorIterator::operator+=(
    int n) {
  ptr_ += n;
  return *this;
}

template <typename T>
typename vector<T>::VectorIterator &vector<T>::VectorIterator::operator-=(
    int n) {
  ptr_ -= n;
  return *this;
}

template <typename T>
typename vector<T>::VectorIterator vector<T>::VectorIterator::operator+(int n) {
  VectorIterator it = *this;
  return it += n;
}

template <typename T>
typename vector<T>::VectorIterator vector<T>::VectorIterator::operator-(int n) {
  VectorIterator it = *this;
  return it -= n;
}

template <typename T>
bool vector<T>::VectorIterator::operator==(const VectorIterator &other) {
  return ptr_ == other.ptr_;
}

template <typename T>
bool vector<T>::VectorIterator::operator!=(const VectorIterator &other) {
  return !(ptr_ == other.ptr_);
}
template <typename T>
bool vector<T>::VectorIterator::operator>(const VectorIterator &other) {
  return ptr_ > other.ptr_;
}
template <typename T>
bool vector<T>::VectorIterator::operator<(const VectorIterator &other) {
  return ptr_ < other.ptr_;
}
template <typename T>
bool vector<T>::VectorIterator::operator>=(const VectorIterator &other) {
  return !(ptr_ < other.ptr_);
}
template <typename T>
bool vector<T>::VectorIterator::operator<=(const VectorIterator &other) {
  return !(ptr_ > other.ptr_);
}

}  // namespace s21