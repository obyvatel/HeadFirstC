#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[])
{
	char line[80];
	
	// проверка количества аргументов
	if (argc != 6)
	{
		fprintf(stderr, "Вы должны передать 5 аргументов!\n");
		return 1;
	}
	
	FILE *in;
	if ( !(in = fopen("spooky.csv", "r")) )
	{
		fprintf(stderr, "Не удалось открыть файл!\n");
		return 1;
	}
	FILE *file1 = fopen(argv[2], "w");
	FILE *file2 = fopen(argv[4], "w");
	FILE *file3 = fopen(argv[5], "w");
	
	while (fscanf(in, "%79[^\n]\n", line) == 1)
	{
		if (strstr(line, argv[1]))
			fprintf(file1, "%s\n", line);
		else if (strstr(line, argv[3]))
			fprintf(file2, "%s\n", line);
		else 
			fprintf(file3, "%s\n", line);
	}
	
	fclose(in);
	fclose(file1);
	fclose(file2);
	fclose(file3);
}