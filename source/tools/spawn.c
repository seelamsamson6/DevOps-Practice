#include <stdio.h>
#include <glib.h>

int main(int argc, char** argv)
{
	(void) argc;
	(void) argv;

	gboolean ok;
	gchar *arguments[10];
	gchar *output;
	gchar *error;
	gint rc;
	arguments[0] = "ls";
	//arguments[0] = "/bin/ls";
	arguments[1]= NULL;

	ok = g_spawn_sync(NULL, arguments, NULL, G_SPAWN_SEARCH_PATH, 0, 0, &output, &error, &rc, NULL);

	printf("%s\n", ok ? "ok" : "notok");

	printf("out: %s\n", output);
	printf("err: %s\n", error);
	printf("rc %d\n", rc);
	return 0;
}
