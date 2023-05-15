.PHONY: all clear rebuild
CC=gcc
GCOV= -fprofile-arcs -ftest-coverage
CFLAGS=-lstdc++ -lgtest -std=c++17 -Wall -Werror -Wextra 
BUILD=build/
EXECUTABLE=result_testing
all: test

test:  testing/tests.cpp
	@mkdir $(BUILD)
	@${CC} $<  ${CFLAGS} -o $(BUILD)$(EXECUTABLE)
	@./$(BUILD)$(EXECUTABLE)


gcov_report: testing/tests.cpp
	@$(CC) $(GCOV) $<  -o $@
	@./$@
	@lcov -t "gcov_rep" --no-external --output-file=coverag.info --capture --directory .
	@genhtml -o ./report coverag.info
	

clean:
	@/bin/rm -rf *.o *.a build *.gcno *gcda report *.info main *.dSYM *.out gcov_report

leaks:
	leaks --atExit -- ./$(BUILD)$(EXECUTABLE)

rebuild: clean all
