#include <stdio.h>

int main()
{
	char food[5];
	
	printf("������� ������� ���: ");
	scanf("%s", food);
	printf("������� ���: %s\n", food);	// ��� ��� ���������� ����� ������ ������, ���� ����� ����� 5 ��������
	
	printf("������� ������� ���: ");
	scanf("%4s", food);
	printf("������� ���: %s\n", food);
	
}