#include <stdio.h>
#include <unistd.h>

/*
	int execv(const char *pathname, char *const argv[]);
	v - execv(), execvp(), execvpe()
       The char *const argv[] argument is an array of pointers to null-
       terminated strings that represent the argument list available to the
       new program.  The first argument, by convention, should point to the
       filename associated with the file being executed.  The array of
       pointers must be terminated by a null pointer.
*/

int main()
{
	const char *my_args[3] = {"c:\\Windows\\notepad.exe", "readme1.txt", NULL};
	execv("c:\\Windows\\notepad.exe", my_args);

	return 0;
}