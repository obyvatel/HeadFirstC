#include <stdio.h>

typedef struct
{
	const char *name;
	int age;
} turtle;

void info(turtle *t)
{
	printf("%s завтра будет отмечать день рождения. Ей %i лет.\n", (*t).name, (*t).age );
}

void happy_birthday(turtle *t)
{
	t->age = t->age + 1;
	printf("С днем рождения, %s! Теперь тебе %i лет!\n", t->name, t->age);
}

int main()
{
	turtle myrtle = {"Тортилла", 99};
	
	info(&myrtle);
	printf("На следующий день:\n");
	happy_birthday(&myrtle);
	
	return 0;
}