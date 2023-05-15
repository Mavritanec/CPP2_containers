#ifndef SRC_LIST_STACK_QUEUE_S21_LIST_H
#define SRC_LIST_STACK_QUEUE_S21_LIST_H
#include <cmath>
#include <iostream>
#include <limits>
#include <stdexcept>

#include "../../vec_array/sequence/s21_sequence.h"

namespace s21 {
template <class T>
class list : public abstract<T> {
 public:
  using pointer = typename abstract<T>::pointer;
  using const_pointer = typename abstract<T>::const_pointer;
  using value_type = typename abstract<T>::value_type;
  using reference = typename abstract<T>::reference;
  using const_reference = typename abstract<T>::const_reference;
  using size_type = typename abstract<T>::size_type;

 private:
  struct ListNode {
   public:
    //            ~ListNode() {};
    value_type value_;
    ListNode* next_;
    ListNode* prev_;
    ListNode() : value_(), next_(nullptr), prev_(nullptr) {}
    explicit ListNode(const const_reference value)
        : value_(value), next_(nullptr), prev_(nullptr) {}
  };

 public:
  using node = ListNode;

 private:
  size_type m_size_;
  node* two_with_;

 public:
  list();
  explicit list(size_type n);
  list(std::initializer_list<value_type> const& items);
  list(const list& l);
  list(list&& l);
  ~list();
  list& operator=(const list& other);
  list& operator=(list&& other);
  bool empty() const noexcept override;

  void output_list() {
    std::cout << "This is your list: " << std::endl;
    if (this->empty()) {
      throw std::invalid_argument("Stop");
    }
    for (node* point = this->two_with_->next_; point != this->two_with_;
         point = point->next_)
      std::cout << point->value_;
    std::cout << std::endl;
  }
  void push_back(const_reference value);
  void pop_back();
  void push_front(const_reference value);
  void pop_front();
  void _push_node(node* node_to_push, node* left_node, node* right_node);
  class ConstIterator {
   public:
    node* data_;

   public:
    ConstIterator() { this->data_ = nullptr; }
    ConstIterator(node* value) { this->data_ = value; }
    ConstIterator(const ConstIterator& other) : data_(other.data_) {}
    ~ConstIterator() {}
    ConstIterator& operator++();
    ConstIterator operator++(int);
    ConstIterator& operator--();
    ConstIterator operator--(int);
    const_reference operator*() const;
    ConstIterator operator+(const size_type value);  // see this
    ConstIterator operator-(const size_type value);  // see this
    bool operator!=(const ConstIterator& other) const;
    bool operator==(const ConstIterator& other) const;
  };
  class Iterator : public ConstIterator {
   public:
    Iterator();
    Iterator(node* value);
    Iterator(const Iterator& other);
    Iterator(const ConstIterator& other);
    ~Iterator() {}
    reference operator*();
    Iterator operator+(const size_type value);
    //            Iterator operator+(Iterator &other);
    Iterator operator-(const size_type value);
    Iterator& operator=(const Iterator other);
  };

 public:
  using iterator = Iterator;
  using const_iterator = ConstIterator;
  iterator begin() const;
  iterator end() const;
  const_reference front() override;
  const_reference back() override;
  size_type size() const noexcept override;
  size_t max_size() const noexcept override;
  void clear();
  iterator insert(iterator pos, const_reference value);
  void erase(iterator pos);
  void swap(list& other);
  void merge(list& other);
  void splice(const_iterator pos, list& other);
  void reverse();
  void unique();

  void Sort();
  void sort();
  void QuickSort(iterator first_element, iterator last_element);
  iterator _partition(iterator first_element, iterator last_element);

  template <typename... Args>
  iterator emplace(const_iterator pos, Args&&... args);
  template <typename... Args>
  void emplace_back(Args&&... args);
  template <typename... Args>
  void emplace_front(Args&&... args);

 private:
  bool is_cicle(node* N);
  void SwapList(list& l);

  void Connect();
  void InitList();
};

}  //  namespace s21

#include "s21_list.tpp"
#endif  // SRC_LIST_STACK_QUEUE_S21_LIST_H
