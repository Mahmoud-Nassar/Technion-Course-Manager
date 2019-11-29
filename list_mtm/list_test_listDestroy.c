#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "test_utilities.h"
#include "list_mtm.h"

/**
 * We're going to be doing this a lot, so we define a macro for this specific
 * test. You can define many such macros for repetitive assertions in your
 * unit-tests.
 */
#define ASSERT_SAME_PERSON(a,b) ASSERT_TEST(personCompare(a,b) == 0)













static bool testListDestroy() {
	listDestroy(NULL);
	return true;
}

int main() {

	RUN_TEST(testListDestroy);
	return 0;
}
