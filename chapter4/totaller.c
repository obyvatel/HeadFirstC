#include <stdio.h>
#include "totaller.h"

float total = 0.0;
short count = 0;
short tax_percent = 6;

int main()
{
	float val;
	
	printf("Цена блюда: ");
	while (scanf("%f", &val) == 1)
	{
		printf("Итого на текущий момент: %.2f\n", add_with_tax(val));
		printf("Цена блюда: ");
	}
	printf("\nИтоговый счет: %.2f\n", total);
	printf("Количество блюд: %hi\n", count);
	return 0;
}

float add_with_tax(float f)
{
	float tax_rate = 1 + tax_percent/100.0;
	total += f * tax_rate;
	count ++;
	return total;
}