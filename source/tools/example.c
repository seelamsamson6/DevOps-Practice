#include <stdio.h>
#include <dll.h>


int main(int argc, char** argv)
{
	(void) argc;
	(void) argv;

	printf("%s version %s\n", argv[0], VERSION);

	return 0;
}
