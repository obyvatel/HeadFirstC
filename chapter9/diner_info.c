#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
	printf("Обедов: %s\n", argv[1]);
	printf("Сок: %s\n", getenv("JUICE"));
	
	return 0;
}