#include <gtest/gtest.h>

#include <stack>

#include "s21_stack.h"

TEST(Test_1, constructor_int) {
  s21::Stack<int> my_stack = {1, 2};
  std::stack<int> orig_stack;
  orig_stack.push(1);
  orig_stack.push(2);
  EXPECT_EQ(my_stack.top(), orig_stack.top());
}

TEST(Test_1, constructor_float) {
  s21::Stack<float> my_stack = {1.5, 2.5};
  std::stack<float> orig_stack;
  orig_stack.push(1.5);
  orig_stack.push(2.5);
  EXPECT_EQ(my_stack.top(), orig_stack.top());
}

TEST(Test_2, copy_arr) {
  s21::Stack<float> my_stack = {1.5, 2.5};
  s21::Stack<float> copy_stack(my_stack);
  EXPECT_EQ(my_stack.top(), copy_stack.top());
}

TEST(Test_2, copy_operator) {
  s21::Stack<int> my_stack = {1, 4, 6, 3, 7};
  s21::Stack<int> copy_stack = my_stack;
  EXPECT_EQ(my_stack.top(), copy_stack.top());
}

TEST(Test_3, move_arr) {
  s21::Stack<int> my_stack = {1, 4, 6, 3, 7};
  s21::Stack<int> move_stack = std::move(my_stack);
  EXPECT_EQ(7, move_stack.top());
}

TEST(Test_4, push) {
  s21::Stack<int> my_stack = {1, 4, 6, 3, 7};
  EXPECT_EQ(7, my_stack.top());
  my_stack.push(10);
  EXPECT_EQ(10, my_stack.top());
}

TEST(Test_5, pop) {
  s21::Stack<int> my_stack = {1, 4, 6, 3, 7};
  EXPECT_EQ(7, my_stack.top());
  my_stack.pop();
  EXPECT_EQ(3, my_stack.top());
}

TEST(Test_6, empty) {
  s21::Stack<int> my_stack = {1, 4, 6, 3, 7};
  s21::Stack<int> empty_stack;
  EXPECT_TRUE(empty_stack.empty());
  EXPECT_FALSE(my_stack.empty());
}

TEST(Test_7, size) {
  s21::Stack<int> my_stack = {1, 4, 6, 3, 7};
  EXPECT_EQ(my_stack.size(), 5);
  my_stack.push(3);
  EXPECT_EQ(my_stack.size(), 6);
}

TEST(Test_8, swap) {
  s21::Stack<int> stack1 = {1, 1, 1, 1, 1};
  s21::Stack<int> stack2 = {2, 2, 2, 2, 2};
  EXPECT_EQ(stack2.top(), 2);
  EXPECT_EQ(stack1.top(), 1);
  stack1.swap(stack2);
  EXPECT_EQ(stack1.top(), 2);
  EXPECT_EQ(stack2.top(), 1);
}

TEST(Test_9, full_pop) {
  s21::Stack<int> stack1 = {1, 2, 3, 4, 5};
  EXPECT_FALSE(stack1.empty());
  const int const_size = stack1.size();
  for (auto i = 0; i < const_size; i++) {
    stack1.pop();
  }
  EXPECT_TRUE(stack1.empty());
}

TEST(Test_10, fill_stack) {
  s21::Stack<int> stack1;
  EXPECT_TRUE(stack1.empty());
  for (auto i = 1; i <= 5; i++) {
    stack1.push(i);
  }
  EXPECT_EQ(stack1.top(), 5);
  EXPECT_FALSE(stack1.empty());
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);

  return RUN_ALL_TESTS();
}