#include <stdio.h>

int main()
{
	printf("char : %i байт\n", sizeof(char));
	printf("int : %i байт\n", sizeof(int));
	printf("short : %i байт\n", sizeof(short));
	printf("long : %i байт\n", sizeof(long));
	printf("float : %i байт\n", sizeof(float));
	printf("double : %i байт\n", sizeof(double));
	printf("long int : %i байт\n", sizeof(long int));
	printf("long long : %i байт\n", sizeof(long long));
	printf("long double : %i байт\n", sizeof(long double));
	
	// 4-х байтовую переменную записать в 2-х байтовую
	int x = 100000;
	short y = x;
	printf("y = %i\n", y);
	
	puts("деление без приведения делимого и делителя к float");
	x = 7;
	y = 2;
	float z = x/y;
	printf("z = %f\n", z);
	
	puts("деление c приведением делимого и делителя к float");
	z = (float)x / (float)y;
	printf("z = %f\n", z);
	
	puts("деление c приведением только делимого к float");
	z = (float)x / y;
	printf("z = %f\n", z);
	
	
	
	return 0;
}