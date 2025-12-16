//Name: Divya Bengali
//Date: 10/1/25
//Title: Lab2 – Step 6 - Rewrite of 5.c to have 5 processes
//Description: This program does the same as step 5 but has user input for delay for the 5 processes.


#include <stdio.h> 
#include <sys/types.h> 
#include <unistd.h> 
#include <stdlib.h> 
#include <errno.h> 
#include <sys/wait.h> 


int main(int argc, char *argv[]) {
    if(argc != 6) {
        fprintf(stderr, "Usage: %s <d1> <d2> <d3> <d4> <d5> \n", argv[0]);
        return 1;
    }
    int d[5] = {atoi(argv[1]), atoi(argv[2]), atoi(argv[3]), atoi(argv[4]), atoi(argv[5])};

    pid_t pid1 = fork();
    pid_t pid2 = fork();
    pid_t pid3 = -1;
    if(pid1 > 0 && pid2 > 0){
        pid3 = fork();
    }

    int delay;
    if (pid1 > 0 && pid2 > 0 && pid3 > 0) {
        delay = d[0];
    } else if (pid1 > 0 && pid2 > 0 && pid3== 0) {
        delay = d[4];
    } else if (pid1 > 0 && pid2 == 0) {
            delay = d[1];
    } else if (pid1==0 && pid2 > 0 ) {
            delay = d[2];
        
     } else {
        delay = d[3];
    }
    for(int i=0; i<10; i++){
        printf("pid=%d at iteration %d\n", getpid(), i);
        usleep(delay);
    }


    /* CODE USING 4 FORKS INSTEAD OF 3, CHANGED AFTER DEMO AS SUGGESTED
    for(int k=0; k<4; k++){
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
    for(int j=0; j<4; j++){
        wait(NULL);
    }
    */

    //Lab instructions show to use wait to help with ensuring processes go smoothly
    while(wait(NULL) > 0){}
    return 0;
}
   