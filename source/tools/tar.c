#include <stdio.h>
#include <stdlib.h>
#include <archive.h>
#include <archive_entry.h>

struct my_data {
	struct archive *source;
};

static ssize_t inner_read(struct archive *a, void *client_data, const void **buff)
{
	struct my_data *mine = client_data;
	ssize_t size;
	static uint8_t buffer[1024];
	(void)a;

	/*
	* use archive_read_data(mine->source),
	* set pointer to data in buff,
	* return size read or error …
	*/
	size = archive_read_data(mine->source, buffer, sizeof(buffer));
	*buff = buffer;
	return size;
}


int
archive_read_open_archive_entry(struct archive *a, struct archive *source)
{
	struct my_data *mine;

	archive_clear_error(a);
	mine = (struct my_data *)calloc(1, sizeof(*mine));
	mine->source = source;
	archive_read_set_read_callback(a, inner_read);
	archive_read_set_callback_data(a, mine);

	int r;
	r = archive_read_open1(a);
	return r;
}

int main(int argc, char** argv)
{
	struct archive *a;
	struct archive_entry *entry;
	int r;

	(void)argc;
	(void)argv;

	a = archive_read_new();
	archive_read_support_filter_all(a);
	archive_read_support_format_all(a);
	r = archive_read_open_filename(a, argv[1], 10240); // Note 1
	if (r != ARCHIVE_OK) {
		return -1;
	}

	while (archive_read_next_header(a, &entry) == ARCHIVE_OK) {
		printf("%s\n", archive_entry_pathname(entry));
		struct archive *inner;
		struct archive_entry *entry_inner;

		inner = archive_read_new();
		archive_read_support_filter_all(inner);
		archive_read_support_format_all(inner);
		archive_read_open_archive_entry(inner, a);

		while (archive_read_next_header(inner, &entry_inner) == ARCHIVE_OK) {
			printf("inner: %s\n", archive_entry_pathname(entry_inner));
			archive_read_data_skip(inner);  // Note 2
		}
		r = archive_read_free(inner);


		archive_read_data_skip(a);  // Note 2
	}

	r = archive_read_free(a);  // Note 3
	if (r != ARCHIVE_OK)
		return -1;

	return 0;
}
