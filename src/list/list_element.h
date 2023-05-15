#ifndef SRC_LIST_ELEMENT_H_
#define SRC_LIST_ELEMENT_H_

namespace s21 {
template <typename Type>
struct Element {
  Type data_;            // данные
  Element<Type>* next_;  // следующий узел
  Element<Type>* prev_;  // предыдущий узел
};
}  // namespace s21

#endif  // SRC_LIST_ELEMENT_H_
