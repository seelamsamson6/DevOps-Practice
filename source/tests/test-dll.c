#include "../src/dll.c"

static void test_dll_new(void)
{
	struct dll *list;

	list = dll_new();
	g_assert(list != NULL);

	g_free(list);
}

static void test_dll_destroy_null(void)
{
	dll_destroy(NULL);
}

static void test_dll_destroy_valid(void)
{
	struct dll *list = dll_new();

	dll_destroy(list);
}

static void test_dll_new_entry(void)
{
	struct dll_entry *entry;

	entry = dll_new_entry();
	g_assert(entry != NULL);
	entry->prev = NULL;
	entry->next = NULL;

	g_free(entry);
}

static void test_dll_destroy_entry_null(void)
{
	dll_destroy_entry(NULL);
}

static void test_dll_destroy_entry_valid(void)
{
	struct dll_entry *entry;

	entry = dll_new_entry();

	dll_destroy_entry(entry);
}

static void test_dll_append(void)
{
	struct dll *list = dll_new();
	struct dll_entry *first;
	struct dll_entry *second;
	struct dll_entry *third;

	first = dll_append(list, "hello");
	g_assert(list->size == 1);
	g_assert(list->first == first);
	g_assert(list->last == first);

	second = dll_append(list, "world");
	g_assert(list->size == 2);
	g_assert(list->first == first);
	g_assert(list->last == second);

	g_assert(first->prev == NULL);
	g_assert(first->next == second);

	g_assert(second->prev == first);
	g_assert(second->next == NULL);

	third = dll_append(list, "world");
	g_assert(list->size == 3);
	g_assert(list->first == first);
	g_assert(list->last == third);

	g_assert(second->prev == first);
	g_assert(second->next == third);

	g_assert(third->prev == second);
	g_assert(third->next == NULL);
}

int main(int argc, char** argv)
{
	(void)argc;
	(void)argv;

	g_test_init(&argc, &argv, NULL);

	g_test_add_func("/dll/new",
		test_dll_new);

	g_test_add_func("/dll/destroy/null",
		test_dll_destroy_null);
	g_test_add_func("/dll/destroy/valid",
		test_dll_destroy_valid);

	g_test_add_func("/dll/new_entry",
		test_dll_new_entry);

	g_test_add_func("/dll/destroy_entry/null",
		test_dll_destroy_entry_null);
	g_test_add_func("/dll/destroy_entry/valid",
		test_dll_destroy_entry_valid);

	g_test_add_func("/dll/append/valid",
		test_dll_append);

	return g_test_run();
}
