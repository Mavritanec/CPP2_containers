namespace s21 {

template <typename T>
set<T>::Node::Node() : value_(0) {
  root_ = nullptr;
  left_ = nullptr;
  right_ = nullptr;
}

template <typename T>
set<T>::Node::Node(T value, Node *root) : value_(value) {
  root_ = root;
  left_ = nullptr;
  right_ = nullptr;
}

template <typename T>
set<T>::SetIterator::SetIterator(Node *ptr) {
  current = ptr;
}

template <typename T>
set<T>::SetIterator::SetIterator() : SetIterator(nullptr) {}

template <typename T>
typename set<T>::value_type set<T>::SetIterator::operator*() {
  if (current == nullptr) throw std::invalid_argument("invalid argument");
  return current->value_;
}

template <typename T>
typename set<T>::SetIterator &set<T>::SetIterator::operator++() {
  if (current != nullptr) {
    if (current->right_ != nullptr) {
      current = current->right_;
      while (current->left_ != nullptr) current = current->left_;
    } else {
      while (current->root_ != nullptr &&
             current->value_ >= current->root_->value_) {
        current = current->root_;
      }
      current = current->root_;
    }
  }
  return *this;
}

template <typename T>
typename set<T>::value_type *set<T>::SetIterator::operator->() {
  if (current != nullptr) return &(current->value_);
  throw std::out_of_range("Iterator::operator*(nullptr)");
}

template <typename T>
bool set<T>::SetIterator::operator==(const SetIterator &other) {
  return current == other.current;
}

template <typename T>
bool set<T>::SetIterator::operator!=(const SetIterator &other) {
  return current != other.current;
}

template <typename T>
void set<T>::SetIterator::setCurrent(Node *value) {
  this->current = value;
}

template <typename T>
bool set<T>::SetIterator::isNull() {
  return current == nullptr;
}

template <typename T>
set<T>::set() : head_(nullptr) {}

template <typename T>
set<T>::set(std::initializer_list<value_type> const &items) : set() {
  for (auto it = items.begin(); it != items.end(); ++it) {
    insert(*it);
  }
}

template <typename T>
set<T>::set(set &s) : set() {
  copy_rec(s.head_);
}

template <typename T>
set<T>::set(set &&s) : set() {
  this->swap(s);
}

template <typename T>
set<T>::~set() {
  free_rec(head_);
}

template <typename T>
typename set<T>::Node *set<T>::get_head() {
  return this->head_;
}

template <typename T>
void set<T>::set_head(Node *value) {
  this->head_ = value;
}

template <typename T>
void set<T>::copy_rec(Node *head) {
  if (head != nullptr) {
    copy_rec(head->left_);
    copy_rec(head->right_);
    this->insert(head->value_);
  }
}

template <typename T>
void set<T>::free_rec(Node *head) {
  if (head != nullptr) {
    free_rec(head->left_);
    free_rec(head->right_);
    delete (head);
  }
}

template <typename T>
typename set<T>::set &set<T>::operator=(const set &other) {
  if (this->head_ != other.head_) {
    this->clear();
    this->copy_rec(other.head_);
  }
  return *this;
}

template <typename T>
typename set<T>::set &set<T>::operator=(set &&other) {
  this->swap(other);
  if (this->head_ != other.head_) other.clear();
  return *this;
}

template <typename T>
typename set<T>::iterator set<T>::begin() {
  return SetIterator(minimum(head_));
}

template <typename T>
typename set<T>::iterator set<T>::end() {
  return SetIterator();
}

template <typename T>
bool set<T>::empty() {
  if (head_ != nullptr) {
    if (head_->left_ == nullptr && head_->right_ == nullptr &&
        head_->root_ == nullptr)
      return false;
  }
  return true;
}

template <typename T>
typename set<T>::size_type set<T>::size() {
  return size_rec(this->head_);
}

template <typename T>
typename set<T>::size_type set<T>::size_rec(Node *ptr) const {
  if (ptr != nullptr) return size_rec(ptr->left_) + size_rec(ptr->right_) + 1;
  return 0;
}

template <typename T>
typename set<T>::size_type set<T>::max_size() {
  return std::numeric_limits<size_t>::max() / sizeof(Node);
}
template <typename T>
void set<T>::clear() {
  free_rec(head_);
  head_ = nullptr;
}
template <typename T>
void set<T>::erase(iterator pos) {
  if (pos.isNull() || size() == 0)
    throw std::invalid_argument("iterator can't be equal nullptr");
  head_ = erase_rec(head_, *pos);
}

template <typename T>
typename set<T>::Node *set<T>::erase_rec(Node *ptr, key_type key) {
  Node *tmp = nullptr;
  if (ptr == nullptr) return ptr;
  if (key < get_key(ptr->value_))
    ptr->left_ = erase_rec(ptr->left_, key);
  else if (key > get_key(ptr->value_))
    ptr->right_ = erase_rec(ptr->right_, key);
  else if (ptr->left_ != nullptr and ptr->right_ != nullptr) {
    ptr->value_ = minimum(ptr->right_)->value_;
    ptr->right_ = erase_rec(ptr->right_, ptr->value_);
  } else if (ptr->left_ != nullptr) {
    tmp = ptr;
    ptr = ptr->left_;
    ptr->root_ = tmp->root_;
  } else if (ptr->right_ != nullptr) {
    tmp = ptr;
    ptr = ptr->right_;
    ptr->root_ = tmp->root_;
  } else {
    tmp = ptr;
    ptr = nullptr;
  }
  if (tmp != nullptr) {
    delete (tmp);
  }
  return ptr;
}

template <typename T>
typename set<T>::key_type set<T>::get_key(value_type value) {
  return value;
};

template <typename T>
void set<T>::swap(set &other) {
  if (this->head_ != other.head_) {
    Node *tmp = this->head_;
    this->head_ = other.head_;
    other.head_ = tmp;
  }
}

template <typename T>
void set<T>::merge(set &other) {
  if (this->head_ != other.head_) {
    for (auto it = other.begin(); it != other.end(); ++it) {
      this->insert(*it);
    }
  }
}

template <typename T>
typename set<T>::iterator set<T>::find(const key_type &key) {
  for (auto it = this->begin(); it != this->end(); ++it) {
    if (*it == key) {
      return it;
    }
  }
  return this->end();
}

template <typename T>
bool set<T>::contains(const key_type &key) {
  if (find(key) != end()) return true;
  return false;
}

template <typename T>
std::pair<typename set<T>::SetIterator, bool> set<T>::insert(
    const typename set<T>::value_type &value) {
  iterator result = add_item(key_type(value), value, &head_, nullptr);
  return std::pair<set<T>::SetIterator, bool>(result, !result.isNull());
}

template <typename T>
typename set<T>::iterator set<T>::add_item(key_type key, value_type value,
                                           Node **ptr_head, Node *root) {
  if (*ptr_head == nullptr) {
    (*ptr_head) = new Node(value, root);
    (*ptr_head)->value_ = value;
    (*ptr_head)->left_ = (*ptr_head)->right_ = nullptr;
    (*ptr_head)->root_ = root;
    return SetIterator(*ptr_head);
  } else {
    if (isLess(value, (*ptr_head)->value_)) {
      add_item(key, value, &(*ptr_head)->left_, *ptr_head);
    } else if (isInsert(value, (*ptr_head)->value_))
      add_item(key, value, &(*ptr_head)->right_, *ptr_head);
  }
  return SetIterator();
}

template <typename T>
bool set<T>::isInsert(value_type value1, value_type value2) {
  return value1 != value2;
}

template <typename T>
bool set<T>::isLess(value_type value1, value_type value2) {
  return value1 < value2;
}

template <typename T>
typename set<T>::Node *set<T>::minimum(Node *ptr) {
  if (ptr == nullptr) return nullptr;
  while (ptr->left_ != nullptr) {
    ptr = ptr->left_;
  }
  return ptr;
}

template <typename T>
template <typename... Args>
vector<std::pair<typename set<T>::SetIterator, bool>> set<T>::emplace(
    Args &&...args) {
  std::initializer_list<value_type> items{args...};
  vector<std::pair<iterator, bool>> result;
  for (auto it = items.begin(); it != items.end(); ++it) {
    result.push_back(insert(*it));
  }
  return result;
}

}  // namespace s21
