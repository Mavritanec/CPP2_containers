#include "s21_list.h"

namespace s21 {
template <class value_type>
list<value_type>::list() {
  this->InitList();
}

template <class value_type>
list<value_type>::list(size_type n) {
  if (n >= max_size())
    throw std::out_of_range("Limit of the container is exceeded");
  this->InitList();
  for (; n > 0; --n) {
    push_back(this->two_with_->value_);
  }
}

template <class value_type>
list<value_type>::list(std::initializer_list<value_type> const& items) {
  this->InitList();
  for (auto& i : items) {
    this->push_back(i);
  }
}

template <class value_type>
list<value_type>::list(const list& l) {
  this->InitList();
  *this = l;
}

template <class value_type>
list<value_type>::list(list&& l) {
  if (this == &l) {
    throw std::invalid_argument("Error move!");
  }
  this->InitList();
  this->SwapList(l);
}
//  Modifiers
template <class value_type>
list<value_type>::~list() {
  this->clear();
  delete this->two_with_;
  //        this->tail_->prev_->next_ = nullptr;
  //        for (node* point = this->head_; point != nullptr; point =
  //        point->next_) {
  //            delete point;
  //        }
}

template <class value_type>
typename list<value_type>::iterator list<value_type>::insert(
    iterator pos, const_reference value) {
  node* element = pos.data_;
  node* convertion = new node(value);
  convertion->next_ = element;
  convertion->prev_ = element->prev_;
  element->prev_->next_ = convertion;
  element->prev_ = convertion;
  this->m_size_++;
  return Iterator(convertion);
}

template <class value_type>
void list<value_type>::erase(iterator pos) {
  node* element = pos.data_;
  element->prev_->next_ = element->next_;
  element->next_->prev_ = element->prev_;
  delete element;
  this->m_size_--;
}

template <class value_type>
void list<value_type>::swap(list& other) {
  this->SwapList(other);
}

template <class value_type>
void list<value_type>::merge(list& other) {
  if (this != &other) {
    iterator oit = other.begin();
    iterator it = this->begin();
    while (!other.empty()) {
      if (it == this->end()) {
        this->insert(it, *oit);
        other.erase(oit);
        ++oit;
      } else if (*oit < *it) {
        this->insert(it, *oit);
        other.erase(oit);
        ++oit;
      } else {
        ++it;
      }
    }
  }
}

template <class value_type>
void list<value_type>::splice(const_iterator pos, list& other) {
  for (iterator iter = other.begin(); iter != other.end(); ++iter) {
    this->insert(pos, *iter);
    other.erase(iter);
  }
}

template <class value_type>
void list<value_type>::reverse() {
  node* tmp = this->two_with_->next_;
  std::swap(this->two_with_->next_, this->two_with_->prev_);
  while (tmp != this->two_with_) {
    std::swap(tmp->prev_, tmp->next_);
    tmp = tmp->prev_;
  }
}

template <class value_type>
void list<value_type>::unique() {
  for (iterator iter = this->begin(); iter != this->end();) {
    if (*iter == *(++iter)) {
      this->erase(iter);
    }
  }
}

template <class value_type>
list<value_type>& list<value_type>::operator=(list&& other) {
  if (this == &other) {
    throw std::invalid_argument("Error move!");
  }
  this->clear();
  this->SwapList(other);
  //        other.clear();
  return *this;
}

template <class value_type>
list<value_type>& list<value_type>::operator=(const list& other) {
  //            this->InitList();
  if (this != &other) {
    this->clear();
    //            for (auto iter = other.begin(); iter != other.end(); ++iter) {
    //                this->push_back(*iter);
    //            }
    node* tmp = other.two_with_->next_;
    if (!tmp) {
      throw std::bad_alloc();
    }
    for (size_type i = 0; i < other.m_size_; ++i) {
      this->push_back(tmp->value_);
      tmp = tmp->next_;
    }
  }
  return *this;
}
template <class value_type>
typename list<value_type>::const_reference list<value_type>::front() {
  return this->two_with_->next_->value_;
}

template <class value_type>
typename list<value_type>::const_reference list<value_type>::back() {
  return this->two_with_->prev_->value_;
}

template <class value_type>
typename list<value_type>::iterator list<value_type>::begin() const {
  return iterator(this->two_with_->next_);
}

template <class value_type>
typename list<value_type>::iterator list<value_type>::end() const {
  return iterator(this->two_with_);
}
template <class value_type>
void list<value_type>::InitList() {
  this->two_with_ = new node();
  if (!this->two_with_) {
    throw std::bad_alloc();
  }
  this->two_with_->next_ = this->two_with_;
  this->two_with_->prev_ = this->two_with_;
  this->m_size_ = 0;
}

template <class value_type>
bool list<value_type>::empty() const noexcept {
  //        std::cout << "Before segmentation fault";
  //        return this->head_->next_ == this->tail_ ? true : false;
  //        return this->two_with_->next_ == nullptr;
  //        return is_cicle(this->two_with_->next_);
  return this->two_with_->next_ == this->two_with_;
}

template <class value_type>
size_t list<value_type>::max_size() const noexcept {
  size_type max_size =
      (std::numeric_limits<size_type>::max() / sizeof(node) / 2);
  return max_size;
}
template <class value_type>
void list<value_type>::Connect() {
  this->tail_ = new node;
  this->head_ = this->tail_;
  this->head_->next_ = this->head_->prev_ = this->head_;
  this->tail_->next_ = this->tail_->prev_ = this->tail_;
}

template <class value_type>
void list<value_type>::clear() {
  while (this->m_size_) {
    this->pop_back();
  }
  //        delete this->two_with_;
}

template <class value_type>
void list<value_type>::push_back(const_reference value) {
  if (this->size() >= this->max_size())
    throw std::out_of_range("Limit of the container is exceeded");
  node* tmp = new node(value);
  if (!tmp) throw std::bad_alloc();
  tmp->next_ = this->two_with_;
  tmp->prev_ = this->two_with_->prev_;
  this->two_with_->prev_->next_ = tmp;
  this->two_with_->prev_ = tmp;
  this->m_size_++;
}

template <class value_type>
void list<value_type>::push_front(const_reference value) {
  if (this->size() >= this->max_size())
    throw std::out_of_range("Limit of the container is exceeded");
  node* tmp = new node(value);
  if (!tmp) throw std::bad_alloc();
  tmp->prev_ = this->two_with_;
  tmp->next_ = this->two_with_->next_;
  this->two_with_->next_->prev_ = tmp;
  this->two_with_->next_ = tmp;
  this->m_size_++;
}

template <class value_type>
typename list<value_type>::size_type list<value_type>::size() const noexcept {
  size_type size = 0U;
  node* temp = this->two_with_->next_;
  while (temp != two_with_) {
    size++;
    temp = temp->next_;
  }
  return size;
}

//
//    template<class value_type>
//    void list<value_type>::push_back(const_reference value) {
//       node* tmp = new node;
//       tmp->value_ = value;
//       tmp->next_ = head_;
//       tmp->prev_ = nullptr;
//       (!this->empty()) ? this->head_->prev_ = tmp : this->tail_ = tmp;
//        this->head_ = tmp;
//        this->m_size_++;
//    }

template <class value_type>
void list<value_type>::pop_back() {
  if (this->empty()) throw std::invalid_argument("the list is empty");
  node* tmp;
  tmp = this->two_with_->prev_;
  this->two_with_->prev_ = this->two_with_->prev_->prev_;
  this->two_with_->prev_->next_ = this->two_with_;
  delete tmp;
  this->m_size_--;
}

template <class value_type>
void list<value_type>::pop_front() {
  if (this->empty()) {
    throw std::invalid_argument("the list is empty");
  }
  node* tmp;
  tmp = this->two_with_->next_;
  this->two_with_->next_ = this->two_with_->next_->next_;
  this->two_with_->next_->prev_ = this->two_with_;
  delete tmp;
  this->m_size_--;
}

//    template <typename T>
//    void list<T>::push_back(const_reference value) {
//        node* new_node = new node;
//        new_node->value_ = value;
//        this->_push_node(new_node, this->tail_->prev_, this->_tail);
//    }
//
//    template <typename T>
//    void list<T>::push_front(const_reference value) {
//        node* new_node = new node;
//        new_node->value_ = value;
//        this->_push_node(new_node, this->head_, this->head_->next_);
//    }
//
//    template <typename T>
//    void list<T>::_push_node(node* node_to_push, node* left_node, node*
//    right_node) {
//        node_to_push->next_ = right_node;
//        node_to_push->prev_ = left_node;
//        left_node->next_ = node_to_push;
//        right_node->prev_ = node_to_push;
//    }

template <class value_type>
void list<value_type>::SwapList(list& l) {
  std::swap(this->two_with_, l.two_with_);
  std::swap(this->m_size_, l.m_size_);
}

// ConstIterator
template <class value_type>
typename list<value_type>::const_reference
list<value_type>::ConstIterator::operator*() const {
  if (this->data_ == nullptr) throw std::invalid_argument("Bad <*> parameter!");
  return this->data_->value_;
}

template <class value_type>
typename list<value_type>::ConstIterator&
list<value_type>::ConstIterator::operator++() {
  this->data_ = this->data_->next_;
  //            return *this->data_->value_;
  return *this;
}

template <class value_type>
typename list<value_type>::ConstIterator
list<value_type>::ConstIterator::operator++(int) {
  ConstIterator temp(this->data_);
  this->data_ = this->data_->next_;
  //        return *this->data_->value_;
  return temp;
}

template <class value_type>
typename list<value_type>::ConstIterator&
list<value_type>::ConstIterator::operator--() {
  this->data_ = this->data_->prev_;
  return *this;
}

template <class value_type>
typename list<value_type>::ConstIterator
list<value_type>::ConstIterator::operator--(int) {
  this->data_ = this->data_->prev_;
  return *this;
}

template <class value_type>
typename list<value_type>::ConstIterator
list<value_type>::ConstIterator::operator+(const size_type value) {
  node* tmp = this->data_;
  for (size_type i = 0; i < value; i++) {
    tmp = tmp->next_;
  }
  ConstIterator it_const(tmp);
  return it_const;
}

template <class value_type>
typename list<value_type>::ConstIterator
list<value_type>::ConstIterator::operator-(const size_type value) {
  ConstIterator it_const(this->data_->prev_ - value);
  return it_const;
}

template <class value_type>
bool list<value_type>::ConstIterator::operator!=(
    const ConstIterator& other) const {
  return this->data_ != other.data_;
}

template <class value_type>
bool list<value_type>::ConstIterator::operator==(
    const ConstIterator& other) const {
  return this->data_ == other.data_;
}

// Iterator
template <class value_type>
list<value_type>::Iterator::Iterator() : ConstIterator() {}

template <class value_type>
list<value_type>::Iterator::Iterator(node* value) : ConstIterator(value) {}

template <class value_type>
list<value_type>::Iterator::Iterator(const Iterator& other)
    : ConstIterator(other) {}

template <class value_type>
list<value_type>::Iterator::Iterator(const ConstIterator& other)
    : ConstIterator(other) {}

template <class value_type>
typename list<value_type>::reference list<value_type>::Iterator::operator*() {
  if (this->data_ == nullptr) {
    throw std::invalid_argument("Bad <*> parameter!");
  }
  return this->data_->value_;
}
template <class value_type>
typename list<value_type>::Iterator list<value_type>::Iterator::operator+(
    const size_type value) {
  node* tmp = this->data_;
  for (size_type i = 0; i < value; i++) {
    tmp = tmp->next_;
  }
  Iterator iter(tmp);
  return iter;
}

//    template<class value_type>
//    typename list<value_type>::Iterator
//    list<value_type>::Iterator::operator+(Iterator &other) {
//        return  this->data_ + other.data_;
////        Iterator tmp(this->data_);
////        return tmp;
//    }

template <class value_type>
typename list<value_type>::Iterator list<value_type>::Iterator::operator-(
    const size_type value) {
  node* tmp = this->data_;
  for (size_type i = 0; i < value; i++) {
    tmp = tmp->prev_;
  }
  Iterator iter(tmp);
  return tmp;
}

template <class value_type>
typename list<value_type>::Iterator& list<value_type>::Iterator::operator=(
    const Iterator other) {
  this->data_ = other.data_;
  return *this;
}

template <class value_type>
bool list<value_type>::is_cicle(node* N) {
  return N == two_with_;
}

template <class value_type>
template <typename... Args>
typename list<value_type>::iterator list<value_type>::emplace(
    const_iterator pos, Args&&... args) {
  return this->insert(pos, std::forward<Args>(args)...);
}

template <class value_type>
template <typename... Args>
void list<value_type>::emplace_back(Args&&... args) {
  this->push_back(value_type(std::forward<Args>(args)...));
}

template <class value_type>
template <typename... Args>
void list<value_type>::emplace_front(Args&&... args) {
  this->push_front(value_type(std::forward<Args>(args)...));
}

template <typename T>
void list<T>::sort() {
  if (this->size() > 1) {
    iterator it = this->end() - 1;
    this->QuickSort(this->begin(), it);
  }
}

template <typename T>
void list<T>::QuickSort(iterator first_element, iterator last_element) {
  if (last_element != this->begin() - 1 && first_element != last_element &&
      first_element != last_element + 1) {
    iterator iter = this->_partition(first_element, last_element);
    this->QuickSort(first_element, iter - 1);
    this->QuickSort(iter + 1, last_element);
  }
}

template <typename T>
typename list<T>::iterator list<T>::_partition(iterator first_element,
                                               iterator last_element) {
  value_type x = *last_element;
  iterator i = first_element - 1;
  for (iterator j = first_element; j != last_element; ++j) {
    if (*j < x) {
      i = i + 1;
      std::swap(*i, *j);
    }
  }
  i = i + 1;
  std::swap(*i, *last_element);
  return i;
}

}  // namespace s21
