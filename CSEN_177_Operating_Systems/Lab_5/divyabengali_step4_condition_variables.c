//Name: Divya Bengali
//Date: Oct 22nd, 2025
//Title: Lab5 – Step 4 - utilizes the given pseduocode from lab document 
//Description: This program "illustrate[s] the use of condition variables for coordinating the access of the producer and consumer threads to the shared buffer"

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <signal.h>
#include <time.h>

#define BUF_SIZE 5
#define N_PROD   2
#define N_CONS   2
#define PER_THREAD_ITEMS 20

typedef struct {
    int data[BUF_SIZE];
    int in;
    int out;
    int count;
    pthread_mutex_t mtx;
    pthread_cond_t not_full;
    pthread_cond_t not_empty;
} buffer_t;

static buffer_t buf = {
    .in = 0, .out = 0, .count = 0,
    .mtx = PTHREAD_MUTEX_INITIALIZER,
    .not_full = PTHREAD_COND_INITIALIZER,
    .not_empty = PTHREAD_COND_INITIALIZER
};

void *producer(void *arg) {
    int id = (int)(size_t)arg;
    for (int i = 0; i < PER_THREAD_ITEMS; i++) {
        int item = id * 1000 + i; 
        usleep(1000 * (rand() % 10));

        pthread_mutex_lock(&buf.mtx);
        while (buf.count == BUF_SIZE) {
            //If the buffer is full it'll wait for the consumer
            pthread_cond_wait(&buf.not_full, &buf.mtx);
        }
        //This adds to buffer
        buf.data[buf.in] = item;
        buf.in = (buf.in + 1) % BUF_SIZE;
        buf.count++;
        printf("[P%d] produced %d (count=%d)\n", id, item, buf.count);
        pthread_cond_signal(&buf.not_empty);
        pthread_mutex_unlock(&buf.mtx);
    }
    return NULL;
}

void *consumer(void *arg) {
    int id = (int)(size_t)arg;
    for (int i = 0; i < PER_THREAD_ITEMS; i++) {
        pthread_mutex_lock(&buf.mtx);
        while (buf.count == 0) {
            //If the buffer is full it'll wait for the producer (3, 2, 1, action!)
            pthread_cond_wait(&buf.not_empty, &buf.mtx);
        }
        //This removes from the buffer
        int item = buf.data[buf.out];
        buf.out = (buf.out + 1) % BUF_SIZE;
        buf.count--;
        printf("      [C%d] consumed %d (count=%d)\n", id, item, buf.count);
        pthread_cond_signal(&buf.not_full);
        pthread_mutex_unlock(&buf.mtx);

        usleep(1000 * (rand() % 15));
    }
    return NULL;
}

static void cleanup(int signo) {
    (void)signo;
    pthread_mutex_destroy(&buf.mtx);
    pthread_cond_destroy(&buf.not_full);
    pthread_cond_destroy(&buf.not_empty);
    fprintf(stderr, "\nFinished clean up.,.yay!!!\n");
    exit(0);
}

int main(void) {
    srand((unsigned)time(NULL));
    signal(SIGINT, cleanup);

    pthread_t prod[N_PROD], cons[N_CONS];
    for (int i = 0; i < N_PROD; i++) {
        if (pthread_create(&prod[i], NULL, producer, (void *)(size_t)i) != 0) {
            perror("WATCH FOR PTHREAD ERROR ON LINE 94!!!");
            exit(1);
        }
    }
    for (int i = 0; i < N_CONS; i++) {
        if (pthread_create(&cons[i], NULL, consumer, (void *)(size_t)i) != 0) {
            perror("WATCH FOR PTHREAD ERROR ON LINE 100!!!");
            exit(1);
        }
    }

    for (int i = 0; i < N_PROD; i++){
        pthread_join(prod[i], NULL);
    }
    for (int i = 0; i < N_CONS; i++){
        pthread_join(cons[i], NULL);
    }

    cleanup(0);
    return 0;
}
