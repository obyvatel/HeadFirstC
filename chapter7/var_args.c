#include <stdio.h>
#include <stdarg.h>	// обработка функций с переменным число аргументов

void print_ints(int args, ...)
{
	va_list ap;				// хранит аргументы
	va_start(ap, args);		// начало переменных аргументов
	
	for (int i=0; i<args; i++)
	{
		printf("аргумент %i = %i\n", i+1, va_arg(ap, int));	// аргументы
	}
	
	va_end(ap);				// закончить работу со списком
}

int main()
{
	puts("Первая последовательность:");
	print_ints(3, 45, 47, 67);
	
	puts("Вторая последовательность");
	print_ints(5, 46, 89, 23, 2, 8);
}