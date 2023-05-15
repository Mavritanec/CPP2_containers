#include <set>

#include "s21_set.h"

using namespace s21;

template <typename T>
void test_eq(set<T> &a, std::set<T> &std_a) {
  EXPECT_EQ(a.size(), std_a.size());
  auto it_std = std_a.begin();
  auto it = a.begin();
  while (it_std != std_a.end() && it != a.end()) {
    EXPECT_EQ(*it, *it_std);
    ++it;
    ++it_std;
  }
}

TEST(s21_set, create) {
  set<double> a;
  std::set<double> std_a;
  a.insert(7.231002);
  a.insert(3);
  a.insert(7.2310001);
  a.insert(65.123123);
  std_a.insert(7.231002);
  std_a.insert(3);
  std_a.insert(7.2310001);
  std_a.insert(65.123123);
  test_eq(a, std_a);
}

TEST(s21_set, copy) {
  set<double> a;
  a.insert(76.231002);
  a.insert(73);
  a.insert(-7.2310001);
  a.insert(655.123123);
  a.insert(37.23134002);
  a.insert(32);
  a.insert(47.2312340001);
  a.insert(65.123423123);
  a.insert(37.22341002);
  a.insert(3);
  a.insert(237.223310001);
  a.insert(6532.123123);
  std::set<double> std_a;
  std_a.insert(76.231002);
  std_a.insert(73);
  std_a.insert(-7.2310001);
  std_a.insert(655.123123);
  std_a.insert(37.23134002);
  std_a.insert(32);
  std_a.insert(47.2312340001);
  std_a.insert(65.123423123);
  std_a.insert(37.22341002);
  std_a.insert(3);
  std_a.insert(237.223310001);
  std_a.insert(6532.123123);
  set<double> b(a);
  std::set<double> std_b(std_a);
  test_eq(b, std_b);
}

TEST(s21_set, move) {
  set<double> a;
  a.insert(76.231002);
  a.insert(73);
  a.insert(-7.2310001);
  a.insert(655.123123);
  a.insert(37.23134002);
  a.insert(32);
  a.insert(47.2312340001);
  a.insert(65.123423123);
  a.insert(37.22341002);
  a.insert(3);
  a.insert(237.223310001);
  a.insert(6532.123123);
  std::set<double> std_a;
  std_a.insert(76.231002);
  std_a.insert(73);
  std_a.insert(-7.2310001);
  std_a.insert(655.123123);
  std_a.insert(37.23134002);
  std_a.insert(32);
  std_a.insert(47.2312340001);
  std_a.insert(65.123423123);
  std_a.insert(37.22341002);
  std_a.insert(3);
  std_a.insert(237.223310001);
  std_a.insert(6532.123123);
  set<double> b(std::move(a));
  std::set<double> std_b(std::move(std_a));
  test_eq(b, std_b);
  test_eq(a, std_a);
}

TEST(s21_set, init_list) {
  set<double> a{2, -3, 4, -1, 5, -7, 6, -9, 8, -10};
  std::set<double> std_a{2, -3, 4, -1, 5, -7, 6, -9, 8, -10};
  test_eq(a, std_a);
}

TEST(s21_set, insert) {
  set<int> a;
  std::set<int> std_a;
  for (int i = 0; i < 100; i++) {
    a.insert(i);
    std_a.insert(i);
  }
  test_eq(a, std_a);
}

TEST(s21_set, iterator) {
  set<int> a{2,   -3, 4,  -1, 5,  -7, 6,    -9,  8,
             -10, 45, 34, 76, -4, 57, -567, -567};
  std::set<int> std_a{2,   -3, 4,  -1, 5,  -7, 6,    -9,  8,
                      -10, 45, 34, 76, -4, 57, -567, -567};
  auto it = a.begin();
  auto std_it = std_a.begin();
  EXPECT_EQ(*it, *std_it);
}

TEST(s21_set, iterator2) {
  set<int> a;
  auto it = a.begin();
  if (it == a.end()) {
    EXPECT_EQ(1, 1);
  } else {
    EXPECT_EQ(0, 1);
  }
}

TEST(s21_set, iterator3) {
  set<int> a;
  auto it = a.begin();
  EXPECT_ANY_THROW(*it);
}

TEST(s21_set, iterator_plus) {
  set<int> a{2,   -3, 4,  -1, 5,  -7, 6,    -9,  8,
             -10, 45, 34, 76, -4, 57, -567, -567};
  std::set<int> std_a{2,   -3, 4,  -1, 5,  -7, 6,    -9,  8,
                      -10, 45, 34, 76, -4, 57, -567, -567};
  auto it = a.begin();
  auto std_it = std_a.begin();
  for (int i = 0; i < 5; ++i) {
    ++it;
    ++std_it;
  }
  EXPECT_EQ(*it, *std_it);
}

TEST(s21_set, iterator_unname) {
  set<int> a{2,   -3, 4,  -1, 5,  -7, 6,    -9,  8,
             -10, 45, 34, 76, -4, 57, -567, -567};
  auto it = a.begin();
  for (int i = 0; i < 9; ++i) {
    ++it;
  }
  EXPECT_EQ(5, *it);
}

TEST(s21_set, erase) {
  set<int> a{2,   -3, 4,  -1, 5,  -7, 6,    -9,  8,
             -10, 45, 34, 76, -4, 57, -567, -567};
  std::set<int> std_a{2,   -3, 4,  -1, 5,  -7, 6,    -9,  8,
                      -10, 45, 34, 76, -4, 57, -567, -567};
  auto it = a.begin();
  auto std_it = std_a.begin();
  for (int i = 0; i < 9; ++i) {
    ++it;
    ++std_it;
  }
  a.erase(it);
  std_a.erase(std_it);
  test_eq(a, std_a);
}

TEST(s21_set, erase2) {
  set<int> a{2, 3};
  std::set<int> std_a{2, 3};
  auto it = a.begin();
  auto std_it = std_a.begin();
  ++it;
  ++std_it;
  a.erase(it);
  std_a.erase(std_it);
  test_eq(a, std_a);
}

TEST(s21_set, erase3) {
  set<int> a{2};
  std::set<int> std_a{2};
  auto std_it = std_a.begin();
  auto it = a.begin();
  a.erase(it);
  std_a.erase(std_it);
  test_eq(a, std_a);
}

TEST(s21_set, erase3_throw) {
  set<int> a{2};
  auto it = a.begin();
  ++it;
  EXPECT_ANY_THROW(a.erase(it));
}

TEST(s21_set, erase4) {
  set<int> a{2, 3, 4, 5, 6, 7};
  auto it = a.begin();
  ++it;
  a.erase(it);
  EXPECT_EQ(a.size(), 5);
}

TEST(s21_set, erase5) {
  set<int> a{-2, -3, -4, -5, -6, -7};
  auto it = a.begin();
  ++it;
  a.erase(it);
  EXPECT_EQ(a.size(), 5);
}

TEST(s21_set, erase6) {
  set<int> a{0, 2, -2, 3, -3, 4, -4, 5, -5, 6, -6, 7, -7};
  std::set<int> std_a{0, 2, -2, 3, -3, 4, -4, 5, -5, 6, -6, 7, -7};
  auto it = a.begin();
  auto std_it = std_a.begin();
  a.erase(it);
  std_a.erase(std_it);
  test_eq(a, std_a);
}

TEST(s21_set, erase7) {
  set<int> a{20, 10, 40, 60, 80, 25, 24};
  std::set<int> std_a{20, 10, 40, 60, 80, 25, 24};
  auto it = a.begin();
  auto std_it = std_a.begin();
  ++it;
  ++std_it;
  a.erase(it);
  std_a.erase(std_it);
  test_eq(a, std_a);
}

TEST(s21_set, erase8) {  // HAVE LEAKS
  set<int> a{1, 2, 3};
  auto it = a.begin();
  a.clear();
  EXPECT_ANY_THROW(a.erase(it));
  EXPECT_EQ(a.size(), 0);
}

TEST(s21_set, op_eq) {
  set<int> a{0, 2, -2, 3, -3, 4, -4, 5, -5, 6, -6, 7, -7};
  std::set<int> std_a{0, 2, -2, 3, -3, 4, -4, 5, -5, 6, -6, 7, -7};
  set<int> b;
  std::set<int> std_b;
  b = a;
  std_b = std_a;
  test_eq(b, std_b);
}

TEST(s21_set, empty) {
  set<int> a;
  std::set<int> std_a;
  EXPECT_EQ(a.empty(), std_a.empty());
}

TEST(s21_set, empty2) {
  set<int> a{1};
  std::set<int> std_a{1};
  EXPECT_EQ(a.empty(), std_a.empty());
}

TEST(s21_set, size) {
  set<int> a;
  std::set<int> std_a;
  EXPECT_EQ(a.size(), std_a.size());
}

TEST(s21_set, clear) {
  set<int> a{0, 2, -2, 3, -3, 4, 6, -6, 7, -7};
  std::set<int> std_a{0, 2, -2, 3, -3, 4, -4, 5, -5, 6, -6, 7, -7};
  a.clear();
  std_a.clear();
  EXPECT_EQ(a.size(), std_a.size());
}

TEST(s21_set, swap) {
  set<int> a{0, 2, -2, 3, -3, 4, -4, 5, -5, 6, -6, 7, -7};
  set<int> b;
  std::set<int> std_a{0, 2, -2, 3, -3, 4, -4, 5, -5, 6, -6, 7, -7};
  std::set<int> std_b;
  b.swap(a);
  std_b.swap(std_a);
  test_eq(b, std_b);
}

TEST(s21_set, merge) {
  set<int> a{0, 2, -2, 3, -3, 4, -4, 5, -5, 6, -6, 7, -7};
  set<int> b{5, 2, 3, 5, 4, 3, 45, 346, 456, 7666, 87};
  std::set<int> std_a{0, 2, -2, 3, -3, 4, -4, 5, -5, 6, -6, 7, -7};
  std::set<int> std_b{5, 2, 3, 5, 4, 3, 45, 346, 456, 7666, 87};
  b.merge(a);
  std_b.merge(std_a);
  test_eq(b, std_b);
}

TEST(s21_set, merge2) {
  set<int> a{0, 2, -2, 3, -3, 4, -4, 5, -5, 6, -6, 7, -7};
  set<int> b{5, 2, 3, 5, 4, 3, 45, 346, 456, 7666, 87};
  std::set<int> std_a{0, 2, -2, 3, -3, 4, -4, 5, -5, 6, -6, 7, -7};
  std::set<int> std_b{5, 2, 3, 5, 4, 3, 45, 346, 456, 7666, 87};
  b.merge(a);
  std_b.merge(std_a);
  test_eq(b, std_b);
}

TEST(s21_set, find) {
  set<int> a{0, 2, -2, 3, -3, 4, -4, 5, -5, 6, -6, 7, -7};
  std::set<int> std_a{0, 2, -2, 3, -3, 4, -4, 5, -5, 6, -6, 7, -7};
  auto it = a.find(5);
  auto std_it = std_a.find(5);
  ASSERT_EQ(*it, *std_it);
}

TEST(s21_set, find2) {
  set<int> a{0, 2, -2, 3, -3, 4, -4, 5, -5, 6, -6, 7, -7};
  std::set<int> std_a{0, 2, -2, 3, -3, 4, -4, 5, -5, 6, -6, 7, -7};
  auto it = a.find(500);
  auto std_it = std_a.find(500);
  if (it == a.end() && std_it == std_a.end())
    EXPECT_EQ(1, 1);
  else
    EXPECT_EQ(1, 0);
}

TEST(s21_set, contains) {
  set<int> a{0, 2, -2, 3, -3, 4, -4, 5, -5, 6, -6, 7, -7};
  EXPECT_EQ(a.contains(500), false);
}

TEST(s21_set, contains2) {
  set<int> a;
  EXPECT_EQ(a.contains(500), false);
}

TEST(s21_set, contains3) {
  set<double> a{2.34534534};
  EXPECT_EQ(a.contains(2.34534538), false);
}

TEST(s21_set, max_size) {
  set<int> a{0, 2, -2, 3, -3, 4, -4, 5, -5, 6, -6, 7, -7};
  std::set<int> std_a{0, 2, -2, 3, -3, 4, -4, 5, -5, 6, -6, 7, -7};
  std::cout << "max size s21::set - " << a.max_size()
            << "\nmax_size std::set - " << std_a.max_size() << std::endl;
}

TEST(s21_set, emplace_bonus) {
  set<double> a{2.34534534};
  a.emplace(2.34, 1.43, 1.0, 14.54, 75.34);
  std::set<double> std_a{2.34534534};
  std_a.emplace(2.34);
  std_a.emplace(1.43);
  std_a.emplace(1.0);
  std_a.emplace(14.54);
  std_a.emplace(75.34);
  test_eq(a, std_a);
}