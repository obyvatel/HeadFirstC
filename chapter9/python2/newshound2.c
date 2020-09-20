#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

void error(char *msg)
{
    fprintf(stderr, "%s: %s\n", msg, strerror(errno));
    exit(1);
}

int main(int argc, char *argv[])
{
	char *phrase = argv[1];
	char *var = "http://rss.cnn.com/rss/edition.rss";
    FILE *f = fopen("stories.txt", "w");

    if (!f)
    {
        error("Can't open stories.txt");
    }
	
	pid_t pid = fork();
	if (pid == -1)
	{
		error("Can't clone process");
	}
		
	if(!pid)
	{
	    if (dup2(fileno(f), 1) == -1)
	    {
	        error("Can't remap standart output");
	    }
	    
		if ( execl(
					"/usr/bin/python3",
					"/usr/bin/python3",
					"./rssgossip_my.py", phrase, "RSS_FEED", var, NULL
					) == -1	)
		{
			error("Can't execute script");
		}
	}

	return 0;
}
