#ifndef ELEMENT_H
#define ELEMENT_H

namespace s21 {
template <class T>
struct Element {
  T data;            // данные
  Element<T>* next;  // следующий
  Element<T>* prev;  // предыдущий
};
}  // namespace s21

#endif  // ELEMENT_H
