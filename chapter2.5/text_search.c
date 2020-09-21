#include <stdio.h>
#include <string.h>

char tracks[][80] = 
	{
		"я оставил свое сердце в √арвардской медицинской школе",
		"Ќьюарк, Ќьюарк - город, полный чудес",
		"“анец с мужланом",
		"ќтсюда и до роодома",
		"ƒевчонка с острова »водзима"
	};
	
void find_track(char search_for[])
{
	int i;
	
	for (i=0; i<5; i++)
		if (strstr(tracks[i], search_for))
			printf("ѕесн¤ номер %i: '%s'\n", i, tracks[i]);
}

int main()
{
	char search_for[80];
	
	printf("»скать: ");
	fgets(search_for, 80, stdin);
	search_for[strlen(search_for)-1] = '\0';
	find_track(search_for);
}
