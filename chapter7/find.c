#include <stdio.h>
#include <string.h>

int NUM_ADS = 7;
char *ADS[] = 
	{
		"Уильям: одинокий мужчина, афроамериканец, с хорошим чувством юмора, любит спорт, телевизор, перекусить",
		"Мэттью: одинокий мужчина,Ю европеец, некурящий, любит живопись, кино, театр",
		"Луис: одинокий мужчина, латиноамериканец, непьющий, любит книги, театр, живопись",
		"Майк: разведенный мужчина, европеец, любит грузовики, спорт и Джастина Бибера",
		"Питер: одинокий мужчина, азиат, любит шахматыЮ, тренироваться в зале и живопись",
		"Джош: одинокий мужчина, еврей, любит спорт, кино и театр",
		"Джед: разведенный мужчина, афроамериканец, любит театр, книги, перекусить"
	};
	
void find()
{
	int i;
	
	puts("Search results:");
	puts("----------------------------------------");
	for (i=0; i<NUM_ADS; i++)
	{
		if (strstr(ADS[i], "спорт") && (!strstr(ADS[i], "Бибер")))
		{
			printf("%s\n", ADS[i]);
		}
	}
	puts("----------------------------------------");
}

int sports_no_bieber(char *s)
{
	return strstr(s, "спорт") && (!strstr(s, "Бибер"));
}

int sports_or_workout(char *s)
{
	
}

int main()
{	
	find();
	
	return 0;
}
