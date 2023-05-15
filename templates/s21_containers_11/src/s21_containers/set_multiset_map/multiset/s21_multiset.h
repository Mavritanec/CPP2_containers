#ifndef SRC_SET_MULTISET_MAP_MULTISET_S21_MULTISET_H
#define SRC_SET_MULTISET_MAP_MULTISET_S21_MULTISET_H
#include "../set/s21_set.h"
namespace s21 {
template <typename Key>
class multiset : public set<Key> {
 public:
  using key_type = typename set<Key>::key_type;
  using value_type = typename set<Key>::value_type;
  using reference = typename set<Key>::reference;
  using const_reference = typename set<Key>::const_reference;
  using size_type = typename set<Key>::size_type;
  using read_black_node = typename set<Key>::read_black_node;
  using Allocator = typename set<Key>::Allocator;
  Allocator allocator;
  using iterator = typename set<Key>::iterator;
  using const_iterator = typename set<Key>::const_iterator;

  multiset() : set<Key>() {}
  explicit multiset(std::initializer_list<value_type> const& items);
  multiset(const multiset& s) : set<Key>(s) {}
  multiset(multiset&& s) : set<Key>(std::move(s)) {}
  ~multiset() {}
  multiset<key_type>& operator=(multiset&& s) {
    if (this != &s) {
      if (this->set_node_) {
        this->clear();
      }
      this->swap(s);
    }
    return *this;
  }
  multiset<key_type>& operator=(const multiset& s) {
    if (this->set_node_) this->clear();
    this->init_set();
    read_black_node tmp = s.set_node_->get_root();
    this->copy_set(tmp);
    this->m_size_ = s.m_size_;
    return *this;
  }
  std::pair<iterator, bool> insert(const value_type& value);
  void merge(multiset& other);

  bool contains(const key_type& key);
  size_type count(const key_type& key);

  std::pair<iterator, iterator> equal_range(const key_type& key);
  iterator lower_bound(const key_type& key);
  iterator upper_bound(const key_type& key);
};

}  // namespace s21

#include "s21_multiset.tpp"
#endif  //  SRC_SET_MULTISET_MAP_MULTISET_S21_MULTISET_H
