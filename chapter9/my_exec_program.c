#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>


int main()
{
	char *my_env[] = {"JUICE=персик и яблоко", NULL};
	
	//execle("diner_info", "diner_info", "4", NULL, my_env);
	execle("diner_info1", "diner_info1", "4", NULL, my_env);
	
	puts("Старик, код из diner_info должно быть сломался");
	puts(strerror(errno));
	
	return 0;
}