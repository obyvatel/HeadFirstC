#include <stdio.h>
#include "encrypt.h"

int main()
{
	char msg[80];
	
	puts("Введите строку:");
	while (fgets(msg, 80, stdin))
	{
		encrypt(msg);
		printf("%s", msg);
	}
	
	return 0;
}