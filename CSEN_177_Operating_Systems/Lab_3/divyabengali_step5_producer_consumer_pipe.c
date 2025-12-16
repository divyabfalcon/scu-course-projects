// Name: Divya Bengali
// Date: October 8th, 2025
// Title: Lab2 – Step 5 - This lab implements a producer-consumer message communication using pipes.
// Description: This program takes input and duplicates it. Once it does that once, it will continue to do so as many times until the user exits the program using control d or control c.
// Note for myself: Demo'd


#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <string.h>
#include <errno.h>

static int write_all(int fd, const void *buf, size_t n) {
    const char *p = (const char *)buf;
    size_t left = n;
    while (left > 0) {
        ssize_t m = write(fd, p, left);
        if (m < 0) {
            if (errno == EINTR){ 
                continue; //I know I can do this in one line, I just strongly dislike loops that start and end in the same sentence idk why, sorry lol
            }
            return -1;
        }
        left = left - (size_t)m;
        p = p + m;
    }
    return 0;
}

int main(void) {
    int fds[2];
    if (pipe(fds) == -1){
        perror("pipe");
        return 1;
    }

    pid_t pid = fork();
    if (pid < 0){ 
        perror("fork"); 
        return 1; 
    }

    if (pid == 0) {
        // Child
        close(fds[1]); 
        char buf[4096];
        ssize_t n;
        fprintf(stderr, "Child waiting\n");
        while ((n = read(fds[0], buf, sizeof(buf))) > 0) {
            if (write_all(1, buf, (size_t)n) < 0){ 
                perror("write"); 
                close(fds[0]); 
                _exit(127); 
            }
        }
        if (n < 0){
            perror("read");
        }
        close(fds[0]);
        _exit(0);
    } else {
        // Parent
        close(fds[0]); 
        fprintf(stderr, "Please enter input. Thanks! \n");
        char line[4096];
        while (fgets(line, sizeof(line), stdin)) {
            size_t len = strnlen(line, sizeof(line));
            if (write_all(fds[1], line, len) < 0){ 
                perror("write"); 
                break; 
            }
        }
        close(fds[1]); // signal 
        int status;
        wait(&status);
    }

    return 0;
}
