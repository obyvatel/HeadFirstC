#include <stdio.h>

int main()
{
	char food[5];
	
	printf("Введите любимую еду: ");
	scanf("%s", food);
	printf("Любимая еда: %s\n", food);	// вот эта инструкция может выдать ошибку, если ввели более 5 символов
	
	printf("Введите любимую еду: ");
	scanf("%4s", food);
	printf("Любимая еда: %s\n", food);
	
}