//Name: Divya Bengali
//Date: Oct 22nd, 2025
//Title: Lab5 – Step 3 - utilizes the given pseduocode from lab document 
//Description: This program "illustrate[s] producer and consumer threads coordinating to access the shared buffer using semaphores"

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <signal.h>
#include <errno.h>
#include <string.h>
#include <time.h>

#include <semaphore.h>
#include <fcntl.h>      

#define BUF_SIZE 5      
#define N_PROD   2
#define N_CONS   2
#define PER_THREAD_ITEMS 20

typedef struct {
    int data[BUF_SIZE];
    int in;
    int out;
} buffer_t;

static buffer_t buf = { .in = 0, .out = 0 };

#ifdef __APPLE__
static sem_t *sem_empty = NULL, *sem_full = NULL, *sem_mutex = NULL;
static const char *SEM_EMPTY_NAME = "/lab5_empty";
static const char *SEM_FULL_NAME  = "/lab5_full";
static const char *SEM_MUTEX_NAME = "/lab5_mutex";

static int sem_setup() {
    //Makes sure everything is "unleaked" and clean (I think that's the right word...I hope idk)
    sem_unlink(SEM_EMPTY_NAME);
    sem_unlink(SEM_FULL_NAME);
    sem_unlink(SEM_MUTEX_NAME);

    sem_empty = sem_open(SEM_EMPTY_NAME, O_CREAT, 0644, BUF_SIZE);
    sem_full  = sem_open(SEM_FULL_NAME,  O_CREAT, 0644, 0);
    sem_mutex = sem_open(SEM_MUTEX_NAME, O_CREAT, 0644, 1);
    if (sem_empty == SEM_FAILED || sem_full == SEM_FAILED || sem_mutex == SEM_FAILED) {
        perror("THE SEMAPHORE IS OPEN!");
        return -1;
    }
    return 0;
}
static void sem_cleanup(int signo) {
    (void)signo;
    sem_unlink(SEM_EMPTY_NAME);
    sem_unlink(SEM_FULL_NAME);
    sem_unlink(SEM_MUTEX_NAME);
    fprintf(stderr, "\nFinished with clean up...yay!\n");
    exit(0);
}
#define SEM_WAIT(x)  sem_wait(x)
#define SEM_POST(x)  sem_post(x)
#else
static sem_t sem_empty, sem_full, sem_mutex;
static int sem_setup() {
    if (sem_init(&sem_empty, 0, BUF_SIZE) != 0){
        return -1;
    }
    if (sem_init(&sem_full,  0, 0) != 0){
        return -1;
    }
    if (sem_init(&sem_mutex, 0, 1)!= 0){
        return -1;
    }
    return 0;
}
static void sem_cleanup(int signo) {
    (void)signo;
    sem_destroy(&sem_empty);
    sem_destroy(&sem_full);
    sem_destroy(&sem_mutex);
    fprintf(stderr, "\nFinished with clean up...yay!\n");
    exit(0);
}
#define SEM_WAIT(x)  sem_wait(&(x))
#define SEM_POST(x)  sem_post(&(x))
#endif

void *producer(void *arg) {
    int id = (int)(size_t)arg;
    for (int i = 0; i < PER_THREAD_ITEMS; i++) {
        int item = id * 1000 + i; 
        usleep(1000 * (rand() % 10));

#ifdef __APPLE__
        SEM_WAIT(sem_empty);
        SEM_WAIT(sem_mutex);
#else
        SEM_WAIT(sem_empty);
        SEM_WAIT(sem_mutex);
#endif

        //This adds the item to the buffer
        buf.data[buf.in] = item;
        buf.in = (buf.in + 1) % BUF_SIZE;
        printf("[P%d] produced %d (in=%d)\n", id, item, buf.in);

#ifdef __APPLE__
        SEM_POST(sem_mutex);
        SEM_POST(sem_full);
#else
        SEM_POST(sem_mutex);
        SEM_POST(sem_full);
#endif
    }
    return NULL;
}

void *consumer(void *arg) {
    int id = (int)(size_t)arg;
    for (int i = 0; i < PER_THREAD_ITEMS; i++) {
#ifdef __APPLE__
        SEM_WAIT(sem_full);
        SEM_WAIT(sem_mutex);
#else
        SEM_WAIT(sem_full);
        SEM_WAIT(sem_mutex);
#endif

        //This removes the next item
        int item = buf.data[buf.out];
        buf.out = (buf.out + 1) % BUF_SIZE;
        printf("      [C%d] consumed %d (out=%d)\n", id, item, buf.out);

#ifdef __APPLE__
        SEM_POST(sem_mutex);
        SEM_POST(sem_empty);
#else
        SEM_POST(sem_mutex);
        SEM_POST(sem_empty);
#endif

        // consume (simulate)
        usleep(1000 * (rand() % 15));
    }
    return NULL;
}

int main(void) {
    srand((unsigned)time(NULL));

    signal(SIGINT, sem_cleanup);
    if (sem_setup() != 0) {
        fprintf(stderr, "Failed to set up semaphores...oh no! :( \n");
        return 1;
    }

    pthread_t prod[N_PROD], cons[N_CONS];
    for (int i = 0; i < N_PROD; i++) {
        if (pthread_create(&prod[i], NULL, producer, (void *)(size_t)i) != 0) {
            perror("CHECK LINE 154 FOR PTHREAD CREATE ERROR!!!");
            exit(1);
        }
    }
    for (int i = 0; i < N_CONS; i++) {
        if (pthread_create(&cons[i], NULL, consumer, (void *)(size_t)i) != 0) {
            perror("CHECK LINE 160 FOR PTHREAD CREATE ERROR!!!");
            exit(1);
        }
    }

    for (int i = 0; i < N_PROD; i++){
        pthread_join(prod[i], NULL);
    }
    for (int i = 0; i < N_CONS; i++){
        pthread_join(cons[i], NULL);
    }

    sem_cleanup(0);
    return 0;
}
