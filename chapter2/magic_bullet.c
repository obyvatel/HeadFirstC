#include <stdio.h>

int main()
{
	char masked_raider[] = "живой!";
	char *jimmy = masked_raider;
	
	printf("Грабитель в маске сейчас %s Джимми сейчас %s\n", masked_raider, jimmy);
	
	masked_raider[0] = 'М';
	masked_raider[1] = 'Е';
	masked_raider[2] = 'Р';
	masked_raider[3] = 'Т';
	masked_raider[4] = 'В';
	masked_raider[5] = '!';
	
	printf("Грабитель в маске сейчас %s Джимми сейчас %s\n", masked_raider, jimmy);
	
	return 0 ;
}