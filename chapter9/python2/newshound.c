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
		pid_t pid = fork();
		if (pid == -1)
		{
			fprintf(stderr, "Can't clone process %s\n", strerror(errno));
			return 1;
		}
		
		if(!pid)
		{
			if ( execl(
						"/usr/bin/python3",
						"/usr/bin/python3",
						"./rssgossip_my.py", phrase, "RSS_FEED", feeds[i], NULL
						) == -1	)
			{
				fprintf(stderr, "Can't execute script %s\n", strerror(errno));
				return 1;
			}
		}
	}
	
	return 0;
}
