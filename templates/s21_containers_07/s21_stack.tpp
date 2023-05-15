namespace s21 {

template <typename value_type>
stack<value_type>::stack() : list_() {}

template <typename value_type>
stack<value_type>::stack(std::initializer_list<value_type> const &items) {
  for (value_type x : items) {
    this->push(x);
  }
}

template <typename value_type>
stack<value_type>::stack(const stack<value_type> &s) : list_(s.list_) {}

template <typename value_type>
stack<value_type>::stack(stack<value_type> &&s) {
  list_.swap(s.list_);
  s.list_.clear();
}

template <typename value_type>
stack<value_type>::~stack<value_type>() {
  list_.clear();
}

template <typename value_type>
stack<value_type> &stack<value_type>::operator=(stack<value_type> &&s) {
  list_.clear();
  list_(s.list_);
  return *this;
}

template <typename value_type>
const value_type &stack<value_type>::top() {
  return list_.front();
}

template <typename value_type>
size_t stack<value_type>::size() {
  return list_.size();
}

template <typename value_type>
bool stack<value_type>::empty() {
  return list_.size() == 0;
}

template <typename value_type>
void stack<value_type>::push(const_reference value) {
  list_.push_front(value);
}

template <typename value_type>
void stack<value_type>::pop() {
  if (!empty()) {
    list_.pop_front();
  } else {
    throw std::out_of_range("Error: empty stack!");
  }
}

template <typename value_type>
void stack<value_type>::swap(stack<value_type> &other) {
  list_.swap(other.list_);
}

template <typename value_type>
template <class... Args>
void stack<value_type>::emplace_front(Args &&...args) {
  s21::stack<value_type> emplace_stack{args...};
  size_t stack_size = emplace_stack.size();
  for (size_t i = 0; i < stack_size; ++i) {
    this->push(emplace_stack.list_.back());
    emplace_stack.list_.pop_back();
  }
}
}  // namespace s21
