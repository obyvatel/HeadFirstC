#include <stdio.h>

int main()
{
	char *cards = "JQK";	
	char a_card = cards[2];
	
	cards[2] = cards[1]; 	// эта строка и последующие приводит к ошибке
							// причина: "JQK" находится в участке памяти констант.
							// данной командой пытаемся записать в константу
							// карта памяти: стек, куча, глобальный переменные, константы, код
	cards[1] = cards[0];
	cards[0] = cards[2];
	cards[2] = cards[1];
	cards[1] = a_card;
	
	
	puts(cards);
	
	return 0 ;
}