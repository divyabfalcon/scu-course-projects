//Name: Divya Bengali
//Date: 10/1/25
//Title: Lab2 – Step 7 - Rewrite of 1.c to have the parent process wait till child is done to exit
//Description: This program does the same as step 1 but uses the ls command.


#include <stdio.h> 
#include <sys/types.h> 
#include <unistd.h> 
#include <stdlib.h> 
#include <errno.h> 
#include <sys/wait.h> 

int main(void){
    pid_t pid = fork();
    if(pid < 0){
        perror("Fork failed");
        return 1;
    }
    //NOTE: I forgot that the instructions gave code snippet so I wrote my own but it does the same thing and is very similar
    if(pid == 0){
        execlp("ls", "ls", (char *)NULL);
        perror("execlp");
        exit(1);
    }
    wait(NULL);
    printf("Child has completed the task!\n");
    return 0;
}