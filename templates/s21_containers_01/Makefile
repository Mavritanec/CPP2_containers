# --gtest_brief=1 - to show only test failures

.PHONY: all re test clean check style leak
#.PHONY если есть файлы с именем как цель, они игнорируются

CC = gcc
FLAGS = -Wall -Werror -Wextra -lstdc++ -std=c++17 -lgtest -Wno-unused -g
#  -pedantic
# TST_LIBS := -lgtest -lm -lpthread

VECTOR = tests/vector_tests.cc
MAP = tests/map_tests.cc
SET = tests/set_tests.cc
MULTISET = tests/multiset_tests.cc

LIST = List/test_list.cc
ARRAY = Array/test_array.cc
QUEUE = Queue/test_queue.cc
STACK = Stack/test_stack.cc


# HEADER = s21_containers.h

# 
CONTAINERS = $(VECTOR)  $(ARRAY) $(LIST) $(STACK) $(QUEUE)
# $(MAP) $(SET) $(MULTISET)

all: test

re: clean test

# 
test: vector_test map_test set_test multiset_test list_test array_test queue_test stack_test

vector_test: vector_test.o
	$(CC) $(FLAGS) vector_test.o -o test_vector
	./test_vector 
# --gtest_brief=1

vector_test.o:
	$(CC) $(FLAGS) -c $(VECTOR) -o vector_test.o

map_test: map_test.o
	$(CC) $(FLAGS) map_test.o -o test_map
	./test_map 
# --gtest_brief=1

map_test.o:
	$(CC) $(FLAGS) -c $(MAP) -o map_test.o

set_test: set_test.o
	$(CC) $(FLAGS) set_test.o -o test_set
	./test_set 
# --gtest_brief=1

set_test.o:
	$(CC) $(FLAGS) -c $(SET) -o set_test.o

multiset_test: multiset_test.o
	$(CC) $(FLAGS) multiset_test.o -o test_multiset
	./test_multiset 
# --gtest_brief=1

multiset_test.o:
	$(CC) $(FLAGS) -c $(MULTISET) -o multiset_test.o


list_test: list_test.o
	$(CC) $(FLAGS) list_test.o -o test_list
	./test_list 
# --gtest_brief=1

list_test.o:
	$(CC) $(FLAGS) -c $(LIST) -o list_test.o

array_test: array_test.o
	$(CC) $(FLAGS) array_test.o -o test_array
	./test_array 
# --gtest_brief=1

array_test.o:
	$(CC) $(FLAGS) -c $(ARRAY) -o array_test.o

queue_test: queue_test.o
	$(CC) $(FLAGS) queue_test.o -o test_queue
	./test_queue 
# --gtest_brief=1

queue_test.o:
	$(CC) $(FLAGS) -c $(QUEUE) -o queue_test.o

stack_test: stack_test.o
	$(CC) $(FLAGS) stack_test.o -o test_stack
	./test_stack 
# --gtest_brief=1

stack_test.o:
	$(CC) $(FLAGS) -c $(STACK) -o stack_test.o

gcov_report: gcov_test.info
	@genhtml -o report/ gcov_test.info
	@open report/index.html

gcov_test.info: gcov_test gcov_test.gcda
	@lcov -t "gcov_test" -o gcov_test.info --no-external -c -d .

gcov_test: $(MULTISET)
	$(CC) $(FLAGS) --coverage $(MULTISET) -o gcov_test

gcov_test.gcda:
	@chmod +x *
	@./gcov_test

clean: 
	@rm -rf *.o *.a test gcov_test *.gcno *.gcda *.info report *.dSYM \
	test_map test_set test_array test_multiset test_vector \
	test_list test_stack test_queue
	
style:
	cp ../materials/linters/.clang-format ./
	clang-format -i tests/* iterators/* Array/* List/* Queue/* Stack/* Map/* Set/* Multiset/* Vector/*
	clang-format -n tests/* iterators/* Array/* List/* Queue/* Stack/* Map/* Set/* Multiset/* Vector/*

leak:
	CK_FORK=no leaks -atExit -- ./test_map
	CK_FORK=no leaks -atExit -- ./test_set
	CK_FORK=no leaks -atExit -- ./test_multiset
	CK_FORK=no leaks -atExit -- ./test_list
	CK_FORK=no leaks -atExit -- ./test_stack
	CK_FORK=no leaks -atExit -- ./test_queue
	CK_FORK=no leaks -atExit -- ./test_array
	CK_FORK=no leaks -atExit -- ./test_vector
