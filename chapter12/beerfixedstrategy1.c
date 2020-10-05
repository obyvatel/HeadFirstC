#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <pthread.h>

int beers = 2000000;
// mutex for lock/unlock common variables for one thread
pthread_mutex_t beers_lock = PTHREAD_MUTEX_INITIALIZER;

void error(char *msg)
{
    fprintf(stderr, "%s: %s\n", msg, strerror(errno));
    exit(1);
}

void* drink_lots(void *a)
{
    int i;

    // lock variables fo one thread
    pthread_mutex_lock(&beers_lock);
    for (i=0; i<100000; i++)
    {
        beers--;
    }

    // unlock variables fo one thread    
    pthread_mutex_unlock(&beers_lock);
    printf("beers = %i\n", beers);
    
    return NULL;
}

int main()
{
    pthread_t threads[20];
    int t;
    
    printf("%i bottles of beer on wall, %i bottles of beer\n", beers, beers);
    for (t=0; t<20; t++)
    {   // create threads
        pthread_create(&threads[t], NULL, drink_lots, NULL);
    }
    
    void* result;
    for(t=0; t<20; t++)
    {   // wait finishing threads
        pthread_join(threads[t], &result);
    }
    
    printf("Now leave %i bottles of beer on wall\n", beers);

    return 0;
}







