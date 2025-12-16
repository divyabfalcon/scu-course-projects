//Name: Divya Bengali
//Date: Oct 15th, 2025
//Title: Lab4 – Step 5 - "a program that implements matrix multiplication in a multi-threaded environment" that's been modified from step4.c
//Description: This program "create[s] N*L threads, each computing the value of the ith row multiplied by the jth column""

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>     
#include <pthread.h>
#include <time.h>

typedef struct { int i, j; } Task;

static int N_, M_, L_;
static double **A, **B, **C;
static pthread_t *threads;
static Task *tasks;

//NOTE: Most of the comments are pretty much the same as step4.c, so I didn't repeat them here other than the ones that are needed
static double **initializeMatrix(int r, int c) {
    double **m = (double **)malloc((size_t)r * sizeof(*m));
    if (!m){ 
        perror("rows1!"); 
        exit(1); 
    }
    for (int i = 0; i < r; ++i) {
        m[i] = (double *)malloc((size_t)c * sizeof(*m[i]));
        if (!m[i]){ 
            perror("rows2!"); 
            exit(1); 
        }
    }
    for (int i = 0; i < r; ++i){
        for (int j = 0; j < c; ++j){
            m[i][j] = (double)rand() / (double)RAND_MAX;
        }
    }
    return m;
}

static void zeroMatrix(int r, int c, double **m) {
    for (int i = 0; i < r; ++i){
        for (int j = 0; j < c; ++j){
            m[i][j] = 0.0;
        }
    }
}

#ifdef PRINT_RESULT
static void printMatrix(int r, int c, double **m) {
    for (int i = 0; i < r; ++i) {
        for (int j = 0; j < c; ++j) {
            printf("%8.4f%s", m[i][j], (j + 1 == c ? "" : " "));
        }
        printf("\n");
    }
}
#endif

//Thread starts by computing a single cell
static void *multiplyCell(void *arg) {
    Task *t = (Task*)arg;
    int i = t->i, j = t->j;
    //Dot product:
    double sum = 0.0;
    for (int k = 0; k < M_; ++k){
        sum += A[i][k] * B[k][j];
    }
    //Writes result to C:
    C[i][j] = sum;
    return NULL;
}

static void freeMatrix(int r, double **m) {
    if (!m) return;
    for (int i = 0; i < r; ++i){
        free(m[i]);
    }
    free(m);
}

int main(int argc, char *argv[]) {
    if (argc < 4) {
        fprintf(stderr, "Usage: %s N M L\n", argv[0]);
        return 2;
    }
    N_ = atoi(argv[1]);
    M_ = atoi(argv[2]);
    L_ = atoi(argv[3]);
    if (N_ <= 0 || M_ <= 0 || L_ <= 0) {
        fprintf(stderr, "Hi! Please use positive integers. Thanks!\n");
        return 2;
    }

    srand((unsigned)time(NULL));
    A = initializeMatrix(N_, M_);
    B = initializeMatrix(M_, L_);
    C = initializeMatrix(N_, L_);
    zeroMatrix(N_, L_, C);

    //Prepare threads and tasks since each task has it's own cell
    size_t total = (size_t)N_ * (size_t)L_;
    threads = (pthread_t*)malloc(total * sizeof(*threads));
    tasks   = (Task*)malloc(total * sizeof(*tasks));
    if (!threads || !tasks){
        perror("threads or tasks, figure it out Divya"); 
        return 1; 
    }

    //Creates threads for each cell
    size_t index = 0;
    for (int i = 0; i < N_; ++i) {
        for (int j = 0; j < L_; ++j) {
            tasks[index].i = i; tasks[index].j = j;
            int rc = pthread_create(&threads[index], NULL, multiplyCell, &tasks[index]);
            if (rc != 0) {
                fprintf(stderr, "pthread_create failed: (%d,%d)\n", i, j);
                return 1;
            }
            ++index;
        }
    }
    //Joins the threads
    for (size_t t = 0; t < total; ++t){
        pthread_join(threads[t], NULL);
    }

#ifdef PRINT_RESULT
    if ((long)N_ * (long)L_ <= 100){
        printMatrix(N_, L_, C); 
    }
    else {
        double sum = 0.0;
        for(int i = 0; i < N_; ++i) for (int j = 0; j < L_; ++j){
            sum += C[i][j];
        }
        printf("sum(C)=%.6f (C is %d x %d)\n", sum, N_, L_);
    }
#endif

    free(threads);
    free(tasks);
    freeMatrix(N_, A);
    freeMatrix(M_, B);
    freeMatrix(N_, C);
    return 0;
}
