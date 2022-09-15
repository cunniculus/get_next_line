all: test

test: minunit.c
	cc -Wall -Werror -Wextra  -I../../src minunit.c ../../src/get_next_line.c -o test
	./test
