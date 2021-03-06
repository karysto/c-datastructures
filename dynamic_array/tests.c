#include "../_test_framework/min_unit.h"
#include "dynamic_array.c"

int tests_run = 0;

/*
 * Test Cases
 */
char *
test_dynamic_array_create_sets_members(void) {
	struct Dynamic_Array *da = dynamic_array_create(5, 2);

	MU_ASSERT("create allocates memory",        da != NULL);
	MU_ASSERT("create sets size to 0",          da->size == 0);
	MU_ASSERT("create sets capacity to 5",      da->capacity == 5);
	MU_ASSERT("create sets resize factor to 2", da->resize_factor == 2);
	MU_ASSERT("create allocates array memory",  da->array != NULL);

	free_dynamic_array(da);
	return 0;
}

char *
test_append_item_updates_size(void) {
	struct Dynamic_Array *da = dynamic_array_create(3, 2);

	append_item(da, 5);
	MU_ASSERT("append_item updates size to 1", da->size == 1);

	append_item(da, 15);
	MU_ASSERT("append_item updates size to 2", da->size == 2);

	append_item(da, 25);
	MU_ASSERT("append_item updates size to 3", da->size == 3);

	free_dynamic_array(da);
	return 0;
}

char *
test_append_item_adds_item(void) {
	struct Dynamic_Array *da = dynamic_array_create(3, 2);

	append_item(da, 5);
	MU_ASSERT("append_item appends 5", da->array[da->size - 1] == 5);

	append_item(da, 15);
	MU_ASSERT("append_item appends 15", da->array[da->size - 1] == 15);

	append_item(da, 25);
	MU_ASSERT("append_item appends 25", da->array[da->size - 1] == 25);

	free_dynamic_array(da);
	return 0;
}

char *
test_capacity_updates_by_resize_factor(void) {
	int in_capacity = 3;
	int in_factor   = 2;
	struct Dynamic_Array *da = dynamic_array_create(in_capacity, in_factor);

	append_item(da, 15);
	append_item(da, 25);
	append_item(da, 35);

	MU_ASSERT("array size updated to 3", da->size == 3);
	MU_ASSERT("capacity equals size",    da->capacity == da->size);
	MU_ASSERT("resize factor unaltered", da->resize_factor == in_factor);

	append_item(da, 45);
	MU_ASSERT("capacity updated by resize factor", da->capacity == in_factor * in_capacity);
	MU_ASSERT("array size updated to 4", da->size == 4);

	append_item(da, 55);
	MU_ASSERT("array size updated to 5", da->size == 5);

	append_item(da, 65);
	MU_ASSERT("array size updated to 6", da->size == 6);

	free_dynamic_array(da);
	return 0;
}

char *
test_has_item_exists(void) {
	struct Dynamic_Array *da = dynamic_array_create(2, 2);

	MU_ASSERT("item 5 does not exist", has_item(da, 5) == -1);
	append_item(da, 5);
	MU_ASSERT("item 5 exist", has_item(da, 5) == 0);

	MU_ASSERT("item 15 does not exist", has_item(da, 15) == -1);
	append_item(da, 15);
	MU_ASSERT("item 15 exists", has_item(da, 15) == 1);

	MU_ASSERT("item 25 does not exist", has_item(da, 25) == -1);
	append_item(da, 25);
	MU_ASSERT("item 25 exists", has_item(da, 25) == 2);

	free_dynamic_array(da);
	return 0;
}

char *
test_remove_item_exists(void) {
	struct Dynamic_Array *da = dynamic_array_create(2, 2);

	MU_ASSERT("item not present in the array", has_item(da, 5) == -1);
	append_item(da, 5);
	MU_ASSERT("item exists in the array", has_item(da, 5) == 0);
	remove_item(da, 5);
	MU_ASSERT("item was removed from the array", has_item(da, 5) == -1);

	free_dynamic_array(da);
	return 0;
}

char *
test_has_item_returns_index(void) {
	struct Dynamic_Array *da = dynamic_array_create(2, 2);

	MU_ASSERT("has_item does not detect item 5", has_item(da, 5) == -1);
	append_item(da, 5);
	MU_ASSERT("has_item returns index of item 5", has_item(da, 5) == 0);

	free_dynamic_array(da);
	return 0;
}

char *
test_remove_item_not_exists(void) {
	struct Dynamic_Array *da = dynamic_array_create(2, 2);

	append_item(da, 5);
	append_item(da, 15);
	append_item(da, 25);
	MU_ASSERT("array has size of 3 before remove", da->size == 3);

	MU_ASSERT("item 35 does not exist in the array", has_item(da, 35) == -1);
	MU_ASSERT("item 45 does not exist in the array", has_item(da, 45) == -1);
	MU_ASSERT("item 55 does not exist in the array", has_item(da, 55) == -1);

	remove_item(da, 35);
	remove_item(da, 45);
	remove_item(da, 55);

	MU_ASSERT("array has size of 3 after remove", da->size == 3);

	free_dynamic_array(da);
	return 0;
}

/*
 * Test Suite
 */
char *
test_suite(void) {
	MU_RUN_TEST(test_dynamic_array_create_sets_members);

	MU_RUN_TEST(test_append_item_updates_size);
	MU_RUN_TEST(test_append_item_adds_item);

	MU_RUN_TEST(test_capacity_updates_by_resize_factor);

	MU_RUN_TEST(test_has_item_exists);
	MU_RUN_TEST(test_has_item_returns_index);

	MU_RUN_TEST(test_remove_item_exists);
	MU_RUN_TEST(test_remove_item_not_exists);
	return 0;
}

/*
 * Test Runner
 */
int
main(int argc, char **argv) {
	char *result = test_suite();
	printf("number of tests run: %d\n", tests_run);
	if (result) printf("FAIL: %s\n", result);
	return 0;
}
