//Name: Divya Bengali
//Date: 10/1/25
//Title: Lab2 – Step 2 - Rewrite of 1.c to have delay as a user input
//Description: This program does the same as step 1 but has user input for delay.



#include <stdio.h> 
#include <sys/types.h>
#include <unistd.h> 
#include <stdlib.h> 
#include <errno.h>
#include <sys/wait.h> 

// main function 
int main(int argc, char *argv[]) {
    if(argc != 2) {
        fprintf(stderr, "Usage: %s <microsecond delay>\n", argv[0]);
        return 1;
    }
    pid_t pid;
    int i, n = atoi(argv[1]); // n is a delay in microseconds inserted in parent and child iterations
    printf("\n Before forking.\n");
    pid = fork();
    if (pid < 0) {
        fprintf(stderr, "Error when attempting to fork %d\n", errno);
        exit(0);
    }
    if (pid){
    // Parent process: pid is > 0
        for (i=0;i<10;i++) {
        printf("\t \t \t I am the parent Process displaying iteration %d \n",i);
        usleep(n);
        }
    wait(NULL);
    }
    else{
        // Child process: pid = 0
        for (i=0;i<10;i++) {
            printf("I am the child process displaying iteration %d\n",i);
            usleep(n);
        }
    }
return 0;
}