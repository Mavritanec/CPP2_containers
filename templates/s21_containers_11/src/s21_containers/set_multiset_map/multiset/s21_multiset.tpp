#include "s21_multiset.h"
namespace s21 {

template <class key_type>
multiset<key_type>::multiset(const std::initializer_list<value_type> &items) {
  //        this->init_set();

  for (auto i = items.begin(); i != items.end(); ++i) {
    insert(*i);
  }
}

template <class key_type>
std::pair<typename multiset<key_type>::iterator, bool>
multiset<key_type>::insert(const value_type &value) {
  std::pair<iterator, bool> result;
  if (this->set_node_->insert(value, WITH_DUPLICATE)) {
    this->m_size_++;
    result = std::pair<iterator, bool>(this->find(value), true);
  }
  //        else {
  //            result = std::pair<iterator, bool>(this->find(value), false);
  //        }
  return result;
}

template <class key_type>
typename multiset<key_type>::iterator multiset<key_type>::lower_bound(
    const key_type &key) {
  auto result = this->begin();
  for (; result != this->end() && *result < key; result++)
    ;
  return result;
}

template <class key_type>
typename multiset<key_type>::iterator multiset<key_type>::upper_bound(
    const key_type &key) {
  auto result = this->begin();
  for (; result != this->end() && *result <= key; result++)
    ;
  return result;
}

template <class key_type>
std::pair<typename multiset<key_type>::iterator,
          typename multiset<key_type>::iterator>
multiset<key_type>::equal_range(const key_type &key) {
  return std::make_pair(this->lower_bound(key), this->upper_bound(key));
}

template <class key_type>
void multiset<key_type>::merge(multiset &other) {
  iterator iter = other.begin();
  while (iter != other.end()) {
    this->insert(*iter);
    iter++;
  }
  other.clear();
}

template <class key_type>
typename multiset<key_type>::size_type multiset<key_type>::count(
    const key_type &key) {
  typename multiset<key_type>::size_type result = 0;
  typename multiset<key_type>::iterator it = this->begin();
  while (it != this->end()) {
    if (*it == key) {
      ++result;
    }
    ++it;
  }
  return result;
}

template <class key_type>
bool multiset<key_type>::contains(const key_type &key) {
  return this->set_node_->search(key);
}

}  //  namespace s21
