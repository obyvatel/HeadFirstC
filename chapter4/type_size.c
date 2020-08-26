#include <stdio.h>
#include <limits.h>
#include <float.h>

int main()
{
	printf("Значение CHAR_MAX равно %i\n", CHAR_MAX);
	printf("Значение CHAR_MIN равно %i\n", CHAR_MIN);
	printf("char занимает %li байт\n\n", sizeof(char)); 
	
	printf("Значение SHRT_MAX равно %i\n", SHRT_MAX);
	printf("Значение SHRT_MIN равно %i\n", SHRT_MIN);
	printf("short занимает %li байт\n\n", sizeof(short));
	
	printf("Значение INT_MAX равно %i\n", INT_MAX);
	printf("Значение INT_MIN равно %i\n", INT_MIN);
	printf("int занимает %li байт\n\n", sizeof(int));
	
	printf("Значение LONG_MAX равно %i\n", LONG_MAX);
	printf("Значение LONG_MIN равно %i\n", LONG_MIN);
	printf("long занимает %li байт\n\n", sizeof(long));
	
	printf("Значение FLT_MAX равно %f\n", FLT_MAX);
	printf("Значение FLT_MIN равно %.50f\n", FLT_MIN);
	printf("float занимает %li байт\n\n", sizeof(float));
	
	printf("Значение DBL_MAX равно %f\n", DBL_MAX);
	printf("Значение DBL_MIN равно %.50f\n", DBL_MIN);
	printf("double занимает %li байт\n\n", sizeof(double));
	
	return 0;
}