#include <stdio.h>

int main()
{
	char first_name[20];
	char last_name[20];
	int number;
	
	printf("������� ��� � �������: ");
	scanf("%19s %19s", first_name, last_name);
	printf("���: %s\n�������: %s\n", first_name, last_name);
	
	printf("������� �����: ");
	scanf("%i", &number);
	printf("��������� �����: %i\n", number);
}