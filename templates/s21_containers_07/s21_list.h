#ifndef S21_LIST_H_
#define S21_LIST_H_

#include <iostream>

namespace s21 {
template <typename T>
class list {
 public:
  class Node;
  class ListIterator;
  class ListConstIterator;
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using size_type = size_t;
  using iterator = ListIterator;
  using const_iterator = ListConstIterator;

  class Node {
   public:
    Node *prev_;
    Node *next_;
    value_type value_;
    Node();
    explicit Node(value_type value);
  };

  class ListIterator {
   private:
    Node *current_ = nullptr;

   public:
    // constructor
    ListIterator();
    explicit ListIterator(Node *ptr);
    // overload operators
    value_type operator*();
    iterator &operator++();
    bool operator==(const iterator &other);
    bool operator!=(const iterator &other);
    Node *getCurrent() { return current_; }
  };

  class ListConstIterator : public ListIterator {
   public:
    ListConstIterator();
    const value_type operator*();
    const const_iterator &operator++();
  };

 private:
  Node *base_;
  Node *head_;
  Node *tail_;
  size_type size_;

 public:
  // List Functions

  // default constructor, creates empty list
  list();
  // parameterized constructor, creates the list of size n
  explicit list(size_type n);
  // initializer list constructor, creates list initizialized using
  // std::initializer_list<T>
  explicit list(std::initializer_list<value_type> const &items);
  // copy constructor
  list(const list &other);
  // move constructor
  list(list &&other);
  // destructor
  ~list();
  // assignment operator overload for copy object
  list &operator=(const list &other);
  // assignment operator overload for moving object
  list &operator=(list &&other);

  // List Element access

  // access the first element
  const_reference front();
  // access the last element
  const_reference back();

  // List Iterators

  // returns an iterator to the beginning
  iterator begin();
  // returns an iterator to the end
  iterator end();
  // Returns a reverse iterator to the element following the last element of the
  // reversed list.
  iterator rbegin();

  // List Capacity

  // checks whether the container is empty
  bool empty();
  // returns the number of elements
  size_type size();
  // returns the maximum possible number of elements
  size_type max_size();

  // List Modifiers

  // clears the contents
  void clear();
  // inserts elements into concrete pos and returns the iterator that points to
  // the new element
  iterator insert(iterator pos, const_reference value);
  // erases element at pos
  void erase(iterator pos);
  // adds an element to the end
  void push_back(const_reference value);
  // removes the last element
  void pop_back();
  // adds an element to the head
  void push_front(const_reference value);
  // removes the first element
  void pop_front();
  // swaps the contents
  void swap(list &other);
  // merges two sorted lists
  void merge(list &other);
  // transfers elements from list other starting from pos
  void splice(iterator pos, list &other);
  // reverses the order of the elements
  void reverse();
  // removes consecutive duplicate elements
  void unique();
  // sorts the elements
  void sort();

  // bonus foo

  // inserts new elements into the container directly before pos
  template <class... Args>
  iterator emplace(iterator pos, Args &&...args);
  // appends new elements to the end of the container
  template <class... Args>
  void emplace_back(Args &&...args);
  // appends new elements to the top of the container
  template <class... Args>
  void emplace_front(Args &&...args);

  void print_list();
};

}  // namespace s21

#include "s21_list.tpp"

#endif  // S21_LIST_H_
