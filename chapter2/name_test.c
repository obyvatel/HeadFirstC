#include <stdio.h>

int main()
{
	char first_name[20];
	char last_name[20];
	int number;
	
	printf("¬ведите им€ и фамилию: ");
	scanf("%19s %19s", first_name, last_name);
	printf("»м€: %s\n‘амили€: %s\n", first_name, last_name);
	
	printf("¬ведите число: ");
	scanf("%i", &number);
	printf("¬веденное число: %i\n", number);
}