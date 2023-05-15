#ifndef S21_SET_H_
#define S21_SET_H_

#include <iostream>

#include "s21_vector.h"

namespace s21 {

template <typename T>
class set {
 public:
  class SetIterator;
  class SetConstIterator;
  using value_type = T;
  using reference = value_type &;
  using const_reference = const value_type &;
  using key_type = value_type;
  using size_type = size_t;
  using iterator = SetIterator;
  using const_iterator = SetConstIterator;

 protected:
  class Node {
   public:
    Node *root_;
    Node *left_;
    Node *right_;
    value_type value_;
    Node();
    Node(value_type value, Node *root);
  };

 public:
  class SetIterator {
   protected:
    Node *current;

   public:
    explicit SetIterator(Node *ptr);
    SetIterator();
    value_type operator*();
    value_type *operator->();
    SetIterator &operator++();
    bool operator==(const iterator &other);
    bool operator!=(const iterator &other);
    void setCurrent(Node *value);
    bool isNull();
  };

 protected:
  Node *head_;

 public:
  set();
  explicit set(std::initializer_list<value_type> const &items);
  set(set &s);
  set(set &&s);
  ~set();

  set &operator=(const set &other);
  set &operator=(set &&other);

  Node *get_head();
  void set_head(Node *value);

  iterator begin();
  iterator end();

  bool empty();
  size_type size();
  size_type max_size();
  void clear();

  void erase(iterator pos);
  void swap(set &other);
  void merge(set &other);

  iterator find(const key_type &key);
  bool contains(const key_type &key);
  std::pair<iterator, bool> insert(const value_type &value);

  template <typename... Args>
  vector<std::pair<iterator, bool>> emplace(Args &&...args);

 protected:
  Node *erase_rec(Node *ptr, key_type key);
  size_type size_rec(Node *ptr) const;
  iterator add_item(key_type key, value_type value, Node **ptr_head,
                    Node *root);
  Node *minimum(Node *ptr);
  virtual bool isInsert(value_type value1, value_type value2);
  virtual bool isLess(value_type value1, value_type value2);
  key_type get_key(value_type value);
  void copy_rec(Node *head);
  void free_rec(Node *head);
};
}  // namespace s21

#include "s21_set.tpp"

#endif  // #ifndef S21_SET_H_
