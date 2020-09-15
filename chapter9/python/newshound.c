#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

int main(int argc, char *argv[])
{
	char *feeds[] = 
	{
		"http://rss.cnn.com/rss/edition.rss",
		"http://feeds.bbci.co.uk/news/business/rss.xml#",
		"http://feeds.skynews.com/feeds/rss/world.xml"
	};
	
	int times = 3;
	char *phrase = argv[1];
	int i;
	
	for (i=0; i<times; i++)
	{
		char var[255];
		sprintf(var, "RSS_FEED=%s", feeds[i]);
		char *vars[] = {var, NULL};
		
		pid_t pid = fork();
		if (pid == -1)
		{
			fprintf(stderr, "Не могу клонировать процесс: %s\n", strerror(errno));
			return 1;
		}
		
		if(!pid)
		{
			if ( execle(
						"C:\\Users\\GalievBYa\\AppData\\Local\\Programs\\Python\\Python38-32\\python.exe",
						"C:\\Users\\GalievBYa\\AppData\\Local\\Programs\\Python\\Python38-32\\python.exe",
						"rssgossip.py", phrase, NULL, vars
						) == -1	)
			{
				fprintf(stderr, "Не могу запустить скрипт: %s\n", strerror(errno));
				return 1;
			}
		}
	}
	
	return 0;
}