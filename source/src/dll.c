#include <glib.h>
#include <dll.h>

struct dll_entry {
	struct dll_entry *prev;
	struct dll_entry *next;
	void *data;
};

struct dll {
	struct dll_entry *first;
	struct dll_entry *last;
	int size;
};

struct dll *dll_new(void)
{
	struct dll *list;

	list = g_new0(struct dll, 1);
	list->size = 0;
	list->first = NULL;
	list->last = NULL;

	return list;
}

void dll_destroy(struct dll *list)
{
	g_free(list);
}

struct dll_entry *dll_new_entry(void)
{
	struct dll_entry* entry;

	entry = g_new0(struct dll_entry, 1);

	return entry;
}

void dll_destroy_entry(struct dll_entry *entry)
{
	g_free(entry);
}

struct dll_entry *dll_append(struct dll *list, void *data)
{
	struct dll_entry *new_entry;

	/* create new entry */
	new_entry = dll_new_entry();
	new_entry->data = data;

	if (list->first == NULL) {
		list->first = new_entry;
	}

	if (list->last != NULL) {
		list->last->next = new_entry;
		new_entry->prev = list->last;
	}


	list->last = new_entry;


	list->size++;

	return new_entry;
}
