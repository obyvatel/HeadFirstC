#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <string.h>
#include <errno.h>
#include <signal.h>

int score = 0;

void end_game(int_sig)
{	// Output score
	printf("\nFinal score: %i\n", score);
	exit(0);
}

int catch_signal(int sig, void (*handler)(int))
{	// Link handler for signal
	struct sigaction action;
	action.sa_handler = handler;
	sigemptyset(&action.sa_mask);
	action.sa_flags = 0;
	return sigaction(sig, &action, NULL);
}

void times_up(int sig)
{	// handler for timeout
	puts("\nTIMEOUT!");
	raise(SIGINT);
}

void error(char *msg)
{	// error messages
	fprintf(stderr, "%s: %s", msg, strerror(errno));
	exit(2);
}

int main()
{
	// link timer
	if (catch_signal(SIGALRM, times_up) == -1)
	{
		error("Can't choose handler for SIGALARM");
	}
	
	// link terminator
	if(catch_signal(SIGINT, end_game) == -1)
	{
		error("Can't choose handler for SIGINT");
	}
	
	srandom(time(0));	// reset randomizer
	while(1)
	{
		int a = random() % 11; // random in 0..10
		int b = random() % 11; // random in 0..10
		char txt[4];
		alarm(5);	// timer on 5 second
		printf("\nWhat is %i times %i ? ", a, b);
		fgets(txt, 4, stdin);
		int answer = atoi(txt);
		if (answer == a*b)
		{
			score++;
		}
		else
		{
			printf("\nWrong! Score: %i\n", score);
		}
	}

	return 0;
}
