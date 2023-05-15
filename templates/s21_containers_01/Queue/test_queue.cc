#include <gtest/gtest.h>

#include <queue>

#include "s21_queue.h"

TEST(Test_1, constructor_int) {
  s21::Queue<int> my_queue = {1, 2};
  std::queue<int> or_queue;
  or_queue.push(1);
  or_queue.push(2);
  EXPECT_EQ(my_queue.front(), or_queue.front());
}

TEST(Test_1, constructor_float) {
  s21::Queue<float> my_queue = {1.5, 2.5};
  std::queue<float> or_queue;
  or_queue.push(1.5);
  or_queue.push(2.5);
  EXPECT_EQ(my_queue.front(), or_queue.front());
  EXPECT_EQ(my_queue.back(), or_queue.back());
}

TEST(Test_2, copy_arr) {
  s21::Queue<float> my_queue = {1.5, 2.5};
  s21::Queue<float> copy_queue(my_queue);
  EXPECT_EQ(my_queue.front(), copy_queue.front());
  EXPECT_EQ(my_queue.back(), copy_queue.back());
}

TEST(Test_2, copy_operator) {
  s21::Queue<int> my_queue = {1, 4, 6, 3, 7};
  s21::Queue<int> copy_queue = my_queue;
  EXPECT_EQ(my_queue.front(), copy_queue.front());
  EXPECT_EQ(my_queue.back(), copy_queue.back());
}

TEST(Test_3, move_arr) {
  s21::Queue<int> my_queue = {1, 4, 6, 3, 7};
  s21::Queue<int> move_queue = std::move(my_queue);
  EXPECT_EQ(1, move_queue.front());
  EXPECT_EQ(7, move_queue.back());
}

TEST(Test_4, push) {
  s21::Queue<int> my_queue = {1, 4, 6, 3, 7};
  my_queue.push(10);
  EXPECT_EQ(10, my_queue.back());
}

TEST(Test_5, pop) {
  s21::Queue<int> my_queue = {1, 4, 6, 3, 7};
  my_queue.pop();
  EXPECT_EQ(4, my_queue.front());
}

TEST(Test_6, empty) {
  s21::Queue<int> my_queue = {1, 4, 6, 3, 7};
  s21::Queue<int> empty_queue;
  EXPECT_TRUE(empty_queue.empty());
  EXPECT_FALSE(my_queue.empty());
}

TEST(Test_7, size) {
  s21::Queue<int> my_queue = {1, 4, 6, 3, 7};
  EXPECT_EQ(my_queue.size(), 5);
}

TEST(Test_8, swap) {
  s21::Queue<int> queue1 = {1, 1, 1, 1, 1};
  s21::Queue<int> queue2 = {2, 2, 2, 2, 2};
  EXPECT_EQ(queue2.front(), 2);
  EXPECT_EQ(queue1.front(), 1);
  queue1.swap(queue2);
  EXPECT_EQ(queue1.front(), 2);
  EXPECT_EQ(queue2.front(), 1);
}

TEST(Test_9, full_pop) {
  s21::Queue<int> queue1 = {1, 2, 3, 4, 5};
  EXPECT_FALSE(queue1.empty());
  const int const_size = queue1.size();
  for (auto i = 0; i < const_size; i++) {
    queue1.pop();
  }
  EXPECT_TRUE(queue1.empty());
}

TEST(Test_10, fill_queue) {
  s21::Queue<int> queue1;
  EXPECT_TRUE(queue1.empty());
  for (auto i = 1; i <= 5; i++) {
    queue1.push(i);
  }
  EXPECT_EQ(queue1.front(), 1);
  EXPECT_EQ(queue1.back(), 5);
  EXPECT_FALSE(queue1.empty());
}

TEST(Test_11, emplace_back_test) {
  s21::Queue<int> queue1;
  queue1.emplace_back(5);
  EXPECT_EQ(5, queue1.front());
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);

  return RUN_ALL_TESTS();
}