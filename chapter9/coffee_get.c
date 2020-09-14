#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

int main(int argc, char *argv[])
{
	char *my_env[] = {"FOOD=кофе", NULL};
	if (execle("coffee", "coffee", "пончики", NULL, my_env) == -1)
	{
		fprintf(stderr, "Не могу запустить процесс 0: %s/n", strerror(errno));
		return 1;
	}
	
	return 0;
}