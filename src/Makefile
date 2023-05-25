FLAGS= -Wall -Wextra -Werror
STD= -std=c11

all: s21_matrix.a

style:
	clang-format -i *.c *.h
	clang-format -n *.c *.h

s21_matrix.a: s21_matrix
	ar rc s21_matrix.a s21_*.o
	ranlib s21_matrix.a

s21_matrix: s21_matrix.c s21_matrix.h
	gcc ${FLAGS} ${STD} -c s21_matrix.c

test: s21_matrix.a test.c
	gcc ${FLAGS} ${STD} -c test.c
	gcc -c -fprofile-arcs -ftest-coverage s21_matrix.c
	gcc -fprofile-arcs -ftest-coverage s21_matrix.c test.o -lcheck -lm -lpthread -o run_tests
	./run_tests

gcov_report: test
	mkdir report
	gcov -f *.gcno
	gcovr -r . --html --html-details -o report/report.html
	open report/report.html
	rm -rf *.gcda *gcno

clean:
	rm -rf *.o *.gcov *.gcno *.gcda test run_tests s21_matrix s21_matrix.a report