#ifndef LIST_ITERATOR
#define LIST_ITERATOR

#include "element.h"

namespace s21 {
template <typename T>

class ListIterator {
 public:
  using self = ListIterator;
  using value_type = T;
  using reference = T &;

 private:
  Element<T> *elem;

 public:
  ListIterator() { elem = nullptr; }

  ListIterator(Element<T> *n_node) : elem(n_node) {}

  ~ListIterator() { this->elem = nullptr; }

  value_type operator*() const { return elem->data; }

  self &operator++() {
    elem = elem->next;
    return *this;
  }

  self &operator--() {
    elem = elem->prev;
    return *this;
  }

  self operator++(int) {
    Element<T> *tmp = *this;
    elem = elem->next;
    return tmp;
  }

  self operator--(int) {
    Element<T> *tmp = *this;
    elem = elem->prev;
    return tmp;
  }

  bool operator==(const Element<T> *&other) const {
    return this->elem == other.node;
  }

  bool operator!=(const Element<T> *&other) const {
    return !(this->elem == other.node);
  }

  friend class List<T>;
  friend class ListConstIterator<T>;
};  // class ListIterator

//^------------------------------------------------

template <typename T>
class ListConstIterator : public ListIterator<T> {
 public:
  using self = ListConstIterator;
  using iterator = ListIterator<T>;
  using value_type = T;
  using reference = T &;

  ListConstIterator() : iterator(nullptr), node(nullptr) {}

  ListConstIterator(const iterator &it) : iterator(it.elem), elem(it.elem) {}

  ListConstIterator(const Element<T> *n_node)
      : iterator(n_node), elem(n_node) {}

  ~ListConstIterator() { this->elem = nullptr; }

  iterator node_const_cast() const {
    return iterator(const_cast<Element<T> *>(elem));
  }

 private:
  const Element<T> *elem;

  friend class List<T>;

};  // class ListConstIterator

}  // namespace s21

#endif  // LIST_ITERATOR
