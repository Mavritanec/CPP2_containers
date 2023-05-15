#ifndef SRC_S21_COMPARE_H_
#define SRC_S21_COMPARE_H_
#include <utility>
namespace s21 {
template <class A>
struct Compare {
    // templates methods
    bool lt(const A &x, const A &y) const {  // less then
        return x < y;
    }
    bool gt(const A &x, const A &y) const {  // grater then
        return x > y;
    }
    bool le(const A &x, const A &y) const {  // less or equal
        return x <= y;
    }
    bool ge(const A &x, const A &y) const {  // grater or equal
        return x >= y;
    }
    bool eq(const A &x, const A &y) const {  // equal
        return x == y;
    }
    bool neq(const A &x, const A &y) const {  // not equal
        return x != y;
    }
};  // struct Compare
}  // namespace s21
#endif  // SRC_S21_COMPARE_H_
