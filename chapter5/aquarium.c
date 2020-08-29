#include <stdio.h>

typedef struct
{
	const char *name;
	unsigned int first_visit : 1;
	unsigned int come_again : 1;
	unsigned int fingers_lost : 4;
	unsigned int shark_attack : 1;
	unsigned int days_a_week : 3;
} survey;

int main()
{
	survey Randy = {"Рэнди", 1, 0, 5, 1, 0};
	printf("Анекта посетителя %s:\n", Randy.name);
	printf("Это Ваш первый визит: %i\n", Randy.first_visit);
	printf("Придете ли Вы снова: %i\n", Randy.come_again);
	printf("Количество пальцев, потерянных в резервуаре с пираньями: %i\n", Randy.fingers_lost);
	printf("Потеряли ли вы ребенка в секции с акулами: %i\n", Randy.shark_attack);
	printf("Сколько дней в неделю Вы бы нас посещали: %i\n", Randy.days_a_week);
	
	return 0;
}