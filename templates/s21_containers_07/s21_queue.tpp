namespace s21 {

template <typename value_type>
queue<value_type>::queue() : list_() {}

template <typename value_type>
queue<value_type>::queue(const std::initializer_list<value_type> &items)
    : list_(items) {}

template <typename value_type>
queue<value_type>::queue(const queue<value_type> &q) : list_(q.list_) {}

template <typename value_type>
queue<value_type>::queue(queue<value_type> &&q) {
  list_.swap(q.list_);
  q.list_.clear();
}

template <typename value_type>
queue<value_type>::~queue<value_type>() {
  list_.clear();
}

template <typename value_type>
queue<value_type> &queue<value_type>::operator=(queue<value_type> &&q) {
  list_.clear();
  list_(q.list_);
  return *this;
}

template <typename value_type>
const value_type &queue<value_type>::front() {
  return list_.front();
}

template <typename value_type>
const value_type &queue<value_type>::back() {
  return list_.back();
}

template <typename value_type>
bool queue<value_type>::empty() {
  return list_.size() == 0;
}

template <typename value_type>
size_t queue<value_type>::size() {
  return list_.size();
}

template <typename value_type>
void queue<value_type>::push(const_reference value) {
  list_.push_back(value);
}

template <typename value_type>
void queue<value_type>::pop() {
  if (!empty()) {
    list_.pop_front();
  } else {
    throw std::out_of_range("Error: empty queue!");
  }
}

template <typename value_type>
void queue<value_type>::swap(queue<value_type> &other) {
  list_.swap(other.list_);
}

template <typename value_type>
template <class... Args>
void queue<value_type>::emplace_back(Args &&...args) {
  list_.emplace_back(args...);
}

}  // namespace s21
