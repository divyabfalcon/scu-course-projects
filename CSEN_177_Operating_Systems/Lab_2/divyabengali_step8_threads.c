//Name: Divya Bengali
//Date: 10/1/25
//Title: Lab2 – Step 8 - Rewrite of 3.c to have 2 threads
//Description: This program does the same as step 3 but has threads instead of processes.



#include <stdio.h> 
#include <sys/types.h> 
#include <unistd.h>
#include <stdlib.h> 
#include <errno.h>
#include <sys/wait.h>
#include <pthread.h> 

void* worker(void* arg) {
    int n = *((int*)arg);
    for (int i = 0; i < 10; i++) {
        printf("Displaying iteration %d\n", i);
        usleep(n);
    }
    return NULL;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <microsecond delay>\n", argv[0]);
        return 1;
    }
    int n = atoi(argv[1]);
    pthread_t t1, t2;
    pthread_create(&t1, NULL, worker, &n);
    pthread_create(&t2, NULL, worker, &n);
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    return 0;
}