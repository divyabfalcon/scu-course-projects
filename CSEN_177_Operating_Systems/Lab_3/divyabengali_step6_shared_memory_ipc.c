// Name: Divya Bengali
// Date: October 8th, 2025
// Title: Lab2 – Step 6 - This lab implements a producer-consumer message communication using shared memory.
// Description: This program takes input and duplicates it. Once it does that once, it will continue to do so as many times until the user exits the program using control d or control c.
// Note for myself: Demo'd


#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <string.h>
#include <errno.h>

#define MSIZ 4096
struct mem{ 
    volatile int ready; 
    char buf[MSIZ]; 
};

int main(void) {
    int sharedmemID = shmget(IPC_PRIVATE, sizeof(struct mem), IPC_CREAT | 0600);
    if (sharedmemID < 0){ 
        perror("sharedmemID"); 
        return 1; 
    }

    struct mem *p = (struct mem *)shmat(sharedmemID, NULL, 0);
    if(p == (void *)-1){ 
        perror("shmat"); 
        shmctl(sharedmemID, IPC_RMID, NULL); 
        return 1; 
    }
    p->ready = 0;
    p->buf[0] = '\0';

    pid_t pid = fork();
    if (pid < 0){ 
        perror("forking...yikes"); 
        shmdt(p); 
        shmctl(sharedmemID, IPC_RMID, NULL); 
        return 1; 
    }

    if (pid == 0) {
        // Child
        fprintf(stderr, "Consumer waiting\n");
        while(!p->ready){ 
            usleep(1000); 
        } 
        printf("%s", p->buf);
        shmdt(p);
        _exit(0);

    } else {
        // Parent
        fprintf(stderr, "Enter a sentence...please: ");
        fflush(stderr);
        char input[MSIZ];
        if (!fgets(input, sizeof(input), stdin)) {
            perror("fgets");
            shmdt(p);
            shmctl(sharedmemID, IPC_RMID, NULL);
            int status; wait(&status);
            return 1;
        }
        // copy and paste as output
        strncpy((char *)p->buf, input, MSIZ - 1);
        p->buf[MSIZ - 1] = '\0';
        __sync_synchronize(); 
        p->ready = 1;

        int status;
        wait(&status);
        shmdt(p);
        shmctl(sharedmemID, IPC_RMID, NULL); 
    }

    return 0;
}
