#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int compare_scores_desc(const void *score_a, const void *score_b)
{
	int a = *(int*)score_a;
	int b = *(int*)score_b;
	
	return a - b;
}

int compare_names(const void* a, const void* b)
{
	char** sa = (char**)a;
	char** sb = (char**)b;
	
	return strcmp(*sa, *sb);
}

int main()
{
	int scores[] = {543, 323, 32, 554, 11, 3, 112};
	int i;
	
	qsort(scores, 7, sizeof(int), compare_scores_desc);
	puts("Это упорядоченные оценки:");
	for (i=0; i<7; i++)
	{
		printf("Оценка = %i\n", scores[i]);
	}
	
	char *names[] = {"Карен", "Марк", "Бретт", "Молли"};
	qsort(names, 4, sizeof(char*), compare_names);
	puts("Это упорядоченные имена:");
	for (i=0; i<4; i++)
	{
		printf("%s\n", names[i]);
	}
	
	return 0;
}