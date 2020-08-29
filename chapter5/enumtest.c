#include <stdio.h>

typedef enum
{
	COUNT, POUNDS, PINTS
} unit_of_measure;

typedef union
{
	short count;
	float weight;
	float volume;
} quantity;

typedef struct
{
	const char *name;
	const char *country;
	quantity amount;
	unit_of_measure units;
} fruit_order;

void display(fruit_order order)
{
	printf("Этот заказ содержит: ");
	
	if (order.units == PINTS)
	{
		printf("%2.2f пинт %s\n", order.amount.volume, order.name);
	}
	else if (order.units == POUNDS)
	{
		printf("%2.2f фунтов %s\n", order.amount.weight, order.name);
	}
	else
	{
		printf("%i %s\n", order.amount.count, order.name);
	}
}

int main()
{
	fruit_order apples = {"яблок", "Англия", .amount.count = 144, COUNT};
	fruit_order strawberries = {"клубники", "Испания", .amount.weight = 17.6, POUNDS};
	fruit_order oj = {"апельсинового сока", "США", .amount.volume = 10.5, PINTS};
	
	display(apples);
	display(strawberries);
	display(oj);
}