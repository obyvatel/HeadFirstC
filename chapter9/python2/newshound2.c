#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <sys/wait.h>

void error(char *msg)
{
    fprintf(stderr, "%s: %s\n", msg, strerror(errno));
    exit(1);
}

int main(int argc, char *argv[])
{
	char *phrase = argv[1];    // string to find
	char *var = "http://rss.cnn.com/rss/edition.rss";   // url
    FILE *f = fopen("stories.txt", "w");

    if (!f)
    {
        // if file opened f = 0
        error("Can't open stories.txt");
    }
	
	// create(clone) child process
	pid_t pid = fork();
	if (pid == -1)
	{
		error("Can't clone process");
	}
		
	if(!pid)
	{
	    // remap standart output to file "stories.txt"
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
	
	// waiting child process ending
	int pid_status;
	if (waitpid(pid, &pid_status, 0) == -1)
	{
	    error("Error during waiting child process");
	}

	return 0;
}
