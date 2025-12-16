//Name: Divya Bengali
//Date: Oct 22nd, 2025
//Title: Lab5 – Step 2 - modified "threadSync.c in Step 1 using mutex locks"
//Description: This program creates pthreads and outputs their "status" (idk what other words to use to describe it).


#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <signal.h>

#define NTHREADS 10

void *go(void *arg);
void cleanup(int sigtype);

pthread_t threads[NTHREADS];
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

int main(void) {
    signal(SIGINT, cleanup);

    int i;
    for (i = 0; i < NTHREADS; i++) {
        if (pthread_create(&threads[i], NULL, go, (void *)(size_t)i) != 0) {
            perror("THREAD CREATE!!!! (aka Line 27)");
            exit(1);
        }
    }
    for (i = 0; i < NTHREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    pthread_mutex_destroy(&mutex);
    return 0;
}

void *go(void *arg) {
    int id = (int)(size_t)arg;
    printf("Thread %d attempting \n", id);
    pthread_mutex_lock(&mutex);
    //Entering critical section (read this but in a Jurrasic Park voice over voice lol)
    sleep(1);
    printf("Thread %d running in Critical Section........\n", id);
    //Exited critical section
    pthread_mutex_unlock(&mutex);
    return NULL;
}

void cleanup(int sigtype) {
    (void)sigtype;
    pthread_mutex_destroy(&mutex);
    printf("\nFinished\n");
    exit(0);
}
