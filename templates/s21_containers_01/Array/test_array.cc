#include <gtest/gtest.h>

#include <array>

#include "s21_array.h"

TEST(Test_1, constructor_int) {
  s21::Array<int, 5> my_arr = {1, 2, 3, 4, 5};
  std::array<int, 5> or_arr = {1, 2, 3, 4, 5};
  EXPECT_EQ(my_arr[0], or_arr[0]);
}

TEST(Test_1, constructor_float) {
  s21::Array<float, 5> my_arr = {1.6, 2.3, 3.2, 4.7, 5.0};
  std::array<float, 5> or_arr = {1.6, 2.3, 3.2, 4.7, 5.0};
  EXPECT_EQ(my_arr.at(2), or_arr.at(2));
}

TEST(Test_2, copy_arr) {
  s21::Array<int, 5> my_arr = {1, 2, 3, 4, 5};
  s21::Array<int, 5> copy_arr(my_arr);
  EXPECT_EQ(copy_arr[1], my_arr[1]);
}

TEST(Test_2, copy_operator) {
  s21::Array<int, 5> my_arr = {1, 2, 3, 4, 5};
  s21::Array<int, 5> copy_arr = my_arr;
  EXPECT_EQ(copy_arr[0], my_arr[0]);
}

TEST(Test_3, move_arr) {
  s21::Array<int, 5> my_arr = {1, 2, 3, 4, 5};
  s21::Array<int, 5> move_arr = std::move(my_arr);
  EXPECT_EQ(move_arr[0], 1);
}

TEST(Test_4, front_and_back) {
  s21::Array<int, 5> my_arr = {1, 2, 3, 4, 5};
  EXPECT_EQ(my_arr.front(), my_arr[0]);
  EXPECT_EQ(my_arr.back(), my_arr[4]);
}

TEST(Test_5, begin_and_end) {
  s21::Array<int, 5> my_arr = {1, 2, 3, 4, 5};
  EXPECT_TRUE(my_arr.begin() == &my_arr[0]);
  EXPECT_TRUE(my_arr.end() == &my_arr[5]);
}

TEST(Test_6, cbegin_and_cend) {
  const s21::Array<int, 5> arr = {1, 2, 3, 4, 5};
  EXPECT_TRUE(arr.cbegin() == &arr[0]);
  EXPECT_TRUE(arr.cend() == &arr[5]);
}

TEST(Test_7, data) {
  s21::Array<int, 5> my_arr = {1, 2, 3, 4, 5};
  EXPECT_TRUE(my_arr.data() == &my_arr[0]);
}

TEST(Test_8, empty) {
  s21::Array<int, 5> my_arr = {1, 2, 3, 4, 5};
  EXPECT_FALSE(my_arr.empty());
  s21::Array<int, 0> emp_arr;
  EXPECT_TRUE(emp_arr.empty());
}

TEST(Test_9, size) {
  s21::Array<int, 5> my_arr = {1, 2, 3, 4, 5};
  EXPECT_EQ(5, my_arr.size());
  EXPECT_EQ(5, my_arr.max_size());
}

TEST(Test_10, swap) {
  s21::Array<int, 5> arr1 = {1, 2, 3, 4, 5};
  s21::Array<int, 5> arr2 = {5, 4, 3, 2, 1};
  EXPECT_FALSE(5 == arr1[0]);
  EXPECT_FALSE(1 == arr2[0]);
  arr1.swap(arr2);
  EXPECT_TRUE(5 == arr1[0]);
  EXPECT_TRUE(1 == arr2[0]);
}

TEST(Test_11, fill) {
  s21::Array<int, 4> arr1 = {1, 2, 3};
  arr1.fill(4);
  EXPECT_EQ(4, arr1[3]);
}

TEST(Test_12, iterator_test) {
  s21::Array<int, 4> arr1 = {1, 2, 3, 4};
  s21::Array<int, 4>::iterator it = arr1.begin();
  for (size_t i = 0; i < arr1.size(); i++) {
    EXPECT_EQ(*it, arr1[i]);
    it++;
  }
}
TEST(Test_12, iterator_edit) {
  s21::Array<int, 4> arr1 = {1, 2, 3, 4};
  s21::Array<int, 4>::iterator it = arr1.begin();
  *it = 7;
  EXPECT_EQ(arr1[0], 7);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);

  return RUN_ALL_TESTS();
}