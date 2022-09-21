#include <unistd.h> //open() close ()
#include <stdlib.h> // free()
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <stdio.h>
#include "get_next_line.h"
#include "minunit.h"

static int foo = 0;
static int bar = 0;
static int  fd;
//static double dbar = 0.1;
//static const char* foostring = "Thisstring";

void test_setup(void) {
	foo = 7;
	bar = 4;
}

void test_teardown(void) {
	/* Nothing */
}

MU_TEST(test_open) {
	mu_assert(fd != -1, "fail to open()");
}
MU_TEST(test_close) {
	mu_assert(fd != -1, "fail to close()");
}

MU_TEST(test_gnl_a_nl)
{
	// ARRANGE
    char    expected_return[] = "a\n";
	char	*actual_return;

    fd = open("test_files/a_nl.txt", O_RDONLY);
	test_open();

	// ACT
	actual_return = get_next_line(fd);

	// ASSERT
	mu_assert_string_eq(actual_return, expected_return);
	fd = close(fd);
	test_close();
	if (actual_return)
    	free(actual_return);
}

MU_TEST(test_emptyfile)
{
	// ARRANGE
    char    *expected_return = 0;
	char	*actual_return;

    fd = open("test_files/empty_file.txt", O_RDONLY);
	test_open();

	// ACT
	actual_return = get_next_line(fd);

	// ASSERT
	mu_assert_string_eq(actual_return, expected_return);
	fd  = close(fd);
	test_close();
	if (actual_return)
    	free(actual_return);
}


MU_TEST(test_ad)
{
	// ARRANGE
    char    *expected_return[4] = {"a\n", "b\n", "c\n", "d\n"};
	char	*actual_return[4];

    fd = open("test_files/a-k.txt", O_RDONLY);
	test_open();

	// ACT
	int i = 0;
	while (i < 4)
	{
		actual_return[i] = get_next_line(fd);
		i++;
	}

	// ASSERT
	i = 0;
	while (i < 4)
	{
		mu_assert_string_eq(actual_return[i], expected_return[i]);
		i++;
	}
	fd = close(fd);
	test_close();
	i = 0;
	while (i < 4)
	{
    	free(actual_return[i]);
		i++;
	}
}

MU_TEST(test_nomes)
{
	// ARRANGE
    char    *expected_return[5] = {"Guilherme Coelho de Oliveira\n",\
									"Fabricio Maia de Oliveira\n",\
									"Johann Sebastian Bach\n",\
									"William Shakespeare\n",\
									"Alan Moore\n"};
	char	*actual_return[5];

    fd = open("test_files/nomes.txt", O_RDONLY);
	test_open();

	// ACT
	int i = 0;
	while (i < 5)
	{
		actual_return[i] = get_next_line(fd);
		i++;
	}

	// ASSERT
	i = 0;
	while (i < 5)
	{
		mu_assert_string_eq(actual_return[i], expected_return[i]);
		i++;
	}
	fd = close(fd);
	test_close();
	i = 0;
	while (i < 5)
	{
    	free(actual_return[i]);
		i++;
	}
}

MU_TEST_SUITE(test_suite) {
	MU_SUITE_CONFIGURE(&test_setup, &test_teardown);

	MU_RUN_TEST(test_gnl_a_nl);
	MU_RUN_TEST(test_emptyfile);
	MU_RUN_TEST(test_ad);
	MU_RUN_TEST(test_nomes);
}

int main(void) 
{
	MU_RUN_SUITE(test_suite);
	MU_REPORT();
	return MU_EXIT_CODE; 
}
