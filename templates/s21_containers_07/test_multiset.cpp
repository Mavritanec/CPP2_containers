#include <set>

#include "s21_multiset.h"

using namespace s21;

template <typename T>
void test_eq(multiset<T> &a, std::multiset<T> &std_a) {
  EXPECT_EQ(a.size(), std_a.size());
  auto it_std = std_a.begin();
  auto it = a.begin();
  while (it_std != std_a.end() && it != a.end()) {
    EXPECT_EQ(*it, *it_std);
    ++it;
    ++it_std;
  }
}

TEST(s21_multiset, create) {
  multiset<double> a;
  std::multiset<double> std_a;
  a.insert(7.231002);
  a.insert(3);
  a.insert(7.231002);
  a.insert(65.123123);
  std_a.insert(7.231002);
  std_a.insert(3);
  std_a.insert(7.231002);
  std_a.insert(65.123123);
  test_eq(a, std_a);
}

TEST(s21_multiset, create1) {
  multiset<int> a;
  auto it = a.insert(15);
  a.insert(15);
  a.insert(16);
  ++it;
  ++it;
  EXPECT_EQ(*it, 16);
}

TEST(s21_multiset, create2) {
  multiset<int> a;
  auto it = a.insert(15);
  a.insert(15);
  a.insert(16);
  ++it;
  ++it;
  EXPECT_EQ(*it, 16);
}

TEST(s21_multiset, init_list) {
  multiset<int> a{1, 1, 1, 1, 2, 2, 2, 2, 3, 3, 3, 3, 4, 4, 4, 4};
  auto it = a.begin();
  ++it;
  ++it;
  ++it;
  EXPECT_EQ(*it, 1);
  ++it;
  ++it;
  ++it;
  ++it;
  EXPECT_EQ(*it, 2);
  ++it;
  ++it;
  ++it;
  ++it;
  EXPECT_EQ(*it, 3);
  ++it;
  ++it;
  ++it;
  ++it;
  EXPECT_EQ(*it, 4);
}

TEST(s21_multiset, copy_constr) {
  multiset<int> a{1, 32, 354, 435, 46, 4, 6556, 5, 6, 867, 9, 789, 7, 85, 4};
  std::multiset<int> std_a{1, 32,  354, 435, 46, 4,  6556, 5,
                           6, 867, 9,   789, 7,  85, 4};
  multiset<int> b(a);
  std::multiset<int> std_b(std_a);
  test_eq(b, std_b);
}

TEST(s21_multiset, move_const) {
  multiset<int> a{1, 32, 354, 435, 46, 4, 6556, 5, 6, 867, 9, 789, 7, 85, 4};
  std::multiset<int> std_a{1, 32,  354, 435, 46, 4,  6556, 5,
                           6, 867, 9,   789, 7,  85, 4};
  multiset<int> b(std::move(a));
  std::multiset<int> std_b(std::move(std_a));
  test_eq(b, std_b);
  test_eq(a, std_a);
}

TEST(s21_multiset, op_eq) {
  multiset<int> a{1, 32, 354, 435, 46, 4, 6556, 5, 6, 867, 9, 789, 7, 85, 4};
  std::multiset<int> std_a{1, 32,  354, 435, 46, 4,  6556, 5,
                           6, 867, 9,   789, 7,  85, 4};
  multiset<int> b;
  b = a;
  std::multiset<int> std_b;
  std_b = std_a;
  test_eq(b, std_b);
  test_eq(a, std_a);
}

TEST(s21_multiset, lower_bound) {
  multiset<int> a{1,  32,  354, 435, 46,     4,   6556, 5,   6, 867,
                  9,  789, 7,   85,  4,      345, 345,  34,  5, 345,
                  34, 53,  645, 7,   578678, 6,   4,    234, 2, 3};
  std::multiset<int> std_a{1,  32,  354, 435, 46,     4,   6556, 5,   6, 867,
                           9,  789, 7,   85,  4,      345, 345,  34,  5, 345,
                           34, 53,  645, 7,   578678, 6,   4,    234, 2, 3};
  for (int key = -50; key < 50; key++) {
    auto it = a.lower_bound(key);
    auto std_it = std_a.lower_bound(key);
    EXPECT_EQ(*it, *std_it);
  }
}

TEST(s21_multiset, upper_bound) {
  multiset<int> a{1,  32,  354, 435, 46, 4,   655, 5,   6, 867,
                  9,  789, 7,   85,  4,  345, 345, 34,  5, 345,
                  34, 53,  645, 7,   57, 6,   4,   234, 2, 3};
  std::multiset<int> std_a{1,  32,  354, 435, 46, 4,   655, 5,   6, 867,
                           9,  789, 7,   85,  4,  345, 345, 34,  5, 345,
                           34, 53,  645, 7,   57, 6,   4,   234, 2, 3};
  for (int key = -50; key < 1000; key += 15) {
    auto it = a.upper_bound(key);
    auto std_it = std_a.upper_bound(key);
    EXPECT_EQ(*it, *std_it);
  }
}

TEST(s21_multiset, eq_range) {
  multiset<int> a{1, 2, 3, 3, 3, 5, 5, 6};
  std::multiset<int> std_a{1, 2, 3, 3, 3, 5, 5, 6};
  for (int key = -10; key < 15; key += 2) {
    auto it = a.equal_range(key);
    auto std_it = std_a.equal_range(key);
    EXPECT_EQ(*it.first, *std_it.first);
    EXPECT_EQ(*it.second, *std_it.second);
  }
}

TEST(s21_multiset, emplace_bonus) {
  multiset<double> a{2.34534534};
  a.emplace(2.34, 1.43, 1.0, 14.54, 75.34);
  std::multiset<double> std_a{2.34534534};
  std_a.emplace(2.34);
  std_a.emplace(1.43);
  std_a.emplace(1.0);
  std_a.emplace(14.54);
  std_a.emplace(75.34);
  test_eq(a, std_a);
}