// Name: Divya Bengali
// Date: October 8th, 2025
// Title: Lab2 – Step 3 - This lab is modified from step 2 so that the writer process can pass the output of "ls" to the upstream.
// Description: This program prints out the file names in the current folder with spacing between each character of each name.
// Note for myself: Need to fix this one and step 7!! - Done




#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>

int main(int argc, char *argv[]){
    int fds[2];
    char buff[60];
    int count, i;

    if (pipe(fds) == -1){ 
        perror("pipe"); 
        return 1; 
    }

    if (fork() == 0){
        // Writer on the upstream end: run `ls`
        close(fds[0]);           
        //According to instructions: "You may use dup2(fds[1],1); forredirection and execlp("ls", "ls", 0); to run the “ls” command"      
        if (dup2(fds[1], 1) == -1){  //dup2 from instructions
            perror("dup2"); 
            _exit(127); 
        }
        close(fds[1]);                 
        execlp("ls", "ls", (char*)0); 
        perror("execlp ls");           
        _exit(127);
    }
    else if (fork() == 0){
        //Code is same from step 2, only above was altered
        printf("\nReader on the downstream end of the pipe \n");
        close(fds[1]);                 
        while ((count = read(fds[0], buff, sizeof(buff))) > 0){
            for (i = 0; i < count; i++){
                write(1, buff + i, 1);
                write(1, " ", 1); //the space is what gives it the space btwn characters
            }
            printf("\n");
        }
        _exit(0);
    }
    else{
        close(fds[0]);
        close(fds[1]);
        wait(0);
        wait(0);
    }
    return 0;
}