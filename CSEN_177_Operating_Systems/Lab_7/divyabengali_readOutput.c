//Name: Divya Bengali
//Date: November 21st, 2025 
//Title: Lab7 – Step 2
//Description: This program reads the output of the generated text file in the previous step .

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <errno.h>

int main(int argc, char *argv[]){
    if(argc!=2){
        fprintf(stderr, "Usage is... %s \n", argv[0]);
        return 1;
    }

    //Convert to int...again
    int cacheSize = atoi(argv[1]);
    //Needs to not be -, yay!
    if(cacheSize <= 0){
        fprintf(stderr, "ERROR!!! Cache size must be greater than 0. Atm, it is %d\n", cacheSize);
        return 1;
    }

    //Added a buffer here
    char pageCache[100];

    while(fgets(pageCache, sizeof(pageCache), stdin)){
        //p --> start
        char *p = pageCache;
        while(isspace(*p)){
            p++;
        }
        errno = 0;
        char *end_ptr = NULL;
        long pageNumber = strtol(p, &end_ptr, 10);

        if(p == end_ptr){
            continue;
        }

        printf("Read page number: %ld\n", pageNumber);
    }
    return 0;   
}