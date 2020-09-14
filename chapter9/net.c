#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

int main()
{
	if (execl("/sbin/ifconfig", "/sbin/ifconfig", NULL) == -1)
	{
		if (execlp("ipconfig", "ipconfig") == -1)
		{
			fprintf(stderr, "Не удалось запустить ipconfig: %s", strerror(errno));
			return 1;
		}
	}
	return 0;
}