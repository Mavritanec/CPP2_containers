CC = gcc
FLAGS = -Wall -Werror -Wextra -lstdc++ -std=c++17 -lgtest

TEST = all_tests

SRC_MAP = tests/map_tests.cpp
SRC_SET = tests/set_tests.cpp
SRC_ARRAY = tests/array_tests.cpp
SRC_MULTISET = tests/multiset_tests.cpp
SRC_VECTOR = tests/vector_tests.cpp
SRC_LIST = tests/list_tests.cpp
SRC_QUEUE = tests/queue_tests.cpp
SRC_STACK = tests/stack_tests.cpp

HEADER = s21_containers.h
HEADER_PLUS = s21_containersplus.h

SRC_CONTAINERS = $(SRC_LIST) $(SRC_MAP) $(SRC_QUEUE) \
				$(SRC_SET) $(SRC_STACK) $(SRC_VECTOR)

SRC_CONTAINERSPLUS = $(SRC_ARRAY) $(SRC_MULTISET)

map_test:
	$(CC) $(FLAGS) $(SRC_MAP) -o test_map
	./test_map --gtest_brief=1

set_test:
	$(CC) $(FLAGS) $(SRC_SET) -o test_set
	./test_set --gtest_brief=1

vector_test:
	$(CC) $(FLAGS) $(SRC_VECTOR) -o test_vector
	./test_vector --gtest_brief=1

list_test:
	$(CC) $(FLAGS) $(SRC_LIST) -o test_list
	./test_list --gtest_brief=1

queue_test:
	$(CC) $(FLAGS) $(SRC_QUEUE) -o test_queue
	./test_queue --gtest_brief=1

stack_test:
	$(CC) $(FLAGS) $(SRC_STACK) -o test_stack
	./test_stack --gtest_brief=1

array_test:
	$(CC) $(FLAGS) $(SRC_ARRAY) -o test_array
	./test_array --gtest_brief=1

multiset_test:
	$(CC) $(FLAGS) $(SRC_MULTISET) -o test_multiset
	./test_multiset --gtest_brief=1

test: map_test set_test vector_test stack_test queue_test \
		list_test array_test multiset_test

style:
	clang-format -n *.h
	clang-format -n iterators/*.h
	clang-format -n tests/*.cpp

clean:
	rm -rf test_map test_set test_array test_multiset test_vector \
	test_list test_stack test_queue
	rm -rf *.gcda *.gcno *.info

