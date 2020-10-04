#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <pthread.h>

// handle errors
void error(char *msg)
{
    fprintf(stderr, "%s: %s\n", msg, strerror(errno));
    exit(1);
}

// function on thread
void* does_not(void *a)
{
    int i = 0;

    for (i=0; i<5; i++)
    {
        sleep(1);
        puts("Nooot!");
    }
    
    return NULL;
}

// function on thread
void* does_too(void *a)
{
    int i = 0;

    for (i=0; i<5; i++)
    {
        sleep(1);
        puts("Yesssss!");
    }
    
    return NULL;
}

int main()
{
    pthread_t t0;   // structure for thread
    pthread_t t1;   // structure for thread
    
    // create thread t0
    if (pthread_create(&t0, NULL, does_not, NULL) == -1)
    {
        error("Can't create thread t0");
    }
    
    // create thread t1
    if (pthread_create(&t1, NULL, does_too, NULL) == -1)
    {
        error("Can't create thread t1");
    }

    void* result;
    
    // wait for a thread t0 finish
    if (pthread_join(t0, &result) == -1)
    {
        error("Can't join thread t0");
    }
    
    // wait for a thread t1 finish
    if (pthread_join(t1, &result) == -1)
    {
        error("Can't join thread t1");
    }

    return 0;
}







