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

void open_url(char *url)
{
    char launch[255];
    // for Windows
    //sprintf(launch, "cmd /c start %s", url);
    //system(launch);
    // for Linux
    sprintf(launch, "x-www-browser '%s' &", url);
    system(launch);
    // for Mac
    //sprintf(launch, "open '%s'", url);
    //system(launch);
}

int main(int argc, char *argv[])
{
	char *phrase = argv[1];    // string to find
	char *var = "http://rss.cnn.com/rss/edition.rss";   // url
    int fd[2];
    
	if (pipe(fd) == -1)
	{
	    error("Can't create channel");
	}
	
	// create(clone) child process
	pid_t pid = fork();
	if (pid == -1)
	{
		error("Can't clone process");
	}
		
	if(!pid)
	{// child process
	    dup2(fd[1], 1); // link stdout with write end of channel
	    close(fd[0]);   // close read end of channel
	    
		if ( execl(
					"/usr/bin/python3",
					"/usr/bin/python3",
					"./rssgossip_my.py", "-u", phrase, "RSS_FEED", var, NULL
					) == -1	)
		{
			error("Can't execute script");
		}

	}
	
	// parent process
	dup2(fd[0], 0); // link stdin with read channel
	close(fd[1]);   // close write end of channel
	char line[255];
	while(fgets(line, 255, stdin))
	{
	    if (line[0] == '\t')
	    {
	        open_url(line+1);
	    }
	}

	return 0;
}
