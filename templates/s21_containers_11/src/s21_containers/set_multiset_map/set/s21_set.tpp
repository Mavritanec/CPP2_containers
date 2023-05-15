#include "s21_set.h"
namespace s21 {
template <class key_type, class Compare>
set<key_type, Compare>::set() {
  this->init_set();
}

template <class key_type, class Compare>
set<key_type, Compare>::set(std::initializer_list<value_type> const &items) {
  //        this->set_node_ = new Tree<key_type>();
  //        Tree<key_type>* tmp = this->set_node_;
  //        this->m_size_ = std::count_if(items.begin(), items.end(),
  //                                 [tmp](key_type i) { return tmp->insert(i,
  //                                 WITHOUT_DUPLICATE, 0); });

  this->init_set();
  for (auto i = items.begin(); i != items.end(); ++i) {
    this->insert(*i);
  }
}

template <class key_type, class Compare>
set<key_type, Compare>::set(const set<key_type, Compare> &s) {
  //        if (!this->set_node_)
  this->init_set();
  *this = s;
}

template <class key_type, class Compare>
set<key_type, Compare>::set(set<key_type, Compare> &&s) {
  this->init_set();
  if (this != &s) {
    *this = s;
    //            this->swap(s);
  }
}

template <class key_type, class Compare>
set<key_type, Compare> &set<key_type, Compare>::operator=(
    const set<key_type, Compare> &s) {
  if (this->set_node_) this->clear();
  this->init_set();
  read_black_node tmp = s.set_node_->get_root();
  this->copy_set(tmp);
  this->m_size_ = s.m_size_;
  return *this;
}

template <class key_type, class Compare>
void set<key_type, Compare>::copy_set(read_black_node &root) {
  if (root != nullptr) {
    copy_set(root->left_);
    key_type value = root->data_;
    this->insert(value);
    copy_set(root->right_);
  }
}

template <class key_type, class Compare>
set<key_type, Compare> &set<key_type, Compare>::operator=(
    set<key_type, Compare> &&s) {
  if (this != &s) {
    if (this->set_node_) {
      this->clear();
    }
    this->swap(s);
  }
  return *this;
}

template <class key_type, class Compare>
set<key_type, Compare>::~set() {
  this->clear();
  //        if (this->set_node_ != nullptr) {
  //            read_black_node root = this->set_node_->get_root();
  //            if (root) {
  //                this->destr(root);
  //            }
  //            delete this->set_node_;
  //        }
}

template <class key_type, class Compare>
bool set<key_type, Compare>::empty() {
  return (this->m_size_ == 0) ? true : false;
}

template <class key_type, class Compare>
typename set<key_type, Compare>::size_type set<key_type, Compare>::size() {
  //        size_type count = 0;
  //        while(this->set_node_->get_root()) {
  //
  //        }
  return this->m_size_;
}

template <class key_type, class Compare>
typename set<key_type, Compare>::size_type set<key_type, Compare>::max_size() {
  //        char bits = 63;
  //        if (sizeof(void *) == 4) {
  //            bits = 31;
  //        }
  //        return static_cast<size_type>(pow(2, bits)) / sizeof(value_type) -
  //        1;
  return allocator.max_size() / 10;
}

template <class key_type, class Compare>
void set<key_type, Compare>::clear() {
  if (this->set_node_ != nullptr) {
    read_black_node root = this->set_node_->get_root();
    if (root) {
      this->destr(root);
    }
    delete this->set_node_;
  }
  this->set_node_ = nullptr;
}

template <class key_type, class Compare>
void set<key_type, Compare>::swap(set<key_type, Compare> &other) {
  std::swap(this->set_node_, other.set_node_);
  std::swap(this->m_size_, other.m_size_);
}

template <class key_type, class Compare>
void set<key_type, Compare>::merge(set<key_type, Compare> &other) {
  iterator iter = other.begin();
  while (iter != other.end()) {
    this->insert(*iter);
    iter++;
  }
  other.clear();
}

template <class key_type, class Compare>
bool set<key_type, Compare>::contains(const key_type &key) {
  return this->set_node_->search(key) != nullptr;
}

template <class key_type, class Compare>
typename set<key_type, Compare>::iterator set<key_type, Compare>::begin() {
  read_black_node tmp = this->set_node_->get_root();
  if (tmp) {
    while (tmp->left_) {
      tmp = tmp->left_;
    }
  } else {
    tmp = this->set_node_->get_nil();
  }
  return iterator(tmp, this->set_node_->get_nil(), last_right());
}

template <class key_type, class Compare>
typename set<key_type, Compare>::iterator set<key_type, Compare>::end() {
  read_black_node nil = this->set_node_->get_nil();
  return iterator(nil, nil, last_right());
}

template <class key_type, class Compare>
std::pair<typename set<key_type, Compare>::iterator, bool>
set<key_type, Compare>::insert(const value_type &value) {
  std::pair<iterator, bool> result;
  if (this->set_node_->insert(value, WITHOUT_DUPLICATE)) {
    this->m_size_++;
    result = std::pair<iterator, bool>(find(value), true);

  } else {
    result = std::pair<iterator, bool>(find(value), false);
  }
  return result;
}

template <class key_type, class Compare>
void set<key_type, Compare>::erase(iterator pos) {
  this->set_node_->remove(*pos);
  this->m_size_--;
}

template <class key_type, class Compare>
typename set<key_type, Compare>::iterator set<key_type, Compare>::find(
    const key_type &key) {
  read_black_node tmp = this->set_node_->search(key);
  if (tmp == nullptr) {
    tmp = this->set_node_->get_nil();
  }
  iterator res(tmp, this->set_node_->get_nil(), last_right());
  return res;
}

template <class key_type, class Compare>
void set<key_type, Compare>::init_set() {
  this->set_node_ = new Tree<key_type>();
  this->m_size_ = 0;
}

template <class key_type, class Compare>
void set<key_type, Compare>::destr(read_black_node &root) {
  if (root != nullptr) {
    this->destr(root->left_);
    this->destr(root->right_);
    delete root;
    this->m_size_--;
  }
}

template <class key_type, class Compare>
typename set<key_type, Compare>::read_black_node
set<key_type, Compare>::last_right() const {
  read_black_node tmp = this->set_node_->get_root();
  while (tmp && tmp->right_) {
    tmp = tmp->right_;
  }
  return tmp;
}

// ConstIterator
template <class key_type, class Compare>
typename set<key_type, Compare>::read_black_node
set<key_type, Compare>::ConstIterator::next_value() {
  if (this->node_have_right()) {
    this->data_ = this->data_->right_;
    while (this->data_->left_) {
      this->data_ = this->data_->left_;
    }
  } else if (this->node_have_father_left()) {
    this->data_ = this->data_->parent_;
  } else if (this->node_have_grand_father_n_father_left()) {
    this->data_ = this->data_->parent_->parent_;
  } else if (this->data_ == this->nil_) {
    this->data_ = this->last_;
  } else {
    this->data_ = this->nil_;
  }
  return this->data_;
}

template <class key_type, class Compare>
bool set<key_type, Compare>::ConstIterator::node_have_left() {
  return this->data_->left_;
}

template <class key_type, class Compare>
bool set<key_type, Compare>::ConstIterator::node_have_father_right() {
  return this->data_->parent_ && this->data_->parent_->right_ == this->data_;
}

template <class key_type, class Compare>
bool set<key_type,
         Compare>::ConstIterator::node_have_grand_father_n_father_right() {
  return this->data_->parent_ && this->data_->parent_->left_ == this->data_ &&
         this->data_->parent_->parent_ &&
         this->data_->parent_ == this->data_->parent_->parent_->right_;
}

template <class key_type, class Compare>
bool set<key_type, Compare>::ConstIterator::node_have_right() {
  return this->data_->right_;
}

template <class key_type, class Compare>
bool set<key_type, Compare>::ConstIterator::node_have_father_left() {
  return this->data_->parent_ && this->data_->parent_->left_ == this->data_;
}

template <class key_type, class Compare>
bool set<key_type,
         Compare>::ConstIterator::node_have_grand_father_n_father_left() {
  return this->data_->parent_ && this->data_->parent_->right_ == this->data_ &&
         this->data_->parent_->parent_ &&
         this->data_->parent_ == this->data_->parent_->parent_->left_;
}

template <class key_type, class Compare>
typename set<key_type, Compare>::read_black_node
set<key_type, Compare>::ConstIterator::prev_value() {
  if (this->node_have_left()) {
    this->data_ = this->data_->left_;
    while (this->data_->right_) {
      this->data_ = this->data_->right_;
    }
  } else if (this->node_have_father_right()) {
    this->data_ = this->data_->parent_;
  } else if (this->node_have_grand_father_n_father_right()) {
    this->data_ = this->data_->parent_->parent_;
  } else if (this->data_ == this->nil_) {
    this->data_ = this->last_;
  } else {
    this->data_ = this->nil_;
  }
  return this->data_;
}

template <class key_type, class Compare>
typename set<key_type, Compare>::ConstIterator &
set<key_type, Compare>::ConstIterator::operator++() {
  this->data_ = this->next_value();
  return *this;
}

template <class key_type, class Compare>
typename set<key_type, Compare>::ConstIterator &
set<key_type, Compare>::ConstIterator::operator--() {
  this->data_ = this->prev_value();
  return *this;
}
template <class key_type, class Compare>
typename set<key_type, Compare>::ConstIterator
set<key_type, Compare>::ConstIterator::operator--(int) {
  auto iter = *this;
  --(*this);
  return iter;
}

template <class key_type, class Compare>
typename set<key_type, Compare>::ConstIterator
set<key_type, Compare>::ConstIterator::operator++(int) {
  auto iter = *this;
  ++(*this);
  return iter;
}

template <class key_type, class Compare>
template <class... Args>
std::vector<std::pair<typename set<key_type, Compare>::iterator, bool>>
set<key_type, Compare>::emplace(Args &&...args) {
  std::vector<std::pair<iterator, bool>> result;
  std::vector<typename set<key_type, Compare>::value_type> argsVector = {
      args...};
  for (auto &i : argsVector) {
    result.push_back(insert(i));
  }
  return result;
}

}  //  namespace s21