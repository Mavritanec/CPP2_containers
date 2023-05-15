#ifndef MULTISET_S21_MULTISET_H_
#define MULTISET_S21_MULTISET_H_

#include <initializer_list>
#include <iostream>
#include <stdexcept>
#include <vector>

#include "../iterators/multiset_iterator.h"
#include "../iterators/tree_iterator.h"
#include "../s21_containers.h"

using std::out_of_range;

namespace s21 {
template <typename Key, typename T = int>
class Multiset : public Set<Key, T> {
 public:
  using key_type = Key;
  using value_type = Key;
  using reference = value_type&;
  using const_reference = const value_type&;
  using iterator = MultisetIterator<Key, T>;
  using size_type = size_t;

  //  Set Member functions
  Multiset() : Set<Key, T>() {}

  Multiset(std::initializer_list<Key> const& items) {
    this->root_ = nullptr;
    this->end_ = nullptr;
    for (auto i = items.begin(); i != items.end(); ++i) {
      this->insert_tree_multiset(*i);
    }
  }

  Multiset(const Multiset& other) { *this = other; }

  Multiset& operator=(const Multiset& other) {
    this->clear();
    auto e = other.end();
    --e;
    auto i = other.end();
    do {
      ++i;
      this->insert_tree(*i);
    } while (i != e);
    return *this;
  }

  Multiset(Multiset&& m) { *this = std::move(m); }

  Multiset<Key, T>& operator=(Multiset&& m) {
    this->clear();
    this->root_ = m.root_;
    this->end_ = m.end_;

    m.root_ = nullptr;
    m.end_ = nullptr;
    return *this;
  }

  iterator insert_m(const value_type& value) {
    this->insert_tree_multiset(value);
    return iterator(this->search(value));
  }

  size_type count(const Key& key) const {
    return this->count_multiset(this->root_, key);
  }

  iterator lower_bound(const Key& key) {
    if (this->contains(key)) {
      return iterator(this->search_multiset(key));
    } else {
      return upper_bound(key);
    }
  }

  iterator upper_bound(const Key& key) {
    return iterator(this->search_multiset(this->upper_bound_multiset(key)));
  }

  std::pair<iterator, iterator> equal_range(const Key& key) {
    return std::make_pair(lower_bound(key), upper_bound(key));
  }
};
}  // namespace s21

#endif  // MULTISET_S21_MULTISET_H_