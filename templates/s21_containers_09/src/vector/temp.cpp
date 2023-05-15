#include <cstring>
#include <utility>
#include <vector>

#include "s21_vector.cpp"

void std_print(std::vector<int>& arr) {
  printf("std array: \n\t");
  printf("capacity: %lu\n\t", arr.capacity());
  printf("size: %lu\n\t", arr.size());
  for (int i = 0; i < arr.capacity(); ++i) {
    printf("%d ", arr[i]);
  }
  printf("\n");
}
void s21_print(s21::vector<int>& arr) {
//  printf("s21 array: \n\t");
//  printf("s21 capacity: %lu\n\t", arr.capacity());
//  printf("s21 size: %lu\n\t", arr.size());
  for (int i = 0; i < arr.capacity(); ++i) {
    printf("%d ", arr[i]);
  }
  printf("\n");
}

int main() {
  s21::vector<int> s21_a;
  std::vector<int> std_a;

  for(int i = 0; i < 10;++i) {
    std_a.push_back(i);
  }

  for(int i = 0; i < 10;++i) {
    s21_a.push_back(i);
    s21_print(s21_a);

  }

  s21_print(s21_a);
  std_print(std_a);

  s21_a.erase(s21_a.begin());
  std_a.erase(std_a.begin());

  printf("-------------\n");
  s21_print(s21_a);
  std_print(std_a);

//  std_print(std_a);
//  s21_print(s21_a);
//
//  std_a.pop_back();
//  s21_a.pop_back();
//
//  std_print(std_a);
//  s21_print(s21_a);
//
//  printf("std array size: %lu\n\t", std_a.size());
//  printf("s21 array size: %lu\n\t", s21_a.size());



  return 0;
}

/*
 *
 */
