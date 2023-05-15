#include <gtest/gtest.h>

#include <list>

#include "s21_list.h"

TEST(Constructor, Default) {
  s21::List<double> l;
  EXPECT_EQ(0, l.size());
  EXPECT_EQ(l.begin(), nullptr);
}

TEST(Constructor, With_parameter) {
  s21::List<double> l1(5);
  EXPECT_EQ(l1.size(), 5);
  EXPECT_EQ(l1.front(), 0);
}

TEST(Constructor, Initializer_list) {
  std::list<int> l1 = {1, 2, 3, 4, 5};
  s21::List<int> l2 = {1, 2, 3, 4, 5};
  EXPECT_EQ(l1.front(), l2.front());
  EXPECT_EQ(l1.back(), l2.back());
  EXPECT_EQ(l1.size(), l2.size());
}

TEST(Constructor, Copy) {
  s21::List<int> l2 = {1, 2, 3, 4, 5};
  s21::List<int> l1(l2);
  EXPECT_EQ(l1.front(), l2.front());
  EXPECT_EQ(l1.back(), l2.back());
  EXPECT_EQ(l1.size(), l2.size());
}

TEST(Constructor, Move) {
  s21::List<int> l2 = {1, 2, 3, 4, 5};
  s21::List<int> l1 = std::move(l2);
  EXPECT_EQ(1, l1.front());
  EXPECT_EQ(5, l1.back());
  EXPECT_EQ(0, l2.size());
}

TEST(list_element, front_and_back) {
  std::list<double> l1 = {1.366, 2, 3};
  s21::List<double> l2 = {1.366, 2, 3};
  EXPECT_EQ(l1.front(), l2.front());
  EXPECT_EQ(l1.back(), l2.back());
}

TEST(List_modifier, Clear) {
  std::list<int> l1 = {1, 2, 3, 4, 5};
  s21::List<int> l2 = {1, 2, 3, 4, 5};
  l1.clear();
  l2.clear();
  EXPECT_EQ(l1.size(), l2.size());
  EXPECT_EQ(l2.size(), 0);
}

TEST(List_modifier, empty) {
  std::list<int> l1 = {1, 2, 3, 4, 5};
  s21::List<int> l2 = {1, 2, 3, 4, 5};
  EXPECT_EQ(l1.empty(), l2.empty());
}

TEST(List_count, size) {
  std::list<int> l1 = {1, 2, 3, 4, 5};
  s21::List<int> l2 = {1, 2, 3, 4, 5};
  EXPECT_EQ(l1.size(), l2.size());
}

TEST(List_iterator, Begin) {
  std::list<int> l1 = {1, 2, 3, 4, 5};
  s21::List<int> l2 = {1, 2, 3, 4, 5};
  auto iter1 = l1.begin();
  auto iter2 = l2.begin();
  EXPECT_EQ(*iter1, *iter2);
}

TEST(List_iterator, End) {
  std::list<int> l1 = {1, 2, 3, 4, 5};
  s21::List<int> l2 = {1, 2, 3, 4, 5};
  auto iter1 = l1.end();
  auto iter2 = l2.end();
  EXPECT_EQ(*iter1, *iter2);
}

TEST(List_modifier, Push_back) {
  std::list<int> l1 = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  s21::List<int> l2 = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  l1.push_back(11);
  l2.push_back(11);
  EXPECT_EQ(l1.back(), l2.back());
  EXPECT_EQ(l1.size(), l2.size());

  std::list<int> l3;
  s21::List<int> l4;
  l3.push_back(11);
  l4.push_back(11);
  EXPECT_EQ(l3.back(), l4.back());
  EXPECT_EQ(l3.size(), l4.size());
}

TEST(List_modifier, Push_front) {
  std::list<int> l1 = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  s21::List<int> l2 = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  l1.push_front(11);
  l2.push_front(11);
  EXPECT_EQ(l1.front(), l2.front());
  EXPECT_EQ(l1.size(), l2.size());

  std::list<int> l3;
  s21::List<int> l4;
  l3.push_front(11);
  l4.push_front(11);
  EXPECT_EQ(l3.front(), l4.front());
  EXPECT_EQ(l3.size(), l4.size());
}

TEST(List_modifier, insert) {
  std::list<int> l1 = {1, 2, 3, 4, 5};
  s21::List<int> l2 = {1, 2, 3, 4, 5};
  auto iter1 = ++l1.begin();
  auto iter2 = 1;
  l1.insert(iter1, 11);
  l2.insert(iter2, 11);
  EXPECT_EQ(l1.front(), l2.front());
  EXPECT_EQ(l1.size(), l2.size());
}

TEST(List_modifier, pop_back) {
  std::list<int> l1 = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  s21::List<int> l2 = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  l1.pop_back();
  l2.pop_back();
  EXPECT_EQ(l1.back(), l2.back());
  EXPECT_EQ(l1.size(), l2.size());
}

TEST(List_modifier, pop_front) {
  std::list<int> l1 = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  s21::List<int> l2 = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  l1.pop_front();
  l2.pop_front();
  EXPECT_EQ(l1.front(), l2.front());
  EXPECT_EQ(l1.size(), l2.size());
}

TEST(List_modifier, erase) {
  std::list<int> l1 = {1, 2, 3, 4, 5};
  s21::List<int> l2 = {1, 2, 3, 4, 5};
  auto iter1 = ++l1.begin();
  auto iter2 = 1;
  l1.erase(iter1);
  l2.erase(iter2);
  EXPECT_EQ(l1.front(), l2.front());
  EXPECT_EQ(l1.size(), l2.size());
}

TEST(List_modifier, Swap) {
  std::list<int> a1 = {1, 2, 3};
  std::list<int> a2 = {3, 4, 5, 6};
  a1.swap(a2);
  s21::List<int> b1 = {1, 2, 3};
  s21::List<int> b2 = {3, 4, 5, 6};
  b1.Swap(b2);

  EXPECT_EQ(a1.front(), b1.front());
  EXPECT_EQ(a1.back(), b1.back());
  EXPECT_EQ(a1.size(), b1.size());
}

TEST(List_modifier, merge) {
  std::list<int> a1 = {1, 2, 3};
  std::list<int> a2 = {3, 4, 5, 6};
  a1.merge(a2);
  s21::List<int> b1 = {1, 2, 3};
  s21::List<int> b2 = {3, 4, 5, 6};
  b1.Merge(b2);

  EXPECT_EQ(a1.front(), b1.front());
  EXPECT_EQ(a1.back(), b1.back());
  EXPECT_EQ(a1.size(), b1.size());
}

TEST(List_modifier, Splice) {
  std::list<int> a1 = {1, 2, 3};
  std::list<int> a2 = {3, 4, 5, 6};
  auto iter1 = ++a1.begin();
  a1.splice(iter1, a2);
  s21::List<int> b1 = {1, 2, 3};
  s21::List<int> b2 = {3, 4, 5, 6};
  auto iter2 = 1;
  b1.Splice(iter2, b2);

  EXPECT_EQ(a1.front(), b1.front());
  EXPECT_EQ(a1.back(), b1.back());
  EXPECT_EQ(a1.size(), b1.size());
}

TEST(List_modifier, reverce) {
  std::list<int> l1 = {1, 2, 3, 4, 5};
  s21::List<int> l2 = {1, 2, 3, 4, 5};
  l1.reverse();
  l2.reverse();
  EXPECT_EQ(l1.front(), l2.front());
  EXPECT_EQ(l1.back(), l2.back());
  EXPECT_EQ(l1.size(), l2.size());
}

TEST(List_modifier, unique) {
  std::list<int> l1 = {1, 2, 3, 4, 5};
  s21::List<int> l2 = {1, 2, 3, 4, 5};
  l1.unique();
  l2.unique();
  EXPECT_EQ(l1.front(), l2.front());
  EXPECT_EQ(l1.back(), l2.back());
  EXPECT_EQ(l1.size(), l2.size());
}

TEST(List_modifier, sort) {
  std::list<int> l1 = {1, 2, 3, 4, 5};
  s21::List<int> l2 = {1, 2, 3, 4, 5};
  l1.sort();
  l2.sort();
  EXPECT_EQ(l1.front(), l2.front());
  EXPECT_EQ(l1.back(), l2.back());
  EXPECT_EQ(l1.size(), l2.size());
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
