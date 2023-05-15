#ifndef SRC_S21_PAIR_COMPARE_H_
#define SRC_S21_PAIR_COMPARE_H_
#include <utility>
namespace s21 {
template <class A, class B>
struct PairCompare {
public:
    // pair methods
    bool lt(const std::pair<A, B> &x, const std::pair<A, B> &y) const {  // less then
        return x.first < y.first;
    }
    bool gt(const std::pair<A, B> &x, const std::pair<A, B> &y) const {  // grater then
        return x.first > y.first;
    }
    bool le(const std::pair<A, B> &x, const std::pair<A, B> &y) const {  // less or equal
        return x.first <= y.first;
    }
    bool ge(const std::pair<A, B> &x, const std::pair<A, B> &y) const {  // grater or equal
        return x.first >= y.first;
    }
    bool eq(const std::pair<A, B> &x, const std::pair<A, B> &y) const {  // equal
        return x.first == y.first;
    }
    bool neq(const std::pair<A, B> &x, const std::pair<A, B> &y) const {  // not equal
        return x.first != y.first;
    }
};  // struct PairCompare
}  // namespace s21
#endif  // SRC_S21_PAIR_COMPARE_H_