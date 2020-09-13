#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

//char* now()
char* now(char* timestr)
{
	time_t t;
	time (&t);
	
	//return asctime(localtime (&t));
	strftime (timestr, 100, "%a %d.%m.%Y %X", localtime (&t));
	
	return timestr;
}

/*	Главная управляющая программа
	Записывает отчеты о работе охранного патруля. */
int main()
{
	char str[50];
	char comment[80];
	char cmd[120];
	
	fgets(comment, 80, stdin);
	comment[strlen(comment)-1] = '\0';

	sprintf(cmd, "echo %s %s >> reports.log", comment, now(str));
	system(cmd);
	
	return 0;
}