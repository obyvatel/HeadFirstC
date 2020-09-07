#include <stdio.h>

enum response_type {DUMP, SECOND_CHANCE, MARRIAGE};
typedef struct
{
	char *name;
	enum response_type type;
} response;

void dump(response r)
{
	printf("Дорогой %s,\n", r.name);
	puts("К сожалению, Ваш недавний партнер по свиданию связался с нами,");
	puts("чтобы сообщить, что Вы с ним больше не увидетесь.");
}

void second_chance(response r)
{
	printf("Дорогой %s,\n", r.name);
	puts("Хорошие новости: Ваш недавний партнер по свиданию попросил нас");
	puts("организовать еще одну встречу. Пожалуйста, перезвоните как можно скорее.");
}

void marriage(response r)
{
	printf("Дорогой %s,\n", r.name);
	puts("Поздравляем! Ваш недавний партнер по свиданию");
	puts("связался с нами с предложением о браке.");
}

int main()
{
	response r[] = { 
		{"Майк", DUMP}, {"Луис", SECOND_CHANCE}, {"Мэттью", SECOND_CHANCE}, {"Уильям", MARRIAGE} 
	};
	int i;
	
	for (i=0; i<4; i++)
	{
		switch (r[i].type)
		{
			case DUMP: dump(r[i]); break;
			case SECOND_CHANCE: second_chance(r[i]); break;
			default: marriage(r[i]); break;
		}
	}
	
	return 0;
}