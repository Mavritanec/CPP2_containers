namespace s21 {

template <typename T>
multiset<T>::multiset() : set<value_type>() {
  null_node = new Node(0, nullptr);
}

template <typename T>
multiset<T>::multiset(std::initializer_list<value_type> const &items)
    : multiset() {
  for (auto it = items.begin(); it != items.end(); ++it) {
    insert(*it);
  }
}

template <typename T>
multiset<T>::multiset(const multiset &ms) : multiset() {
  this->copy_rec(ms.head_);
}

template <typename T>
multiset<T>::multiset(multiset &&ms) : multiset() {
  this->swap(ms);
}

template <typename T>
multiset<T>::~multiset() {
  delete null_node;
}

template <typename T>
typename multiset<T>::multiset multiset<T>::operator=(multiset &&ms) {
  this->swap(ms);
  if (this->head_ != ms.head_) ms.clear();
  return *this;
}

template <typename T>
typename multiset<T>::multiset multiset<T>::operator=(const multiset &ms) {
  if (this->head_ != ms.head_) {
    this->clear();
    this->copy_rec(ms.head_);
  }
  return *this;
}

template <typename T>
std::pair<typename multiset<T>::iterator, typename multiset<T>::iterator>
multiset<T>::equal_range(const key_type &key) {
  std::pair<iterator, iterator> it;
  it.first = this->lower_bound(key);
  it.second = this->upper_bound(key);
  return it;
}

template <typename T>
typename multiset<T>::iterator multiset<T>::lower_bound(const key_type &key) {
  int count = 0;
  for (auto tmp = this->begin(); tmp != this->end(); ++tmp) {
    if (!this->isLess(*tmp, key)) return tmp;
    ++count;
  }
  iterator it = this->begin();
  it.setCurrent(null_node);
  null_node->value_ = count;
  return it;
}
template <typename T>
typename multiset<T>::iterator multiset<T>::upper_bound(const key_type &key) {
  int count = 0;
  for (auto tmp = this->begin(); tmp != this->end(); ++tmp) {
    if (this->isLess(key, *tmp)) return tmp;
    ++count;
  }
  auto it = this->begin();
  it.setCurrent(null_node);
  null_node->value_ = count;
  return it;
}

template <typename T>
typename multiset<T>::iterator multiset<T>::insert(const value_type &value) {
  iterator result = this->add_item(value, value, &this->head_, nullptr);
  return result;
}

template <typename T>
bool multiset<T>::isInsert(value_type value1, value_type value2) {
  if (value1 == value2) return true;
  return true;
}
}  // namespace s21