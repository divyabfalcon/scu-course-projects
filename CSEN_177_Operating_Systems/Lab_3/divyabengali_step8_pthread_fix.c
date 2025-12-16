// Name: Divya Bengali
// Date: October 8th, 2025
// Title: Lab2 – Step 8 - This lab fixes the error from step 7.
// Description: This program prints out the pthread and thread number along with it's iteration number.
// Note for myself: Demo'd. Fix "hello" part to make it a copy - Done!

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#ifndef NTHREADS
#define NTHREADS 10
#endif

static void* worker(void *arg) {
    int val = *(int *)arg;
#ifdef HEAP_MODE
    //Free heap!!
    free(arg);               
#endif
    printf("Hello from thread %d with (pthread_t=%lu)\n", val, (unsigned long)pthread_self());
    return NULL;
}

int main(void) {
    pthread_t th[NTHREADS];

#ifndef HEAP_MODE
    for (int i = 0; i < NTHREADS; i++) { 
        int *p = (int *)malloc(sizeof(int)); 
        if (!p){ 
            perror("malloc"); 
            return 1; 
        } 
        *p = i; 
        if(pthread_create(&th[i], NULL, worker, p) != 0){ 
            perror("pthread_create"); 
            return 1; } 
        }
#endif

    for (int i = 0; i < NTHREADS; i++) {
        pthread_join(th[i], NULL);
    }
    return 0;
}
