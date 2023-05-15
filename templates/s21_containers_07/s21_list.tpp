namespace s21 {

// Constructor & detructor //

// Node

template <typename value_type>
list<value_type>::Node::Node() {
  prev_ = nullptr;
  next_ = nullptr;
}

template <typename value_type>
list<value_type>::Node::Node(value_type value) : Node() {
  value_ = value;
}

// Iterator

template <typename value_type>
list<value_type>::iterator::ListIterator() : current_(nullptr) {}

template <typename value_type>
list<value_type>::iterator::ListIterator(Node *ptr) : current_(ptr) {}

template <typename value_type>
typename list<value_type>::value_type list<value_type>::iterator::operator*() {
  if (current_ == nullptr) {
    throw std::invalid_argument("invalid argument");
  }
  return current_->value_;
}

template <typename value_type>
typename list<value_type>::iterator &list<value_type>::iterator::operator++() {
  if (current_) {
    current_ = current_->next_;
  }
  return *this;
}

template <typename value_type>
bool list<value_type>::iterator::operator==(const iterator &other) {
  return this->current_ == other.current_;
}

template <typename value_type>
bool list<value_type>::iterator::operator!=(const iterator &other) {
  return this->current_ != other.current_;
}

template <typename value_type>
list<value_type>::ListConstIterator::ListConstIterator() : ListIterator() {}

template <typename value_type>
const typename list<value_type>::value_type
list<value_type>::ListConstIterator::operator*() {
  return ListIterator::operator*();
}

template <typename value_type>
const typename list<value_type>::ListConstIterator &
list<value_type>::ListConstIterator::operator++() {
  return ListIterator::operator++();
}

// List

template <typename value_type>
list<value_type>::list() : head_(nullptr), tail_(nullptr), size_(0) {
  base_ = new Node;
}

template <typename value_type>
list<value_type>::list(size_type n) : list() {
  for (size_type i = 0; i < n; ++i) {
    this->push_back(0);
  }
}

template <typename value_type>
list<value_type>::list(std::initializer_list<value_type> const &items)
    : list() {
  for (auto &it : items) this->push_back(it);
}

template <typename value_type>
list<value_type>::list(const list &other) : list() {
  Node *it = other.head_;
  while (it != other.base_) {
    this->push_back(it->value_);
    it = it->next_;
  }
}

template <typename value_type>
list<value_type>::list(list &&other) : list() {
  this->swap(other);
}

template <typename value_type>
list<value_type> &list<value_type>::operator=(list &&other) {
  this->swap(other);
  return *this;
}

template <typename value_type>
list<value_type> &list<value_type>::operator=(const list &other) {
  this->clear();
  size_ = 0;
  iterator it = this->begin();
  for (size_type i = 0; i < other.size_; ++i) {
    push_back(it.getCurrent()->value_);
    ++it;
  }
  return *this;
}

template <typename value_type>
list<value_type>::~list() {
  clear();
  delete base_;
}

// List Element access //

template <typename value_type>
typename list<value_type>::const_reference list<value_type>::front() {
  if (empty()) {
    throw std::out_of_range("list is empty");
  }
  return head_->value_;
}

template <typename value_type>
typename list<value_type>::const_reference list<value_type>::back() {
  if (empty()) {
    throw std::out_of_range("list is empty");
  }
  return tail_->value_;
}

// List Iterators //

template <typename value_type>
typename list<value_type>::iterator list<value_type>::begin() {
  return iterator(head_);
}

template <typename value_type>
typename list<value_type>::iterator list<value_type>::end() {
  return iterator(base_);
}

template <typename value_type>
typename list<value_type>::iterator list<value_type>::rbegin() {
  return iterator(tail_);
}

// List Capacity //

template <typename value_type>
bool list<value_type>::empty() {
  return head_ == nullptr;
}

template <typename value_type>
size_t list<value_type>::size() {
  return size_;
}

template <typename value_type>
size_t list<value_type>::max_size() {
  return std::numeric_limits<size_t>::max() / sizeof(Node) / 2;
}

// List Modifiers //

template <typename value_type>
void list<value_type>::clear() {
  while (size_ != 0) {
    pop_back();
  }
  head_ = nullptr;
  tail_ = nullptr;
}

template <typename value_type>
typename list<value_type>::iterator list<value_type>::insert(
    iterator pos, const_reference value) {
  if (pos == begin()) {
    push_front(value);
  } else if (pos == end()) {
    push_back(value);
  } else {
    Node *tmp = pos.getCurrent();
    Node *newNode = new Node(value);
    newNode->next_ = tmp;
    newNode->prev_ = tmp->prev_;
    tmp->prev_->next_ = newNode;
    tmp->prev_ = newNode;
    ++size_;
    base_->value_ = (int)size_;
  }
  return pos;
}

template <typename value_type>
void list<value_type>::erase(iterator pos) {
  Node *tmp = pos.getCurrent();
  Node *del;
  if (tmp == nullptr || tmp == base_)
    throw std::out_of_range("insert : iterator point to null");
  if (tmp == head_) head_ = tmp->next_;
  if (tmp == tail_) tail_ = tmp->prev_;
  del = tmp;
  tmp->prev_->next_ = tmp->next_;
  tmp->next_->prev_ = tmp->prev_;
  --size_;
  base_->value_ = (int)size_;
  delete del;
}

template <typename value_type>
void list<value_type>::push_front(const value_type &value) {
  Node *tmp = new Node(value);
  tmp->value_ = value;

  if (head_ == nullptr) {
    tmp->next_ = base_;
  } else {
    tmp->next_ = head_;
  }
  tmp->prev_ = base_;
  if (head_ != nullptr) {
    head_->prev_ = tmp;
  }
  head_ = tmp;
  if (tail_ == nullptr) {
    tail_ = tmp;
  }
  ++size_;
  base_->prev_ = tail_;
  base_->next_ = head_;
  base_->value_ = (int)size_;
}

template <typename value_type>
void list<value_type>::push_back(const value_type &value) {
  Node *tmp = new Node(value);
  tmp->value_ = value;
  if (tail_ == nullptr) {
    tmp->prev_ = base_;
  } else {
    tmp->prev_ = tail_;
  }
  tmp->next_ = base_;
  if (tail_ != nullptr) {
    tail_->next_ = tmp;
  }
  tail_ = tmp;
  if (head_ == nullptr) {
    head_ = tmp;
  }
  ++size_;
  base_->prev_ = tail_;
  base_->next_ = head_;
  base_->value_ = (int)size_;
}

template <typename value_type>
void list<value_type>::pop_front() {
  if (size_ == 0) throw std::out_of_range("List is empty");
  Node *tmp = head_->next_;
  tmp->prev_ = base_;
  head_->next_->prev_ = base_;
  base_->next_ = tmp;
  delete head_;
  --size_;
  if (size_)
    head_ = tmp;
  else
    head_ = nullptr;
  base_->value_ = (int)size_;
}

template <typename value_type>
void list<value_type>::pop_back() {
  if (size_ == 0) throw std::out_of_range("List is empty");
  Node *tmp = tail_->prev_;
  tmp->next_ = base_;
  tail_->prev_->next_ = base_;
  base_->prev_ = tmp;
  delete tail_;
  --size_;
  if (size_)
    tail_ = tmp;
  else
    tail_ = nullptr;
  base_->value_ = (int)size_;
}

template <typename value_type>
void list<value_type>::swap(list &other) {
  Node *swap_head = head_, *swap_tail = tail_, *swap_base = base_;
  size_type swap_size = size_;
  head_ = other.head_;
  tail_ = other.tail_;
  size_ = other.size_;
  base_ = other.base_;
  other.head_ = swap_head;
  other.tail_ = swap_tail;
  other.size_ = swap_size;
  other.base_ = swap_base;
}

template <typename value_type>
void list<value_type>::reverse() {
  if (size_ > 1) {
    value_type tmp;
    int count = size_ / 2;
    for (Node *it_begin = head_, *it_end = tail_; count != 0;
         it_begin = it_begin->next_, it_end = it_end->prev_) {
      tmp = it_begin->value_;
      it_begin->value_ = it_end->value_;
      it_end->value_ = tmp;
      --count;
    }
    base_->prev_ = tail_;
    base_->next_ = head_;
  }
}

template <typename value_type>
void list<value_type>::unique() {
  if (size_ > 1) {
    iterator it = this->begin();
    while (it != this->rbegin()) {
      iterator it_prev = it;
      ++it;
      if (*it == *it_prev) {
        this->erase(it_prev);
      }
    }
  }
}

template <typename value_type>
void list<value_type>::splice(iterator pos, list &other) {
  iterator it = other.begin();
  for (size_t i = 0; i < other.size(); ++i) {
    insert(pos, *it);
    ++it;
  }
  other.clear();
}

template <typename value_type>
void list<value_type>::merge(list &other) {
  iterator it = this->begin();
  iterator it_other = other.begin();
  while (*it_other >= *it) ++it;
  this->splice(it, other);
}

template <typename value_type>
void list<value_type>::sort() {
  if (size_ < 2) {
    return;
  }
  value_type tmp;
  for (Node *it_i = head_; it_i != base_; it_i = it_i->next_) {
    for (Node *it_j = head_; it_j != base_; it_j = it_j->next_) {
      if (it_j->value_ > it_i->value_) {
        tmp = it_j->value_;
        it_j->value_ = it_i->value_;
        it_i->value_ = tmp;
      }
    }
  }
}

template <typename value_type>
void list<value_type>::print_list() {
  Node *tmp = head_;
  std::cout << "HEAD  ";
  while (tmp != nullptr) {
    std::cout << tmp->value_ << " -> ";
    tmp = tmp->next_;
  }
  std::cout << std::endl;
}

// bonus foo //

template <typename value_type>
template <class... Args>
typename list<value_type>::ListIterator list<value_type>::emplace(
    iterator pos, Args &&...args) {
  s21::list<value_type> emplace_list{args...};
  iterator emplace_it = emplace_list.begin();
  for (size_t i = 0; i < emplace_list.size(); ++i) {
    pos = this->insert(pos, *emplace_it);
    ++emplace_it;
  }
  return pos;
}

template <typename value_type>
template <class... Args>
void list<value_type>::emplace_back(Args &&...args) {
  emplace(end(), args...);
}

template <typename value_type>
template <class... Args>
void list<value_type>::emplace_front(Args &&...args) {
  emplace(begin(), args...);
}

}  // namespace s21