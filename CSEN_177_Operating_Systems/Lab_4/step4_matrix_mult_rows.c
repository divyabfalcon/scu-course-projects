//Name: Divya Bengali
//Date: Oct 15th, 2025
//Title: Lab4 – Step 4 - "a program that implements matrix multiplication in a multi-threaded environment"
//Description: This program computes matrix multiplication using pthreads.



#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>     
#include <pthread.h>
#include <time.h>

static int N_, M_, L_;
static double **A, **B, **C;
//p_thread for each row:
static pthread_t *threads; 

//Allocates a matrix and fills it with random values between 0 and 1
static double **initializeMatrix(int r, int c) {  
    double **m = (double **)malloc((size_t)r * sizeof(*m));
    if (!m){ 
        perror("Rows1!"); exit(1); 
    }
    //Allocate rows
    for (int i = 0; i < r; ++i) {
        m[i] = (double *)malloc((size_t)c * sizeof(*m[i]));
        if (!m[i]){ 
            perror("Rows2!"); 
            exit(1); 
        }
    }
    //Add in the rand values (yay!)
    for (int i = 0; i < r; ++i)
        for (int j = 0; j < c; ++j)
            m[i][j] = (double)rand() / (double)RAND_MAX;
    return m;
}

//This function sets all values in the matrix to 0.0
static void zeroMatrix(int r, int c, double **m) {
    for (int i = 0; i < r; ++i)
        for (int j = 0; j < c; ++j)
            m[i][j] = 0.0;
}

//This prints the matrix!
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

//This computes the multiplication of rows!
static void *multiplyRow(void *arg) {
    size_t i = (size_t)(uintptr_t)arg; 
    for (int j = 0; j < L_; ++j) {
        double sum = 0.0;
        for (int k = 0; k < M_; ++k) {
            sum += A[i][k] * B[k][j];
        }
        C[i][j] = sum;
    }
    return NULL;
}

//Free allocated matrix from memory (much needed! :) )
static void freeMatrix(int r, double **m) {
    if (!m){ 
        return;
    }
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

    //Creats thread per row
    threads = (pthread_t*)malloc((size_t)N_ * sizeof(*threads));
    if (!threads){ 
        perror("threads :(   "); 
        return 1; 
    }

    //3, 2, 1, launch time!! I launch the threads here (I like space, I know haha)
    for (size_t i = 0; i < (size_t)N_; ++i) {
        int rc = pthread_create(&threads[i], NULL, multiplyRow, (void*)(uintptr_t)i);
        if (rc != 0){ 
            fprintf(stderr, "Oh no!   pthread_create failed for row %zu\n", i); 
            return 1; 
        }
    }
    
    //Waits for rows to finish
    for (size_t i = 0; i < (size_t)N_; ++i){
        pthread_join(threads[i], NULL);
    }

//This is how we print the result when the cell is greater than 100 so it's not TOO messy 
#ifdef PRINT_RESULT
    if ((long)N_ * (long)L_ <= 100) { printMatrix(N_, L_, C); }
    else {
        double sum = 0.0;
        for (int i = 0; i < N_; ++i) for (int j = 0; j < L_; ++j) sum += C[i][j];
        printf("sum(C)=%.6f (C is %d x %d)\n", sum, N_, L_);
    }
#endif

    free(threads);
    freeMatrix(N_, A);
    freeMatrix(M_, B);
    freeMatrix(N_, C);
    return 0;
}
