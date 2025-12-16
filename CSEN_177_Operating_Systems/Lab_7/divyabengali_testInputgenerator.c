//Name: Divya Bengali
//Date: November 21st, 2025 
//Title: Lab7 – Step 1
//Description: This program generates a "testInput.txt" file.


#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char *argv[]) {
    FILE *fp;
    
    //It might be better to make this an actual number instead, but I'm gonna keep it as the lab format had it :)
    char buffer [sizeof(int)];
    int i;

    if(argc < 3){
        fprintf(stderr, "Usage is: %s <numRequests> <maxPageNumber>\n", argv[0]);
        return 1;
    }

    //Convert to integers
    int numRequests = atoi(argv[1]);
    int maxPageNumber = atoi(argv[2]);

    //Just making sure it's positive
    if(numRequests <= 0 || maxPageNumber <= 0){
        fprintf(stderr, "ERROR!!! Both numRequests and maxPageNumber need to be greater than 0. Atm, at least one of them is less than 0...thank you.\n");
        return 1;
    }

    //NOTE: If you want to make it repeatable, we can do srand(), however, the lab doesn't ask for that so I'm not doing it. Srand could have any number as an input and it would still be repeatable (which is kind of crazy lol)
    fp = fopen("testInput.txt", "w");
    if(!fp){
        perror("Error on opening file!! Need to check");
        return 1;
    }
    for (i=0; i<numRequests; i++){
        sprintf(buffer, "%d\n", rand()%maxPageNumber);
        fputs(buffer, fp);
    }
    fclose(fp);
    return 0;
}