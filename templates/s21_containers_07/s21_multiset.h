#ifndef S21_MULTISET_H_
#define S21_MULTISET_H_

#include "s21_set.h"

namespace s21 {
template <typename T>
class multiset : public s21::set<T> {
  using value_type = T;
  using key_type = value_type;
  using size_type = size_t;
  using reference = value_type &;
  using iterator = typename set<value_type>::SetIterator;
  using Node = typename set<value_type>::Node;
  using const_reference = const value_type &;
  using const_iterator = typename set<value_type>::SetConstIterator;

 private:
  Node *null_node;

 public:
  multiset();
  explicit multiset(std::initializer_list<value_type> const &items);
  multiset(const multiset &ms);
  multiset(multiset &&ms);
  ~multiset();

  multiset operator=(multiset &&ms);
  multiset operator=(const multiset &ms);

  std::pair<iterator, iterator> equal_range(const key_type &key);
  iterator lower_bound(const key_type &key);
  iterator upper_bound(const key_type &key);
  iterator insert(const value_type &value);
  virtual bool isInsert(value_type value1, value_type value2) override;
};

}  // namespace s21

#include "s21_multiset.tpp"

#endif  //  S21_MAP_H_
