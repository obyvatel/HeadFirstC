#include <stdio.h>

struct fish
{
	const char *name;
	const char *species;
	int teeth;
	int age;
};

void catalog(struct fish f)
{
	printf("%s - это %s с %i зубами. Ему %i года.\n", f.name, f.species, f.teeth, f.age);
}

void label(struct fish f)
{
	printf("Кличка: %s\n", f.name);
	printf("Разновидность: %s\n", f.species);
	printf("%i года, %i зубов\n", f.age, f.teeth);
}

int main()
{
	struct fish snappy = {"Зубастик", "пиранья", 69, 4};
	
	catalog(snappy);
	label(snappy);
	
	return 0;
}