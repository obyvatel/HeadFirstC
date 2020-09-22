#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>

void error(char *msg)
{
    fprintf(stderr, "%s: %s", msg, strerror(errno));
    exit(1);
}

int main(int argc, char *argv[])
{
	char *advice[] = {
		"Eat in small portions. \r\n",
		"Buy tight jeans. No, they DO NOT make you fat. \r\n",
		"Two words: not good. \r\n",
		"Be honest today. Tell your boss what you *really* think about him. \r\n",
		"Maybe you should choose a different hairstyle. \r\n"
	};
	
	// create socket
	int listener_d = socket(PF_INET, SOCK_STREAM, 0);
	if (listener_d == -1)
	{
	    error("Can't open socket");
	}
	
	// set socket params
	struct sockaddr_in name;
	name.sin_family = PF_INET;
	name.sin_port = (in_port_t)htons(30000);
	name.sin_addr.s_addr = htonl(INADDR_ANY);
	
	// set reuse option for socket (don't wait 30 seconds after restart server)
	int reuse = 1;
	if (setsockopt(listener_d, SOL_SOCKET, SO_REUSEADDR, (char *)&reuse, sizeof(int)) == -1)
	{
	    error("Can't set reuse option for socket");
	}
	
	// binding socket
	int c = bind(listener_d, (struct sockaddr *) &name, sizeof(name));	// bind socket to port
	if (c == -1)
	{
	    error("Can't bind socket");
	}
	
	// define queue length
	if (listen(listener_d, 10) == -1)	// 10 waiters
	{
	    error("Can't listen port");
	}
	puts("Waiting connection");
	
	// handle connections
	while(1)
	{
		struct sockaddr_storage client_addr;
		unsigned int address_size = sizeof(client_addr);
		int connect_d = accept(listener_d, (struct sockaddr *) &client_addr, &address_size);	// receive connection
		if (connect_d == -1)
		{
		    error("Can't open second socket");
		}
		
		char *msg = advice[rand() % 5];			// choose advice from array
		if (send(connect_d, msg, strlen(msg), 0) == -1)	// begin dialog with client
		{
		    error("sending error");
		}
		close(connect_d);
	}
	
	return 0;
	
}
