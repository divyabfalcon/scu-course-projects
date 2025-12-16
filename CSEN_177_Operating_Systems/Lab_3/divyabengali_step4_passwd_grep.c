// Name: Divya Bengali
// Date: October 8th, 2025
// Title: Lab2 – Step 4 - This lab implements cat /etc/passwd | grep root.
// Description: This program uses cat /etc/passwd | grep root. to print out current user/operator information.
// Note for myself: Demo'd


#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <errno.h>

int main(void) {
    int fds[2];
    if (pipe(fds) == -1){ 
        perror("pipe"); 
        return 1; 
    }

    //The left:
    pid_t pid_left = fork(); 
    if (pid_left < 0){ 
        perror("fork left"); 
        return 1; 
    }

    if (pid_left == 0) {
        if (dup2(fds[1], 1) == -1){ //This was the same one from step 2 or 3 idr but it mentioned to use dup2
            perror("left"); 
            _exit(127); 
        }
        //Closing read and write
        close(fds[0]); 
        close(fds[1]); 
        execlp("cat", "cat", "/etc/passwd", (char *)0);
        perror("execlp cat");
        _exit(127);
    }

    //The right:
    pid_t pid_right = fork(); 
    if (pid_right < 0){ 
        perror("pid_right < 0 right"); //just did that for me to easily refrence code, i know usually it's meant to be more "informative"
        return 1; 
    }

    if (pid_right == 0) {
        if (dup2(fds[0], 0) == -1){
            perror("dup2 right");
            _exit(127); 
        }
        //Close read and write
        close(fds[1]); 
        close(fds[0]); 
        execlp("grep", "grep", "root", (char *)0);
        perror("execlp grep");
        _exit(127);
    }

    // Parent close while waiting for kids so it doesn't become a zombie process
    close(fds[0]);
    close(fds[1]);
    int status;
    while (wait(&status) > 0) {}
    return 0;
}
