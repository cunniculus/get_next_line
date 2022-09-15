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
int  fd;
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

    fd = open("../test_files/a_nl.txt", O_RDONLY);
	test_open();

	// ACT
	actual_return = get_next_line(fd);
	// ASSERT
	mu_assert_string_eq(actual_return, expected_return);
	close(fd);
	test_close();
    free(actual_return);
}

/*
MU_TEST(test_check) {
	mu_check(foo == 7);
}

MU_TEST(test_assert) {
	mu_assert(foo == 7, "foo should be 7");
}

MU_TEST(test_assert_int_eq) {
	mu_assert_int_eq(4, bar);
}

MU_TEST(test_assert_double_eq) {
	mu_assert_double_eq(0.1, dbar);
}

MU_TEST(test_string_eq){
		mu_assert_string_eq("Thisstring", foostring);
}

MU_TEST(test_fail) {
	mu_fail("Fail now!");
}
*/


MU_TEST_SUITE(test_suite) {
	MU_SUITE_CONFIGURE(&test_setup, &test_teardown);

	MU_RUN_TEST(test_gnl_a_nl);
}

int main(void) {
	MU_RUN_SUITE(test_suite);
	MU_REPORT();
	return MU_EXIT_CODE; }
