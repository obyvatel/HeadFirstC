#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// для связного списка необходимо имя 
// (не только псевдоним) струткуры
typedef struct island
{
	char *name;
	char *opens;
	char *closes;
	struct island *next;
} island;

// функция для создания экземпляра структуры
// возвращает адрес нового острова в куче
island* create(char *name)
{
	island *i = malloc(sizeof(island));
	//i->name = name;		// эта строка ссылается на один и тот же адрес для всех 
							// 		экземпляров структуры,
	i->name = strdup(name);	// strdup создает копию name в куче
	// поля opens и closes не меняются, поэтому им присваиваем строку из области констант
	// все экземпляры структуры будут сслыаться на один и тот 
	//		же адрес в области констант для "09:00" и для "17:00"
	i->opens = "09:00";		
	i->closes = "17:00";
	i->next = NULL;
	
	return i;
}

// вывод на экран полей структур
void display(island *start)
{
	island *i = start;
	for(; i != NULL; i = i-> next)
	{
		printf("Название: %s открыт: %s-%s\n", i->name, i->opens, i->closes);
	}
}

int main()
{
	char name[80];
	
	fgets(name, 80, stdin);
	island *p_island0 = create(name);
	
	fgets(name, 80, stdin);
	island *p_island1 = create(name);
	p_island0->next = p_island1;
	
	display(p_island0);
	
	return 0;
}