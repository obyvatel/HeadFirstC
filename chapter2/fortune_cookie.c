#include <stdio.h>

void fortune_cookie(char msg[])
{
	printf("Сообщение гласит: %s\n", msg);
	printf("msg занимает %i байтов\n", sizeof(msg));		// 4 байт
	printf("Строка msg находится по адресу %p\n", msg);
}

int main()
{
	char quote[] = "Печенье вас полнит";
	
	fortune_cookie(quote);
	
	char message[] = "Привет";
	printf("message занимает %i байт\n", sizeof(message)); 	// 7 байт
	
	return 0;
}
