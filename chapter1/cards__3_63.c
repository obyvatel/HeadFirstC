/*
* ��������� ��� ���������� �������� ����
* �������� ��� ��������� ���-��������� ���������.
* (�) 2014 ������� �������� �� ����-�����
*/

#include <stdio.h>
#include <stdlib.h>

int main()
{
	char card_name[3];
	
	puts("������� �������� �����: ");
	scanf("%2s", card_name);
	int val = 0;
	
	switch (card_name[0])
	{
		case 'K':
		case 'Q':
		case 'J':
			val = 10;
			break;
		case 'A' : val = 11; break;
		default : val = atoi(card_name);
	}
	
	/* ���������, ��������� �� �������� ����� 3 � 7 */
	if ((val > 2) && (val < 7))
		puts("������� ����������");
	/* � ��������� ������ ���������, ���� �� ��� ����� 10,
		J(�������), Q(������), K(�������) */
	else if (val==10)
		puts("������� ����������");
	
	return 0;
	
}