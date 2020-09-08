#include <stdio.h>
#include <stdarg.h>

enum drink {MUDSLIDE, FUZZY_NAVEL, MONKEY_GLAND, ZOMBIE};

double price(enum drink d)
{
	switch(d)
	{
		case MUDSLIDE: return 6.79; //break;
		case FUZZY_NAVEL: return 5.31; //break;
		case MONKEY_GLAND: return 4.82; //break;
		case ZOMBIE: return 5.89; //break;
	}
	
	return 0;
}

double total(int args, ...)
{
	double total = 0;
	
	va_list ap;
	va_start(ap, args);
	int i;
	for (i=0; i<args; i++)
	{
		enum drink d = va_arg(ap, enum drink);
		total += price(d);
	}
	va_end(ap);
	
	return total;
}

int main()
{
	// первая функция использует два первых аргумента
	printf("Цена равняется %.2f\n", total(2, MONKEY_GLAND, MUDSLIDE, FUZZY_NAVEL));
	printf("Цена равняется %.2f\n", total(3, MONKEY_GLAND, MUDSLIDE, FUZZY_NAVEL));
	printf("Цена равняется %.2f\n", total(1, ZOMBIE));
	
	return 0;
}