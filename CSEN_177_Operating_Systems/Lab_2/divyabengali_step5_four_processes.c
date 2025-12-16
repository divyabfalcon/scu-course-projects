//Name: Divya Bengali
//Date: 10/1/25
//Title: Lab2 – Step 5 - Rewrite of 3.c to have 4 processes
//Description: This program does the same as step 3 but has user input for delay for the 4 processes.


#include <stdio.h> 
#include <sys/types.h> 
#include <unistd.h> 
#include <stdlib.h> 
#include <errno.h> 
#include <sys/wait.h> 

/* main function */
int main(int argc, char *argv[]) {
    if(argc != 5) {
        fprintf(stderr, "Usage: %s <d1> <d2> <d3> <d4> \n", argv[0]);
        return 1;
    }
    int d[4] = {atoi(argv[1]), atoi(argv[2]), atoi(argv[3]), atoi(argv[4])};


    pid_t pid1 = fork();
    pid_t pid2 = fork();

    // NOTE: This portion of code comes from lecture notes
    int delay;
    if (pid1 > 0 && pid2 > 0) {
        // Parent 
        delay = d[0];
    } else if (pid1 > 0 && pid2 == 0) {
        // 2nd fork child
        delay = d[1];
    } else if (pid1 == 0 && pid2 > 0) {
        // 1st fork child
        delay = d[2];
    } else {
        // Third child process
        delay = d[3];
    }

    for(int i=0; i<10; i++){
        printf("pid=%d at iteration %d\n", getpid(), i);
        usleep(delay);
    }
/*CODE USING 3 FORKS INSTEAD OF 2, CHANGED AFTER DEMO AS SUGGESTED
    for(int k=0; k<3; k++){
        pid_t pid = fork();
        if (pid < 0) {
            fprintf(stderr, "can't fork, error %d\n", errno);
            exit(0);
        }
        if(pid == 0){
        


            for(int i=0; i<10; i++){
                printf("I am process %d at iteration %d\n", getpid(), i);
                usleep(d[k+1]);
            }
            exit(0);
        }   
    }


    for(int i=0; i<10; i++){
        printf("\t \t \t I am the parent Process displaying iteration %d \n",i);
        usleep(d[0]);
    }


    for(int j=0; j<3; j++){
        wait(NULL);
    }


    */

    //Lab instructions show to use wait to help with ensuring processes go smoothly
    while(wait(NULL) > 0){}
    
    return 0;
}
   