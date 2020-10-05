#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <pthread.h>

void error(char *msg)
{
    fprintf(stderr, "%s: %s\n", msg, strerror(errno));
    exit(1);
}

void* do_stuff(void *param)
{
    // convert to long type
    long thread_no = (long)param;

    printf("Thread number %ld\n", thread_no);
    
    return (void*)(thread_no + 1);
}

int main()
{
    pthread_t threads[20];
    long t;
    
    for (t=0; t<3; t++)
    {   // sending param in thread function
        pthread_create(&threads[t], NULL, do_stuff, (void*)t);
    }
    
    void* result;
    for(t=0; t<3; t++)
    {   // receive thread function result
        pthread_join(threads[t], &result);
        printf("Thread number %ld return %ld\n", t, (long)result);
    }

    return 0;
}

