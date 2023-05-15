#ifndef SRC_LIST_LIST_H_
#define SRC_LIST_LIST_H_



// #include <initializer_list>
// #include <iostream>

// #include "element.h"



// NOTE: определяем простанство имен (требуется по заданию для каждого класса)
namespace s21 {
// NOTE: указываем, что дальше идет шаблон класса с параметром Type
//       (вообще, можно указывать список параметров через запятую)
template <typename Type>
class list {
  // NOTE: все элементы класса (аттрибуты и методы) смотри в задании:
  //       ../materials/containers_info.md
  //       ../materials/containers_info_rus.md


  // List Member type
  public:
    // NOTE: аналог typedef из Cи, используется для удобства
    //       применено, т.к. присутствует в примере и задании (ну и для удобства)
    using value_type = Type;                    // тип элемента (он же - параметр шаблона)
    using referense = Type&;                    // ссылка на элемент
    using const_reference = const Type&;        // ссылка на константный элемент
    using iterator = ListIterator;              // внутренний класс для итерации по контейнеру
    using const_iterator = ListConstIterator;   // внутренний класс для итерации по константному контейнеру
    using size_type = std::size_t;              // тип для указания размера контейнера

    // using node_type = ListNode;                 // внутренний класс узла списка

  private:
    // struct ListIterator;
    // struct ListConstIterator;
    // struct ListNode;
    // Element<value_type>* first;
    // Element<value_type>* last;
    size_type count_;                           // количество элементов в списке

  public:



  // List Functions
  // list()                                                  // default constructor, creates an empty list
  // list(size_type n)                                       // parameterized constructor, creates the list of size n
  // list(std::initializer_list<value_type> const &items)    // initializer list constructor, creates a list initizialized using std::initializer_list<T>
  // list(const list &l)                                     // copy constructor
  // list(list &&l)                                          // move constructor
  // ~list()                                                 // destructor
  // operator=(list &&l)                                     // assignment operator overload for moving an object



  // List Element access
  // const_reference front()                                 // access the first element
  // const_reference back()                                  // access the last element



  // List Iterators
  // iterator begin()                                        // returns an iterator to the beginning
  // iterator end()                                          // returns an iterator to the end



    // List Capacity
    /**
     * @brief Проверяет список (контейнер) на пустоту
     *
     * @return true - список (контейнер) пустой \
     * @return false - список (контейнер) непустой
     */
    bool empty() const noexcept { return count_ == 0; }

    /**
     * @brief Возвращает количество элементов списка (контейнера)
     *
     * @return size_type - количество элементов
     */
    size_type size() const noexcept { return count_; }









  size_type max_size() const noexcept {
    allocator<value_type> Alloc;
    return Alloc.max_size();
  }

  // size_type max_size()                                    // returns the maximum possible number of elements



  // List Modifiers
  // void clear()                                            // clears the contents
  // iterator insert(iterator pos, const_reference value)    // inserts elements into concrete pos and returns the iterator that points to the new element
  // void erase(iterator pos)                                // erases an element at pos
  // void push_back(const_reference value)                   // adds an element to the end
  // void pop_back()                                         // removes the last element
  // void push_front(const_reference value)                  // adds an element to the head
  // void pop_front()                                        // removes the first element
  // void swap(list& other)                                  // swaps the contents
  // void merge(list& other)                                 // merges two sorted lists
  // void splice(const_iterator pos, list& other)            // transfers elements from list other starting from pos
  // void reverse()                                          // reverses the order of the elements
  // void unique()                                           // removes consecutive duplicate elements
  // void sort()                                             // sorts the elements











};  // class
}  // namespace s21

#endif  // SRC_LIST_LIST_H_


/*
 public:
  List() {
    first = nullptr;
    last = nullptr;
    count = 0;
  }

  List(T n) : List() {
    for (T i = 0; i < n; i++) {
      push_back(0);
    }
  }

  List(initializer_list<T> const& items) : List() {
    for (auto iter = items.begin(); iter != items.end(); iter++) {
      push_back(*iter);
    }
  }

  List(const List& other) : List() { Copy(other); }

  List(List&& other) : List() {
    Copy(other);
    other.clear();
  }

  ~List() { clear(); }  //  destructor

  List<T>& operator=(const List& other) {
    Copy(other);
    return *this;
  }

  //^------------------------------------------

  const_reference front() { return first->data; }

  const_reference back() { return last->data; }

  //^---------------------------------------------

  iterator begin() { return &first->data; }
  const_iterator cbegin() const noexcept { return &first->data; }

  iterator end() noexcept { return &last->data; }
  const_iterator cend() const noexcept { return &last->data; }

  //^------------------------------------------------

  void clear() noexcept {
    while (first != nullptr) {
      pop_back();
    }
  }

  void push_back(T _data) {  // добавить в конец
    Element<T>* elem = new Element<T>;
    elem->next = nullptr;
    elem->prev = last;
    elem->data = _data;

    if (first == nullptr) {
      first = last = elem;
    } else {
      elem->prev = last;
      last->next = elem;
      last = elem;
    }
    count++;
  }

  void push_front(const_reference _data) {  // добавляет в начало
    Element<T>* elem = new Element<T>;
    elem->prev = nullptr;
    elem->next = nullptr;
    elem->data = _data;

    if (first == nullptr) {
      first = elem;
      last = elem;
    } else {
      elem->next = first;
      first->prev = elem;
      first = elem;
    }
    count++;
  }

  void insert(size_type index, const_reference _data) {  // добавить на позицию
    int flag = 0;
    if (!CorrectIndex(index)) {
      flag = 1;
    }
    if (index == count) {
      push_back(_data);
      flag = 1;
    }
    if (index == 0) {
      push_front(_data);
      flag = 1;
    }
    if (flag != 1) {
      Element<T>* itrm_prev = Move(index - 1);
      Element<T>* item = Move(index);

      Element<T>* t = new Element<T>;
      t->data = _data;
      t->next = item;
      t->prev = itrm_prev;

      itrm_prev->next = t;
      item->prev = t;

      count++;
    } else {
      cout << "incorrect index" << endl;
    }
  }

  void erase(size_type index) {  // удалить с позиции
    int flag = 0;
    if (count == 0) {
      flag = 1;
    }
    if (!CorrectIndex(index)) {
      flag = 1;
    }

    if (flag != 1) {
      Element<T>* item = Move(index);  // Перейти к удаляемому элементу
      Element<T>* item_prev = item->prev;
      Element<T>* item_next = item->next;

      if ((count > 1) && (item_prev != nullptr)) {  // если удаляется не 1ый
        item_prev->next = item_next;
      }
      if ((item_next != nullptr) &&
          (count > 1)) {  // если удаляется не последний
        item_next->prev = item_prev;
      }
      if (index == 0) {
        first = item_next;
      }  // если 1ый
      if (index == count - 1) {
        last = item_prev;
      }  // если последний

      delete item;
      count--;
    }
  }

  void pop_back() {  // удалить последний
    if (count != 0) {
      Element<T>* elem = last;
      last = last->prev;
      delete elem;
      count--;
      if (last == nullptr) {
        first = nullptr;
        count = 0;
      } else {
        last->next = nullptr;
      }
    }
  }

  void pop_front() {  // удалить первый
    if (count != 0) {
      Element<T>* elem = first;
      first = first->next;
      delete elem;
      count--;
      if (first == nullptr) {
        last = nullptr;
        count = 0;
      } else {
        first->prev = nullptr;
      }
    }
  }

  void Swap(List& other) {
    swap(first, other.first);
    swap(last, other.last);
    swap(count, other.count);
  }

  void Merge(List& other) {
    Element<T>* t = other.first;
    while (t != nullptr) {
      push_back(t->data);
      t = t->next;
    }
  }

  void Splice(size_type pos, List& other) {
    Element<T>* elem = other.first;
    while (elem != nullptr) {
      insert(pos, elem->data);
      elem = elem->next;
      pos++;
    }
  }

  void reverse() {
    List<T> L;
    Element<T>* elem = first;
    while (elem != nullptr) {
      L.push_front(elem->data);
      elem = elem->next;
    }
    *this = L;
  }

  void unique() {
    Element<T>* t = first;
    size_type i = 0;
    while (t->next != nullptr) {
      if (t->data == t->next->data) {
        erase(i);
        Move(0);
        t = first;
      } else {
        t = t->next;
        Move(i++);
      }
    }
  }

  void sort() {
    Element<T>* elem = first;
    for (size_type i = 0; i < count - 1; i++) {
      while (elem->next != nullptr) {
        if (elem->data > elem->next->data) {
          auto temp = elem->data;
          elem->data = elem->next->data;
          elem->next->data = temp;
        }
        elem = elem->next;
      }
      elem = first;
    }
  }

  void print() noexcept {
    if (count != 0) {
      Element<T>* elem = first;
      while (elem != nullptr) {
        cout << elem->data << endl;
        elem = elem->next;
      }
    }
  }
  //^-------------------------------------------------

  Element<T>* Move(size_type index) {
    Element<T>* t = first;
    for (size_type i = 0; i < index; i++) t = t->next;
    return t;  //  Вернуть указатель
  }

  bool CorrectIndex(size_type index) {
    size_type a = 0;
    return (index >= a) && (index < count);
    // при ошибке возвращает 0
  }

  void Copy(const List<T>& other) {  // copy
    clear();
    Element<T>* elem = other.first;
    while (elem != nullptr) {
      push_back(elem->data);
      elem = elem->next;
    }
  }
*/
