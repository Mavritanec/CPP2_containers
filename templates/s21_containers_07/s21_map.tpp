namespace s21 {

template <typename Key, typename T>
map<Key, T>::map() : set<std::pair<Key, T>>() {}

template <typename Key, typename T>
map<Key, T>::map(std::initializer_list<value_type> const &items) : map() {
  for (auto it = items.begin(); it != items.end(); ++it) {
    insert(*it);
  }
}

template <typename Key, typename T>
map<Key, T>::map(const map &ms) : map() {
  this->copy_rec(ms.head_);
}

template <typename Key, typename T>
map<Key, T>::map(map &&ms) {
  this->swap(ms);
}

template <typename Key, typename T>
typename map<Key, T>::map map<Key, T>::operator=(map &&ms) {
  this->swap(ms);
  if (this->head_ != ms.head_) ms.clear();
  return *this;
}

template <typename Key, typename T>
typename map<Key, T>::map map<Key, T>::operator=(const map &ms) {
  if (this->head_ != ms.head_) {
    this->clear();
    this->copy_rec(ms.head_);
  }
  return *this;
}

template <typename Key, typename T>
typename map<Key, T>::mapped_type &map<Key, T>::at(const Key &key) {
  auto it = find(key);
  if (this->end() == it) {
    throw std::out_of_range("map:at");
  }
  return it->second;
}

template <typename Key, typename T>
typename map<Key, T>::iterator map<Key, T>::find(const key_type &key) {
  for (auto it = this->begin(); it != this->end(); ++it) {
    if (it->first == key) {
      return it;
    }
  }
  return this->end();
}

template <typename Key, typename T>
bool map<Key, T>::contains(const key_type &key) {
  if (this->find(key) == this->end()) return false;
  return true;
}

template <typename Key, typename T>
typename map<Key, T>::mapped_type &map<Key, T>::operator[](
    const key_type &&key) {
  return this->at(key);
}

template <typename Key, typename T>
std::pair<typename map<Key, T>::iterator, bool> map<Key, T>::insert(
    const value_type &value) {
  iterator result = this->add_item(value, value, &this->head_, nullptr);
  return std::pair<iterator, bool>(result, !result.isNull());
}

template <typename Key, typename T>
std::pair<typename map<Key, T>::iterator, bool> map<Key, T>::insert(
    const Key &key, const mapped_type &obj) {
  return this->insert({key, obj});
}

template <typename Key, typename T>
std::pair<typename map<Key, T>::iterator, bool> map<Key, T>::insert_or_assign(
    const Key &key, const mapped_type &obj) {
  iterator it = this->find(key);
  if (it != this->end()) {
    it->second = obj;
    return std::pair<iterator, bool>(it, true);
  }
  return this->insert({key, obj});
}

template <typename Key, typename T>
bool map<Key, T>::isLess(std::pair<Key, T> value1, std::pair<Key, T> value2) {
  return value1.first < value2.first;
}

template <typename Key, typename T>
bool map<Key, T>::isInsert(std::pair<Key, T> value1, std::pair<Key, T> value2) {
  return value1.first != value2.first;
}

template <typename Key, typename T>
void map<Key, T>::merge(map &other) {
  if (this->head_ != other.head_) {
    for (auto it = other.begin(); it != other.end(); ++it) {
      this->insert(it->first, it->second);
    }
  }
}

// template <typename Key, typename T>
// template <typename... Args>
// std::pair<typename map<Key, T>::SetIterator, bool> map<Key, T>::emplace(Args
// &&...args) {
//   std::initializer_list<value_type> items{args...};
//   std::pair<iterator, bool> result;
//   for (auto it = items.begin(); it != items.end(); ++it) {
//     result = insert(it);
//   }
//   return result;
// }

}  // namespace s21